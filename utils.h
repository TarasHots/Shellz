#ifndef SHELLZ_UTILS_H
#define SHELLZ_UTILS_H

#include <algorithm>
#include <cctype>

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

static inline std::vector<std::string> split(std::string_view &s, char delimiter = ' ') {
    std::vector<std::string> result;

    std::string tmp_string = {};
    for (size_t i = 0; i <= s.size(); ++i) {
        if (i == s.size() || s.at(i) == delimiter) {
            result.push_back(tmp_string);
            tmp_string = {};
        } else {
            tmp_string += s.at(i);
        }
    }

    return result;
}

#endif //SHELLZ_UTILS_H
