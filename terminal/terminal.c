#include "terminal.h"

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
        return OK;
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
        return Ok;
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
        return Ok;
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
        return Ok;
    }

}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if(termData->transAmount<=termData->maxTransAmount)
    {
        return Ok;
    }
    else
    {
        return EXCEED_MAX_AMOUNT;
    }
}
