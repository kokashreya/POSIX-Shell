#ifndef CD_H
#define CD_H
#include <vector>
using namespace std;

extern string display;
extern string display_st;
extern char home_dir[1024];
extern char dir_to_store[1024];

void cd_cmd(vector<char*> token_array);
string display_update(const string &path);

#endif