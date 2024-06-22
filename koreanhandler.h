#ifndef KOREANHANDLER_H
#define KOREANHANDLER_H

/* Since other external libraries that handle korean characters were too complicated, I just wrote the whole thing from scratch by myself 

This was a terrible idea. */

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cwchar>
#include <stdexcept>
#include <iomanip>

std::vector<wchar_t> decompose(const std::string& src);
wchar_t compose(const std::vector<wchar_t>& src);

#endif // KOREANHANDLER_H