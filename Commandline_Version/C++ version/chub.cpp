#include <iostream>
#include <string>
#include <sys/stat.h>

#define args_err "More arguments needed"

int createProject(char *str);
void createSubFolder(char *name);

const std::string init = "-init";

int main(int argc, std::string argv[]){
    if (argc < 1){
        std::cerr << args_err << std::endl;
        return 1;
    }
    switch (argv[1]){
        case init:{
            if (argc < 2){
            std::cerr << args_err << std::endl;
            return 1;
        }
        switch (createProject(argv[2])){
            case 0:{
                std::cout << "Project Created Successfully" << std::endl;
                return 0;
            }
            case 1:{
                std::cerr << "An error occured during project creation" << std::endl;
                return 1;
            }
        }
        }
        case ("-help" || "-h") :{
            using namespace std;
            cout << "-h or -help: shows commands" << endl;
            cout << "-version: displays the current version" << endl;
            cout << "-init <project name>: creates a new project folder in the current directory" << endl;
            cout << "-console: launches the console version of the app" << endl;
            return 0;
        }
        case "-version":{
            using namespace std;
            cout << "chub version alpha-0.0.2-C++" << endl;
            cout << "Made by theokarvoun" << endl;
            cout << "Check for newer versions on: https://github.com/theokarvoun/Creator-Hub-Console/tree/main/Commandlne_Version" << endl;
            return 0;
        }
        case "-console":{
            system("Creator-Hub-Console.exe");
            return 0;
        }
        case "-shell":{
            system("powershell");
            return 0;
        }
        default:{
            std::cerr << "Invalid Command\n Use -help" << std::endl;
            return 0;
        }
    /*if (strcmp(argv[1],"-init")==0){
        if (argv[2]==NULL){
            std::cerr << args_err << std::endl;
            return 1;
        }
        switch (createProject(argv[2])){
            case 0:{
                std::cout << "Project Created Successfully" << std::endl;
                return 0;
            }
            case 1:{
                std::cerr << "An error occured during project creation" << std::endl;
                return 1;
            }
        }
    }
    if (strcmp(argv[1],"-version")==0){
        using namespace std;
        cout << "chub version alpha-0.0.2-C++" << endl;
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
    */
}
}

int createProject(std::string str){
    if (!mkdir(str)) {
        std::string temp;
        strcpy(temp,str);
        strcat(temp,"\\footage");
        createSubFolder(temp);
        temp.clear();
        temp.copy(str);
        strcpy(temp,str);
        strcat(temp,"\\sfx");
        createSubFolder(temp);
        strcpy(temp,str);
        strcat(temp,"\\clips");
        createSubFolder(temp);
        return 0;
    } else {
        return 1;
    }
}

void createSubFolder(std::string name){
    if (mkdir(name)){
        std::cerr << "Couldn't create subfolder" << std::endl;
        return;
    }
}