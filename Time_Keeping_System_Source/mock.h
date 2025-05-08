#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define BASICSALARY  110000            //basic salary
#define MINUSMONEY   20000             //Money be minus

typedef struct _employee
{
    short iID;                        // Employee ID
    char sName[24];                   // Full name
    int iBasicSalary;                 // Basic salary
} employee;

//////SHOW ADMIN MODE AND NORMAL MODE//////

////Function to print feaures of admin mode to choose////
void FeatureOfAdminMenu(char cCharacter);

////Function to print features of normal mode to choose////
void FeatureOfNormalMenu(char cCharacter);

//////FUNCTIONS FOR ADMIN MODE //////

////Function use to check password right or wrong////
char CheckPassword(char sPassword[30], char sTempPassword[30]);

////Function to change password of admin to text file////
short ChangePassword();

////Function to add new employee////
short AddNewEmployee(employee *pEmployee);

////Function to view 3 information of all employees////
short ViewAllEmployees();

////Function to view working time of specified employee////
short ViewWorkingTimeOfSpecifiedEmployee();

////Function to calculate working time and minus money of each employee when they check out//// 
short CalculateWorkingHourPerDay(short iIDNeedToCheck);

//////Function to calculte salary for all employees//// 
short CalculateSalary();

//////FUNCTIONS FOR NORMAL MODE//////

////Funcion for employee to check in////
short UserCheckIn(short iIDNeedToCheck);

////Funcion to save data check in of each employee////
short SaveCheckIn(short iIDNeedToCheck);

////Funcion for employee to check out//// 
short UserCheckOut(short iIDNeedToCheck);

////Funcion to save data check out of each employee////
short SaveCheckOut(short iIDNeedToCheck);

////Function to check how many day in a month////
short CountNumberOfDays(int iMonth);