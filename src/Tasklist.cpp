#include "Tasklist.h"

Tasklist::Tasklist() { }

void Tasklist::load_norg_workspace(filesystem::path norg_workspace) {
    if (!exists(norg_workspace)) {
        throw invalid_argument("norg workspace specified in config does not exist");
    }

    int current_id = 0;

    root_context.name = "root";
    root_context.id_begin = current_id;

    //loop through the directories in norg workspace
    for (const filesystem::path entry : filesystem::directory_iterator(norg_workspace)) {
        if (!filesystem::is_directory(entry)) continue;
        string entry_name = entry.filename().string();
        if (entry_name[0] == '.') continue;

        context con;
        con.name = entry.filename().string();
        con.id_begin = current_id;

        //loop through all the files in the 
        for (const filesystem::path subentry : filesystem::directory_iterator(entry)) {
            if (!filesystem::is_regular_file(subentry)) continue;
            string subentry_name = subentry.filename().string();
            if (subentry_name[0] == '.') continue;

            context subcon;

            subcon.name = subentry_name;
            subcon.id_begin = current_id;

            // read through the file and extract the tasks to all_tasks, incrementing current_id
            ifstream file;
            file.open(subentry);
            if (!file.is_open()) throw runtime_error("unable to open file in workspace: " + subentry.string());

            bool readingtask = false;

            while (file) {
                string line;
                getline(file, line);
                boost::algorithm::trim(line);

                if (readingtask) {
                    size_t field_value_delim_pos = line.find("=");

                    string field = line.substr(0, field_value_delim_pos);
                    boost::algorithm::trim(field);

                    string value = line.substr(field_value_delim_pos+1, line.find("--"));
                    boost::algorithm::trim(value);

                    if (line == "@end") {
                        //finish the task initalization
                        readingtask = false;
                        continue;
                    }

                    cout << "'" << field << "' -- '" << value << "'" << endl; 
                } else {
                    if (line == "@code lua task") {
                        readingtask = true;
                        task temp;
                        all_tasks.push_back(temp);
                    }
                }
            }

            file.close();

            subcon.id_end = current_id;
        }

        con.id_end = current_id;
        root_context.children.push_back(&con);
    }
}

vector<task*> Tasklist::get_current_tasks_sorted() {
    return this->current_tasks_sorted;
}
