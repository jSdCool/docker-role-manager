#include "mqueue.hpp"
#include <iostream>
#include <string.h>
#include <stdlib.h> // for system()
#include <chrono>//for sleep
#include <thread>//for sleep

//NOTE this program must be run as root!

using namespace std;

typedef struct messageHolder{
    char message[512];
} messageHolder;

void handleMessage(messageHolder message){
    int firstLength = strlen(message.message);
    if(firstLength >= 512){
        //the string does not have a terminating position, this message must not be valid
        return;
    }
    int posibleLengthLeft = 512 - firstLength-2;
    int secondLength = strlen(message.message+firstLength+1);
    if(secondLength >= posibleLengthLeft){
        //the second string does not terminate by the end of the alicated array, it must not be valid
        return;
    }
    string action(message.message);
    string user(message.message+firstLength+1);

    if(action == "add"){
        string command = "usermod -aG docker \"";
        //remove all spaces from passed in username to prevent additional flags from being passed to the command
        size_t space = user.find(' ');
        while(space != string::npos){
            user.replace(space,1,"~");
        }
        if(user[0]=='-'){
            user.replace(0,1,"_");
        }

        command += user +"\"";
        //run the command
        system(command.c_str());
        cout << "add "<<user<<" with the command "<<command<<endl;
    }else if (action == "remove"){
        string command = "gpasswd -d ";
         //remove all spaces from passed in username to prevent additional flags from being passed to the command
        size_t space = user.find(' ');
        while(space != string::npos){
            user.replace(space,1,"~");
        }
        if(user[0]=='-'){
            user.replace(0,1,"_");
        }
        command+=user+" docker";
        system(command.c_str());
        cout << "remove "<<user<<" with the command "<<command<<endl;
    }else{
        //no action
    }
}

int main(int argc, char * argv[]){
    MQueue<messageHolder, 4> queue{"/dokusrm"};

    if(argc >=2){
        if(!strcmp("reset",argv[1])){
            queue.resetInternals();
        }
    }

    while(1){
        if(!queue.empty()){
            messageHolder mesage = queue.pop();
            //cout <<"recieved message: "<< mesage.message << endl;
            handleMessage(mesage);
        }
        this_thread::sleep_for(chrono::milliseconds(1));
    }

    return EXIT_SUCCESS;
}