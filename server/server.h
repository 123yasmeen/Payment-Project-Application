#ifndef UNTITLED_SERVER_H
#define UNTITLED_SERVER_H
typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;
typedef enum EN_serverError_t
{
	OK2, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE,BLOCKED_ACCOUNT
}EN_serverError_t;
typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	unsigned int transactionSequenceNumber;
}ST_transaction;
typedef enum EN_accountState_t
{
	RUNNING, BLOCKED
	
}EN_accountState_t;
typedef struct ST_accountsDB_t
{
	float balance;
	EN_accountState_t state;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;
EN_transState_t receiveTransactionData(ST_transaction* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData);
EN_serverError_t saveTransaction(ST_transaction* transData);
EN_serverError_t isBlocked(ST_accountsDB_t* pa);
#endif // !UNTITLED_SERVER_H

