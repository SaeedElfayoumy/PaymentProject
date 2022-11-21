#include "server.h"


 ST_accountsDB_t accountsDB[255] = {
   {8867747,RUNNING,"17512548023014523"},{2000,BLOCKED,"18701136987412235"},
   {2000,RUNNING,"18402002454550563"},{20000,BLOCKED,"13401145200366357"},
   {14000,RUNNING,"102022420025445663"},{11947,BLOCKED,"11212456698747502"},
   {9979946,RUNNING,"163123587002450225"},{15000,BLOCKED,"17404568569525822"},
   {37950,RUNNING,"150244756996125458"},{175185453,BLOCKED,"10510258745869547"} };

 ST_transaction_t transactions[255] = { 0 };
 ST_accountsDB_t Saving_Data = {0};
 float current_Balance = 0 ;
 ST_transaction_t TempStock = { 0 };
 uint32_t j = 0, Seq_NO = 100;

 EN_transState_t recieveTransactionData(ST_transaction_t* transData)
 {
	 EN_cardError_t X;
	 EN_serverError_t Z;
	 EN_terminalError_t Y;
	 ST_accountsDB_t ZZ;

	 do
	 {
		 X = getCardHolderName(&transData->cardHolderData);
	 } while (X != 0);
	 StrCpy(TempStock.cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);

	 do
	 {
		 Y = getTransactionDate(&transData->terminalData);
	 } while (Y != 0);
	 StrCpy(TempStock.terminalData.transactionDate, transData->terminalData.transactionDate);

	 do
	 {
		 X = getCardExpiryDate(&transData->cardHolderData);
	 } while (X != 0);
	 StrCpy(TempStock.cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);

	 Y = isCardExpired(transData->cardHolderData, transData->terminalData);
	 if (Y != 0)
	 {
		 printf("\n INTERNAL_SERVER_ERROR  (Expire Card)\n");
		 transData->transState = INTERNAL_SERVER_ERROR;
		 return INTERNAL_SERVER_ERROR;
	 }

	 Z = isValidAccount(&transData->cardHolderData, &ZZ);
	 if (Z != 0)
	 {
		 printf("\n FRAUD_CARD \n");
		 transData->transState = FRAUD_CARD;
		 TempStock.transState = transData->transState;
		 
		 return FRAUD_CARD;
	 }
	 
	 Z = isBlockedAccount(&transData->transState);
	 if (Z != 0)
	 {
		 printf("\n DECLINED_STOLEN_CARD \n");
		 transData->transState = DECLINED_STOLEN_CARD;
		 TempStock.transState = transData->transState;
		 return DECLINED_STOLEN_CARD;
	 }

	 do
	 {
		 Y = setMaxAmount(&transData->terminalData);
		 TempStock.terminalData.maxTransAmount = transData->terminalData.maxTransAmount;

	 } while (Y != 0);
	 
	 Z = isAmountAvailable(&transData->terminalData, &ZZ);
	  transData->terminalData.transAmount = TempStock.terminalData.transAmount ;

	 if (Z != 0)
	 {
		 printf("\n DECLINED_INSUFFECIENT_FUND \n");
		 transData->transState = DECLINED_INSUFFECIENT_FUND;
		 TempStock.transState = transData->transState;
		 return DECLINED_INSUFFECIENT_FUND;
	 }
	 printf("\ntransData->terminalData : %f \n", transData->terminalData.transAmount);
	 printf("\ntransData->terminalData : %f \n", transData->terminalData.maxTransAmount);
	 Y = isBelowMaxAmount(&transData->terminalData);
	 if (Y != 0)
	 {
		 printf("\n INTERNAL_SERVER_ERROR (Declined Exceed Max) \n");
		 transData->transState = INTERNAL_SERVER_ERROR;
		 TempStock.transState = transData->transState;
		 return INTERNAL_SERVER_ERROR;
	 }

	 printf("\n APPROVED \n");
	 current_Balance -= TempStock.terminalData.transAmount;
	 printf(" Your Current Balance After Transaction : %f \n", current_Balance);
	 transData->transactionSequenceNumber = Seq_NO;
	 TempStock.transactionSequenceNumber = transData->transactionSequenceNumber;
	 printf(" Operation No. : %d  \n", transData->transactionSequenceNumber);
	 transData->transState = APPROVED;
	 TempStock.transState = transData->transState;

	 return APPROVED;

 }

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	ST_cardData_t* tmp;
	tmp = &cardData;

	EN_cardError_t res2;
	do
	{
		res2 = getCardPAN(&cardData);
	} while (res2 != 0);

	for (int i = 0; i < 10; i++)  // as global array has 10 accounts
	{
		if (strcmp(tmp->primaryAccountNumber, accountsDB[i].primaryAccountNumber) == 0)
		{
			Saving_Data = accountsDB[i];
			current_Balance = accountsDB[i].balance;
			accountRefrence->state = accountsDB[i].state;
			StrCpy(TempStock.cardHolderData.primaryAccountNumber, accountsDB[i].primaryAccountNumber);
			if (Saving_Data.state == RUNNING)
			{
				printf(" Runing Account \n");
				printf(" Current Balance : %d \n", Saving_Data.balance);
			}
			else if (Saving_Data.state == BLOCKED)
			{
				printf(" Blocked Account \n");
			}
			return SERVER_OK;

		}
	}
	accountRefrence->state = 3;
	printf(" Undefined Account \n");
	return ACCOUNT_NOT_FOUND;

}
void isValidAccountTest(void)
{
	printf("Tester Name: Saeed Alaa \n");
	printf("Function Name: isValidAccount \n\n");

	EN_serverError_t state;
	ST_cardData_t cardData;
	ST_accountsDB_t accountRefrence;

	printf(" Case 1 : Vaild account + RUNNING !! \n");
	StrCpy(cardData.primaryAccountNumber, "102022420025445663");
	accountRefrence.state = Saving_Data.state;
	printf("Input Data : PAN Number (%s)  Account State : (%s)", cardData.primaryAccountNumber,
		accountRefrence.state == 0 ? "RUNNING" : "BLOCKED");
	state = isValidAccount(&cardData, &accountRefrence);
	if (state != 0)
	{
		printf("Expected Result : NOT OK \n");
		printf("Actual Result : %d \n", state);
	}
	else
	{
		printf("Expected Result : it's OK \n");
		printf("Actual Result : %d \n", state);
	}

	printf(" \nCase 2 : Vaild account + BLOCKED !! \n");
	StrCpy(cardData.primaryAccountNumber, "13401145200366357");
	accountRefrence.state = Saving_Data.state;
	printf("Input Data : PAN Number (%s)  Account State : (%s)", cardData.primaryAccountNumber,
		accountRefrence.state == 0 ? "RUNNING" : "BLOCKED");
	state = isValidAccount(&cardData, &accountRefrence);
	if (state != 0)
	{
		printf("Expected Result : NOT OK \n");
		printf("Actual Result : %d \n", state);
	}
	else
	{
		printf("Expected Result : it's OK \n");
		printf("Actual Result : %d \n", state);
	}

	printf(" \nCase 3 : NOT Vaild account  !! \n");
	StrCpy(cardData.primaryAccountNumber, "10203040506708090");
	accountRefrence.state = Saving_Data.state;
	printf("Input Data : PAN Number (%s)  ", cardData.primaryAccountNumber);
	state = isValidAccount(&cardData, &accountRefrence);
	if (state != 0)
	{
		printf("Expected Result : NOT OK \n");
		printf("Actual Result : %d \n", state);
	}
	else
	{
		printf("Expected Result : it's OK \n");
		printf("Actual Result : %d \n", state);
	}

}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	accountRefrence->state = Saving_Data.state;
	if (accountRefrence->state  == BLOCKED)
		return BLOCKED_ACCOUNT;
	else
		return SERVER_OK;

}
void isBlockedAccountTest(void)
{
	printf("Tester Name: Saeed Alaa \n");
	printf("Function Name: isBlockedAccount \n\n");

	EN_serverError_t state;
	ST_cardData_t cardData;
	ST_accountsDB_t accountRefrence;

	printf(" Case 1 : RUNNING !! \n");
	StrCpy(cardData.primaryAccountNumber, "102022420025445663");
	state = isValidAccount(&cardData.primaryAccountNumber, &accountRefrence.state);
	accountRefrence.state = Saving_Data.state;
	printf("\nInput Data :  Account State : (%s) \n", accountRefrence.state == 0 ? "RUNNING" : "BLOCKED");
	state = isBlockedAccount(&accountRefrence);
	if (state != 0)
	{
		printf("Expected Result : NOT OK \n");
		printf("Actual Result : %d \n", state);
	}
	else
	{
		printf("Expected Result : it's OK \n");
		printf("Actual Result : %d \n", state);
	}

	printf("\n Case 2 : BLOCKED !! \n");
	StrCpy(cardData.primaryAccountNumber, "13401145200366357");
	state = isValidAccount(&cardData.primaryAccountNumber, &accountRefrence.state);
	accountRefrence.state = Saving_Data.state;
	printf("\nInput Data :  Account State : (%s) \n", accountRefrence.state == 0 ? "RUNNING" : "BLOCKED");
	state = isBlockedAccount(&accountRefrence);
	if (state != 0)
	{
		printf("Expected Result : NOT OK \n");
		printf("Actual Result : %d \n", state);
	}
	else
	{
		printf("Expected Result : it's OK \n");
		printf("Actual Result : %d \n", state);
	}

}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	ST_terminalData_t* tmp1;
	tmp1 = &termData;

	EN_terminalError_t res3;
	do
	{
		res3 = getTransactionAmount(&termData);	
	} while (res3 != 0);
	TempStock.terminalData.transAmount = tmp1->transAmount;

	if (accountRefrence->state == RUNNING)
	{
		if (Saving_Data.balance > tmp1->transAmount)
		{
			
			printf(" SERVER_OK \n");
			return SERVER_OK;
		}
		else
		{
			printf(" LOW_BALANCE \n");
			return LOW_BALANCE;
		}
	}
	else
	{
		printf(" Blocked Account \n");
	}



}
void isAmountAvailableTest(void)
{
	printf("Tester Name: Saeed Alaa \n");
	printf("Function Name: isAmountAvailable \n\n");

	EN_serverError_t state;
	ST_terminalData_t termData;
	ST_accountsDB_t accountRefrence;
	ST_cardData_t cardData;
	
	printf(" Case 1 : amount is exist !! \n");
	StrCpy(cardData.primaryAccountNumber, "102022420025445663");
	state = isValidAccount(&cardData, &accountRefrence);
	termData.transAmount = 2000;
	accountRefrence.state = Saving_Data.state;
	printf("\nInput Data :  Amount Transfer : (%f) \n", termData.transAmount);
	state = isAmountAvailable(&termData, &accountRefrence);
	if (state != 0)
	{
		printf("Expected Result : NOT OK \n");
		printf("Actual Result : %d \n", state);
	}
	else
	{
		printf("Expected Result : it's OK \n");
		printf("Actual Result : %d \n", state);
	}

	printf(" \nCase 2 : amount is  NOT exist !! \n");
	termData.transAmount = 5000;
	accountRefrence.state = RUNNING;
	state = isValidAccount(&termData.transAmount, &accountRefrence.state);
	printf("\nInput Data :  Amount Transfer : (%f) \n", termData.transAmount);
	state = isAmountAvailable(&termData, &accountRefrence);
	if (state != 0)
	{
		printf("Expected Result : NOT OK \n");
		printf("Actual Result : %d \n", state);
	}
	else
	{
		printf("Expected Result : it's OK \n");
		printf("Actual Result : %d \n", state);
	}

	printf(" \nCase 3 : Account is blocked !! \n");
	termData.transAmount = 2000;
	accountRefrence.state = BLOCKED;
	state = isValidAccount(&termData.transAmount, &accountRefrence.state);
	printf("\nInput Data :  Amount Transfer : (%f) \n", termData.transAmount);
	state = isAmountAvailable(&termData, &accountRefrence);
	if (state != 0)
	{
		printf("Expected Result : NOT OK \n");
		printf("Actual Result : %d \n", state);
	}
	else
	{
		printf("Expected Result : it's OK \n");
		printf("Actual Result : %d \n", state);
	}
}


EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	*transData = TempStock;
	transactions[j] = *transData;

	if (transactions[j].transState == SERVER_OK)
	{
		printf("\n Done Saving \n");
	}
	else
	{
		printf("\n REFUSED !!! NOT Saving \n");
	}

	j++;
	return SERVER_OK;
}

void saveTransactionTest(void)
{
	printf("Tester Name: Saeed Alaa \n");
	printf("Function Name: saveTransaction \n\n");

	EN_serverError_t state;
	ST_transaction_t transData;

	printf(" Case 1 : Data is saving !! ");
	TempStock.transState = SERVER_OK;
	state = saveTransaction(&transData);
	if (state != 0)
	{
		printf(" Expected Result : NOT OK \n");
		printf(" Actual Result : %d \n", state);
	}
	else
	{
		printf(" Expected Result : it's OK \n");
		printf(" Actual Result : %d \n", state);
	}

	printf(" \n Case 2 : Data is NOT saving !! ");
	TempStock.transState = 10;
	state = saveTransaction(&transData);
	if (state == 0)
	{
		printf(" Expected Result : NOT OK \n");
		printf(" Actual Result : %d \n", state);
	}
	else
	{
		printf(" Expected Result : it's OK \n");
		printf(" Actual Result : %d \n", state);
	}

}

