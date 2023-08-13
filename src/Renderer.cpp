#include "Renderer.h"
#include "Time.h"

#include <ncurses.h>
using namespace std;


int Renderer::run(int argc, char** argv) {

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
