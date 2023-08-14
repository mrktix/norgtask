#include "Config.h"

Config::Config(filesystem::path config_file) {
    //read stuff from config file
}

filesystem::path Config::norg_workspace() {
    filesystem::path ws = "/home/arleok/wiki/";
    return ws;
}
