#docker user group managemnt 'server' (dkgms) 
#set this program up to run as root when the computer starts
g++ -pthread -o dkgms root-server.cpp
#docker group modify (dkgm) 
#place this somewhere in the PATH and let all users execute it 
#use this program to add or remove your self from the docker user group (not you will have to relog for this change to take effect)
g++ -pthread -o dkgm user-management-interface.cpp