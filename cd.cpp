#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <string>
#include "cd.h"
using namespace std;
char current_dir[1024];
char prev_dir[1024];
string display_update(const string &path){
    if(path==".."){
        int pos;
        int flag=0;
        for(int i=display.length()-1;i>=0;i--){
            if(display[i]=='/'){
                pos=i;
                flag=1;
                break;
            }
        }
        string p1=display.substr(0, pos);
        if(flag==1){
            display=p1+">";
        }
        else{
            display=p1;
        }
    }
    else{
        string p1=display.substr(0, display.size()-1);
        string p2=display.substr(display.size()-1);
        if(path[0]=='/'){
            display=p1+path+p2;
        }
        else{
            display=p1+"/"+path+p2;
        }
        
    } 
    return display;    
}

void cd_cmd(vector<char*> token_array){
    const char* path=token_array[1];

    if(strcmp(token_array[1],".")==0){
        if(chdir(".")==0){
            cout<<"Staying in same directory"<<endl;
        }
        else{
            perror("Error");
        }
    }
    else if(strcmp(token_array[1],"..")==0){
        getcwd(prev_dir, sizeof(prev_dir));
        if(strlen(prev_dir)>0){
            if(chdir("..")==0){
                display=display_update(path);
                getcwd(current_dir, sizeof(current_dir));
                cout<<"Moved to parent directory"<<endl;
            }
            else{
                perror("Error");
            }
        } 
    }
    else if(strcmp(token_array[1],"-")==0){
        if(chdir(prev_dir)==0){
            strcpy(prev_dir,current_dir);
            getcwd(current_dir,sizeof(current_dir));
            cout<<"Moved to previous directory"<<endl;
        }
        else{
            perror("Error");
        }
        if(strcmp(home_dir,current_dir)==0){
            display=display_st+">";
        }
        else{
            int i=0;
            string temp="";
            while(strlen(home_dir)){
                if(home_dir[i]!=current_dir[i]){
                    break;
                }
                i=i+1;
            }
            while(current_dir[i]){
                temp+=current_dir[i];
                i++;
            }
            display=display_st+temp+">";
        }

    }
    else if(strcmp(token_array[1],"~")==0){
        if(chdir(home_dir)==0){
            cout<<"Moved to root"<<endl;
            display=display_st+">";
        }
        else{
            perror("Error");
        }
    }
    else{
        getcwd(dir_to_store, sizeof(dir_to_store));
        if(chdir(path)==0){
            strcpy(prev_dir, dir_to_store);
            getcwd(current_dir, sizeof(current_dir));  
            display=display_update(path);
            cout<<"Directory changed"<<endl; 
        }
        else{
            perror("Error");
        }
    }
}