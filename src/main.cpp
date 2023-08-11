#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    initscr(); // sets up mem and clears screen
    curs_set(0); // hides cursor



    int height=10, width=40, y=4, x=4;
    WINDOW * win = newwin(height, width, y, x);
    mvwprintw(win, 1, 1, "test");
    box(win, 0, 0);
    


    refresh();
    wrefresh(win);
    getch();



    clear();
    mvprintw(4, 10, "hello world");
    refresh();
    getch();




    endwin(); // deallocates memory and ends ncurses
    return 0;
}
