#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

void authorise(void);
void createProject(void);
void createModsFolder(void);
void writeToConfig(void);
void readConfig(void);

const char username[]="admin";
const int pass=123456;
//username and password are temporary

bool auth;
bool moded;

int main(void){
	readConfig();
	char userInput[100]={0};
	while (strcmp(userInput,".exit")!=0){
		printf("%s\n",auth?"Admin mode":"User mode");
		printf("Use .help to show commands%s\n",auth?", use !help to show all admin commands":"");
		printf("> ");
		scanf("%s",userInput);
//		fgets(userInput,100,stdin);
//		if (strlen(userInput)<99){
//			userInput[strlen(userInput)-1]='\0';
//		}
		switch (userInput[0]){
			case '.':{
				if (strcmp(userInput,".help")==0){
					printf(".help: shows available commands\n");
					printf(".clear: clears the console\n");
					printf(".authorise: enter username and password to access more features\n");
					printf(".project-n: create new project folder\n");
					printf(".exit: exit the program\n");
				}
				if (strcmp(userInput,".clear")==0){
					system("cls");
				}
				if (strcmp(userInput,".authorise")==0){
					authorise();
				}
				if (strcmp(userInput,".project-n")==0){
					createProject();
				}
				break;
			}
			case '!':{
				if (auth==false){
					printf("Please use .authorise to access feature\n");
				} else {
					if (strcmp(userInput,"!help")==0){
						printf(".help: shows available commands\n");
						printf("!help: shows all commands\n");
						printf(".clear: clears the console\n");
						printf(".authorise: enter username and password to access more features\n");
						printf(".project-n: create new project folder\n");
						printf("!mods-enable: enables modding and creates a mods folder\n");
						printf(".exit: exit the program\n");
					}
					if (strcmp(userInput,"!mods-enable")==0){
						createModsFolder();
					}	
				}
				break;
			}
			default:{
				printf("Invalid command\n");
				break;
			}
		}
		
	}
	writeToConfig();
	return 0;
}

void authorise(void){
	char user[50];
	int password;
	printf("Enter username: ");
//	fgets(user,50,stdin);
//	if (strlen(user)<49){
//		user[strlen(user)-1]='\0';
//	}
	scanf("%s",user);
	printf("Enter password: ");
	scanf("%d",&password);
	if ((strcmp(user,username)==0)&&(password==pass)){
		printf("Authorisation succesful\n");
		auth=true;
	} else {
		printf("Incorrect username or password\n");
	}
}

void createProject(void){
	char folderName[100];
    printf("Enter the project name: ");
    scanf("%s", folderName);
    if (mkdir(folderName) == 0) {
        printf("Project '%s' created successfully.\n", folderName);
    } else {
        printf("Project to create folder '%s'.\n", folderName);
    }
}

void createModsFolder(void){
	if (moded){
		printf("Mods folder already exists\n");
		return;
	}
    if (mkdir("mods") == 0) {
        printf("Mods folder created successfully.\n");
        moded=true;
    } else {
        printf("Failed to create mods folder.\n");
    }
}

void writeToConfig(void){
	FILE *fptr = fopen("config.txt","w");
	fprintf(fptr,"auth:%d\nmoded:%d",auth?1:0,moded?1:0);
	fclose(fptr);
}

void readConfig(void){
	int temp_auth,temp_mod;
	FILE *fptr = fopen("config.txt","r");
	fscanf(fptr,"auth:%d\nmoded:%d",&temp_auth,&temp_mod);
	fclose(fptr);
	if (temp_auth==1){
		auth=true;
	} else {
		auth=false;
	}
	if (temp_mod==1){
		moded=true;
	} else {
		moded=false;
	}
}
