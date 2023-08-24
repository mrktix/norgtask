#include "Renderer.h"
#include <curses.h>
#include <ncurses.h>
#include <iostream>

// ~/wiki/softwaredev/norgtask.norg

int init_curses() {
    initscr(); // sets up mem and clears screen
    curs_set(0); // hides cursor
    cbreak(); // ^C exits program
    noecho(); // don't write what you type to the screen

    if (!has_colors()) {
        printw("Terminal doesn't support colors");
        getch();
        return -1;
    } else {
        start_color();
    }

    use_default_colors();

    init_pair(0, -1, -1); // white
    init_pair(1,  1, -1); // red
    init_pair(2,  2, -1); // green
    init_pair(3,  3, -1); // yellow
    init_pair(4,  4, -1); // blue
    init_pair(5,  5, -1); // purple
    init_pair(6,  6, -1); // aqua
    init_pair(7,  0, -1); // black
    
    return 0;
}

int main(int argc, char** argv) {
    if (init_curses() == -1) return -1;

    int result = Renderer::run(argc, argv);

    endwin();
    return result;
}
