#ifndef FJEICON_HPP
#define FJEICON_HPP

#include <string>

/**
 * @brief Class representing an icon for JSON elements.
 */
class JSONIcon {
public:
    std::string icon;
};

/**
 * @brief Null icon for JSON elements.
 */
class JSONIcon_Null : public JSONIcon {
public:
    JSONIcon_Null();
};

/**
 * @brief Poker icon for JSON elements.
 */
class JSONIcon_Poker : public JSONIcon {
public:
    JSONIcon_Poker();
};

#endif