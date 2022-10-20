#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"Card.h"
#include "terminal.h"
#include"server.h"
#include "app.h"

void appStart()
{
	EN_cardError_t carderror;
	EN_terminalError_t terminalerror;
	ST_transaction user;
	int choice;
	while (1)
	{
		while (1)
		{
			carderror = getCardHolderName(&user.cardHolderData);
			if (carderror == WRONG_NAME)
				printf("Invalid name:check if it is less than 24 and bigger than 20 and no numbers or special characters invloved\n");
			else
				break;
		}
		while (1)
		{
			carderror = getCardExpiryDate(&user.cardHolderData);
			if (carderror == WRONG_EXP_DATE)
				printf("Invalid Expiration Date:check if it is equal to 5 and similar to the mentioned form\n");
			else
				break;
		}
		while (1)
		{
			carderror = getCardPAN(&user.cardHolderData);
			if (carderror == WRONG_PAN)
				printf("Invalid PAN:check if it is less than 19 and bigger than 16\n");
			else
				break;
		}
		while (1)
		{
			terminalerror = getTransactionDate(&user.terminalData);
			if (terminalerror == WRONG_DATE)
				printf("Invalid Date:check if it is equal to 10 and similar to the mentioned form\n");
			else
				break;
		}
		while (1)
		{
			if (isCardExpired(user.cardHolderData, user.terminalData))
			{
				printf("Declined Expired Card\n");
				break;
			}
			if (setMaxAmount(&user.terminalData))
			{
				printf("server error");
				break;
			}
			while (1)
			{
				if (getTransactionAmount(&user.terminalData))
					printf("Invalid Amount:check if the amount is bigger than zero\n");
				else
					break;
			}
			if (isBelowMaxAmount(&user.terminalData))
			{
				printf("Declined Amount Exceeding Limit\n");
				break;
			}
			EN_transState_t state = receiveTransactionData(&user);
			if (state == DECLINED_STOLEN_CARD)
			{
				printf("INVALID Blocked account\n");
			}
			else if (state == DECLINED_INSUFFECIENT_FUND)
			{
				printf("Not enough balance for your transaction\n");
				break;
			}
			else if (state == INTERNAL_SERVER_ERROR)
			{
				printf("transaction can not be saved\n");
				break;
			}

			else if (state == APPROVED)
			{
				printf("your transaction has been approved\n");
				break;
			}
			else if (state == BLOCKED_ACCOUNT)
				printf("your account is blocked");
		}
		printf("press zero if you want to exit or press any button to make another transaction ");
		scanf_s("%d", &choice);
		if (choice == 0)
			break;
	}
}