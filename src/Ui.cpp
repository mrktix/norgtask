#include "Ui.h"

Ui::Ui(Config* config) {
    this->config = config;
    current_mode = tasks;
    Tasklist* tasklist = new Tasklist(config->option("norg_workspace"));
}

void Ui::draw() {
    switch (current_mode) {
        case tasks:
            draw_tasks();
            break;
        case contexts:
            draw_contexts();
            break;
    }
}

void Ui::draw_tasks() {

}

void Ui::draw_contexts() {

}
