#include "Ui.h"

Ui::Ui(Config* config) {
    this->config = config;
    current_mode = tasks;
    endwin();
    tasklist = new Tasklist((filesystem::path) config->path("norg_workspace"));
}

void Ui::draw() {
    draw_outline();
    switch (current_mode) {
        case tasks:
            draw_tasks();
            break;
        case contexts:
            draw_contexts();
            break;
    }
}

void Ui::update_vars() {
    maxx = getmaxx(stdscr);
    maxy = getmaxy(stdscr);
}

void Ui::draw_outline() {
    box(stdscr, 0, 0);
}

void Ui::draw_tasks() {
    cout << "Ui::draw_tasks(): function begin" << endl;
    endwin();
    /* vector<task> tasks_sorted = tasklist->get_current_tasks_sorted(); //segfault */

    int available_lines = maxy-2;
    cout << "Ui::draw_tasks(): about to access tasklist public field" << endl;
    int task_count = tasklist->current_tasks_sorted.size();
    vector<task> test = tasklist->get_current_tasks_sorted();
    cout << "Ui::draw_tasks(): finished accessing tasklist public field, task_count: " << task_count << endl;
    cout << "Ui::draw_tasks(): finished accessing tasklist public field, task_count function: " << test.size() << endl;
    int end = min(available_lines, task_count);

    for (int i = 0; i < end; i++) {
        mvprintw(i+1, 1, (tasklist->current_tasks_sorted)[i].name.c_str());
    }
}

void Ui::draw_contexts() {

}
