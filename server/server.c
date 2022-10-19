#include "server.h"
#include <stdio.h>
#include <string.h>
int CardIndex=0;
float CardBalance=0;
ST_accountsDB_t accountsDb [255]={ {7000.00,RUNNING,8945623985431754},{2200.00,BLOCKED,8945623985431755},{400000.00,RUNNING,8945623985431756}};
ST_transaction transaction[255]={0};
EN_transState_t receiveTransactionData(ST_transaction* transData)
{
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
int error3= saveTransaction(&transData);
    if(error3==SAVING_FAILED){
        transData->transState=INTERNAL_SERVER_ERROR;
        return INTERNAL_SERVER_ERROR;
    }
    accountsDb[CardIndex].balance -= transData->terminalData.transAmount;
    printf("your balance after transaction= %.2f",accountsDb[CardIndex].balance);
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
            CardIndex==i;
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
EN_serverError_t saveTransaction(ST_transaction* transData){


}

