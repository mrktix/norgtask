#pragma once
#include <string>

using namespace std;

struct task {
    string name;
    long time_begin, time_end;
    int id;
    string folder, file, tag;
    short folder_color, file_color;
};
