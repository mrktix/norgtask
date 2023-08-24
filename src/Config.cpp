#include "Config.h"

Config::Config(filesystem::path config_path) {
    ifstream file;
    file.open(config_path);
    if (!file.is_open()) throw runtime_error("unable to open config file: " + config_path.string());

    string error;
    int linenum;
    while (file) {
        linenum++;
        error = config_path.string()+" @ line "+to_string(linenum)+", ";
        
        string line;
        getline(file, line);
        boost::algorithm::trim(line);
        if (line == "") continue;

        size_t field_value_sep = line.find("=");
        if (field_value_sep == -1) {
            error += "failed to parse: '"+line+"'";
            throw runtime_error(error);
        }

        string field = line.substr(0, field_value_sep);
        string value = line.substr(field_value_sep+1);
        boost::algorithm::trim(field);
        boost::algorithm::trim(value);

        options[field] = value;
    }

    file.close();
}

string Config::option(string key) const {
    return options.find(key)->second;
}

filesystem::path Config::path(string key) const {
    string ret = options.find(key)->second;
    if (ret[0] == '~') {
        ret = getenv("HOME") + ret.substr(1);
    }
    return (filesystem::path) ret;
}
