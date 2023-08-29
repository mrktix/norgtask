#pragma once
#include "task.h"
#include "Tasklist.h"
#include "Config.h"

#include <vector>
#include <memory>
#include <string>

#include <ncurses.h>

using namespace std;

class Ui {
    public:
        Ui(const Config* config);
        bool draw(bool collect_input);
    private:
        enum mode { tasks, contexts };
        enum timerange { before, day, week, year };

        string format_task_name(task t);
        void update_vars();
        void draw_outline();
        void draw_tasks();
        void draw_contexts();
        bool print_task(task t, timerange& trng);
        bool input();

        const Config* config;
        Tasklist tasklist;
        vector<task> sorted_tasks;

        mode current_mode;
        int maxx, maxy;
};
