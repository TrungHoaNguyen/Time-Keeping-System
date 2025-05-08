#include "mock.h"

FILE* fpPassword;                             //Text file of password
FILE* fpInformationOfEmployee;                  //Text file of 3 information of each employee
FILE* fpCheckinAndCheckout;                      //Text file save data of check in and check out history
FILE* fpWorkingTimePerDay;            //Text file save working time per day of each employee
FILE* fpCalculateSalary;              //Text file save salary of each employee

employee *pEmployee = NULL;

char cCharacter = 0;                   //Variable to choose admin mode or normal mode
char sPassword[30];                    //User enter password for admin mode
char sTempPassword[30];                //Variable get password value from file text to check with input of user (Admin mode - feature 1)
short iIDNeedToCheck = 0;              //Variable is ID used to check in (Normal mode - check in)

int main()
{
    memset(sPassword, 0, 30);
    memset(sTempPassword, 0, 30);

    while(1)
    {    
        MainMenu:
        system("cls");
        printf("Choose Admin Mode or Normal Mode\nEnter 'a' or 'A' to choose Admin Mode\nEnter 'n' or 'N' to choose Normal Mode\nEnter 'e' or 'E' to Exit\n");
        printf("\nEnter character: ");
        scanf("%c", &cCharacter);                                       //Choose mode or exit program
        getchar();

        switch (cCharacter)
        {
            //Character to choose admin mode
            case 'a':
            case 'A':
            EnterPasswordAgain:
            fpPassword = fopen("Password.txt", "r+");                                   //Open file text of password for admin mode
            system("cls");
            //rewind(fp);                                                                       
            fgets(sTempPassword, 30, fpPassword);                                       //Get password in text file to check with password user input
            fclose(fpPassword);                                                         //Close file text of password for admin mode
            printf("Enter password: ");                                         //Enter password to admin menu
            gets(sPassword);

            if(CheckPassword(sPassword, sTempPassword) == 1)                    //If password true -> go to Admin menu
            {
                FeatureOfAdminMenu(cCharacter);         
            }

            else if(CheckPassword(sPassword, sTempPassword) == 0)               //If password wrong -> ener password again or returnn to main menu
            {
                printf("Wrong password! Please enter '1' to try again or enter '0' to return main menu\n");
                printf("Enter character: ");
                scanf("%c", &cCharacter);
                getchar();

                if(cCharacter == '1')
                {
                    goto EnterPasswordAgain;                            //When password wrong -> Enter password again
                }

                else
                {
                    goto MainMenu;                                      //When password wrong -> Return to main menu
                }
                
            }
 
            break;

            //Character to choose normal mode
            case 'n':
            case 'N':
            system("cls");
            FeatureOfNormalMenu(cCharacter);
            break;

            //Choose character to exit program
            case 'e':
            case 'E':
            printf("\n\n\nOUT PROGRAM.\n");
            return(0);
            break;

            default:
            printf("\n\n\nInvalid character! Press Enter to input again.\n");
            getchar();
            break;
        }

    }
   
    return 0;
}
