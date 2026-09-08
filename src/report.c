#include<stdio.h>
void generateReport()
{
    FILE *fp=fopen("data.txt","r");
    if(fp==NULL)
    {
        printf("\n>> ERROR: UNABLE TO OPEN DATA FILE FOR REPORT.\n");
        return;
    }

    int count=0;//total no of cardholders
    int card;
    char name[50],mobile[20];

    //fetching the count of cardholders
    while(fscanf(fp,"%d %s %s",&card,name,mobile)==3)
    {
        count++;
    }
    fclose(fp);

    int rice=count*5;//5 is the price for rice per kg
    int wheat=count*2;//2 is the price for wheat per kg
    int oil=count;

    int stockRice=0,stockWheat=0,stockOil=0;
    //Available stock in inventory
    FILE *fpStock=fopen("stock.txt","r");
    if(fpStock!=NULL)
    {
        fscanf(fpStock,"%d %d %d",&stockRice,&stockWheat,&stockOil);
        fclose(fpStock);
    }

    printf("\n============ SYSTEM REPORT ============\n");
    printf("TOTAL REGISTERED CARDHOLDERS : %d\n",count);
    printf("ESTIMATED RATIONS DISTRIBUTED:\n");
    printf("   %d KG RICE\n",rice);
    printf("   %d KG WHEAT\n",wheat);
    printf("   %d L OIL\n",oil);
    printf("CURRENT STOCK:\n");
    printf("   %d KG RICE\n",stockRice);
    printf("   %d KG WHEAT\n",stockWheat);
    printf("   %d L OIL\n",stockOil);
    printf("=======================================\n");
}
