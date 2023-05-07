////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <mml/window/video_mode_impl.hpp>
#include <windows.h>
#include <algorithm>


namespace mml
{
namespace priv
{

struct monitor_data
{
    WCHAR adapterName[CCHDEVICENAME] {};
    HMONITOR handle{};
};

BOOL WINAPI callback(HMONITOR handle,
        HDC /*dc*/,
        LPRECT /*rect*/,
        LPARAM data)
{
    MONITORINFOEX mi;
    ZeroMemory(&mi, sizeof(mi));
    mi.cbSize = sizeof(mi);

    if (GetMonitorInfo(handle, (MONITORINFO*) &mi))
    {
        monitor_data* monitor = (monitor_data*) data;
        if (wcscmp(mi.szDevice, monitor->adapterName) == 0)
            monitor->handle = handle;
    }

    return TRUE;
}

int video_mode_impl::get_number_of_displays()
{
    int disp_count{};

    DISPLAY_DEVICE adapter;
    DWORD adapter_index = 0;
    for(;;adapter_index++)
    {
        ZeroMemory(&adapter, sizeof(adapter));
        adapter.cb = sizeof(adapter);

        if (!EnumDisplayDevices(nullptr, adapter_index, &adapter, 0))
            break;

        if (!(adapter.StateFlags & DISPLAY_DEVICE_ACTIVE))
            continue;

        DWORD display_index = 0;
        for(;;display_index++)
        {
            DISPLAY_DEVICE display;
            ZeroMemory(&display, sizeof(display));
            display.cb = sizeof(display);

            if (!EnumDisplayDevices(adapter.DeviceName, display_index, &display, 0))
                break;

            if (!(display.StateFlags & DISPLAY_DEVICE_ACTIVE))
                continue;

            disp_count++;
        }

        // HACK: If an active adapter does not have any display devices
        //       (as sometimes happens), add it directly as a monitor
        if (display_index == 0)
        {
            disp_count++;
        }

    }

    return disp_count;
}

////////////////////////////////////////////////////////////
std::vector<video_mode> video_mode_impl::get_desktop_modes(int index)
{
    std::vector<video_mode> modes;

    int disp_count{};

    DISPLAY_DEVICE adapter;
    DWORD adapter_index = 0;

    for(;;adapter_index++)
    {
        ZeroMemory(&adapter, sizeof(adapter));
        adapter.cb = sizeof(adapter);

        if (!EnumDisplayDevices(nullptr, adapter_index, &adapter, 0))
            break;

        if (!(adapter.StateFlags & DISPLAY_DEVICE_ACTIVE))
            continue;

        DWORD display_index = 0;
        for(;;display_index++)
        {
            DISPLAY_DEVICE display;
            ZeroMemory(&display, sizeof(display));
            display.cb = sizeof(display);

            if (!EnumDisplayDevices(adapter.DeviceName, display_index, &display, 0))
                break;

            if (!(display.StateFlags & DISPLAY_DEVICE_ACTIVE))
                continue;

            if(index == disp_count)
            {
                // Enumerate all available video modes for the primary display adapter
                DEVMODE win32Mode;
                win32Mode.dmSize = sizeof(win32Mode);
                win32Mode.dmDriverExtra = 0;
                for (int count = 0; EnumDisplaySettings(nullptr, count, &win32Mode); ++count)
                {
                    // Convert to mml::video_mode
                    video_mode mode{};
                    mode.width = win32Mode.dmPelsWidth;
                    mode.height = win32Mode.dmPelsHeight;
                    mode.bits_per_pixel = win32Mode.dmBitsPerPel;
                    mode.refresh_rate = win32Mode.dmDisplayFrequency;

                    // Add it only if it is not already in the array
                    if (std::find(modes.begin(), modes.end(), mode) == modes.end())
                        modes.push_back(mode);
                }

                break;
            }

            disp_count++;
        }

        if(!modes.empty())
        {
            break;
        }
    }

    return modes;
}


////////////////////////////////////////////////////////////
video_mode video_mode_impl::get_desktop_mode(int index)
{
    video_mode mode{};

    int disp_count{};

    DISPLAY_DEVICE adapter;
    DWORD adapter_index = 0;

    for(;;adapter_index++)
    {
        ZeroMemory(&adapter, sizeof(adapter));
        adapter.cb = sizeof(adapter);

        if (!EnumDisplayDevices(nullptr, adapter_index, &adapter, 0))
            break;

        if (!(adapter.StateFlags & DISPLAY_DEVICE_ACTIVE))
            continue;

        DWORD display_index = 0;
        for(;;display_index++)
        {
            DISPLAY_DEVICE display;
            ZeroMemory(&display, sizeof(display));
            display.cb = sizeof(display);

            if (!EnumDisplayDevices(adapter.DeviceName, display_index, &display, 0))
                break;

            if (!(display.StateFlags & DISPLAY_DEVICE_ACTIVE))
                continue;

            if(index == disp_count)
            {
                DEVMODE win32Mode;
                win32Mode.dmSize = sizeof(win32Mode);
                win32Mode.dmDriverExtra = 0;
                EnumDisplaySettings(adapter.DeviceName, ENUM_CURRENT_SETTINGS, &win32Mode);

                mode.width = win32Mode.dmPelsWidth;
                mode.height = win32Mode.dmPelsHeight;
                mode.bits_per_pixel = win32Mode.dmBitsPerPel;
                mode.refresh_rate = win32Mode.dmDisplayFrequency;

                break;
            }

            disp_count++;
        }

        if(mode.width != 0 && mode.height != 0)
        {
            break;
        }
    }

    return mode;
}

video_bounds video_mode_impl::get_display_bounds(int index)
{
    video_bounds bounds{};

    int disp_count{};

    DISPLAY_DEVICE adapter;
    DWORD adapter_index = 0;

    for(;;adapter_index++)
    {
        ZeroMemory(&adapter, sizeof(adapter));
        adapter.cb = sizeof(adapter);

        if (!EnumDisplayDevices(nullptr, adapter_index, &adapter, 0))
            break;

        if (!(adapter.StateFlags & DISPLAY_DEVICE_ACTIVE))
            continue;

        DWORD display_index = 0;
        for(;;display_index++)
        {
            DISPLAY_DEVICE display;
            ZeroMemory(&display, sizeof(display));
            display.cb = sizeof(display);

            if (!EnumDisplayDevices(adapter.DeviceName, display_index, &display, 0))
                break;

            if (!(display.StateFlags & DISPLAY_DEVICE_ACTIVE))
                continue;

            if(index == disp_count)
            {
                DEVMODE win32Mode;
                win32Mode.dmSize = sizeof(win32Mode);
                win32Mode.dmDriverExtra = 0;
                EnumDisplaySettings(adapter.DeviceName, ENUM_CURRENT_SETTINGS, &win32Mode);

                RECT rect;
                rect.left   = win32Mode.dmPosition.x;
                rect.top    = win32Mode.dmPosition.y;
                rect.right  = win32Mode.dmPosition.x + win32Mode.dmPelsWidth;
                rect.bottom = win32Mode.dmPosition.y + win32Mode.dmPelsHeight;

                monitor_data monitor;

                wcscpy_s(monitor.adapterName, adapter.DeviceName);
                EnumDisplayMonitors(nullptr, &rect, callback, (LPARAM)&monitor);

                MONITORINFO mi{};
                mi.cbSize = { sizeof(mi) };
                GetMonitorInfo(monitor.handle, &mi);

                bounds.x = mi.rcMonitor.left;
                bounds.y = mi.rcMonitor.top;
                bounds.width = mi.rcMonitor.right - mi.rcMonitor.left;
                bounds.height = mi.rcMonitor.bottom - mi.rcMonitor.top;

                break;
            }

            disp_count++;
        }

        if(bounds.width != 0 && bounds.height != 0)
        {
            break;
        }
    }

    return bounds;
}

} // namespace priv

} // namespace mml
