#ifndef LS_H
#define LS_H
#include <vector>
using namespace std;

void ls_cmd(vector<char*> token_array);
void ls_dir(const char* &path, int flag);

#endif