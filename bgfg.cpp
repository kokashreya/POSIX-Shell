#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "bgfg.h"
using namespace std;

void bg_fg_process(vector<char*> token_array, int background){
    pid_t pid=fork();
    if(pid<0){
        perror("Fork unsuccessful");
    }
    if(pid==0){
        if(execvp(token_array[0], token_array.data())==-1){
            perror("Failed");
            exit(0);
        }
    }
    else{
        if(background){
            cout<<"Process running in background with PID "<<pid<<endl;
        }
        else{
            waitpid(pid, NULL, 0);
        }
    }
}