#ifndef FJESTYLE_HPP
#define FJESTYLE_HPP

#include "FunnyJSONIcon.hpp"

#include <nlohmann/json.hpp>

/**
 * @brief Abstract base class for JSON styles.
 */
class JSONStyle {
public:
    /**
     * @brief Explore the JSON data and return a formatted string representation.
     *
     * @param cur Current JSON object being explored.
     * @param depth Current depth in the JSON structure.
     * @param prev Previous keys visited.
     * @param icon Icon used for representation.
     * @return std::string Formatted string representation of JSON.
     */
    virtual std::string explore(
        const nlohmann::json &cur,
        int depth,
        std::vector<std::string> prev,
        JSONIcon *icon
    ) const = 0;
};

/**
 * @brief JSON style using tree structure.
 */
class JSONStyle_Tree : public JSONStyle {
    std::string explore(
        const nlohmann::json &cur,
        int depth,
        std::vector<std::string> prev,
        JSONIcon *icon
    ) const;
};

/**
 * @brief JSON style using rectangular structure.
 */
class JSONStyle_Rect : public JSONStyle {
    std::string explore(
        const nlohmann::json &cur,
        int depth,
        std::vector<std::string> prev,
        JSONIcon *icon
    ) const;
};

#endif