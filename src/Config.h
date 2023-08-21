#pragma once
#include <filesystem>
#include <boost/algorithm/string/trim.hpp>
#include <fstream>
#include <unordered_map>

#include <iostream>

using namespace std;

class Config {
    public:
        Config(filesystem::path config_path);
        string option(string key);
        string path(string key);
    private:
        unordered_map<string, string> options;
};
