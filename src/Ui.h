#pragma once
#include "task.h"
#include "Tasklist.h"
#include "Config.h"

#include <vector>
#include <memory>

#include <ncurses.h>

using namespace std;

class Ui {
    public:
        Ui(const Config* config);
        bool draw(bool collect_input);
    private:
        string format_task_name(task t);
        void update_vars();
        void draw_outline();
        void draw_tasks();
        void draw_contexts();
        string task_format(task t);
        bool input();

        const Config* config;
        Tasklist tasklist;
        vector<task> sorted_tasks;

        enum mode { tasks, contexts };
        mode current_mode;
        int maxx, maxy;
};
