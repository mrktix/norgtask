#pragma once
#include <string>
#include <vector>
using namespace std;

struct context {
    string name;
    vector<context> children;
    int id_begin, id_end; //id_end is one above the highest task id in this context
};
