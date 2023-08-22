#pragma once
#include "task.h"
#include "Tasklist.h"
#include "Config.h"

#include <vector>

#include <ncurses.h>

using namespace std;

class Ui {
    public:
        Ui(Config* config);
        bool draw(bool collect_input);
    private:
        string format_task_name(task t);
        void update_vars();
        void draw_outline();
        void draw_tasks();
        void draw_contexts();
        bool input();

        Tasklist* tasklist;
        Config* config;
        vector<task> sorted_tasks;

        enum mode { tasks, contexts };
        mode current_mode;
        int maxx, maxy;
};
