#include "Renderer.h"
#include "Time.h"
#include "Config.h"
#include "Tasklist.h"
#include "Ui.h"

#include <ncurses.h>
#include <memory>

using namespace std;


int Renderer::run(int argc, char** argv) {
    string configpathstr = getenv("XDG_CONFIG_HOME");
    configpathstr += "/norgtask/config";

    filesystem::path configpath = configpathstr;
    unique_ptr<Config> config(new Config(configpath));
    unique_ptr<Ui> ui(new Ui(config.get()));

    ui->draw(false);
    while(true) {
        if (ui->draw(true)) break;
    }

    return 0;
}
