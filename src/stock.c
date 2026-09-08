#include<stdio.h>

const char *stockFile="stock.txt";
//a pointer pointer pointing to the file [stock.txt]

void initializeStock()
{
    //initializes the stock at the admin end
    int rice,wheat,oil;

    printf("\n--- SET STOCK QUANTITY ---\n");
    printf("Enter rice (kg): ");
    scanf("%d",&rice);
    printf("Enter wheat (kg): ");
    scanf("%d",&wheat);
    printf("Enter oil (lit): ");
    scanf("%d",&oil);
    getchar();// clears the buffer

    FILE *fp=fopen(stockFile,"w");
    if(fp==NULL)
    {
        printf("Error: Can't write to stock file.\n");
        return;
    }

    fprintf(fp,"%d %d %d\n",rice,wheat,oil);
    fclose(fp);
    printf(">> Stock saved successfully.\n");
}

void viewStock()
{
    int rice,wheat,oil;
    FILE *fp=fopen(stockFile,"r");
    if(fp==NULL)
    {
        printf("Error: Can't open stock file.\n");
        return;
    }

    fscanf(fp,"%d %d %d",&rice,&wheat,&oil);
    fclose(fp);

    printf("\n--- CURRENT STOCK ---\n");
    printf("Rice  : %d kg\n",rice);
    printf("Wheat : %d kg\n",wheat);
    printf("Oil   : %d litres\n",oil);
}
