#include <fstream>
#include <iostream>
#include <argparse/argparse.hpp>
#include <nlohmann/json.hpp>

#include "FunnyJSONExplorer.hpp"

using ArgumentParser = argparse::ArgumentParser;
using json = nlohmann::json;

int main(int argc, char const *argv[]) {
    ArgumentParser parser("Funny JSON Explorer");

    parser.add_argument("-f", "--file")
        .metavar("<json file>")
        .help("JSON file to explore")
        .required();

    auto styleParser = parser.add_argument("-s", "--style")
        .metavar("<style>")
        .help("Style of the output")
        .default_value("tree");

    for (auto &style : FunnyJSONExplorer::getStyleList())
        styleParser.choices(style);

    auto iconParser = parser.add_argument("-i", "--icon")
        .metavar("<icon family>")
        .help("Icon of the output")
        .default_value("null");

    for (auto &icon : FunnyJSONExplorer::getIconList())
        iconParser.choices(icon);

    try {
        parser.parse_args(argc, argv);
    }
    catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    std::string file = parser.get<std::string>("--file");
    std::string style = parser.get<std::string>("--style");
    std::string icon = parser.get<std::string>("--icon");

    std::ifstream ifs(file);
    json data = json::parse(ifs);

    FunnyJSONExplorer explorer(data, style, icon);

    std::cout << explorer << std::endl;

    return 0;
}
