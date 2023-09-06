#include "Ui.h"
#include <curses.h>

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
    clear();

    update_vars();

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

void Ui::draw_tasks() {
    int available_lines = maxy;
    int task_count = tasklist.current_tasks_sorted.size();
    int end = min(available_lines, task_count);

    task t = tasklist.current_tasks_sorted[tasklist.current_tasks_sorted.size()];

    timerange trng = before;

    int offset = 0;
    for (int i = 0; i < end; i++) {
        move(i, 0);
        if (!print_task(tasklist.current_tasks_sorted[i-offset], trng)) {
            offset++; //reprint the same task
            end = min(available_lines, end+1); //make sure we get to the end of the list, if the screen space allows
        }
    }
}

bool Ui::print_task(task t, timerange& trng) {
    long daystilldue = t.time_end/86400 - Time::utime()/86400 + 1;

    string timesep = "======= ";
    bool ret = false;

    if (daystilldue == 0 && trng == before) {
        trng = today;
        timesep += "TODAY";
        ret = true;
    } else if (daystilldue == 1 && (trng == today || trng == before)) {
        trng = tommorow;
        timesep += "TOMMOROW";
        ret = true;
    } else if (daystilldue > 1 && (trng == tommorow || trng == today || trng == before)) {
        trng = week;
        timesep += "THIS WEEK";
        ret = true;
    } else if (daystilldue > 7 && (trng == week || trng == tommorow || trng == today || trng == before)) {
        trng = year;
        timesep += "THIS YEAR";
        ret = true;
    }

    if (ret) {
        timesep += " ";
        while (timesep.length() < maxx) {
            timesep += "=";
        }
        attron(COLOR_PAIR(7));
        printw(timesep.c_str());
        attroff(COLOR_PAIR(7));
        return false;
    }

    bool event = t.tag == "event";

    int folder_col = t.folder_color%6+1;
    int file_col = t.file_color%6+1;
    int time_col = (event)? 7 : (t.time_end/86400)%6+1;
    int name_col = (event)? 7 : 0;

    string folder = t.folder.substr((t.folder[0] == '.')? 1 : 0, 3);
    string file = t.file.substr((t.file[0] == '.')? 1 : 0, 3);

    time_t utime = t.time_end;
    struct tm *tm = localtime(&utime);
    char datestr[24];

    if (t.time_end < Time::utime() + 45000000000) { //earlier than 1500 years into future
        strftime(datestr, sizeof(datestr), " %a %H:%M ~ %d.%m.%Y", tm);
    } else {
        datestr[0] = 0;
    }

    string context_name_tag = folder + "/" + file + " " + t.name;
    if (t.tag != "none" && t.tag != "event") context_name_tag += " (" + t.tag + ")";
    context_name_tag += " ";

    string final;

    for (int i = 0; i < maxx; i++) {
        if (i < context_name_tag.length()) {
            final += context_name_tag[i];
        } else if (i > maxx - sizeof(datestr)) {
            final += datestr[i - maxx - 1 + sizeof(datestr)];
        } else {
            final += ".";
        }
    }

    attron(COLOR_PAIR(folder_col));
    printw(final.substr(0,4).c_str());
    attroff(COLOR_PAIR(folder_col));

    attron(COLOR_PAIR(file_col));
    printw(final.substr(4,4).c_str());
    attroff(COLOR_PAIR(file_col));

    attron(COLOR_PAIR(name_col));
    printw(final.substr(8, context_name_tag.length()-8).c_str());
    attroff(COLOR_PAIR(name_col));

    attron(COLOR_PAIR(time_col));
    printw(final.substr(context_name_tag.length()).c_str());
    attroff(COLOR_PAIR(time_col));

    return true;
}

void Ui::draw_contexts() {

}
