#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <time.h>
#include <libgen.h>
#include <unistd.h>

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
void createNote(const char *folderName, const char *fileName);
void wipeProjectNote(const char *folderName, const char *fileName);
void globalNote(void);
void globalNoteWipe(void);
void openProjectnote(char *folderName,char *fileName);

const char username[]="admin";
const int pass=123456;
//username and password are temporary

bool auth;
bool moded;
bool cleanMode;

int main(void){
	readConfig();
	char userInput[100];
	while (strcmp(userInput,".exit")!=0){
		if (cleanMode==false){
			printf("%s\n",auth?"Admin mode":"User mode");
			printf("Use .help to show commands%s\n",auth?", use !help to show all admin commands":"");	
		}
		printf("> ");
		scanf("%s",userInput);
//		getchar();
//		fgets(userInput,100,stdin);
//		if (strlen(userInput)<99){
//			userInput[strlen(userInput)-1]='\0';
//		}
		switch (userInput[0]){
			case '.':{
				if (strcmp(userInput,".help")==0){
					printf(".help: shows available commands\n");
					printf(".cleanMode-on: enables clean mode\n");
					printf(".cleanMode-off: disables clean mode\n");
					printf(".clear: clears the console\n");
					printf(".authorise: enter username and password to access more features\n");
					printf(".project-n: create new project folder\n");
                    printf(".project-note-n: creates a note for a specific project\n");
                    printf(".project-note-o: opens project note file\n");
                    printf(".note-a: add notes to global note\n");
                    printf(".note-o: open global note file\n");
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
                if (strcmp(userInput,".project-note-n")==0){
                    char projectName[100];
                    char noteName[100];
                    printf("Give project name: ");
                    scanf("%s",projectName);
                    strcpy(noteName,projectName);
                    strcat(noteName,"_note.txt");
                    createNote(projectName,noteName);
                }
                if (strcmp(userInput,".note-a")==0){
                	globalNote();
				}
				if (strcmp(userInput,".cleanMode-on")==0){
					cleanMode=true;
				}
				if (strcmp(userInput,".cleanMode-off")==0){
					cleanMode=false;
				}
				if (strcmp(userInput,".note-o")==0){
					system("notes.txt");
				}
				if (strcmp(userInput,".project-note-o")==0){
					char projectName[100];
                    char noteName[100];
                    printf("Give project name: ");
                    scanf("%s",projectName);
                    strcpy(noteName,projectName);
                    strcat(noteName,"_note.txt");
                    openProjectnote(projectName,noteName);
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
						printf(".cleanMode-on: enables clean mode\n");
						printf(".cleanMode-off: disables clean mode\n");
						printf(".clear: clears the console\n");
						printf(".authorise: enter username and password to access more features\n");
						printf(".project-n: create new project folder\n");
                        printf(".project-note-n: creates a note for a specific project\n");
                        printf(".project-note-o: opens project note file\n");
                        printf(".note-a: add notes to global note\n");
                        printf(".note-o: open global note file\n");
						printf("!mods-enable: enables modding and creates a mods folder\n");
						printf("!cfg-update: reads the cfg file and updates the app accordingly\n");
						printf("!reset: resets the app to default\n");
						printf(".exit: exit the program\n");
					}
					if (strcmp(userInput,"!mods-enable")==0){
						createModsFolder();
					}
					if (strcmp(userInput,"!cfg-update")==0){
						readConfig();
					}
					if (strcmp(userInput,"!reset")==0){
						char selection;
						printf("Are you sure(y/n):");
						getchar();
						scanf("%c",&selection);
						switch (selection){
							case 'y':{
								auth=false;
								moded=false;
								cleanMode=false;
								writeToConfig();
								system("cls");
								printf("Reset successful\n");
								break;
							}
						}
						
					}	
				}
				break;
			}
			case '-':{
				if (strcmp(userInput,"-help")==0){
					printf("Debug commands:\n");
					printf("-help: shows debug commands\n");
					printf("-debug: Tries to write to config, wipes config and logs bug if it fails\n");
					printf("-wipecfg: Manually wipes the config file\n");
					printf("-wipeGlobalnotes: Wipes the contents of the global note file\n");
					printf("-wipeProjectNote: Wipes the contents of a note file of a specific project\n");
				}
				if (strcmp(userInput,"-debug")==0){
					system("cls");
					debug();
				}
				if (strcmp(userInput,"-wipecfg")==0){
					wipeConfig();
				}
				if (strcmp(userInput,"-wipeGlobalnotes")==0){
					globalNoteWipe();
				}
				if (strcmp(userInput,"-wipeProjectNote")==0){
					char projectName[100];
                    char noteName[100];
                    printf("Give project name: ");
                    scanf("%s",projectName);
                    strcpy(noteName,projectName);
                    strcat(noteName,"_note.txt");
					wipeProjectNote(projectName,noteName);
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
	fprintf(fptr,"auth:%d\nmoded:%d\ncleanMode:%d",auth?1:0,moded?1:0,cleanMode?1:0);
	fclose(fptr);
}

int readConfig(void){
	int temp_auth,temp_mod,temp_clean;
	FILE *fptr = fopen("config.cfg","r");
	if (fptr==NULL){
		printf("Error opening file\n");
		return -1;
	}
	fscanf(fptr,"auth:%d\nmoded:%d\ncleanMode:%d",&temp_auth,&temp_mod,&temp_clean);
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
	if (temp_clean==1){
		cleanMode=true;
	} else {
		cleanMode=false;
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
	if (feof(stdin)) {
	    printf("End of file encountered\n");
	    bugReport("Error_EOF_stdin\n");
	} else if (ferror(stdin)) {
	    printf("Error reading from stdin");
	    bugReport("Error_stdin\n");
	}

}

void createNote(const char *folderName, const char *fileName) {
    char currentDir[256];
    if (getcwd(currentDir, sizeof(currentDir)) == NULL) {
        perror("Error getting current working directory");
        exit(EXIT_FAILURE);
    }
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s/%s/%s", currentDir, folderName, fileName);
    FILE *file = fopen(fullPath, "a");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    char *buffer=(char*)malloc(512*sizeof(char));
    printf("Enter note text:\n");
    getchar();
    fgets(buffer,512,stdin);
    DATETIME current;
	current = getCurrentDateTime();
	fprintf(file,"%d/%d/%d %d:%d:%d\t",current.day,current.month,current.year,current.hour,current.minute,current.second);
    fprintf(file, "%s\n",buffer);
    fclose(file);
    free(buffer);
}

void globalNote(void) {
    char *text = (char *) malloc(512 * sizeof(char));
    printf("Enter text:\n");
    getchar();
    fgets(text, 512, stdin);
    FILE *fptr = fopen("notes.txt", "a");
    if (fptr == NULL) {
        printf("Error opening notes\n");
        free(text);
        return;
    }
	DATETIME current;
	current = getCurrentDateTime();
	fprintf(fptr,"%d/%d/%d %d:%d:%d\t",current.day,current.month,current.year,current.hour,current.minute,current.second);
	fputs(text,fptr);
	free(text);
	fclose(fptr);
}

void wipeProjectNote(const char *folderName, const char *fileName) {
    char currentDir[256];
    if (getcwd(currentDir, sizeof(currentDir)) == NULL) {
        perror("Error getting current working directory");
        exit(EXIT_FAILURE);
    }
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s/%s/%s", currentDir, folderName, fileName);
    FILE *file = fopen(fullPath, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
}
void globalNoteWipe(void){
	FILE *fptr = fopen("notes.txt","w");
	fprintf(fptr,"");
	fclose(fptr);
}

void openProjectnote(char *folderName,char *fileName){
	char currentDir[256];
    if (getcwd(currentDir, sizeof(currentDir)) == NULL) {
        perror("Error getting current working directory");
        exit(EXIT_FAILURE);
    }
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s/%s/%s", currentDir, folderName, fileName);
    system(fullPath);
}
