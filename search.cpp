#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include "search.h"
using namespace std;

bool search_dir(string &cur_dir, string &file){
    DIR *dir=opendir(cur_dir.c_str());
    struct dirent *direntry;
    struct stat file_buf;
    while((direntry=readdir(dir))!=NULL){
        string path=cur_dir+"/"+direntry->d_name;
        if(strcmp(direntry->d_name, ".")==0 || strcmp(direntry->d_name, "..")==0){
            continue;
        }
        if(stat(path.c_str(), &file_buf)==-1){
            perror("Error");
        }
        if(strcmp(direntry->d_name, file.c_str())==0){
            return true;
        }
        if(S_ISDIR(file_buf.st_mode)){
            if(search_dir(path, file)){
                return true;
            }
        }
    }
    return false;
}
void search_cmd(vector<char*> token_array){
    string file=token_array[1];
    string cur_dir=".";
    if(search_dir(cur_dir, file)){
        cout<<"True"<<endl;
    }
    else{
        cout<<"False"<<endl;
    }
}