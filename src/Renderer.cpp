#include "Renderer.h"
#include "Time.h"
#include "Config.h"
#include "Tasklist.h"

#include <ncurses.h>

using namespace std;


int Renderer::run(int argc, char** argv) {

    filesystem::path configpath = "~/.config/norgtask/config";
    Config* config = new Config(configpath);
    Tasklist* tasklist = new Tasklist();

    endwin();
    tasklist->load_norg_workspace(config->norg_workspace());

    return 0;


    printw("%d", (int) Time::utime());
    
    getch();
    endwin();
    return 0;


    init_pair(1, -1, -1);
    attron(COLOR_PAIR(1));

    int height=10, width=40, y=4, x=4;
    WINDOW* win = newwin(height, width, y, x);
    wattron(win, COLOR_PAIR(1));
    box(win, 0, 0);

    mvwprintw(win, 1, 1, "a test");
    


    refresh();
    wrefresh(win);
    getch();



    mvprintw(2, 10, "hello world");
    refresh();
    getch();


    return 0;
}
