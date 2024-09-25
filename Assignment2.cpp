#include <iostream>
#include <stdio.h>
#include <pwd.h>
#include <unistd.h>    
#include <sys/types.h>  
#include <sys/wait.h>   
#include <signal.h> 
#include <vector>
#include <cstring>
#include <string>
#include "cd.h"
#include "pwd.h"
#include "echo.h"
#include "ls.h"
#include "bgfg.h"
#include "search.h"
#include "history.h"
#include "ioredir.h"
#include "pinfo.h"
using namespace std;
string display;
string display_st;
char home_dir[1024];
char dir_to_store[1024];
vector<string> commands;

pid_t pid=-1;
void ctrlz(int num){
if(pid!=-1){
    kill(pid,SIGCONT);
    pid=0;
}
cout<<pid<<endl;
}

void ctrlc(int num){
    if(pid!=-1){
        kill(pid,SIGINT);
        pid=0;
    }
}

vector<char*> tokenize_command(char* s_array){
    vector<char*> tk;
    char* token=strtok(s_array, " ");
    //cout<<token<<endl;
    while(token){
        tk.push_back(token);
        token=strtok(NULL, " ");
    }
    return tk;
}
vector<vector<char*>> tokenization(char* s_array){
    vector<vector<char*>> commands_array;
    char* command=strtok(s_array, ";");
    while(command){
        //cout<<command<<endl;
        vector<char*> tokens=tokenize_command(command);
        commands_array.push_back(tokens);
        command=strtok(NULL,";");
    }
    return commands_array;
}

bool contains_redir(string &s){
        for(size_t i=0;i<s.length();i++){
            if(s[i]=='>'||s[i]=='<'){
                return true;
            }
        }
        return false;
}
int main(){
    getcwd(home_dir, sizeof(home_dir));
    string s;
    string username=getlogin();
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));
    display=username+"@"+hostname+":~";
    display_st=display;
    display+=">";
    int background=0;
    int exitflag=0;
    signal(SIGINT, ctrlc);
    signal(SIGCONT, ctrlz);

    while(true){
        cout<<display<<flush;
        getline(cin,s);
        add_to_hist(commands,s);
        
        //converting string to a character array
        char* s_array=new char[s.length()+1];
        strcpy(s_array, s.c_str());

        //performing tokenization by calling tokenization function
        vector<vector<char*>> tokens=tokenization(s_array);
        
        for(auto &token_array:tokens){
        //vector<char*> token_array=tokenization(s_array);
        int n=token_array.size();
        //cout<<n<<endl;
        if(contains_redir(s)){
            string input;
            string output;
            bool append=false;
            check_cmd(s, token_array, input, output, append);
            pid_t pid=fork();
            if(pid==0){
                exec_redir(token_array, input, output, append);
                exit(0);
            }
            else if(pid>0){
                wait(NULL);
            }
            else{
                perror("Fork");
            }
            free(token_array[0]);
        }

        //break from loop if input is exit
        if(strcmp(token_array[0],"exit")==0){
            exitflag=1;
            break;
        }

        //if not exit
        else{
            //history function call
            if(strcmp(token_array[0],"history")==0){
                if(token_array.size()==1){
                    hist_cmd(0);
                }
                else{
                    string num=token_array[1];
                    hist_cmd(stoi(num));
                }
            }
            //cd function call
            else if(strcmp(token_array[0],"cd")==0){
                if(token_array.size()==1){
                    if(chdir(home_dir)==0){
                        cout<<"Moved to root"<<endl;
                        display=display_st+">";
                    }
                    else{
                        perror("Error");
                    }
                }
                else{
                    cd_cmd(token_array);
                }
            }
            //pwd function call
            else if(strcmp(token_array[0],"pwd")==0){
                pwd_cmd();
            }
            //echo function call
            else if(strcmp(token_array[0],"echo")==0){
                if(token_array.size()==1){
                    cout<<"Please provide an argument for echo"<<endl;
                    break;
                }
                else{
                    echo_cmd(token_array);
                }
            }
            //ls function call
            else if(strcmp(token_array[0],"ls")==0){
                ls_cmd(token_array);
            }
            //search function call
            else if(strcmp(token_array[0],"search")==0){
                search_cmd(token_array);
            }
            else if(strcmp(token_array[0],"pinfo")==0){
                int pid;
                if(token_array.size()==1){
                    pid=getpid();
                }
                else{
                    pid=stoi(token_array[1]);
                }
                pinfo_cmd(pid);
            }
            //background and foreground processes
            else{
                if(strcmp(token_array[n-1],"&")==0){
                    background=1;
                    bg_fg_process(token_array, background);
                }
                else{
                    background=0;
                    bg_fg_process(token_array, background);
                }
            }
        }
    }
    if(exitflag==1){
        break;
    }
    }
    return 0;
}