#include <filesystem>

using namespace std;

class Config {
    public:
        Config(filesystem::path config_file);
        filesystem::path norg_workspace();
};
