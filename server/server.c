#include "server.h"
#include <stdio.h>
#include <string.h>
#include "card.h"
#include "terminal.h"
#include <stdlib.h>


#define MAX_LINES 100
#define MAX_LEN 1000
int CardIndex=0;
FILE *fp = NULL;
FILE *fpac = NULL;
float CardBalance=0;
int transactionIndex = 0;

ST_accountsDB_t accountsDb[255] = { 0 };
ST_transaction Transatabase[255]={0};
EN_transState_t receiveTransactionData(ST_transaction* transData)
{
    FILE *fp1 = NULL;

    fp1 = fopen( "accounts.txt", "r");
    float bal;
    int stat;
    char pan[20];
    int i=0;
    while (!feof(fp1))
    {
        fscanf(fp1,"%f",&bal);
        fscanf(fp1,"%d",&stat);
        fscanf(fp1,"%s",pan);
        accountsDb[i].balance = bal;
        accountsDb[i].state = stat;
        strcpy((char*)accountsDb[i].primaryAccountNumber,pan);
        ++i;

    }
    fclose(fp1);

    int error1 =isValidAccount(&transData->cardHolderData);
if(error1==ACCOUNT_NOT_FOUND||error1==BLOCKED_ACCOUNT){
    transData->transState=DECLINED_STOLEN_CARD;
    return DECLINED_STOLEN_CARD;
}
int error2= isAmountAvailable(&transData->terminalData);
    if(error2==LOW_BALANCE){
        transData->transState=LOW_BALANCE;
        return LOW_BALANCE;
    }
int error3= saveTransaction(transData);
    if(error3==SAVING_FAILED){
        transData->transState=INTERNAL_SERVER_ERROR;
        return INTERNAL_SERVER_ERROR;
    }
    accountsDb[CardIndex].balance -= transData->terminalData.transAmount;
    printf("your balance after transaction= %.2f\n", accountsDb[CardIndex].balance);
    errno_t error;
    error = fopen_s(&fp, "transactions.txt", "a");
    fprintf(fp, "%f\n", accountsDb[CardIndex].balance);
    fprintf(fp, "-----------------------------------------------\n");

    fclose(fp);
    fp1 = fopen( "accounts.txt", "w");
    for (int j=0; j<i; j++) {
        fprintf(fp1, "%f ", accountsDb[j].balance);
        fprintf(fp1, "%d ", accountsDb[j].state);
        fprintf(fp1, "%s\n", accountsDb[j].primaryAccountNumber);

    }
        fclose(fp1);

    CardIndex=0;
    CardBalance=0.00;
    transData->transState= APPROVED;

    return APPROVED;
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
    for (int i = 0; i < 255; i++) {
        if(strcmp(cardData->primaryAccountNumber,accountsDb[i].primaryAccountNumber)==0){
            if(accountsDb[i].state==BLOCKED){
                return BLOCKED_ACCOUNT;
            }
            CardIndex=i;
            CardBalance=accountsDb[i].balance;
            return OK2;
        }
    }
    return ACCOUNT_NOT_FOUND;

}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData){

    if (CardBalance<termData->transAmount){
        return LOW_BALANCE;
    }
    return OK2;
}
EN_serverError_t saveTransaction(ST_transaction* transData) {
    transData->transactionSequenceNumber = transactionIndex;
    if (transData->transactionSequenceNumber < 255)
    {
        Transatabase[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
        Transatabase[transData->transactionSequenceNumber].terminalData = transData->terminalData;
        Transatabase[transData->transactionSequenceNumber].transState = transData->transState;
        Transatabase[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber + 1;

        fp = fopen("transactions.txt", "a");
        fprintf(fp,"%s\n", Transatabase[transData->transactionSequenceNumber].cardHolderData.cardHolderName);
        fprintf(fp, "%s\n", Transatabase[transData->transactionSequenceNumber].cardHolderData.cardExpirationDate);
        fprintf(fp,"%s\n", Transatabase[transData->transactionSequenceNumber].cardHolderData.primaryAccountNumber);
        fprintf(fp, "%s\n", Transatabase[transData->transactionSequenceNumber].terminalData.transactionDate);
        fprintf(fp, "%f\n", Transatabase[transData->transactionSequenceNumber].terminalData.transAmount);
        fprintf(fp, "%d\n", Transatabase[transData->transactionSequenceNumber].transactionSequenceNumber);


        fclose(fp);
        transactionIndex++;
        return OK2;
    }

    return SAVING_FAILED;
}



