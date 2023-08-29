#include "Tasklist.h"

Tasklist::Tasklist(const Config* config)
:config(config)
{
    this->load_norg_workspace();
}

void Tasklist::sort_tasks() {
    context current_context = get_current_context();
    vector<task> ret;

    for (int i = current_context.id_begin; i < current_context.id_end; i++) {
        task insert = all_tasks[i];

        if (current_tasks_sorted.size() == 0) {
            current_tasks_sorted.push_back(insert);
            continue;
        }

        long insert_end = insert.time_end;
        bool inserted = false;

        for (int j = current_tasks_sorted.size()-1; j >= 0; j--) {
            long marker_end = current_tasks_sorted[j].time_end;

            if (insert_end >= marker_end) {
                // since marker has already been inserted, it has a lower id (appears earlier in workspace)
                // so insert should be inserted right after it even if the time is equal
                current_tasks_sorted.insert(current_tasks_sorted.begin()+j+1, insert);
                inserted = true;
                break;
            }
        }

        if (!inserted) {
            current_tasks_sorted.insert(current_tasks_sorted.begin(), insert);
        }
    }
}

context Tasklist::get_current_context() {
    int size = current_context_path.size();
    if (size == 0) {
        return root_context;
    } else if (size == 1) {
        return root_context.children[current_context_path[0]];
    } else if (size == 2) {
        return root_context.children[current_context_path[0]].children[current_context_path[1]];
    }

    throw runtime_error("current_context_path has a length greater than 2");
}

void Tasklist::load_norg_workspace() {
    filesystem::path norg_workspace = config->path("norg_workspace");

    if (!exists(norg_workspace)) {
        throw invalid_argument("norg workspace specified in config does not exist: " + norg_workspace.string());
    }

    int current_id = 0;

    root_context.name = "root";
    root_context.id_begin = current_id;
    root_context.children.clear();

    int folder_col; //col from 1 to 8

    // loop through the directories in norg workspace
    for (const filesystem::path entry : filesystem::directory_iterator(norg_workspace)) {
        if (!filesystem::is_directory(entry)) continue;
        string entry_name = entry.filename().string();
        if (entry_name[0] == '.') continue;

        context con;
        con.name = entry.filename().string();
        con.id_begin = current_id;

        int file_col;
        //loop through all the files in the 
        for (const filesystem::path subentry : filesystem::directory_iterator(entry)) {
            if (!filesystem::is_regular_file(subentry)) continue;
            string subentry_name = subentry.filename().string();
            if (subentry.extension() != ".norg") continue;

            context subcon;

            subcon.name = subentry_name;
            subcon.id_begin = current_id;

            current_id = load_norg_file(subentry, current_id, con.name, folder_col, file_col);

            subcon.id_end = current_id;

            if (subcon.id_end > subcon.id_begin) {
                con.children.push_back(subcon);
                file_col++;
            }
        }

        con.id_end = current_id;

        if (con.id_end > con.id_begin) {
            root_context.children.push_back(con);
            folder_col++;
        }
    }

    root_context.id_end = current_id;

    sort_tasks();
}

int Tasklist::load_norg_file(const filesystem::path norg_file, int current_id, string folder_name, short folder_col, short file_col) {
    // read through the file and extract the tasks to all_tasks, incrementing current_id
    ifstream file;
    file.open(norg_file);
    if (!file.is_open()) throw runtime_error("unable to open file in workspace: " + norg_file.string());

    bool readingtask = false;
    bool filled_field[4]; // 0-name, 1-tag, 2-begin, 3-end 
    fill_n(filled_field, 4, false);
    enum field_name { name, tag, begin, end };

    int linenum = 0;
    while (file) {
        linenum++;
        string line;
        getline(file, line);
        boost::algorithm::trim(line);

        string error = "line "+to_string(linenum)+" in "+norg_file.string()+", ";

        if (readingtask) {
            if (line == "@end") {
                //finish the task initalization
                error += "error parsing task";
                // check if all the fields were filled out
                assert (!all_tasks.empty());
                if (!filled_field[name]) {
                    error += ": name not defined";
                    throw runtime_error(error);
                }
                if (!filled_field[tag]) {
                    all_tasks.back().tag = "none";
                }
                if (!filled_field[begin]) {
                    all_tasks.back().time_begin = 0;
                }
                if (!filled_field[end]) {
                    all_tasks.back().time_end = Time::utime() + 60000000000; //2000 years into the future
                }

                all_tasks.back().folder = folder_name;
                all_tasks.back().file = norg_file.filename().string();
                all_tasks.back().folder_color = folder_col;
                all_tasks.back().file_color = file_col;

                all_tasks.back().id = current_id;
                current_id++;

                readingtask = false;
                fill_n(filled_field, 4, false);
                continue;
            }

            size_t field_value_delim_pos = line.find("=");
            size_t comment_delim_pos = line.find("--");

            string field = line.substr(0, field_value_delim_pos);
            boost::algorithm::trim(field);

            string value = line.substr(field_value_delim_pos+1, comment_delim_pos-field_value_delim_pos-1);
            boost::algorithm::trim(value);

            if (value[0] == '"' && value[value.size()-1] == '"') value = value.substr(1, value.size()-2);

            assert (!all_tasks.empty());
            if (field == "name") {
                filled_field[name] = true;
                all_tasks.back().name = value;
            } else if (field == "tag") {
                filled_field[tag] = true;
                all_tasks.back().tag = value;
            } else if (field == "begin" || field == "end") {
                error += "date is not formatted properly";

                struct tm tm;
                int r = sscanf(value.c_str(), "%d-%d-%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min);

                if (r < 6) tm.tm_sec = 0;
                if (r < 5) tm.tm_min = 0;
                if (r < 4) tm.tm_hour = 0;
                if (r < 3) tm.tm_mday = 0;
                if (r < 2) tm.tm_mon = 0;
                if (r < 1) throw runtime_error(error);
                tm.tm_isdst = -1;

                tm.tm_year -= 1900;
                tm.tm_mon -= 1;

                long utime = mktime(&tm);

                if (utime == -1) throw runtime_error(error);

                if (field == "begin") {
                    filled_field[begin] = true;
                    all_tasks.back().time_begin = utime;
                } else { // must be "end" by previous if check
                    filled_field[end] = true;
                    all_tasks.back().time_end = utime;
                }
            } else if (field == "done") {
                readingtask = false;
                all_tasks.pop_back();
            }
        } else {
            if (line == "@code lua task") {
                readingtask = true;
                task temp;
                all_tasks.push_back(temp);
            }
        }
    }

    file.close();
    return current_id;
}
