#pragma once
#include "task.h"
#include "context.h"
#include <time.h>
#include <cstdio>
#include <vector>
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <climits>
#include <boost/algorithm/string/trim.hpp>

#include <iostream>

using namespace std;

class Tasklist {
    public:
        Tasklist(filesystem::path norg_workspace); //loads the workspace passed in
        void sort_tasks();
        vector<task> current_tasks_sorted;
    private:
        void load_norg_workspace(filesystem::path norg_workspace);
        int load_norg_file(const filesystem::path norg_file, int current_id);
        context get_current_context();

        vector<task> all_tasks;
        vector<int> current_context_path; // list of indexes to get from root to current
        context root_context;
};
