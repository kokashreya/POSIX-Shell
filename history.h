#ifndef HISTORY_H
#define HISTORY_H
#include <vector>
#include<string>
#include<stdio.h>
using namespace std;

extern vector<string> commands;
vector<string> get_hist();
void print_hist(vector<string>commands, int num);
void add_to_hist(vector<string>commands, string command);
void save_hist(vector<string> commands);
void hist_cmd(int num);

#endif