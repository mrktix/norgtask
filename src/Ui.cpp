#include "Ui.h"

Ui::Ui(const Config* config_passed)
:config(config_passed), tasklist(config->path("norg_workspace"))
{
    current_mode = tasks;
}

bool Ui::input() {
    char input = getch();

    if (input == ';') return true;
    else return false;
}

bool Ui::draw(bool collect_input) {
    if (collect_input && input()) return true;

    update_vars();
    draw_outline();
    switch (current_mode) {
        case tasks:
            draw_tasks();
            break;
        case contexts:
            draw_contexts();
            break;
    }
    refresh();
    return false;
}

void Ui::update_vars() {
    maxx = getmaxx(stdscr);
    maxy = getmaxy(stdscr);
    cout << "Ui::update_vars(): maxx: " << maxx << ", maxy: " << maxy << endl;
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
    int task_count = tasklist.current_tasks_sorted.size();
    int end = min(available_lines, task_count);

    cout << "availines:" << available_lines << endl;
    cout << "task_count:" << task_count << endl;
    
    cout << "Ui::draw_tasks(): amount of lines to print: " << end << endl;

    for (int i = 0; i < end; i++) {
        string taskstr = task_format(tasklist.current_tasks_sorted[i]);
        mvprintw(i+1, 1, taskstr.c_str());
    }
}

string Ui::task_format(task t) {
    string ret = t.folder + "/" + t.file + "/" + t.name + " (" + t.tag + ")";
    return ret;
}

void Ui::draw_contexts() {

}
