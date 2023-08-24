#include "Ui.h"

Ui::Ui(const Config* config_passed)
:config(config_passed), tasklist(config_passed)
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
}

void Ui::draw_outline() {
    box(stdscr, 0, 0);
}

void Ui::draw_tasks() {
    int available_lines = maxy-2;
    int task_count = tasklist.current_tasks_sorted.size();
    int end = min(available_lines, task_count);

    for (int i = 0; i < end; i++) {
        move(i+1, 1);
        print_task(tasklist.current_tasks_sorted[i]);
    }
}

void Ui::print_task(task t) {
    int folder_col = t.folder_color%7+1;
    int file_col = t.file_color%7+1;
    string folder = t.folder.substr((t.folder[0] == '.')? 1 : 0, 3);
    string file = t.file.substr((t.file[0] == '.')? 1 : 0, 3);

    attron(COLOR_PAIR(folder_col));
    printw((folder + "/").c_str());
    attroff(COLOR_PAIR(folder_col));

    attron(COLOR_PAIR(file_col));
    printw((file + "/").c_str());
    attroff(COLOR_PAIR(file_col));

    printw((t.name + " (" + t.tag + ")").c_str());
}

void Ui::draw_contexts() {

}
