#ifndef FJE_HPP
#define FJE_HPP

#include <nlohmann/json.hpp>

/**
 * @brief Class representing an icon for JSON elements.
 */
class JSONIcon;

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
 * @brief Class representing an icon for JSON elements.
 */
class JSONIcon {
public:
    std::string icon;
};

/**
 * @brief Main class for exploring JSON data.
 */
class FunnyJSONExplorer {
public:
    /**
     * @brief Construct a new FunnyJSONExplorer object.
     * 
     * @param data JSON data to be explored.
     * @param style Style to be used for exploring JSON.
     * @param icon Icon to be used for JSON elements.
     */
    FunnyJSONExplorer(
        const nlohmann::json &data,
        const std::string &style,
        const std::string &icon
    );

    /**
     * @brief Destroy the FunnyJSONExplorer object.
     */
    ~FunnyJSONExplorer();

    /**
     * @brief Get the exploration result as a string.
     * 
     * @return std::string Formatted string representation of JSON exploration.
     */
    std::string getExplore() const;

    /**
     * @brief Output operator for FunnyJSONExplorer.
     * 
     * @param os Output stream.
     * @param fje FunnyJSONExplorer object.
     * @return std::ostream& Reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const FunnyJSONExplorer &fje);

    /**
     * @brief Get the list of available styles.
     * 
     * @return std::vector<std::string> List of style names.
     */
    static std::vector<std::string> getStyleList();

    /**
     * @brief Get the list of available icons.
     * 
     * @return std::vector<std::string> List of icon names.
     */
    static std::vector<std::string> getIconList();

private:
    const nlohmann::json &data;
    JSONStyle *style;
    JSONIcon *icon;
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
