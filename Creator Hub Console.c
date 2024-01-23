#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <time.h>

typedef struct DateTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
}DATETIME;

void authorise(void);
void createProject(void);
void createModsFolder(void);
void writeToConfig(void);
int readConfig(void);
void wipeConfig(void);
void bugReport(char *reason);
DATETIME getCurrentDateTime(void);
void debug(void);

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
					writeToConfig();
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
						printf("!cfg-update: reads the cfg file and updates the app accordingly\n");
						printf(".exit: exit the program\n");
					}
					if (strcmp(userInput,"!mods-enable")==0){
						createModsFolder();
					}
					if (strcmp(userInput,"!cfg-update")){
						readConfig();
					}	
				}
				break;
			}
			case '-':{
				if (strcmp(userInput,"-debug")){
					system("cls");
					debug();
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

void bugReport(char *reason){
	FILE *fptr = fopen("bugreport.txt","a");
	DATETIME current = getCurrentDateTime();
	fprintf(fptr,"%d/%d/%d | %d:%d:%d | %s",current.day,current.month,current.year,current.hour,current.minute,current.second,reason);
	fclose(fptr);
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
	FILE *fptr = fopen("config.cfg","w");
	if (fptr==NULL){
		printf("Error opening file\n");
		return;
	}
	fprintf(fptr,"auth:%d\nmoded:%d",auth?1:0,moded?1:0);
	fclose(fptr);
}

int readConfig(void){
	int temp_auth,temp_mod;
	FILE *fptr = fopen("config.cfg","r");
	if (fptr==NULL){
		printf("Error opening file\n");
		return -1;
	}
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
	return 0;
}

DATETIME getCurrentDateTime(void){
	struct DateTime currentDateTime;
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    currentDateTime.year = localTime->tm_year + 1900;
    currentDateTime.month = localTime->tm_mon + 1;
    currentDateTime.day = localTime->tm_mday;
    currentDateTime.hour = localTime->tm_hour;
    currentDateTime.minute = localTime->tm_min;
    currentDateTime.second = localTime->tm_sec;
    return currentDateTime;
}

void wipeConfig(void){
	FILE *fptr = fopen("config.cfg","w");
	if (fptr==NULL){
		printf("Error opening file\n");
		return;
	}
	fprintf(fptr,"NULL");
	fclose(fptr);
}

void debug(void){
	int count=0;
	system("cls");
	while (readConfig()==-1&&count<5){
		writeToConfig();
		count++;
	}
	if (count==5){
		wipeConfig();
		bugReport("Error_Failed_To_Read_Config\n");
	}
}
