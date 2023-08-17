#pragma once
#include "task.h"
#include "Tasklist.h"
#include "Config.h"

#include <ncurses.h>

using namespace std;

class Ui {
    public:
        Ui(Config* config);
        void draw();
    private:
        string format_task_name(task t);
        void draw_tasks();
        void draw_contexts();

        Tasklist* tasklist;
        Config* config;

        enum mode { tasks, contexts };
        mode current_mode;
};
