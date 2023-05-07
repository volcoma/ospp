#include "cursor.h"

namespace os
{
    cursor::cursor(cursor::type system_type)
    {
    }

    cursor::cursor(const image& img, const point& hotspot)
    {
    }

    auto cursor::get_impl() const noexcept -> void*
    {
        return impl_.get();
    }

    std::map<cursor::type, cursor>& system_cursors()
    {
        static std::map<cursor::type, cursor> cursors
        {
            {cursor::type::unknown, cursor(cursor::type::arrow)},
            {cursor::type::arrow, cursor(cursor::type::arrow)},
            {cursor::type::arrow_wait, cursor(cursor::type::arrow_wait)},
            {cursor::type::wait, cursor(cursor::type::wait)},
            {cursor::type::ibeam, cursor(cursor::type::ibeam)},
            {cursor::type::crosshair, cursor(cursor::type::crosshair)},
            {cursor::type::size_nwse, cursor(cursor::type::size_nwse)},
            {cursor::type::size_nesw, cursor(cursor::type::size_nesw)},
            {cursor::type::size_we, cursor(cursor::type::size_we)},
            {cursor::type::size_ns, cursor(cursor::type::size_ns)},
            {cursor::type::size_all, cursor(cursor::type::size_all)},
            {cursor::type::not_allowed, cursor(cursor::type::not_allowed)},
            {cursor::type::hand, cursor(cursor::type::hand)}
        };
        return cursors;
    }

    const cursor& get_system_cursor(cursor::type type)
    {
        auto& sys_cursors = system_cursors();
        auto it = sys_cursors.find(type);
        if(it == std::end(sys_cursors))
        {
            return sys_cursors.at(cursor::type::unknown);
        }

        return it->second;
    }

}
