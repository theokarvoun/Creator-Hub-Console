#include <iostream>
#include <string>
#include <sys/stat.h>

#define args_err "More arguments needed"

int createProject(char *str);
void createSubFolder(char *name);

int main(int argc, char **argv){
    if (argc < 1){
        std::cerr << args_err << std::endl;
        return 1;
    }
    if (argv[1] == (std::string)"-init"){
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
    if (argv[1] == (std::string)"-version"){
        using namespace std;
        cout << "chub version alpha-0.0.3-C++" << endl;
        cout << "Made by theokarvoun" << endl;
        cout << "Check for newer versions on: https://github.com/theokarvoun/Creator-Hub-Console/tree/main/Commandlne_Version" << endl;
        return 0;
    }
    if ((argv[1] == (std::string)"-h") ||(argv[1] == (std::string)"-help")){
        using namespace std;
        cout << "-h or -help: shows commands" << endl;
        cout << "-version: displays the current version" << endl;
        cout << "-init <project name>: creates a new project folder in the current directory" << endl;
        cout << "-console: launches the console version of the app" << endl;
        return 0;
    }
    if (argv[1] == (std::string)"-console"){
        system("Creator-Hub-Console.exe");
        return 0;
    }
    if (argv[1] == (std::string)"-shell"){
        system("powershell");
        return 0;
    }
    return 0;
}


int createProject(char *str){
    if (!mkdir(str)){
        std::string temp;
        temp = str;
        temp.append("\\footage");
        //strcat(temp,"\\footage");
        createSubFolder((char *)&temp);
        temp.clear();
        temp = str;
        temp.append("\\sfx");
        //strcat(temp,"\\sfx");
        createSubFolder((char *)&temp);
        temp.clear();
        temp = str;
        temp.append("\\clips");
        //strcpy(temp,str);
        //strcat(temp,"\\clips");
        createSubFolder((char *)&temp);
        return 0;
    } else {
        return 1;
    }
}

void createSubFolder(char *name){
    if (mkdir((char *)&name)){
        std::cerr << "Couldn't create subfolder" << std::endl;
        return;
    }
}