#include "mock.h"

extern FILE* fpPassword;                             //Text file of password
extern FILE* fpInformationOfEmployee;        //Text file of 3 information of each employee
extern FILE* fpCheckinAndCheckout;           //Text file save data of check in and check out
extern FILE* fpWorkingTimePerDay;            //Text file save working time per day of each employee
extern FILE* fpCalculateSalary;              //Text file save salary of each employee

extern employee *pEmployee;


extern char cCharacter;                       //Variable to choose admin mode or normal mode
extern char sPassword[30];                    //User enter password for admin mode
extern char sTempPassword[30];                //Variable get password value from file text to check with input of user (Admin mode - feature 1)
extern short iIDNeedToCheck ;                 //Variable is ID used to check in (Normal mode - check in)



////Function to print feaures of admin mode to choose////
void FeatureOfAdminMenu(char cCharacter)
{
    while(1)
    {
        //AdminMenu:
        system("cls");
        printf(">> ADMIN MODE << \n\n");
        printf("1. Change admin password\n");
        printf("2. Add employee\n");
        printf("3. View information of all employees\n");
        printf("4. View working time of a specified employee\n");
        printf("5. Calculate salary for all employees\n");
        printf("6. Exit to main menu\n");
        printf("\nEnter character: ");
        scanf("%c", &cCharacter);
        getchar();

        //Exit to main menu
        if(cCharacter == '6')
        {
            break;
        }

        switch (cCharacter)
        {
            //Change admin password
            case '1':
            system("cls");
            ChangePassword();
            break;

            //Add new employee
            case '2':
            system("cls");
            AddNewEmployee(pEmployee);
            break;

            //View all employees
            case '3':
            system("cls");
            ViewAllEmployees();
            break;

            //View working time of specified employee
            case '4':
            system("cls");
            ViewWorkingTimeOfSpecifiedEmployee();
            break;

            //Calculate salary for all employee 
            case '5':
            system("cls");
            CalculateSalary();
            break;

            //Wrong character 
            default:
            printf("\nInvalid character! Input again.\nPress Enter to continue.\n");
            getchar();
            break;
        }
    }

}


///////////////////ADMIN MODE///////////////////////

////Function to print features of normal mode to choose////
void FeatureOfNormalMenu(char cCharacter)
{
    while(1)
    {
        system("cls");
        printf(">> NORMAL MODE << \n\n");
        printf("1. Check in\n");
        printf("2. Check out\n");
        printf("3. Exit to main menu\n");
        printf("\nEnter character: ");
        scanf("%c", &cCharacter);
        getchar();

        //Exit to main menu
        if(cCharacter == '3')
        {
            break;
        }

        switch (cCharacter)
        {
            //Check in
            case '1':
            system("cls");
            UserCheckIn(iIDNeedToCheck);
            break;

            //Check out
            case '2':
            system("cls");
            UserCheckOut(iIDNeedToCheck);
            break;

            //Wrong character
            default:
            printf("\nInvalid character! Input again.\nPress Enter to continue.\n");
            getchar();
            break;
        }
    }
}


////Function use to check password right or wrong////
char CheckPassword(char sPassword[30], char sTempPassword[30])
{
    char cTemp = 0;
    char cIndex = 0;                                               //Count how many character in new password
    char cTempValueIndex = 0;
    char cCount = 0;
    char cLengthOfPassword = 0;

    cLengthOfPassword = strlen(sPassword);                  //Count how many character in name

    //Loop through all character of password user input
    for(cCount = 0; cCount < cLengthOfPassword; cCount++)
    {
        //Check each character of password user input with password in text file
        if(sPassword[cCount] == sTempPassword[cLengthOfPassword - 1 - cCount] - 24)           //Reverse characters in text file
        {
            cTemp++;                                                                   //If each character same -> this variable++ 
        }

    }

    //If all characters are right -> go to Admin Menu
    if(cTemp == strlen(sTempPassword))                 
    {
        return 1;
    }

    //If wrong -> Enter password again
    if(cTemp != strlen(sTempPassword))                 
    {
        return 0;
    }

}

////Function to change password of admin to text file////
short ChangePassword()
{
    char sChangePassword[30];                                      //New password that user enter
    memset(sChangePassword, 0, 30);
    char cIndex = 0;                                               //Count how many character in new password
    char cTempValueIndex = 0;                                      //Variable to swap all character in new password

    fpPassword = fopen("Password.txt", "w+");                              //Open text file of password

    if(fpPassword == NULL)
    {
        printf("\t\t\t\tThe file could not be opened, or the file has no data.\n");
        fclose(fpPassword);
        return 1;
    }
    
    while(1)
    {
        printf("Enter new password (maximum 30 character): ");
        gets(sChangePassword);

        while(sChangePassword[cIndex] != 0)                            //count how many character in name
        {
            cIndex++;
        }

        //If Index <= 30 characters -> password is ok
        if(cIndex <= 30)
        {
            break;   
        }

        //If Index > 30 characters -> password is invalid
        if(cIndex > 30)
        {
            cIndex = 0;
            printf("\nInvalid length! Enter new password again.\nPress Enter to continue.\n");
            getchar();
            system("cls");
        }

    }

    //Reverse all character
    for(char cCount = 0; cCount < (cIndex / 2); cCount++)
    {
        cTempValueIndex = sChangePassword[cCount];
        sChangePassword[cCount] = sChangePassword[cIndex - 1 - cCount];
        sChangePassword[cIndex - 1 - cCount] = cTempValueIndex;
    }

    //Each character + 24
    for(char cCount = 0; cCount < cIndex ; cCount++)
    {
        sChangePassword[cCount] = sChangePassword[cCount] + 24;
    }

    fputs(sChangePassword, fpPassword);                                    //Save new password to file
    fclose(fpPassword);                                                    //Close file text of password

    printf("\nPassword changed.\n");
    printf("\nPress Enter to continue.\n");
    getchar();
}

