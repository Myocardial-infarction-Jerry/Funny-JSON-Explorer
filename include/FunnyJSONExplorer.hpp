#ifndef FJE_HPP
#define FJE_HPP

#include <nlohmann/json.hpp>

class JSONIcon;

class JSONStyle {
public:
    virtual std::string explore(
        const nlohmann::json &cur,
        int depth,
        std::vector<std::string> prev,
        JSONIcon *icon
    ) const = 0;
};

class JSONIcon {
public:
    std::string icon;
};

class FunnyJSONExplorer {
public:
    FunnyJSONExplorer(
        const nlohmann::json &data,
        const std::string &style,
        const std::string &icon
    );
    ~FunnyJSONExplorer();

    std::string getExplore() const;
    friend std::ostream &operator<<(std::ostream &os, const FunnyJSONExplorer &fje);

    static std::vector<std::string> getStyleList();
    static std::vector<std::string> getIconList();

private:
    const nlohmann::json &data;
    JSONStyle *style;
    JSONIcon *icon;
};

class JSONStyle_Tree : public JSONStyle {
    std::string explore(
        const nlohmann::json &cur,
        int depth,
        std::vector<std::string> prev,
        JSONIcon *icon
    ) const;
};

class JSONStyle_Rect : public JSONStyle {
    std::string explore(
        const nlohmann::json &cur,
        int depth,
        std::vector<std::string> prev,
        JSONIcon *icon
    ) const;
};

class JSONIcon_Null : public JSONIcon {
public:
    JSONIcon_Null();
};

class JSONIcon_Poker : public JSONIcon {
public:
    JSONIcon_Poker();
};

#endif