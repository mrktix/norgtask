#include "Renderer.h"
#include <ncurses.h>

// ~/wiki/softwaredev/norgtask.norg

int init_curses() {
    initscr(); // sets up mem and clears screen
    curs_set(0); // hides cursor
    cbreak(); // ^C exits program
    noecho(); // don't write what you type to the screen
    use_default_colors();

    if (!has_colors()) {
        printw("Terminal doesn't support colors");
        getch();
        return -1;
    } else {
        start_color();
    }
    return 0;
}

int main(int argc, char** argv) {
    if (init_curses() == -1) return -1;

    int result;
    try {
        result = Renderer::run(argc, argv);
    } catch (...) {
        endwin();
        throw;
    }

    endwin();
    return result;
}