void listSavedTransactions(void)
{

	printf("\n###############################\n");
	printf(" Name             : %s\n", transactions[j - 1].cardHolderData.cardHolderName);
	printf(" Date             : %s\n", transactions[j - 1].terminalData.transactionDate);
	printf(" PAN No.          : %s\n", transactions[j - 1].cardHolderData.primaryAccountNumber);
	printf(" Expire Date      : %s\n", transactions[j - 1].cardHolderData.cardExpirationDate);
	printf(" MAX Trans Amount : %f\n", transactions[j - 1].terminalData.maxTransAmount);
	printf(" Trans Amount     : %f\n", transactions[j - 1].terminalData.transAmount);
	printf(" Trans State      : %s\n", transactions[j - 1].transState == 0 ? "OK" : "NOT");
	printf(" Operation Number : %d\n", transactions[j - 1].transactionSequenceNumber);
	printf("#################################\n");

}

void listSavedTransactionsTest(void)
{
	printf("Tester Name: Saeed Alaa\n");
	printf("Function Name: listSavedTransactions\n");
	printf("Case 1 : Print all Saving Data \n");
	printf("Input Data : No Data , it's a void Function \n");
	listSavedTransactions();
	printf("Expected Result : All Data is ready to Display !! \n");
	printf("Actual Data : \n");

}

