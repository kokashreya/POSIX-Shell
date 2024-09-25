#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <ctime>
#include <string>
#include <dirent.h>
#include <algorithm>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include "ls.h"
using namespace std;
void ls_dir(string &path, int flag){
    DIR *dir=opendir(path.c_str());
    struct dirent *direntry;
    vector<string> files;

    if(flag==1){
        while((direntry=readdir(dir))!=NULL){
            if(direntry->d_name[0]!='.'){
                files.push_back(direntry->d_name);
            }
            else{
                continue;
            }
        }
        closedir(dir);
        sort(files.begin(),files.end());
        for(size_t i=0;i<files.size();i++){
                struct stat FileStat;
                struct passwd *password=getpwuid(FileStat.st_uid);
                struct group *gp=getgrgid(FileStat.st_gid);
                struct tm *datetime=localtime(&FileStat.st_mtime);
                char timebuffer[25];
                strftime(timebuffer, sizeof(timebuffer), "%b %d %H:%M", datetime);
                string complete_path=string(path)+"/"+files[i];
                if(stat(complete_path.c_str(), &FileStat)==-1){
                    perror("Stat");
                    continue;
                }
                cout<<(S_ISDIR(FileStat.st_mode)?'d':'-')
                    <<((FileStat.st_mode & S_IRUSR)?'r':'-')
                    <<((FileStat.st_mode & S_IWUSR)?'w':'-')
                    <<((FileStat.st_mode & S_IXUSR)?'x':'-')
                    <<((FileStat.st_mode & S_IRGRP)?'r':'-')
                    <<((FileStat.st_mode & S_IWGRP)?'w':'-')
                    <<((FileStat.st_mode & S_IXGRP)?'x':'-')
                    <<((FileStat.st_mode & S_IROTH)?'r':'-')
                    <<((FileStat.st_mode & S_IWOTH)?'w':'-')
                    <<((FileStat.st_mode & S_IWOTH)?'x':'-')
                    <<" "<<FileStat.st_nlink
                    <<" "<<(password?password->pw_name:"shreya")
                    <<" "<<(gp?gp->gr_name:"shreya")
                    <<" "<<FileStat.st_size
                    <<" "<<timebuffer
                    <<" "<<files[i]<<endl;
        }
    }
    else if(flag==2){
        while((direntry=readdir(dir))!=NULL){
            if(direntry->d_name[0]!='.'){
                files.push_back(direntry->d_name);
            }
            else{
                files.push_back(direntry->d_name);
            }
        }
        closedir(dir);
        sort(files.begin(),files.end());
        size_t i;
        for(i=0;i<files.size()-1;i++){
            cout<<files[i]<<" ";
        }
        if(i=files.size()-1){
            cout<<files[i]<<endl;
        }
    }
    else if(flag==3){
        while((direntry=readdir(dir))!=NULL){
            if(direntry->d_name[0]!='.'){
                files.push_back(direntry->d_name);
            }
            else{
                files.push_back(direntry->d_name);
            }
        }
        closedir(dir);
        sort(files.begin(),files.end());
        for(size_t i=0;i<files.size();i++){
                struct stat FileStat;
                struct passwd *password=getpwuid(FileStat.st_uid);
                struct group *gp=getgrgid(FileStat.st_gid);
                struct tm *datetime=localtime(&FileStat.st_mtime);
                char timebuffer[25];
                strftime(timebuffer, sizeof(timebuffer), "%b %d %H:%M", datetime);
                string complete_path=string(path)+"/"+files[i];
                if(stat(complete_path.c_str(), &FileStat)==-1){
                    perror("Stat");
                    continue;
                }
                cout<<(S_ISDIR(FileStat.st_mode)?'d':'-')
                    <<((FileStat.st_mode & S_IRUSR)?'r':'-')
                    <<((FileStat.st_mode & S_IWUSR)?'w':'-')
                    <<((FileStat.st_mode & S_IXUSR)?'x':'-')
                    <<((FileStat.st_mode & S_IRGRP)?'r':'-')
                    <<((FileStat.st_mode & S_IWGRP)?'w':'-')
                    <<((FileStat.st_mode & S_IXGRP)?'x':'-')
                    <<((FileStat.st_mode & S_IROTH)?'r':'-')
                    <<((FileStat.st_mode & S_IWOTH)?'w':'-')
                    <<((FileStat.st_mode & S_IWOTH)?'x':'-')
                    <<" "<<FileStat.st_nlink
                    <<" "<<(password?password->pw_name:"shreya")
                    <<" "<<(gp?gp->gr_name:"shreya")
                    <<" "<<FileStat.st_size
                    <<" "<<timebuffer
                    <<" "<<files[i]<<endl;
        }
    }
    else{
        while((direntry=readdir(dir))!=NULL){
            if(direntry->d_name[0]!='.'){
                files.push_back(direntry->d_name);
            }
            else{
                continue;
            }
        }
        closedir(dir);
        sort(files.begin(),files.end());
        size_t i;
        for(i=0;i<files.size()-1;i++){
            cout<<files[i]<<" ";
        }
        if(i=files.size()-1){
            cout<<files[i]<<endl;
        }
}
}
void ls_cmd(vector<char*> token_array){
    string path;
    int flag=0;
    if(token_array.size()==1){
        path=".";
        ls_dir(path, flag);
    }
    else{
        if(token_array.size()==3 && ((strcmp(token_array[1],"-a")==0 && strcmp(token_array[2],"-l")==0) || (strcmp(token_array[1],"-l")==0 && strcmp(token_array[2],"-a")==0))){
            path=".";
            flag=3;
            ls_dir(path, flag);
        }
        else if(token_array.size()==4 && ((strcmp(token_array[1],"-a")==0 && strcmp(token_array[2],"-l")==0) || (strcmp(token_array[1],"-l")==0 && strcmp(token_array[2],"-a")==0))){
            path=token_array[3];
            flag=3;
            ls_dir(path, flag);
        }
        else if(strcmp(token_array[1],"-l")==0){
            if(token_array.size()==3){
                path=token_array[2];
                flag=1;
                ls_dir(path, flag);
            }
            else{
                path=".";
                flag=1;
                ls_dir(path, flag);
            } 
        }
        else if(strcmp(token_array[1],"-a")==0){
            if(token_array.size()==3){
                path=token_array[2];
                flag=2;
                ls_dir(path, flag);
            }
            else{
                path=".";
                flag=2;
                ls_dir(path, flag);
            } 
        }
        else if(strcmp(token_array[1],"-la")==0 || strcmp(token_array[1],"-al")==0){
            if(token_array.size()==3){
                path=token_array[2];
                flag=3;
                ls_dir(path, flag);
            }
            else{
                path=".";
                flag=3;
                ls_dir(path, flag);
            }  
        }
        else{
            path=token_array[1];
            flag=0;
            ls_dir(path, flag);

        }
    }
    
}