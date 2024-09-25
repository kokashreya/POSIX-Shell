#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>
#include "history.h"
using namespace std;
string history_file="test1.txt";
int max_to_store=20;
int max_to_print=10;

vector<string> get_hist(){
    string cmd="";
    char read_buffer[1024];
    int fd=open(history_file.c_str(), O_RDONLY);
    int bytes_read=read(fd, read_buffer, sizeof(read_buffer)-1);
   // while(bytes_read){
        for(int i=0;i<bytes_read;i++){
            if(read_buffer[i]=='\n'){
                commands.push_back(cmd);
                cmd.clear();
            }
            else{
                cmd=cmd+read_buffer[i];
            }
        }
   // }
    return commands;
}

void print_hist(vector<string>commands, int num){
    //cout<<"in print"<<endl;
    if(num==0 || num>commands.size()){
        if(commands.size()>=max_to_print){
            num=max_to_print;
        }
        else{
            num=commands.size();
        }
    }
    int start_ind=commands.size()-num;
    for(int i=start_ind;i<commands.size();i++){
        cout<<commands[i]<<endl;
    }
}

void add_to_hist(vector<string>commands, string command){
    if(commands.size()>=max_to_store){
        commands.erase(commands.begin());
    }
    commands.push_back(command);
    int wr_fd=open(history_file.c_str(), O_WRONLY|O_CREAT|O_APPEND);
    write(wr_fd, command.c_str(), command.size());
    write(wr_fd,"\n",1);
    close(wr_fd);
}
void save_hist(vector<string> commands){
    int wr_fd=open(history_file.c_str(), O_WRONLY|O_CREAT|O_TRUNC);
    for(auto&command : commands){
        write(wr_fd, command.c_str(), command.size());
        write(wr_fd,"\n",1);
    }
    close(wr_fd);
}
void hist_cmd(int num){
    vector<string> commands=get_hist();
    print_hist(commands, num);
}