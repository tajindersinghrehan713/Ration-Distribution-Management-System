#include<stdio.h>
#include<string.h>
#include<ctype.h>

int isValidMobile(const char *mobile)
{
    //function for the mobile number entry
    if(strlen(mobile)!=10)
        return 0;
    for(int i=0;i<10;i++)
    {
        if (!isdigit(mobile[i]))
            return 0;
    }
    return 1;
}

//function for new registration
void registerCardholder()
{
    int newCard;
    char newUser[50];
    char newMobile[15];
    int existingCard;
    char tempUser[50], tempMobile[15];
    int duplicate=0;

    printf("\n------ REGISTER NEW CARDHOLDER ------\n");
    printf("ENTER NEW CARD NUMBER: ");
    scanf("%d",&newCard);
    getchar();

    FILE *fp=fopen("data.txt","r");
    if(fp!=NULL)
    {
        while(fscanf(fp,"%d %s %s",&existingCard,tempUser,tempMobile)==3)
        {
            //checking if the entered details are exists or not
            if(existingCard==newCard)
            {
                duplicate=1;
                break;
            }
        }
        fclose(fp);
    }

    if(duplicate)
    {
        printf("\n>> ERROR: CARD NUMBER ALREADY EXISTS.\n");
        return;
    }

    printf("ENTER USERNAME     : ");
    fgets(newUser,sizeof(newUser),stdin);
    newUser[strcspn(newUser,"\n")]='\0';
    //removes the \n from string

    printf("ENTER MOBILE NUMBER(10 digits): ");
    fgets(newMobile,sizeof(newMobile),stdin);
    newMobile[strcspn(newMobile,"\n")]='\0';
    //removes \n from string

    while(!isValidMobile(newMobile))
    {
        printf(">> INVALID MOBILE NUMBER.TRY AGAIN.\n");
        printf("ENTER MOBILE NUMBER (10 digits): ");
        fgets(newMobile,sizeof(newMobile),stdin);
        newMobile[strcspn(newMobile,"\n")]='\0';
        //removes \n from string
    }

    fp=fopen("data.txt","a");
    if(fp==NULL)
    {
        printf("\n>> ERROR: COULD NOT OPEN FILE TO WRITE.\n");
        return;
    }

    //puts the entered data into file
    fprintf(fp,"%d %s %s\n",newCard,newUser,newMobile);
    fclose(fp);

    printf("\n>> REGISTRATION SUCCESSFUL FOR CARD NUMBER %d.\n", newCard);
}
