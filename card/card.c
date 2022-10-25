#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "card.h"
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint8_t Wspace_counter = 0;
	printf("enter your name\n");
	gets(cardData->cardHolderName);
	for (int i = 0;i < strlen(cardData->cardHolderName);i++)
	{
		if (!isalpha(cardData->cardHolderName[i]))
		{
			if (cardData->cardHolderName[i] != ' ')
				return WRONG_NAME;
		}
	}
	for (int i = 0;i < strlen(cardData->cardHolderName);i++)
	{
		if (cardData->cardHolderName[i] == ' ')
			Wspace_counter++;
	}
	if (Wspace_counter != 2)
		return WRONG_NAME;
	if (strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24 || cardData->cardHolderName == NULL)
		return WRONG_NAME;
	else
		return OK;

}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("Enter the expiry date as following mm/yy\n");
	gets(cardData->cardExpirationDate);
	for (int i = 0;i < strlen(cardData->cardExpirationDate);i++)
	{
		if (cardData->cardExpirationDate[2] != '/')
			return WRONG_EXP_DATE;
		if (i != 2 && !(isdigit(cardData->cardExpirationDate[i])))
			return WRONG_EXP_DATE;
	}
	if (cardData->cardExpirationDate[0] - '0' > 1)
		return WRONG_EXP_DATE;
	if (cardData->cardExpirationDate[0] - '0' == 1 && cardData->cardExpirationDate[1] - '0' > 2)
		return WRONG_EXP_DATE;
	if (strlen(cardData->cardExpirationDate) != 5 || cardData->cardExpirationDate == NULL)
		return WRONG_EXP_DATE;
	else
		return OK;
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Enter your primary account number\n");
	gets(cardData->primaryAccountNumber);
	for (int i = 0;i < strlen(cardData->primaryAccountNumber);i++)
	{
		if (!(isdigit(cardData->primaryAccountNumber[i])))
			return WRONG_PAN;
	}
	if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19 || cardData->primaryAccountNumber == NULL)
		return WRONG_PAN;
	else
		return OK;
}