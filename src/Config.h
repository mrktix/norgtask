#pragma once
#include <filesystem>
#include <boost/algorithm/string/trim.hpp>
#include <fstream>
#include <unordered_map>

#include <iostream>

using namespace std;

class Config {
    public:
        Config(std::filesystem::path config_path);
        string option(string key) const;
        filesystem::path path(string key) const;
    private:
        unordered_map<string, string> options;
};
