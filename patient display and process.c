#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patients
{
    int id;   //I chose integers for id (just in case), integer for age since we will compute the average and integer for test result to count positives
    int age;  // and negatives.
    int test;
    char symptom[20];
};

struct Patients *load_data(char *, int*);
void display_data(struct Patients*, int);
void process_data(struct Patients*, char *, int);

int main(int argc, char * argv[])
{
    int number_of_rows=0;

    struct Patients *pat;

    pat=load_data(argv[1], &number_of_rows);
    display_data(pat, number_of_rows);
    process_data(pat, argv[2], number_of_rows);



    return 0;
}

struct Patients* load_data(char *argument, int * number_of_rows)
{


    struct Patients *a1;

    int a=0, b=0, c=0;  //variables to count how many lines are there in the file. Not important variables.
    char d[20];
    int x; //used in for loop to populate structure

    FILE *openfile;

    openfile=fopen(argument, "r");

    if(openfile==NULL)
    {
        printf("Couldn't open file!");
        exit(1);
    }

    while(fscanf(openfile,"%d %d %d %s", &a, &b, &c, d)!=EOF)
    {
        (*number_of_rows)++;
    }

    a1=(struct Patients*)malloc((*number_of_rows)*sizeof(struct Patients*)); //dynamic memory allocation

    rewind(openfile);

    for(x=0; x<*number_of_rows; x++)
    {
        fscanf(openfile,"%d %d %d %[^\n]", &a1[x].id, &a1[x].age, &a1[x].test, a1[x].symptom);
    }

    fclose(openfile);





    return a1;
}

void display_data(struct Patients *patient, int number_of_rows)
{
    printf("\nYour daha is succesfully processed and looks as follows:\n");
    int x;
    printf("ID\t Age\t Test\t Symptom\t\n");
    for(x=0; x<number_of_rows; x++)
    {
        printf("%d \t %d \t %d \t %s \n", patient[x].id, patient[x].age, patient[x].test, patient[x].symptom);
    }
}

void process_data(struct Patients *a1, char* argument,int number_of_rows)
{
    printf("\nStatistics are as follows:\n");
    int x, positive, negative, none, headache, fatigue;
    float average, total;
    FILE *write;

    write=fopen(argument, "w");

    for(x=0; x<number_of_rows; x++)
    {
        total=total+a1[x].age;
        if(a1[x].test==0)
        {
            negative++;
        }
        else if(a1[x].test==1)
        {
            positive++;
        }
        if(strcmp(a1[x].symptom,"None")==0)
        {
            none++;
        }
        if(strcmp(a1[x].symptom,"Headache")==0)
        {
            headache++;
        }
        if(strcmp(a1[x].symptom,"Fatigue")==0)
        {
            fatigue++;
        }
    }
    average=total/number_of_rows;

    printf("\nAverage age: %.2f", average);
    printf("\n%d positive and %d negative patients", positive, negative);
    printf("\n%d None, %d Headache and %d fatigue symptoms.", none, headache, fatigue);

    fprintf(write,"Average:%.2f \nPositive:%d \t Negative:%d \nNone:%d \t Headache:%d \t Fatigue:%d", average, positive, negative, none, headache, fatigue);

    printf("\n%s is also updated!", argument);



    fclose(write);

}
