#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define COLUMNS 10
int main()
{
    float *sums=malloc(sizeof(float) * COLUMNS);
    FILE * finput=fopen("movie_database.txt","r");
    char movie_dtbs[COLUMNS][345];
    int a =0;
    while(fgets(movie_dtbs[a],345,finput)){
        a++;
    }
    fclose(finput);
    int count0=-1;
    char line0[345];
    finput=fopen("user_ratings.txt","r");
    while(fgets(line0,345,finput)){
        count0++;
    }
    rewind(finput);
    float **arr=malloc(sizeof(float *) * count0);
    int row=0;
    for(int i=0;i<count0;i++)
        arr[i]=malloc(sizeof(float)*COLUMNS);
    fgets(line0,345,finput);
    while(!feof(finput)){
        for(int j=0;j<COLUMNS;j++){
            if((fscanf(finput,"%f",&arr[row][j]))==EOF)
                break;
        }
        row++;
        if (row==count0) break;
    }
    fclose(finput);
    int choice;
    do{
    bool b1=true;
    int counter=1;
    char name[45];
    mainMenu();
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
                    rewind(fpointer);
                    break;
                }
                else{
                b1=false;
                continue;
                }
            }
        }
        rewind(fpointer);
        while(fgets(line,355,fpointer)){
                counter++;
            }
        rewind(fpointer);
        count0=counter;
        fpointer=fopen("user_data.txt","a");
        fprintf(fpointer,"\n%s %d",name,counter);
        printf("User %s is successfully registered.\n",name);
        fclose(fpointer);
        arr=realloc(arr,sizeof(float *) * count0);
        arr[count0-1]=malloc(sizeof(float)*COLUMNS);
        for(int i=0;i<COLUMNS;i++){
           arr[count0-1][i]=0;
        }
        fpointer=fopen("user_ratings.txt","w");
        fprintf(fpointer,"%d %d \n",count0,COLUMNS);
        for(int i=0;i<count0;i++){
            for(int j=0;j<COLUMNS;j++){
              fprintf(fpointer,"%f ",arr[i][j]);
            }
            fprintf(fpointer,"\n");
        }
        fclose(fpointer);
        break;
    case 2:
         movieDataBase();
        break;
    case 3:
        b1=true;
        int count1=-1;
        char line3[345];
        printf("Enter your username : ");
        scanf("%s",&name);
        FILE *fpointer3=fopen("user_data.txt","r");
        while(fgets(line3,345,fpointer3)){
            count1++;
            char copy1[355];
            char d1[]=" ";
            strcpy(copy1,line3);
            char *p2=strtok(copy1,d1);
            if(strcmpi(name,p2)==0){
                b1=true;
                break;
            }
            else{
                b1=false;
                continue;
            }
        }
        if(b1==false){
            printf("User not found. Please register first.\n");
            continue;
        }
        movieDataBase();
        printf("Enter the number of the movie you want to rate: ");
        int choice1;
        scanf("%d",&choice1);
        while(!(choice1>=1&&choice1<=10)){
            printf("There are no movies at this number.Please enter a valid index for a movie. ");
            scanf("%d",&choice1);
        }
        printf("Enter your rating (1-5): ");
        int choice2;
        scanf("%d",&choice2);
        while(!(choice2>=1&&choice2<=5)){
            printf("Invalid rating. Please enter a rating between 1 and 5. ");
            printf("Enter your rating (1-5): ");
            scanf("%d",&choice2);
        }
        arr[count1][choice1-1]=(float)choice2;
        fclose(fpointer3);
        fpointer3=fopen("user_ratings.txt","w");
        fprintf(fpointer3,"%d %d \n",count0,COLUMNS);
        for(int i=0;i<count0;i++){
            for(int j=0;j<COLUMNS;j++){
              fprintf(fpointer3,"%f ",arr[i][j]);
            }
            fprintf(fpointer3,"\n");
        }
        printf("Rating recorded successfully.\n");
        fclose(fpointer3);
        break;
    case 4:
        b1=true;
        int count4=-1;
        char line4[345];
        printf("Enter your username : ");
        scanf("%s",&name);
        FILE *fpointer4=fopen("user_data.txt","r");
        while(fgets(line4,345,fpointer4)){
            count4++;
            char copy4[355];
            char d4[]=" ";
            strcpy(copy4,line4);
            char *p4=strtok(copy4,d4);
            if(strcmpi(name,p4)==0){
                b1=true;
                break;
            }
            else{
                b1=false;
                continue;
            }
        }
        if(b1==false){
            printf("User not found. Please register first.\n");
            continue;
        }
        fclose(fpointer4);
        for(int k=0;k<COLUMNS;k++){
            sums[k]=0;
            for(int j=0;j<count0;j++){
                if(j==count4)
                    continue;
                for(int i=0;i<COLUMNS;i++){}
                sums[k]+=(arr[j][k])/(count0-1);
            }
        }
        printf("\n***** Recommended Movies *****\n");
        for(int i=0;i<COLUMNS;i++){
            if(arr[count4][i]==0){
                printf("%s Predicted rating: %.1f \n",movie_dtbs[i],sums[i]);
            }
        }
        break;
    break;
    }
    }while(choice!=0);
    free(sums);
    for(int i=0;i<count0;i++)
        free(arr[i]);
    free(arr);
    return 0;
}
void mainMenu(){
    printf("***** Movie Recommendation System *****\n1. Register User\n2. Display Movies\n3. Rate a Movie\n4. Get Movie Recommendations\n0. Exit\nEnter your choice: ");
}
void movieDataBase(){
    printf("***** Movie Database *****\n");
    char line2[345];
    int g=1;
    FILE *fpointer2=fopen("movie_database.txt","r");
    while(fgets(line2,345,fpointer2)){printf("%d.%s",g,line2);g++;}
    fclose(fpointer2);
    }
