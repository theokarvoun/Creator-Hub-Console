#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int createProject(char *str);

int main(int argc,char **argv){
    if (argv[1] == NULL){
        fputs("More arguments needed",stderr);
        return 1;
    }
    if ((strcmp(argv[1],"-h")==0)||(strcmp(argv[1],"-help")==0)){
        printf("-h or -help: shows commands\n");
        printf("-init <project name>: creates a new project folder in the current directory\n");
        printf("-console: launches the console version of the app\n");
    }
    if (strcmp(argv[1],"-init")==0){
        if (argv[2]==NULL){
            fputs("More arguments needed",stderr);
            return 1;
        }
        switch (createProject(argv[2])){
            case 0:{
                printf("Project created successfully\n");
                break;
            }
            case 1:{
                fputs("An error occured during project creation\n",stderr);
                return 1;
            }
        }
    }
    if (strcmp(argv[1],"-console")==0){
        system("Creator-Hub-Console.exe");
    }
    return 0;
}

int createProject(char *str){
    if (mkdir(str) == 0) {
        return 0;
    } else {
        return 1;
    }
}