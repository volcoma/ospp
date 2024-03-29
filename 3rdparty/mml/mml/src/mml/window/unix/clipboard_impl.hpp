#ifndef MML_CLIPBOARD_IMPL_HPP
#define MML_CLIPBOARD_IMPL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <X11/Xlib.h>

#include <deque>
#include <string>

namespace mml
{
namespace priv
{

////////////////////////////////////////////////////////////
/// \brief Give access to the system clipboard
///
////////////////////////////////////////////////////////////
class clipboard_impl
{
public:
	////////////////////////////////////////////////////////////
	/// \brief Get the content of the clipboard as string data
	///
	/// This function returns the content of the clipboard
	/// as a string. If the clipboard does not contain string
	/// it returns an empty string object.
	///
	/// \return Current content of the clipboard
	///
	////////////////////////////////////////////////////////////
	static std::string get_string();

	////////////////////////////////////////////////////////////
	/// \brief Set the content of the clipboard as string data
	///
	/// This function sets the content of the clipboard as a
	/// string.
	///
	/// \param text string object containing the data to be sent
	/// to the clipboard
	///
	////////////////////////////////////////////////////////////
	static void set_string(const std::string& text);

	////////////////////////////////////////////////////////////
	/// \brief Process pending events for the hidden clipboard window
	///
	/// This function has to be called as part of normal window
	/// event processing in order for our application to respond
	/// to selection requests from other applications.
	///
	////////////////////////////////////////////////////////////
	static void process_events();

private:
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	////////////////////////////////////////////////////////////
	clipboard_impl();

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	~clipboard_impl();

	////////////////////////////////////////////////////////////
	/// \brief Get singleton instance
	///
	/// \return Singleton instance
	///
	////////////////////////////////////////////////////////////
	static clipboard_impl& get_instance();

	////////////////////////////////////////////////////////////
	/// \brief getString implementation
	///
	/// \return Current content of the clipboard
	///
	////////////////////////////////////////////////////////////
	std::string get_string_impl();

	////////////////////////////////////////////////////////////
	/// \brief setString implementation
	///
	/// \param text sf::String object containing the data to be sent to the clipboard
	///
	////////////////////////////////////////////////////////////
	void set_string_impl(const std::string& text);

	////////////////////////////////////////////////////////////
	/// \brief processEvents implementation
	///
	////////////////////////////////////////////////////////////
	void process_events_impl();

	////////////////////////////////////////////////////////////
	/// \brief Process an incoming event from the window
	///
	/// \param windowEvent Event which has been received
	///
	////////////////////////////////////////////////////////////
	void process_event(XEvent& windowEvent);

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	::Window window_;				 ///< X identifier defining our window
	::Display* display_;			 ///< Pointer to the display
	Atom clipboard_;				 ///< X Atom identifying the CLIPBOARD selection
	Atom targets_;					 ///< X Atom identifying TARGETS
	Atom text_;						 ///< X Atom identifying TEXT
	Atom utf8_string_;				 ///< X Atom identifying UTF8_STRING
	Atom target_property_;			 ///< X Atom identifying our destination window property
	std::string clipboard_contents_; ///< Our clipboard contents
	std::deque<XEvent> events_;		 ///< Queue we use to store pending events for this window
	bool request_responded_;		 ///< Holds whether our selection request has been responded to or not
};

} // namespace priv

} // namespace mml

#endif // MML_CLIPBOARD_IMPL_HPP
