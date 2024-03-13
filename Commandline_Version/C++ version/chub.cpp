#include <iostream>
#include <string>
#include <sys/stat.h>

#define args_err "More arguments needed"

int createProject(char *str);
void createSubFolder(char *name);

int main(int argc,char **argv){
    if (argv[1] == NULL){
        stderr;std::cout << args_err << std::endl;
        return 1;
    }
    if (strcmp(argv[1],"-init")==0){
        if (argv[2]==NULL){
            stderr;std::cout << args_err << std::endl;
            return 1;
        }
        switch (createProject(argv[2])){
            case 0:{
                std::cout << "Project Created Successfully" << std::endl;
                return 0;
            }
            case 1:{
                stderr;std::cout << "An error occured during project creation" << std::endl;
                return 1;
            }
        }
    }
    if (strcmp(argv[1],"-version")==0){
        using namespace std;
        cout << "chub version alpha-0.0.1" << endl;
        cout << "Made by theokarvoun" << endl;
        cout << "Check for newer versions on: https://github.com/theokarvoun/Creator-Hub-Console/tree/main/Commandlne_Version" << endl;
        return 0;
    }
    if ((strcmp(argv[1],"-h")==0)||(strcmp(argv[1],"-help")==0)){
        using namespace std;
        cout << "-h or -help: shows commands" << endl;
        cout << "-version: displays the current version" << endl;
        cout << "-init <project name>: creates a new project folder in the current directory" << endl;
        cout << "-console: launches the console version of the app" << endl;
        return 0;
    }
    if (strcmp(argv[1],"-console")==0){
        system("Creator-Hub-Console.exe");
        return 0;
    }
    if (strcmp(argv[1],"-shell")==0){
        system("powershell");
        return 0;
    }
    return 0;
}

int createProject(char *str){
    if (!mkdir(str)) {
        char *temp = (char*)malloc(50*sizeof(char));
        strcpy(temp,str);
        strcat(temp,"\\footage");
        createSubFolder(temp);
        free(temp);
        temp = (char*)malloc(50*sizeof(char));
        strcpy(temp,str);
        strcat(temp,"\\sfx");
        createSubFolder(temp);
        free(temp);
        temp = (char*)malloc(50*sizeof(char));
        strcpy(temp,str);
        strcat(temp,"\\clips");
        createSubFolder(temp);
        free(temp);
        return 0;
    } else {
        return 1;
    }
}

void createSubFolder(char *name){
    if (mkdir(name)){
        fputs("Couldn't create subfolder",stderr);
        return;
    }
}