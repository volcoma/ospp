////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <mml/system/err.hpp>
#include <mml/window/unix/clipboard_impl.hpp>
#include <mml/window/unix/display.hpp>

#include <X11/Xatom.h>

#include <chrono>
#include <vector>

namespace
{
// Filter the events received by windows (only allow those matching a specific window)
Bool checkEvent(::Display*, XEvent* event, XPointer userData)
{
	// Just check if the event matches the window
	return event->xany.window == reinterpret_cast<::Window>(userData);
}
} // namespace

namespace mml
{
namespace priv
{

////////////////////////////////////////////////////////////
std::string clipboard_impl::get_string()
{
	return get_instance().get_string_impl();
}

////////////////////////////////////////////////////////////
void clipboard_impl::set_string(const std::string& text)
{
	get_instance().set_string_impl(text);
}

////////////////////////////////////////////////////////////
void clipboard_impl::process_events()
{
	get_instance().process_events_impl();
}

////////////////////////////////////////////////////////////
clipboard_impl::clipboard_impl()
	: window_(0)
	, request_responded_(false)
{
	// Open a connection with the X server
	display_ = open_display();

	// Get the atoms we need to make use of the clipboard
	clipboard_ = get_atom("CLIPBOARD", false);
	targets_ = get_atom("TARGETS", false);
	text_ = get_atom("TEXT", false);
	utf8_string_ = get_atom("UTF8_STRING", true);
	target_property_ = get_atom("SFML_CLIPBOARD_TARGET_PROPERTY", false);

	// Create a hidden window that will broker our clipboard interactions with X
	window_ = XCreateSimpleWindow(display_, DefaultRootWindow(display_), 0, 0, 1, 1, 0, 0, 0);

	// Register the events we are interested in
	XSelectInput(display_, window_, SelectionNotify | SelectionClear | SelectionRequest);
}

////////////////////////////////////////////////////////////
clipboard_impl::~clipboard_impl()
{
	// Destroy the window
	if(window_)
	{
		XDestroyWindow(display_, window_);
		XFlush(display_);
	}

	// Close the connection with the X server
	close_display(display_);
}

////////////////////////////////////////////////////////////
clipboard_impl& clipboard_impl::get_instance()
{
	static clipboard_impl instance;

	return instance;
}

////////////////////////////////////////////////////////////
std::string clipboard_impl::get_string_impl()
{
	// Check if anybody owns the current selection
	if(XGetSelectionOwner(display_, clipboard_) == None)
	{
		clipboard_contents_.clear();

		return clipboard_contents_;
	}

	// Process any already pending events
	process_events();

	request_responded_ = false;

	// Request the current selection to be converted to UTF-8 (or STRING
	// if UTF-8 is not available) and written to our window property
	XConvertSelection(display_, clipboard_, (utf8_string_ != None) ? utf8_string_ : XA_STRING,
					  target_property_, window_, CurrentTime);

	auto last = std::chrono::steady_clock::now();
	// Wait for a response for up to 1000ms
	while(!request_responded_ &&
		  (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last) <
		   std::chrono::milliseconds(1000)))
		process_events();

	// If no response was received within the time period, clear our clipboard contents
	if(!request_responded_)
		clipboard_contents_.clear();

