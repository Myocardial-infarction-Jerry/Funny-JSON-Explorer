#include "FunnyJSONExplorer.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>

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

