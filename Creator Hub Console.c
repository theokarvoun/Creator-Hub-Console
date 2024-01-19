#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void authorise(void);

const char username[]="admin";
const int pass=123456;
//username and password are temporary

bool auth = false;

int main(void){
	char userInput[100];
	do{
		printf("Use .help to show commands\n");
		printf("> ");
		gets(userInput);
		switch (userInput[0]){
			case '.':{
				if (strcmp(userInput,".help")==0){
					printf(".help: shows available commands\n");
					printf(".clear: clears the console\n");
					printf(".authorise: enter username and password to access more features\n");
					printf(".exit: exit the program\n");
				}
				if (strcmp(userInput,".clear")==0){
					system("cls");
				}
				if (strcmp(userInput,".authorise")==0){
					authorise();
				}
				break;
			}
			case '!':{
				if (auth==false){
					printf("Please use .authorise to access feature\n");
				} else {
					
				}
				break;
			}
		}
		
	} while (strcmp(userInput,".exit")!=0);
	
	return 0;
}

void authorise(void){
	char user[50];
	int password;
	printf("Enter username: ");
	gets(user);
	printf("Enter password: ");
	scanf("%d",&password);
	if ((strcmp(user,username)==0)&&(password==pass)){
		printf("Authorisation succesful\n");
		auth=true;
	} else {
		printf("Incorrect username or password\n");
	}
}