	return clipboard_contents_;
}

////////////////////////////////////////////////////////////
void clipboard_impl::set_string_impl(const std::string& text)
{
	clipboard_contents_ = text;

	// Set our window as the current owner of the selection
	XSetSelectionOwner(display_, clipboard_, window_, CurrentTime);

	// Check if setting the selection owner was successful
	if(XGetSelectionOwner(display_, clipboard_) != window_)
		err() << "Cannot set clipboard string: Unable to get ownership of X selection" << std::endl;
}

////////////////////////////////////////////////////////////
void clipboard_impl::process_events_impl()
{
	XEvent event;

	// Pick out the events that are interesting for this window
	while(XCheckIfEvent(display_, &event, &checkEvent, reinterpret_cast<XPointer>(window_)))
		events_.push_back(event);

	// Handle the events for this window that we just picked out
	while(!events_.empty())
	{
		event = events_.front();
		events_.pop_front();
		process_event(event);
	}
}

////////////////////////////////////////////////////////////
void clipboard_impl::process_event(XEvent& windowEvent)
{
	switch(windowEvent.type)
	{
		case SelectionClear:
		{
			// We don't have any resources we need to clean up
			// when losing selection ownership so we don't do
			// anything when we receive SelectionClear
			// We will still respond to any future SelectionRequest
			// events since doing so doesn't really do any harm
			break;
		}
		case SelectionNotify:
		{
			// Notification that the current selection owner
			// has responded to our request

			XSelectionEvent& selectionEvent = *reinterpret_cast<XSelectionEvent*>(&windowEvent.xselection);

			clipboard_contents_.clear();

			// If retrieving the selection fails or conversion is unsuccessful
			// we leave the contents of the clipboard empty since we don't
			// own it and we don't know what it could currently be
			if((selectionEvent.property == None) || (selectionEvent.selection != clipboard_))
				break;

			Atom type;
			int format;
			unsigned long items;
			unsigned long remainingBytes;
			unsigned char* data = 0;

			// The selection owner should have wrote the selection
			// data to the specified window property
			int result = XGetWindowProperty(display_, window_, target_property_, 0, 0x7fffffff, False,
											AnyPropertyType, &type, &format, &items, &remainingBytes, &data);

			if(result == Success)
			{
				// We don't support INCR for now
				// It is very unlikely that this will be returned
				// for purely text data transfer anyway
				if(type != get_atom("INCR", false))
				{
					// Only copy the data if the format is what we expect
					if((type == utf8_string_) && (format == 8))
					{
						clipboard_contents_ = std::string(data, data + items);
					}
					else if((type == XA_STRING) && (format == 8))
					{
						clipboard_contents_ = std::string(data, data + items);
					}
				}

				XFree(data);

				// The selection requestor must always delete the property themselves
				XDeleteProperty(display_, window_, target_property_);
			}

			request_responded_ = true;

			break;
		}
		case SelectionRequest:
		{
			// Respond to a request for our clipboard contents
			XSelectionRequestEvent& selectionRequestEvent =
				*reinterpret_cast<XSelectionRequestEvent*>(&windowEvent.xselectionrequest);

			// Our reply
			XSelectionEvent selectionEvent;

			selectionEvent.type = SelectionNotify;
			selectionEvent.requestor = selectionRequestEvent.requestor;
			selectionEvent.selection = selectionRequestEvent.selection;
			selectionEvent.property = selectionRequestEvent.property;
			selectionEvent.time = selectionRequestEvent.time;

			if(selectionRequestEvent.selection == clipboard_)
			{
				if(selectionRequestEvent.target == targets_)
				{
					// Respond to a request for our valid conversion targets
					std::vector<Atom> targets;

					targets.push_back(targets_);
					targets.push_back(text_);
					targets.push_back(XA_STRING);

					if(utf8_string_ != None)
						targets.push_back(utf8_string_);

					XChangeProperty(display_, selectionRequestEvent.requestor, selectionRequestEvent.property,
									XA_ATOM, 32, PropModeReplace,
									reinterpret_cast<unsigned char*>(&targets[0]), targets.size());

					// Notify the requestor that they can read the targets from their window property
					selectionEvent.target = targets_;

					XSendEvent(display_, selectionRequestEvent.requestor, True, NoEventMask,
							   reinterpret_cast<XEvent*>(&selectionEvent));

					break;
				}
				else if((selectionRequestEvent.target == XA_STRING) ||
						((utf8_string_ == None) && (selectionRequestEvent.target == text_)))
				{
					// Respond to a request for conversion to a Latin-1 string
					std::string data = clipboard_contents_;

					XChangeProperty(display_, selectionRequestEvent.requestor, selectionRequestEvent.property,
									XA_STRING, 8, PropModeReplace,
									reinterpret_cast<const unsigned char*>(data.c_str()), data.size());

					// Notify the requestor that they can read the data from their window property
					selectionEvent.target = XA_STRING;

					XSendEvent(display_, selectionRequestEvent.requestor, True, NoEventMask,
							   reinterpret_cast<XEvent*>(&selectionEvent));

					break;
				}
				else if((utf8_string_ != None) && ((selectionRequestEvent.target == utf8_string_) ||
												   (selectionRequestEvent.target == text_)))
				{
					// Respond to a request for conversion to a UTF-8 string
					// or an encoding of our choosing (we always choose UTF-8)
					// std::basic_string<uint8> data = m_clipboardContents.toUtf8();
					std::string data = clipboard_contents_;

					XChangeProperty(display_, selectionRequestEvent.requestor, selectionRequestEvent.property,
									utf8_string_, 8, PropModeReplace,
									reinterpret_cast<const unsigned char*>(data.c_str()), data.size());

					// Notify the requestor that they can read the data from their window property
					selectionEvent.target = utf8_string_;

					XSendEvent(display_, selectionRequestEvent.requestor, True, NoEventMask,
							   reinterpret_cast<XEvent*>(&selectionEvent));

					break;
				}
			}

			// Notify the requestor that we could not respond to their request
			selectionEvent.target = selectionRequestEvent.target;
			selectionEvent.property = None;

			XSendEvent(display_, selectionRequestEvent.requestor, True, NoEventMask,
					   reinterpret_cast<XEvent*>(&selectionEvent));

			break;
		}
		default:
			break;
	}
}

} // namespace priv

} // namespace mml