////Function to add new employee////
short AddNewEmployee(employee *pEmployee)
{
    unsigned short iIdOfEmployee = 0;                                                    //Variable take ID of employee
    char sTemp[100];                                                                     //Loop through each employee
    char cIndex = 0;                                                                     //Index in string of full name to check length of full name

    fpInformationOfEmployee = fopen("Information_Of_Employee.txt", "r+");                                    //Open text file take 3 information of each employee

    if(fpInformationOfEmployee == NULL)
    {
        printf("\t\t\t\tThe file could not be opened, or the file has no data.\n");
        fclose(fpInformationOfEmployee);
        return 1;
    }

    pEmployee = NULL;
    pEmployee = malloc(sizeof(employee));

    //Loop through entire text file to check how many employee in file
    while(fgets(sTemp, 100, fpInformationOfEmployee) != NULL)
    {
        iIdOfEmployee++;
    }

    //Enter ID
    pEmployee -> iID = iIdOfEmployee + 1;                                       //Set new ID for new employee
    printf("ID: %d\n", pEmployee -> iID);
 
    //Enter full name
    while(1)
    {
        printf("Full Name: ");
        gets(pEmployee -> sName);

        //count how many character in name
        while(pEmployee -> sName[cIndex] != 0)                                  
        {
            cIndex++;
        }

        //If Index <= 24 characters -> full name is ok
        if(cIndex <= 24)
        {
            break;   
        }

        //If Index > 24 characters -> full name is invalid
        if(cIndex > 24)
        {
            cIndex = 0;
            printf("\nInvalid length! Enter full name again.\nPress Enter to continue.\n");
            getchar();
        }
    }
    
    //Enter basic salary
    printf("Basic Salary (VND): ");
    scanf("%d", &(pEmployee -> iBasicSalary));
    getchar();

    //Write data of new employee to text file
    fprintf(fpInformationOfEmployee, "%d _ %s _ %d\n", pEmployee -> iID, pEmployee -> sName, pEmployee -> iBasicSalary);  

    //Print information of new employeeonn terminal
    printf("\nInformation of new employee: %d _ %s _ %d VND\n\nPress Enter to continue.\n", pEmployee -> iID, pEmployee -> sName, pEmployee -> iBasicSalary);
    getchar();
    fclose(fpInformationOfEmployee);
    free(pEmployee);
 
}

////Function to view 3 information of all employees////
short ViewAllEmployees()
{
    char sTemp[100];                                                     //Loop through each employee
    fpInformationOfEmployee = fopen("Information_Of_Employee.txt", "r+");                    //Open text file 3 information of all employees

    if(fpInformationOfEmployee == NULL)
    {
        printf("\t\t\t\tThe file could not be opened, or the file has no data.\n");
        fclose(fpInformationOfEmployee);
        return 1;
    }

    //Loop througn all file, print each line of file is information of each employee
    while(fgets(sTemp, 100, fpInformationOfEmployee) != NULL)
    {
        printf("%s\n", sTemp);
    }

    fclose(fpInformationOfEmployee);
    printf("\n\nPress Enter to continue.");
    getchar();
}


///////////////////NORMAL MODE///////////////////////

////Funcion for employee to check in//// 
short UserCheckIn(short iIDNeedToCheck)
{
    EnterIdTocheckIn:
    system("cls");
    fpInformationOfEmployee = fopen("Information_Of_Employee.txt", "r+");                         //Open text file 3 information of all employees   

    if(fpInformationOfEmployee == NULL)
    {
        printf("\t\t\t\tThe file could not be opened, or the file has no data.\n");
        fclose(fpInformationOfEmployee);
        return 1;
    } 

    unsigned short iTempID = 0;                                                        //Variable take ID from text file to check wih ID user input
    char sTemp[100];                                                          //Loop through each employee
    char cYesOrNo;                                                            //Variable for user to check informaion right or wrong
    
    printf("Enter Empoyee ID: ");
    scanf("%d", &iIDNeedToCheck);
    getchar();

    while(fscanf(fpInformationOfEmployee, "%d _ %24[^_] %*s %*s", &iTempID ,sTemp) != -1)                            //Check informaion from ID user input
    {
    
        //If ID exist -> save check in
        if(iTempID == iIDNeedToCheck)
        {
            printf("%d _ %s\n", iIDNeedToCheck, sTemp);
            printf("\nIs this you? (y/n): ");                                           //If right -> check in. If wrong -> input ID again
            scanf("%c", &cYesOrNo);
            getchar();

            if(cYesOrNo == 'y')                                                          //If right -> check in
            {
                SaveCheckIn(iIDNeedToCheck); 
                break; 
            }

            else if  (cYesOrNo == 'n')                                                //If wrong -> input ID again
            {
                system("cls");
                goto EnterIdTocheckIn;
            }
        }

    }

    fclose(fpInformationOfEmployee);

    //If ID don't exist -> enter ID again
    if(iTempID != iIDNeedToCheck)
    {
        printf("\nInvalid ID! Input ID again.\nPress Enter to continue.\n");
        getchar();
        goto EnterIdTocheckIn;
    }
    
}


