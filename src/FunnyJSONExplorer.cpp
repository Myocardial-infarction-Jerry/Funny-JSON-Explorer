#include "FunnyJSONExplorer.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <utf8proc.h>

#ifdef _WIN32
#include <windows.h>  // Windows API for console functions
#else
#include <sys/ioctl.h> // UNIX-like systems for ioctl
#include <unistd.h>    // UNIX-like systems for STDOUT_FILENO
#endif

int getWindowWidth() {
    int width = 0;

#ifdef _WIN32
    // Windows-specific code
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hStdout, &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    else {
        std::cerr << "Failed to retrieve console buffer info." << std::endl;
        return -1; // Return -1 on error
    }
#else
    // UNIX-like specific code (Linux, macOS)
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        std::cerr << "ioctl error" << std::endl;
        return -1; // Return -1 on error
    }
    width = ws.ws_col;
#endif

    return width;
}

FunnyJSONExplorer::FunnyJSONExplorer(
    const nlohmann::json &data,
    const std::string &style,
    const std::string &icon
) : data(data) {
    if (style == "tree")
        this->style = new JSONStyle_Tree();
    else if (style == "rect")
        this->style = new JSONStyle_Rect();

    if (icon == "null")
        this->icon = new JSONIcon_Null();
    else if (icon == "poker")
        this->icon = new JSONIcon_Poker();
}

FunnyJSONExplorer::~FunnyJSONExplorer() {
    delete style;
    delete icon;
}

std::ostream &operator<<(std::ostream &os, const FunnyJSONExplorer &fje) {
    os << fje.getExplore();
    return os;
}

std::string FunnyJSONExplorer::getExplore() const {
    std::vector<std::string> prev;
    return style->explore(data, 0, prev, icon);
}

std::vector<std::string> FunnyJSONExplorer::getStyleList() {
    return {
        "tree",
        "rect"
    };
}

std::vector<std::string> FunnyJSONExplorer::getIconList() {
    return {
        "null",
        "poker"
    };
}



JSONIcon_Null::JSONIcon_Null() { icon = ""; }
JSONIcon_Poker::JSONIcon_Poker() { icon = "♠️"; }

std::string JSONStyle_Tree::explore(
    const nlohmann::json &cur,
    int depth,
    std::vector<std::string> prev,
    JSONIcon *icon
) const {
    std::string ret = "";
    prev.push_back("│   ");

    for (auto it = cur.begin(); it != cur.end(); ++it) {
        for (int i = 0; i < depth; i++)
            ret += prev[i];

        if (it == --cur.end()) {
            ret += "└── ";
            prev[prev.size() - 1] = "    ";
        }
        else
            ret += "├── ";

        if (it->is_structured()) {
            if (cur.is_object())
                ret += icon->icon + it.key() + "\n";
            else if (cur.is_array())
                ret += icon->icon + "[ARRAY] \n";
            else if (cur.is_null())
                ret += "NULL \n";

            ret += explore(it.value(), depth + 1, prev, icon);
        }
        else {
            if (cur.is_object())
                ret += icon->icon + it.key() + ": ";

            ret += it->dump() + "\n";
        }
    }

    return ret;
}

// 函数来计算 UTF-8 字符串的显示宽度
int calcWidth(const std::string &str) {
    int width = 0;
    utf8proc_int32_t codepoint;
    const utf8proc_uint8_t *utf8 = reinterpret_cast<const utf8proc_uint8_t *>(str.c_str());

    while (*utf8) {
        utf8proc_ssize_t result = utf8proc_iterate(utf8, -1, &codepoint);
        if (result < 1) break;
        utf8 += result;
        width += utf8proc_charwidth(codepoint);
    }
    return width;
}

std::string JSONStyle_Rect::explore(
    const nlohmann::json &cur,
    int depth,
    std::vector<std::string> prev,
    JSONIcon *icon
) const {
    std::string ret = "";
    int width = getWindowWidth();
    prev.push_back("│   ");

    for (auto it = cur.begin(); it != cur.end(); ++it) {
        std::string line = "";

        for (int i = 0; i < depth; i++)
            line += prev[i];

        if (it == cur.begin() && depth == 0)
            line += "┌── ";
        else if (it == --cur.end() && depth == 0)
            line += "└── ";
        else
            line += "├── ";

        if (it->is_structured()) {
            if (cur.is_object())
                line += icon->icon + it.key();
            else if (cur.is_array())
                line += icon->icon + "[ARRAY]";
            else if (cur.is_null())
                line += "NULL";
        }
        else {
            if (cur.is_object())
                line += icon->icon + it.key() + ": ";

            line += it->dump();
        }

        int padding = width - calcWidth(line) - 2;
        for (int i = 0; i < padding; ++i)
            line += "─";

        if (it == cur.begin() && depth == 0)
            line += "┐";
        else if (it == --cur.end() && depth == 0)
            line += "┘";
        else
            line += "┤";

        ret += line + "\n";

        if (it->is_structured())
            ret += explore(it.value(), depth + 1, prev, icon);
    }

    return ret;
}