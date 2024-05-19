#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int main()
{
    bool b1=true;
    int choice;
    int counter=0;
    mainMenu();
    char name[45];
    scanf("%d", &choice);
    switch(choice){
    case 1:
        printf("Please enter a name\n");
        scanf("%s",&name);
        char line[355];
        FILE * fpointer=fopen("user_data.txt","r");
        while(b1){
            while(fgets(line,355,fpointer)){
                char copy[355];
                char d[]=" ";
                strcpy(copy,line);
                char *p1=strtok(copy,d);
                if(strcmpi(p1,name)==0){
                    b1=true;
                    printf("User already exists. Please choose a different name.\n");
                    scanf("%s",&name);
                    break;
                }
                else{
                b1=false;
                continue;
                }
            }
        }
        /*while(fgets(line,355,fpointer)){
                counter++;
            }
        printf("%d",counter);
        fpointer=fopen("user_data.txt","a");
        fputs(name,fpointer);
        fclose(fpointer);*/
        break;
    case 2: break;
    case 3: break;
    case 4: break;
    case 5: exit(0);
    break;
    }
    return 0;
}
void mainMenu(){
    printf("***** Movie Recommendation System *****\n1. Register User\n2. Display Movie\n3. Rate a Movie\n4. Get Movie Recommendations\n0. Exit\nEnter your choice:");
}