////Funcion to save data check in of each employee////
short SaveCheckIn(short iIDNeedToCheck)
{
    int iMoneyPerDay = 0;
    short iHourInDay = 0;
    short iMinuteInDay = 0;

    fpCheckinAndCheckout = fopen("Checkin_Checkout_History.txt", "a+");        //Open text file save check in time of each employee

    if(fpCheckinAndCheckout == NULL)
    {
        printf("\t\t\t\tThe file could not be opened, or the file has no data.\n");
        fclose(fpCheckinAndCheckout);
        return 1;
    }

    fprintf(fpCheckinAndCheckout, "%d _ ", iIDNeedToCheck);

    struct tm TimeSetToCheckIn;                        //Set check in time (Function in time.h library)
    TimeSetToCheckIn.tm_min    = 30;                   //Minute set for check in 
    TimeSetToCheckIn.tm_hour   = 8;                    //Hour set for check in

    //gmtime() function of time.h library
    time_t tCurrenttime;
    time(&tCurrenttime);
    struct tm* plocaltime = localtime(&tCurrenttime);

    //If sooner than 8h AM -> CHECK IN ON TIME
    if(plocaltime->tm_hour < TimeSetToCheckIn.tm_hour)        
    {
        printf("You checked in on time.\n\n");

        printf("%d/%d/%d/%d _ %d : %02d\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min);

        //Save check in time of each employee to text file
        fprintf(fpCheckinAndCheckout, "%d/%d/%d/%d _ %d : %02d _ %d _ in.\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min, iMoneyPerDay); 
    }

    //If hour at 8h AM -> CHECK MINUTE
    else if(plocaltime->tm_hour == TimeSetToCheckIn.tm_hour)
    {

        //If minute sooner or equal to 30 minutes -> CHECK IN ON TIME
        if(plocaltime->tm_min <= TimeSetToCheckIn.tm_min)
        {
            printf("You checked in on time.\n\n");

            printf("%d/%d/%d/%d _ %d : %02d\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min);

            //Save check in time of each employee to text file
            fprintf(fpCheckinAndCheckout, "%d/%d/%d/%d _ %d : %02d _ %d _ in.\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min, iMoneyPerDay); 
        }

        //If minute greater than 30 minutes -> CHECK IN LATE
        else
        {
            printf("You checked in late.\n\n");
            iMoneyPerDay = MINUSMONEY;

            printf("%d/%d/%d/%d _ %d : %02d\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min);

            //Save check in time of each employee to text file
            fprintf(fpCheckinAndCheckout, "%d/%d/%d/%d _ %d : %02d _ %d _ in.\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min, iMoneyPerDay); 
        }

    }

    //If hour greater than 8h AM -> CHECK IN LATE
    else if((plocaltime->tm_hour > TimeSetToCheckIn.tm_hour) && (plocaltime->tm_hour < 12))
    {
        printf("You checked in late.\n\n");
        iMoneyPerDay = MINUSMONEY;

        printf("%d/%d/%d/%d _ %d : %02d\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min);

        //Save check in time of each employee to text file
        fprintf(fpCheckinAndCheckout, "%d/%d/%d/%d _ %d : %02d _ %d _ in.\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min, iMoneyPerDay); 
    }

    //If hour greater than 12h PM and smaller than 13h PM -> CHECK IN TOO LATE
    else if(plocaltime->tm_hour >= 12 && plocaltime->tm_hour < 13)
    {
        printf("You checked in too late.\n\n");
        iHourInDay = 13;
        iMinuteInDay = 0;
        iMoneyPerDay = 0;

        printf("%d/%d/%d/%d _ %d : %02d\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, iHourInDay, iMinuteInDay);

        //Save check in time of each employee to text file
        fprintf(fpCheckinAndCheckout, "%d/%d/%d/%d _ %d : %02d _ %d _ in.\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, iHourInDay, iMinuteInDay, iMoneyPerDay); 
    }

    //If hour greater than 13h PM -> CHECK IN TOO LATE
    else if(plocaltime->tm_hour >= 13)
    {
        printf("You checked in too late.\n\n");
        iMoneyPerDay = 0;

        printf("%d/%d/%d/%d _ %d : %02d\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min);

        //Save check in time of each employee to text file
        fprintf(fpCheckinAndCheckout, "%d/%d/%d/%d _ %d : %02d _ %d _ in.\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min, iMoneyPerDay); 
        
    }
    
    fclose(fpCheckinAndCheckout);

    printf("\nPress Enter to continue");
    getchar();
}


////Funcion for employee to check out//// 
short UserCheckOut(short iIDNeedToCheck)
{
    EnterIdTocheckOut:
    system("cls");
    fpInformationOfEmployee = fopen("Information_Of_Employee.txt", "r+");                                  //Open text file 3 information of all employees 
         
    if(fpInformationOfEmployee == NULL)
    {
        printf("\t\t\t\tThe file could not be opened, or the file has no data.\n");
        fclose(fpInformationOfEmployee);
        return 1;
    }

    short iTempID = 0;                                                                 //Variable take ID from text file to check wih ID user input
    char sTemp[100];                                                                   //Loop through each employee
    char cYesOrNo;                                                                     //Variable for user to check informaion right or wrong
    
    printf("Enter Empoyee ID: ");
    scanf("%d", &iIDNeedToCheck);
    getchar();

    while(fscanf(fpInformationOfEmployee, "%d _ %24[^_] %*s %*s", &iTempID ,sTemp) != -1)                 //Check informaion from ID user input
    {
       
        //If ID exist -> save check in
        if(iTempID == iIDNeedToCheck)
        {
            printf("%d _ %s\n", iIDNeedToCheck, sTemp);
            printf("\nIs this you? (y/n): ");                                           //If right -> check in. If wrong -> input ID again
            scanf("%c", &cYesOrNo);
            getchar();

            if(cYesOrNo == 'y')                                                          //If right -> check in
            {
                SaveCheckOut(iIDNeedToCheck);  
                break;
            }

            else if  (cYesOrNo == 'n')                                                  //If wrong -> input ID again
            {
                system("cls");
            }

        }    

    }

    fclose(fpInformationOfEmployee);

    //If ID don't exist -> enter ID again
    if(iTempID != iIDNeedToCheck)
    {
        printf("\nInvalid ID! Input ID again.\nPress Enter to continue.\n");
        getchar();
        goto EnterIdTocheckOut;
    }
    
}


////Funcion to save data check out of each employee////
short SaveCheckOut(short iIDNeedToCheck)
{
    int iMoneyPerDay = 0;                                                              //Variable take value of minus money
    short iHourInDay = 0;
    short iMinuteInDay = 0;

    fpCheckinAndCheckout = fopen("Checkin_Checkout_History.txt", "a+");                                        //Open text file save check in time of each employee

    if(fpCheckinAndCheckout == NULL)
    {
        printf("\t\t\t\tThe file could not be opened, or the file has no data.\n");
        fclose(fpCheckinAndCheckout);
        return 1;
    }

    fprintf(fpCheckinAndCheckout, "%d _ ", iIDNeedToCheck);

    struct tm TimeSetToCheckOut;                                                       //Set check in time (Function in time.h library)
    TimeSetToCheckOut.tm_min    = 30;
    TimeSetToCheckOut.tm_hour   = 16;

    //gmtime() function of time.h library
    time_t tCurrenttime;
    time(&tCurrenttime);
    struct tm* plocaltime = localtime(&tCurrenttime);

    //If later than 4h PM -> CHECK OUT ON TIME
    if(plocaltime->tm_hour > TimeSetToCheckOut.tm_hour)        
    {
        printf("You checked out on time.\n\n");

        printf("%d/%d/%d/%d _ %d : %02d\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min);

        //Save check out time of each employee to text file
        fprintf(fpCheckinAndCheckout, "%d/%d/%d/%d _ %d : %02d _ %d _ out.\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min, iMoneyPerDay); 
    }

    //If hour at 4h PM -> CHECK MINUTE
    else if(plocaltime->tm_hour == TimeSetToCheckOut.tm_hour)
    {

        //If minute later or equal to 30 minutes -> CHECK OUT ON TIME
        if(plocaltime->tm_min >= TimeSetToCheckOut.tm_min)
        {
            printf("You checked out on time.\n\n");

            printf("%d/%d/%d/%d _ %d : %02d\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min);

            //Save check out time of each employee to text file
            fprintf(fpCheckinAndCheckout, "%d/%d/%d/%d _ %d : %02d _ %d _ out.\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min, iMoneyPerDay); 
        }

        //If minute smaller than 30 minutes -> CHECK OUT SOON
        else if(plocaltime->tm_min < TimeSetToCheckOut.tm_min)
        {
            printf("You checked out soon.\n\n");
            iMoneyPerDay = MINUSMONEY;

            printf("%d/%d/%d/%d _ %d : %02d\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min);

            //Save check out time of each employee to text file
            fprintf(fpCheckinAndCheckout, "%d/%d/%d/%d _ %d : %02d _ %d _ out.\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min, iMoneyPerDay); 
        }

    }

    //If hour smaller than 4h PM -> CHECK OUT SOON
    else if((plocaltime->tm_hour < TimeSetToCheckOut.tm_hour) && (plocaltime->tm_hour >= 13))
    {
        printf("You checked out soon.\n\n");
        iMoneyPerDay = MINUSMONEY;

        printf("%d/%d/%d/%d _ %d : %02d\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min);

        //Save check out time of each employee to text file
        fprintf(fpCheckinAndCheckout, "%d/%d/%d/%d _ %d : %02d _ %d _ out.\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min, iMoneyPerDay); 
    }

    //If hour smaller than 1h PM and greater than 12h PM-> CHECK OUT TOO SOON
    else if(plocaltime->tm_hour >= 12 && plocaltime->tm_hour < 13)
    {
        printf("You checked out too soon.\n\n");
        iHourInDay = 12;
        iMinuteInDay = 0;
        iMoneyPerDay = 0;

        printf("%d/%d/%d/%d _ %d : %02d\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, iHourInDay, iMinuteInDay);

        //Save check out time of each employee to text file
        fprintf(fpCheckinAndCheckout, "%d/%d/%d/%d _ %d : %02d _ %d _ out.\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, iHourInDay, iMinuteInDay, iMoneyPerDay);
    }

    //If hour is smaller than 12h PM -> CHECK OUT TOO SOON
    else if(plocaltime->tm_hour < 12)
    {
        printf("You checked out too soon.\n\n");
        iMoneyPerDay = 0;

        printf("%d/%d/%d/%d _ %d : %02d\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min);

        //Save check out time of each employee to text file
        fprintf(fpCheckinAndCheckout, "%d/%d/%d/%d _ %d : %02d _ %d _ out.\n", plocaltime->tm_wday + 1, plocaltime->tm_mday, plocaltime->tm_mon + 1, plocaltime->tm_year + 1900, plocaltime->tm_hour, plocaltime->tm_min, iMoneyPerDay);
    }

    fclose(fpCheckinAndCheckout);

    //Save working time and minus money in that day to text file after check out
    CalculateWorkingHourPerDay(iIDNeedToCheck);          

    printf("\nPress Enter to continue");
    getchar();

}


////Function to calculate working time and minus money of each employee when they check out//// 
short CalculateWorkingHourPerDay(short iIDNeedToCheck)
{
    //gmtime() function of time.h library
    time_t tCurrenttime;
    time(&tCurrenttime);
    struct tm* plocaltime = localtime(&tCurrenttime);

    int iStempID, iWday, iMday, iMon, iYear, iHour, iMinute, iMinusMoney;          //Temp Variables get values from text file of check in/out history
    char sTemp[4];                                                                 //Temp string just to check status that is 'check in' or 'check out'
    short iHourIn = 0, iMinuteIn = 0, iHourOut = 0, iMinuteOut = 0;                //Variables get value of hour, minute of each 'check in/out' of each 'day' of each 'employees' 
    int iTotalMinusMoney = 0;                                                      //Total minus money per day
    float fWorkingHourPerDay;                                                      //From hour and minute of working of each day -> working hours per day 
    int iTempMinusMoneyWhenCheckOut = 0;                                           //Variable get value of minus money of the last check out 
    char cCheckIfCheckIn = 0;                                                      //Variable check if employee check in                                                              

    fpCheckinAndCheckout = fopen("Checkin_Checkout_History.txt", "r");                                     //Open text file of check in/out history 

    if(fpCheckinAndCheckout == NULL)
    {
        printf("\t\t\t\tThe file could not be opened, or the file has no data.\n");
        fclose(fpCheckinAndCheckout);
        return 1;
    }
    
    //Loop through 'check in' line of file to get first 'Check in' line of 'ID' and 'Day of month' from 2 'For loop'
    while(fscanf(fpCheckinAndCheckout, "%d _ %d/%d/%d/%d _ %d : %02d _ %d _ %4[^.].\n", &iStempID, &iWday, &iMday, &iMon, &iYear, &iHour, &iMinute, &iMinusMoney, sTemp) == 9)
    {
        //If that line has 'ID' and 'Day of month' from 2 'For loop' -> ge value of 'minus money' and 'Check in hour, minute'
        if((iStempID == iIDNeedToCheck) && (iMday == plocaltime->tm_mday) && (iMon == plocaltime->tm_mon + 1) && !strcmp(sTemp,"in"))
        {
            iTotalMinusMoney = iTotalMinusMoney + iMinusMoney;            //Total minus money of each day (calculate from start of month)
            iHourIn = iHour;                                              //Get value of check out hour
            iMinuteIn = iMinute;                                          //Get value of check out minute
            cCheckIfCheckIn++;               //If in day, employee checked in, this variable +1                             
            break;
        }
        
    }
        
    //Bring file pointer to the start of text file to check information of check out 
    rewind(fpCheckinAndCheckout);  

    //Loop through 'check in' line of file to get first 'Check out' line of 'ID' and 'Day of month' from 2 'For loop'
    while(fscanf(fpCheckinAndCheckout, "%d _ %d/%d/%d/%d _ %d : %02d _ %d _ %4[^.].\n", &iStempID, &iWday, &iMday, &iMon, &iYear, &iHour, &iMinute, &iMinusMoney, sTemp) == 9)
    {
        
        //If that line has 'ID' and 'Day of month' from 2 'For loop' -> ge value of 'minus money' and 'Check out hour, minute'
        if((iStempID == iIDNeedToCheck) && (iMday == plocaltime->tm_mday) && (iMon == plocaltime->tm_mon + 1) && !strcmp(sTemp,"out"))
        {
            iTempMinusMoneyWhenCheckOut = iMinusMoney;
            iHourOut = iHour;                                                //Get value of check out hour
            iMinuteOut = iMinute;                                            //Get value of check out minute
        }

    }

    iTotalMinusMoney = iTotalMinusMoney + iTempMinusMoneyWhenCheckOut;               //Total minus money of each day 
            
    fWorkingHourPerDay = ((float)iHourOut + (float)iMinuteOut / 60) - ((float)iHourIn + (float)iMinuteIn / 60);      //Calculate working hour per day              

    //If working time >= 8 -> working time = 8 hours
    if(fWorkingHourPerDay >= 8)                                       //If working hour greater than 8 -> working hour = 8 hours
    {
        fWorkingHourPerDay = 8;
    }

    //If working time <= 0 -> working time = 0 hours
    if(fWorkingHourPerDay <= 0)
    {
        fWorkingHourPerDay = 0;
    }
    
    //Bring file pointer to the start of text file for next loop
    rewind(fpCheckinAndCheckout);
    fclose(fpCheckinAndCheckout);

    fpWorkingTimePerDay = fopen("Working_Time_Per_Day.txt", "a+");

    if(fpWorkingTimePerDay == NULL)
    {
        printf("\t\t\t\tThe file could not be opened, or the file has no data.\n");
        fclose(fpWorkingTimePerDay);
        return 1;
    }

    //Check if don't have check in time in day, so don't save working time of that day
    if(cCheckIfCheckIn != 0)
    {
        fprintf(fpWorkingTimePerDay, "%d _ %d/%d/%d _ %0.2f _ %d.\n", iIDNeedToCheck, iMday, iMon, iYear, fWorkingHourPerDay, iTotalMinusMoney);
    }

    fclose(fpWorkingTimePerDay);
}

//////Function to calculte salary for all employees//// 
short CalculateSalary()
{
    //gmtime() function of time.h library
    time_t tCurrenttime;
    time(&tCurrenttime);
    struct tm* plocaltime = localtime(&tCurrenttime);

    short iIdOfEmployee = 0;                                                       //Count how many ID of employees in company
    char sTemp[100];                                                               //Temp string to loop through all line of text file to check how many employee
    int iStempID, iMday, iMon, iYear, iMinusMoney = 0;                             //Temp Variables get values from text file of information of each employee to calculate salary
    float fWorkingTime;                                                            //Temp Variables get values from text file of working time of each employee to calculate salary
    float fTotalSalary = 0;                                                        //Total salary for each employee when calculate salary
    char sTempName[24];                                                            //Temp variable to get name of employee from 'Employee Information' file
    short NumberOfDayOfPreviousMonth = 0;                                          //Temp variable to get number of day of previous month when calculate salary
    int iTempMinusMoney = 0;                                                       //Variable get value of minus money of the lastest working time calculation per day
    float fTempWorkingTime = 0;                                                    //Variable get value of working time of the lastest working time calculation per day               

    //In time.h library, month from 0-11, so set 0 is december
    if(plocaltime->tm_mon == 0)
    {
        NumberOfDayOfPreviousMonth = CountNumberOfDays(12);
    }

    else
    {
        NumberOfDayOfPreviousMonth = CountNumberOfDays(plocaltime->tm_mon);
    }

    
    fpInformationOfEmployee = fopen("Information_Of_Employee.txt", "r");                               //Open text file of 3 information of employees 

    if(fpInformationOfEmployee == NULL)
    {
        printf("\t\t\t\tThe file could not be opened, or the file has no data.\n");
        fclose(fpInformationOfEmployee);
        return 1;
    }
    
    //Loop entire file to check how many ID
    while(fgets(sTemp, 100, fpInformationOfEmployee) != NULL)
    {
         iIdOfEmployee++;
    }

    fclose(fpInformationOfEmployee);  

    float fTotalWorkingTime[iIdOfEmployee + 1];                                       //Array save total working time of each employee
    memset(fTotalWorkingTime, 0, (iIdOfEmployee + 1) * 4);
    int iTotalMinusMoney[iIdOfEmployee + 1];                                          //Array save total minus money of each employee
    memset(iTotalMinusMoney, 0, (iIdOfEmployee + 1) * 4); 

    fpWorkingTimePerDay = fopen("Working_Time_Per_Day.txt", "r+");                   //Open text file save total working time and total minus money of each employee

    //Loop through all employees 
    for(int iCount = 1; iCount <= iIdOfEmployee; iCount++)
    {
        //Loop from today to the last day of previous month
        for(int i = plocaltime->tm_mday; i <= NumberOfDayOfPreviousMonth ; i++)
        {
            //Get data from each line of text file
            while(fscanf(fpWorkingTimePerDay, "%d _ %d/%d/%d _ %f _ %d.\n", &iStempID, &iMday, &iMon, &iYear, &fWorkingTime, &iMinusMoney) == 6)
            {
                
                if((iStempID == iCount) && (iMday == i) && ((iMon - 1) == (plocaltime->tm_mon - 1)) && (iYear == (plocaltime->tm_year + 1900)))
                {
                    fTempWorkingTime = fWorkingTime;                              //Get working time value
                    iTempMinusMoney = iMinusMoney;                                //Get miinus money value                  
                }

            }

            fTotalWorkingTime[iCount] = fTotalWorkingTime[iCount] + fTempWorkingTime;  //Incremenntally add for total working time of each employee
            iTotalMinusMoney[iCount] = iTotalMinusMoney[iCount] +  iTempMinusMoney;    //Incremenntally add for total minus money of each employee
            fTempWorkingTime = 0.000000;                                               //Reset variable get value of working time of the lastest working time calculation per day
            iTempMinusMoney = 0;                                                       //Reset variable get value of minus money of the lastest working time calculation per day

            rewind(fpWorkingTimePerDay);                                               //Reset file pointer to the start of file
        }
        
        //Loop from the first day of present month to the day before
        for(int i = 1; i < plocaltime->tm_mday; i++)
        {
            //Get data from each line of text file
            while(fscanf(fpWorkingTimePerDay, "%d _ %d/%d/%d _ %f _ %d.\n", &iStempID, &iMday, &iMon, &iYear, &fWorkingTime, &iMinusMoney) == 6)
            {

                if((iStempID == iCount) && (iMday == i) && (iMon == (plocaltime->tm_mon + 1)) && (iYear == (plocaltime->tm_year + 1900)))
                {
                    fTempWorkingTime = fWorkingTime;                               //Get working time value
                    iTempMinusMoney = iMinusMoney;                                 //Get miinus money value   
                }

            }

            fTotalWorkingTime[iCount] = fTotalWorkingTime[iCount] + fTempWorkingTime;        //Incremenntally add for total working time of each employee
            iTotalMinusMoney[iCount] = iTotalMinusMoney[iCount] + iTempMinusMoney;           //Incremenntally add for total minus money of each employee
            fTempWorkingTime = 0.000000;                                                     //Reset variable get value of working time of the lastest working time calculation per day
            iTempMinusMoney = 0;                                                             //Reset variable get value of minus money of the lastest working time calculation per day

            rewind(fpWorkingTimePerDay);                                                     //Reset file pointer to the start of file
        }

    }

    fclose(fpWorkingTimePerDay);

    fpCalculateSalary = fopen("Total_Salary.txt", "w+");

    if(fpCalculateSalary == NULL)
    {
        printf("\t\t\t\tThe file could not be opened, or the file has no data.\n");
        fclose(fpCalculateSalary);
        return 1;
    }

    fpInformationOfEmployee = fopen("Information_Of_Employee.txt", "r");  

    if(fpInformationOfEmployee == NULL)
    {
        printf("\t\t\t\tThe file could not be opened, or the file has no data.\n");
        fclose(fpInformationOfEmployee);
        return 1;
    }

    //Loop through all employees
    for(int iCount = 1; iCount <= iIdOfEmployee; iCount++)
    {
        printf("Total minus money: %d _ Total working time: %0.2f\n", iTotalMinusMoney[iCount], fTotalWorkingTime[iCount]);
        fscanf(fpInformationOfEmployee, "%*s %*s %24[^_] %*s %*s", sTempName);
        fTotalSalary = fTotalWorkingTime[iCount] * BASICSALARY - iTotalMinusMoney[iCount];        //Calculate total salary
        printf("%d _ %s _ %0.2f VND\n\n", iCount, sTempName, fTotalSalary);                             //Print total salary on terminal
        fprintf(fpCalculateSalary, "%d _ %s _ %0.2f VND\n", iCount, sTempName, fTotalSalary);         //Save information of salary to text file
    }

    fclose(fpCalculateSalary);
    fclose(fpInformationOfEmployee);

    printf("Press Enter to continue.");
    getchar();
}


////Function to view working time of specified employee////
short ViewWorkingTimeOfSpecifiedEmployee()
{
    //gmtime() function of time.h library
    time_t tCurrenttime;
    time(&tCurrenttime);
    struct tm* plocaltime = localtime(&tCurrenttime);

    short iIdViewWorkingTime = 0;                                                   //ID to view working time of specfied employee
    char sTemp[100];                                                               //Temp string to loop through all line of text file to check how many employee
    int iStempID, iMday, iMon, iYear, iMinusMoney = 0;                             //Temp Variables get values from text file of information of each employee to calculate salary
    float fWorkingTime;                                                            //Temp Variables get values from text file of working time of each employee to calculate salary
    char sTempName[24];                                                            //Temp variable to get name of employee from 'Employee Information' file
    short NumberOfDayOfPreviousMonth = 0;                                          //Temp variable to get number of day of previous month when calculate salary
    float fTempWorkingTime = 0;                                                    //Variable get value of working time of the lastest working time calculation per day 
    float fTotalWorkingTime = 0;   
    short iTempID = 0;                                                                 //Variable take ID from text file to check wih ID user input
    char sTempLine[100];                                                                   //Loop through each employee
    char cYesOrNo;                                                                     //Variable for user to check informaion right or wrong     

    EnterIdAgain:
    fpInformationOfEmployee = fopen("Information_Of_Employee.txt", "r");

    if(fpInformationOfEmployee == NULL)
    {
        printf("\t\t\t\tThe file could not be opened, or the file has no data.\n");
        fclose(fpInformationOfEmployee);
        return 1;
    }

    printf("Enter ID of employee: ");
    scanf("%d", &iIdViewWorkingTime);
    getchar();

    //Check informaion from ID user input
    while(fscanf(fpInformationOfEmployee, "%d _ %24[^_] %*s %*s", &iTempID ,sTempLine) != -1)  
    {
        if(iTempID == iIdViewWorkingTime)
        {
            break;
        }
    }     

    fclose(fpInformationOfEmployee);

    if(iTempID != iIdViewWorkingTime)
    {
        printf("\nInvalid ID! Press Enter to input ID again.");
        getchar();
        system("cls");
        goto EnterIdAgain;
    }
     
    //In time.h library, month from 0-11, so set 0 is december
    if(plocaltime->tm_mon == 0)
    {
        NumberOfDayOfPreviousMonth = CountNumberOfDays(12);
    }

    else
    {
        NumberOfDayOfPreviousMonth = CountNumberOfDays(plocaltime->tm_mon);
    }

    fpWorkingTimePerDay = fopen("Working_Time_Per_Day.txt", "r+");                      //Open text file save total working time and total minus money of each employee

  
    //Loop from today to the last day of previous month
    for(int i = plocaltime->tm_mday; i <= NumberOfDayOfPreviousMonth ; i++)
    {
        //Get data from each line of text file
        while(fscanf(fpWorkingTimePerDay, "%d _ %d/%d/%d _ %f _ %d.\n", &iStempID, &iMday, &iMon, &iYear, &fWorkingTime, &iMinusMoney) == 6)
        {
                
            if((iStempID == iIdViewWorkingTime) && (iMday == i) && ((iMon - 1) == (plocaltime->tm_mon - 1)) && (iYear == (plocaltime->tm_year + 1900)))
            {
                fTempWorkingTime = fWorkingTime;                                   //Get working time value                  
            }

        }

        fTotalWorkingTime = fTotalWorkingTime + fTempWorkingTime;                  //Incremenntally add for total working time of each employee
        fTempWorkingTime = 0.000000;                                               //Reset variable get value of working time of the lastest working time calculation per day

        rewind(fpWorkingTimePerDay);                                               //Reset file pointer to the start of file
    }
        
    //Loop from the first day of present month to the day before
    for(int i = 1; i < plocaltime->tm_mday; i++)
    {
        //Get data from each line of text file
        while(fscanf(fpWorkingTimePerDay, "%d _ %d/%d/%d _ %f _ %d.\n", &iStempID, &iMday, &iMon, &iYear, &fWorkingTime, &iMinusMoney) == 6)
        {

            if((iStempID == iIdViewWorkingTime) && (iMday == i) && (iMon == (plocaltime->tm_mon + 1)) && (iYear == (plocaltime->tm_year + 1900)))
            {
                fTempWorkingTime = fWorkingTime;                               //Get working time value
            }

        }

        fTotalWorkingTime = fTotalWorkingTime + fTempWorkingTime;        //Incremenntally add for total working time of each employee
        fTempWorkingTime = 0.000000;                                                     //Reset variable get value of working time of the lastest working time calculation per day

        rewind(fpWorkingTimePerDay);                                                     //Reset file pointer to the start of file
    }


    fclose(fpWorkingTimePerDay);

    printf("\nWorking time of employee ID '%d': %0.2f hours\n\n", iIdViewWorkingTime, fTotalWorkingTime);
    printf("Press Enter to continue.");
    getchar();

}


////Function to check how many day in a month////
short CountNumberOfDays(int iMonth) 
{ 
  
    // Check for 31 Days 
    if (iMonth == 1 || iMonth == 3 || iMonth == 5 || iMonth == 7 || iMonth == 8 || iMonth == 10 || iMonth == 12)
    { 
        return 31; 
    } 
  
    // Check for 30 Days 
    else if (iMonth == 4 || iMonth == 6 || iMonth == 9 || iMonth == 11)
    { 
        return 30; 
    } 
  
    // Check for 28/29 Days 
    else if (iMonth == 2)
    { 
        return 28; 
    } 

} 