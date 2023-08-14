#include "task.h"
#include "context.h"
#include <ncurses.h>
#include <vector>
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <boost/algorithm/string/trim.hpp>

#include <iostream>

using namespace std;

class Tasklist {
    public:
        Tasklist(); //loads the workspace passed in
        void load_norg_workspace(filesystem::path norg_workspace);
        vector<task*> get_current_tasks_sorted();
    private:
        vector<task> all_tasks;
        vector<task*> current_tasks_sorted;
        context root_context;
        context current_context;
};
