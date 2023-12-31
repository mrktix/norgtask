#pragma once

#include "task.h"
#include "context.h"
#include "Config.h"
#include "Time.h"

#include <time.h>
#include <string>
#include <cstdio>
#include <vector>
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <climits>
#include <boost/algorithm/string/trim.hpp>

using namespace std;

class Tasklist {
    public:
        Tasklist(const Config* config); //loads the workspace passed in
        void sort_tasks();
        vector<task> current_tasks_sorted;
    private:
        void load_norg_workspace();
        int load_norg_file(const filesystem::path norg_file, int current_id, string folder_name, short folder_col, short file_col);
        context get_current_context();

        const Config* config;
        vector<task> all_tasks;
        vector<int> current_context_path; // list of indexes to get from root to current
        context root_context;
};
