#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <string>
#include "pwd.h"
using namespace std;
char curr_dir[1024];
void pwd_cmd(){
    if(getcwd(curr_dir, sizeof(curr_dir))!=NULL){
        if(strcmp(home_dir,curr_dir)==0){
            cout<<home_dir<<endl;
            display=display_st+">";
        }
        else{
            int i=0;
            string temp="";
            while(strlen(home_dir)){
                if(home_dir[i]!=curr_dir[i]){
                    break;
                }
                i=i+1;
            }
            while(curr_dir[i]){
                temp+=curr_dir[i];
                i++;
            }
            cout<<home_dir+temp+">"<<endl;
            display=display_st+temp+">";
        }
    }
    else{
        perror("Error");
    }
}