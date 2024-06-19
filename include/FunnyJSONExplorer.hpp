#ifndef FJE_HPP
#define FJE_HPP

#include "FunnyJSONIcon.hpp"
#include "FunnyJSONStyle.hpp"

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

#endif
