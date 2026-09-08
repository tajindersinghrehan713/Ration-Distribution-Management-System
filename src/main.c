#include<stdio.h>
#include<stdlib.h>
int adminlogin();
void adminPanel();
int userlogin();
void userPanel(int cardNumber);
void registerCardholder();

int main()
{
    int choice,cardNumber;
    char buffer[10];

    while(1)
        {//main menu
        printf("\n============================================\n");
        printf("   RATION DISTRIBUTION MANAGEMENT SYSTEM\n");
        printf("============================================\n");
        printf("1. ADMIN LOGIN\n");
        printf("2. USER LOGIN\n");
        printf("3. REGISTER NEW CARDHOLDER\n");
        printf("4. EXIT\n");
        printf("--------------------------------------------\n");
        printf("ENTER YOUR CHOICE (1,2,3,4): ");

        fgets(buffer,sizeof(buffer),stdin);
        //sscanf reads the from buffer(string)
        //scanf can also be used but with getchar to clear buffer
        sscanf(buffer,"%d",&choice);

        switch(choice)
        {
            case 1://checks the credentials for admin
                if(adminlogin())
                {
                    printf("\n>> WELCOME ADMIN!\n");
                    adminPanel();
                }
                else
                {
                    printf("\n>> ADMIN LOGIN FAILED.\n");
                }
                break;
            case 2://checks the credentials for user
                cardNumber=userlogin();
                if (cardNumber!=-1)
                {
                    userPanel(cardNumber);
                }
                else
                {
                    printf("\n>> USER LOGIN FAILED.\n");
                }
                break;
            case 3://registration for new user
                registerCardholder();
                break;
            case 4:
                printf("\n>> EXITING THE SYSTEM... THANK YOU!\n");
                exit(0);
            default:
                printf("\n>> INVALID CHOICE. PLEASE TRY AGAIN.\n");
        }
    }
    return 0;
}
