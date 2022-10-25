#include "terminal.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "card.h"
#include <stdlib.h>
#include <string.h>

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    printf("enter transaction date\n");
	scanf("%s", &termData->transactionDate);
	if(strlen(termData->transactionDate) != 10 || termData->transactionDate[2] !=47 || termData->transactionDate[5] !=47) //47 is ascii code for slash
    {
        return WRONG_DATE;
    }
    else if(termData->transactionDate[0]>'3' || (termData->transactionDate[0]=='3' && termData->transactionDate[1]>'1'))
    {
        return WRONG_DATE;
    }
    else if(termData->transactionDate[3]>'1' || (termData->transactionDate[3]=='1' && termData->transactionDate[4]>'2'))
    {
        return WRONG_DATE;
    }
    else
    {
        return OK1;
    }
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    char *expirationDateYear = &cardData.cardExpirationDate[3];
    char *expirationDateMonth = &cardData.cardExpirationDate[0];
    char *terminalDateYear = &termData.transactionDate[8];
    char *terminalDateMonth = &termData.transactionDate[3];

    int expirationDate = 100*atoi( expirationDateYear) + atoi(expirationDateMonth);
    int terminalDate = 100*atoi(terminalDateYear) + atoi(terminalDateMonth);

    if(terminalDate < expirationDate)
    {
        return OK1;
    }
    else
    {
        return EXPIRED_CARD;
    }
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    printf("enter transaction amount\n");
    scanf("%f",&termData->transAmount);
    if(termData->transAmount<=0)
    {
        return INVALID_AMOUNT;
    }
    else
    {
        return OK1;
    }
}


EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    termData->maxTransAmount=15000;
    if(termData->maxTransAmount<=0)
    {
        return INVALID_MAX_AMOUNT;
    }
    else
    {
        return OK1;
    }

}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if(termData->transAmount<=termData->maxTransAmount)
    {
        return OK1;
    }
    else
    {
        return EXCEED_MAX_AMOUNT;
    }
}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
    int num = 0, sum = 0, pos = 0;
    for (char i = strlen(cardData->primaryAccountNumber) - 1; i >= 0; i--)
    {
        num = cardData->primaryAccountNumber[i] - '0';

        if (pos == 1)
            num = num * 2;

        sum += num % 10;
        sum += num / 10;
        pos = !pos;

    }

    if (sum % 10 != 0)
        return INVALID_CARD;

    return OK1;
}