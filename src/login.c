#include<stdio.h>
#include<string.h>

#define ADMIN_ID "admin"//credential for admin are
#define ADMIN_PASS "1234"//set at compile time

void generateReport();
void initializeStock();
void viewStock();

int adminlogin()
{
    char id[50],pass[50];

    printf("\n------ ADMIN LOGIN ------\n");
    printf("ENTER ADMIN ID: ");
    fgets(id,sizeof(id),stdin);
    id[strcspn(id,"\n")]='\0';//removes the \n character

    printf("ENTER PASSWORD : ");
    fgets(pass,sizeof(pass),stdin);
    pass[strcspn(pass, "\n")]='\0';//removes the \n character

    return strcmp(id,ADMIN_ID)==0 && strcmp(pass,ADMIN_PASS)==0;
    //checks if the entered details matches
}

void adminPanel()
{
    int choice;
    char buffer[10];

    while(1)
    {
        printf("\n============ ADMIN PANEL ============\n");
        printf("1. VIEW SYSTEM REPORT\n");
        printf("2. INITIALIZE STOCK\n");
        printf("3. VIEW STOCK\n");
        printf("4. LOGOUT\n");
        printf("-------------------------------------\n");
        printf("ENTER YOUR CHOICE(1,2,3,4): ");

        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d",&choice);
        //sscanf reads the from buffer(string)
        //scanf can also be used but with getchar to clear buffer

        switch(choice)
        {
            case 1:
                generateReport();
                break;
            case 2:
                initializeStock();//initialize or restore the stock
                break;
            case 3:
                viewStock();//shows how much stock is remained
                break;
            case 4:
                printf("\n>> LOGGING OUT FROM ADMIN PANEL.\n");
                return;
            default:
                printf("\n>> INVALID CHOICE. PLEASE TRY AGAIN.\n");
        }
    }
}

int userlogin()
{
    int cardno,found=0;
    char buffer[20];
    FILE *fp=fopen("data.txt","r");

    if(fp==NULL)
    {
        printf(">> ERROR: UNABLE TO OPEN DATA FILE.\n");
        return -1;
    }

    printf("\n--------- USER LOGIN ---------\n");
    printf("ENTER CARD NUMBER: ");
    fgets(buffer,sizeof(buffer),stdin);
    sscanf(buffer,"%d",&cardno);
    //sscanf reads the from buffer(string)
    //scanf can also be used but with getchar to clear buffer

    int file_card;
    char username[50],mobile[15];

    while(fscanf(fp,"%d %s %s",&file_card,username,mobile)==3)
    {
        if(file_card==cardno)//checks if duplicate or not
        {
            found=1;
            break;
        }
    }

    fclose(fp);

    if(found)
    {
        printf("\n>> WELCOME %s! LOGIN SUCCESSFUL.\n",username);
        return cardno;
    }
    else
    {
        printf("\n>> CARD NUMBER NOT FOUND.\n");
        return -1;
    }
}

void userPanel(int cardNumber)
{
    int choice;
    char buffer[10];
    char name[50],mobile[15];
    int card;
    FILE *fp;

    while(1)
    {
        printf("\n============= USER PANEL =============\n");
        printf("1. VIEW CARD INFORMATION\n");
        printf("2. VIEW MONTHLY RATION\n");
        printf("3. LOGOUT\n");
        printf("--------------------------------------\n");
        printf("ENTER YOUR CHOICE(1,2,3): ");

        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d",&choice);
        //sscanf reads the from buffer(string)
        //scanf can also be used but with getchar to clear buffer

        switch(choice)
        {
            case 1:
                fp=fopen("data.txt","r");
                if(fp==NULL)
                {
                    printf(">> ERROR: UNABLE TO OPEN DATA FILE.\n");
                    break;
                }

                int found=0;
                while(fscanf(fp,"%d %s %s",&card,name,mobile)==3)
                {
                    if(card==cardNumber)
                    {
                        found=1;
                        break;
                    }
                }
                fclose(fp);

                if(found)
                {
                    printf("\n---------- CARD INFORMATION ----------\n");
                    printf("CARD NUMBER : %d\n",card);
                    printf("NAME        : %s\n",name);
                    printf("MOBILE NO.  : %s\n",mobile);
                    printf("--------------------------------------\n");
                }
                else
                {
                    printf(">> CARD DETAILS NOT FOUND.\n");
                }
                break;

                case 2:
                {
                FILE *fp=fopen("stock.txt","r+");
                if(fp==NULL)
                {
                    printf(">> ERROR: Unable to open stock file.\n");
                    break;
                }

                int rice,wheat,oil;
                fscanf(fp,"%d %d %d",&rice,&wheat,&oil);

                if (rice<5 || wheat<2 || oil<1)
                {
                    //minimum stock alert
                    printf(">> INSUFFICIENT STOCK. PLEASE CONTACT ADMIN.\n");
                    fclose(fp);
                    break;
                }

                rice-=5;//updates the stock after allocation
                wheat-=2;// of ration to the particular
                oil-=1;//user

                rewind(fp);
                fprintf(fp,"%d %d %d\n",rice,wheat,oil);
                fclose(fp);

                printf("\n------ MONTHLY RATION ALLOTMENT ------\n");
                printf("RICE  : 5 KG\n");
                printf("WHEAT : 2 KG\n");
                printf("OIL   : 1 LITRE\n");
                printf(">> STOCK UPDATED.\n");
                printf("--------------------------------------\n");
                break;
                //allocation of ration can be included according
                //units or family member in future
            }

            case 3:
                printf("\n>> LOGGING OUT FROM USER PANEL.\n");
                return;

            default:
                printf(">> INVALID CHOICE. PLEASE TRY AGAIN.\n");
        }
    }
}
