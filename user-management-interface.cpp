#include "mqueue.hpp"
#include "string.h"
#include <iostream>
#include <vector>

using namespace std;

typedef struct messageHolder{
    char message[512];
} messageHolder;

void printHelpMessage(string arg1){
    cout << "docker user group manager"<< endl << "add or remove your account from the docker group" << endl << "useage: " << endl << arg1 << " [argument] <options>" << endl;
    cout << endl << endl << endl;
    cout << "valid arguments:" << endl << "add <username> \t\t - adds the specified user to the docker group" << endl 
    << "remove <username> \t - removes the specified user from the docker group" << endl 
    << "--help \t\t\t - display this message" << endl;
}

int main(int argc, char * argv[]){
    if(argc <2){
        printHelpMessage(argv[0]);
        return EXIT_FAILURE;
    }

    vector<string> args;
    for(int i=0;i<argc-1;i++){
        args.push_back(argv[i+1]);
    }

    MQueue<messageHolder,4> queue{"/dokusrm"};
    
    for(int i=0;i<argc-1;i++){
        if(args[i] == "add"){
            messageHolder msg;
            strcpy(msg.message,"add");
            if(i+1<argc-1){
                strcpy(msg.message+4,args[i+1].c_str());
                queue.push(msg);
                i++;
            }else{
                cerr << "the option add requires 1 argument <username>"<< endl;
                return EXIT_FAILURE;
            }
        } else if(args[i] == "remove"){
            messageHolder msg;
            strcpy(msg.message,"remove");
            if(i+1<argc-1){
                strcpy(msg.message+7,args[i+1].c_str());
                queue.push(msg);
                i++;
            }else{
                cerr << "the option remove requires 1 argument <username>"<< endl;
                return EXIT_FAILURE;
            }
        }else if(args[i] == "--help"){
            printHelpMessage(argv[0]);
            return EXIT_SUCCESS;
        }else{
            cerr << "unknown argument "<<args[i] << " run with --help for valid arguments" << endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}