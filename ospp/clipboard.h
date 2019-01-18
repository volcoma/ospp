#pragma once
#include <string>

namespace os
{
namespace clipboard
{

std::string get_text() noexcept;
void set_text(const std::string& text);

}
}
