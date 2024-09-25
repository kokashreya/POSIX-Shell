#include <iostream>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <string>
#include "echo.h"
using namespace std;

void echo_cmd(vector<char*> token_array){
    int i;
    for(i=1;i<token_array.size()-1;i++){
        cout<<token_array[i]<<" ";
    }
    if(i==token_array.size()-1){
        cout<<token_array[i]<<endl;
    }
}