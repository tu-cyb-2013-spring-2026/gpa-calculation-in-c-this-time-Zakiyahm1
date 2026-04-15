#include <stdio.h>
#include <string.h>

//These put a constraint on the amount stored/what auser can input
#define MAX_SEMESTERS 100
#define LINE_SIZE 100

typedef struct//Keeps all related categories together deeper within code
{
    char semester[10];
    int year;
    int total_hours;
    float total_points;
} 
    SemesterRecord;


int main()
{
    SemesterRecord records[MAX_SEMESTERS];
    int semester_count = 0;

    //Keeps track of overall GPA
    int total_hours = 0;
    float total_points = 0.0;

    //Stores whatever the user input is so long as it does not exceed 100 characters
    char line[LINE_SIZE];

    printf("----> To quit entering grades, enter a blank line.\n");

    while(1) {
    char grade;
    int hours;
    char semester[10];
    int year;

    float points;
    float quality_points; //grade points * credit hours
    int found = 0; //This is to see if a certain semester is already in the array
    
    printf("Enter a letter grade and hours for a course with its year and semester: ");
     if (fgets(line, sizeof(line), stdin) == NULL) { //Use fgets to read the full line
            break;
        }
        if (line[0] == '\n') { //Checks for a blank line
            break;
        }
        if (scanf(" %c %d %9s %d", &grade, &hours, semester, &year) != 4) { //Takes out 4 pieces within the line that match each variable, if it can not get the 4 pieces, then the code is invalid
            printf("Invalid input.\n");
            continue;
        }

        if (grade == 'A'|| grade == 'a') points = 4.0;
        else if (grade == 'B' || grade == 'b') points = 3.0;
        else if (grade == 'C' || grade == 'c') points = 2.0;
        else if (grade == 'D' || grade == 'd') points = 1.0;
        else if (grade == 'F' || grade == 'f') points = 0.0;
        else{
            printf("Invalid grade\n");
            continue;
        }

        quality_points = points * hours;
        total_hours += hours;
        total_points += quality_points;

     for (int i = 0; i < semester_count; i++) //Checking to see if a semester has already been stored
        {
            if (strcmp(records[i].semester, semester) == 0 && records[i].year == year) //Checks if the semester and year match the input
            {
                records[i].total_hours += hours;
                records[i].total_points += quality_points;
                found = 1;
                break;
            }
        }

        if (found == 0) //If it was not found, I make a new semester record that includes the new data
        {
            strcpy(records[semester_count].semester, semester);
            records[semester_count].year = year;
            records[semester_count].total_hours = hours;
            records[semester_count].total_points = quality_points;
            semester_count++;
        }
    }
printf("\n-------------------------------------\n");
printf("Unofficial Transcript\n");

 for (int i = 0; i < semester_count; i++) //Prints each semesters GPA
    {
        printf("%-6s %4d (%d hours) %.3f\n",
               records[i].semester,
               records[i].year,
               records[i].total_hours,
               records[i].total_points / records[i].total_hours); //Total GPA formuala
    }
 printf("\n--\n");
 printf("Total credit hours: %d\n", total_hours);

if (total_hours > 0) {
    printf("Overall GPA: %.3f\n", total_points / total_hours);
    }
    else {
    printf("Overall GPA: 0.000\n");
    }
printf("-------------------------------------\n");

return 0;

}
