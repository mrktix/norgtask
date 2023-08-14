#include <string>
#include <vector>
using namespace std;

struct context {
    string name;
    vector<context*> children;
    int id_begin, id_end;
};
