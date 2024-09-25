#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <limits.h>
#include <vector>
#include <fcntl.h>
#include <string.h>
using namespace std;

void pinfo_cmd(int pid){
    cout<<"pid --"<<pid<<endl;
    string file="/proc/"+to_string(pid)+"/stat";
    ifstream stat(file);
    if(stat.is_open()){
        string l;
        getline(stat, l);
        stat.close();
        istringstream iss(l);
        string tok;
        int field_num=0;
        pid_t pgrp, tpgid;
        string proc_status;
        unsigned long long proc_mem;
        while(iss>>tok){
            field_num=field_num+1;
            if(field_num==3){
                proc_status=tok;
            }
            else if(field_num==5){
                pgrp=stoi(tok);
            }
            else if(field_num==8){
                tpgid=stoi(tok);
            }
            else if(field_num==23){
                proc_mem=stoull(tok);
            }
        }
        if(pgrp==tpgid){
            proc_status+="+";
        }
        cout<<"Process Status --"<<proc_status<<endl;
        cout<<"Memory --"<<proc_mem/1024<<" {Virtual Memory}"<<endl;
    }
    string exe_path="/proc/"+to_string(pid)+"/exe";
    char path[PATH_MAX];
    int len=readlink(exe_path.c_str(), path, PATH_MAX-1);
    if(len!=-1){
        path[len]='\0';
        cout<<"Executable Path --"<<path<<endl;
    }
    else{
        perror("error");
    }
}
