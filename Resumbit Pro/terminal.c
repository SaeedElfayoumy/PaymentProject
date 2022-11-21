#include"terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{

	int f = 0;
	printf(" \n Please, Enter Transaction Date in a form DD/MM/YYYY : ");
	gets(termData->transactionDate);


	if (termData->transactionDate[0] == '0')
	{
		if (termData->transactionDate[1] >= '1' && termData->transactionDate[1] <= '9')
		{
			f++;
		}
	}
	else if (termData->transactionDate[0] == '1' || termData->transactionDate[0] == '2')
	{
		if (termData->transactionDate[1] >= '0' && termData->transactionDate[1] <= '9')
		{
			f++;
		}
	}
	else if (termData->transactionDate[0] == '3')
	{
		if (termData->transactionDate[1] == '0')
		{
			f++;
		}
	}
	else
		return WRONG_DATE;


	if (termData->transactionDate[3] == '0')
	{
		if (termData->transactionDate[4] >= '1' && termData->transactionDate[4] <= '9')
		{
			f++;
		}
	}
	else if (termData->transactionDate[3] == '1')
	{
		if (termData->transactionDate[4] >= '0' && termData->transactionDate[4] <= '2')
		{
			f++;
		}
	}
	else
		return WRONG_DATE;

	if (termData->transactionDate[6] == '2' && termData->transactionDate[7] == '0')
		f++;
	else
		return WRONG_DATE;

	if (termData->transactionDate[8] == '2' && termData->transactionDate[9] >= '2' && termData->transactionDate[9] <= '9')
		f++;
	else if (termData->transactionDate[8] >= '3' && termData->transactionDate[9] >= '0' && termData->transactionDate[9] <= '9')
		f++;
	else
		return WRONG_DATE;


	if (strlen(termData->transactionDate) != 0 && strlen(termData->transactionDate) >= 10 && f != 0)
		return TERMINAL_OK;
	else
		return WRONG_DATE;
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{

	if (cardData.cardExpirationDate[3] > termData.transactionDate[8])
	{
		return TERMINAL_OK;
	}
	else if (cardData.cardExpirationDate[3] == termData.transactionDate[8])
	{
		if (cardData.cardExpirationDate[4] > termData.transactionDate[9])
		{
			return TERMINAL_OK;
		}
		else if (cardData.cardExpirationDate[4] < termData.transactionDate[9])
		{
			return EXPIRED_CARD;
		}
		else if (cardData.cardExpirationDate[4] == termData.transactionDate[9])
		{
			if (cardData.cardExpirationDate[0] > termData.transactionDate[3])
			{
				return TERMINAL_OK;
			}
			else if (cardData.cardExpirationDate[0] < termData.transactionDate[3])
			{
				return EXPIRED_CARD;
			}
			else if (cardData.cardExpirationDate[0] == termData.transactionDate[3])
			{
				if (cardData.cardExpirationDate[1] > termData.transactionDate[4])
				{
					return TERMINAL_OK;
				}
				else
				{
					return EXPIRED_CARD;
				}
			}

		}

	}
	else
	{
		return EXPIRED_CARD;
	}



}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{

	printf(" \n Please, Enter Transaction Amount  ......  L.E : ");
	scanf_s("%f", &termData->transAmount);
		
	if (termData->transAmount <= 0)
	{
		return INVALID_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}

}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf(" \n Please, Enter MAX Transaction Amount  ......  L.E : ");
	scanf_s("%f", &termData->maxTransAmount);

	if (termData->maxTransAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}

}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{

	if (termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}

}



void getTransactionDateTest(void)
{
	printf("Tester Name: Saeed Alaa \n");
	printf("Function Name: getTransactionDate \n\n");

	ST_terminalData_t TermData;
	EN_terminalError_t state;

	printf(" Case 1 : OLD Date !! \n");
	StrCpy(TermData.transactionDate, "01/02/2021");
	printf("Input Data : Transaction Date (%s) ", TermData.transactionDate);
	state = getTransactionDate(&TermData);
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

	printf("\n Case 2 : Format Date is not correct !! \n");
	StrCpy(TermData.transactionDate, "01112022");
	printf("Input Data : Transaction Date (%s) ", TermData.transactionDate);
	state = getTransactionDate(&TermData);
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

	printf("\n Case 3 : Format Date is OK  and Current Date !! \n");
	StrCpy(TermData.transactionDate, "05/10/2022");
	printf("Input Data : Transaction Date (%s) ", TermData.transactionDate);
	state = getTransactionDate(&TermData);
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

	printf("\n Case 4 : Format Date is not correct !! \n");
	StrCpy(TermData.transactionDate, "1/11/2022");
	printf("Input Data : Transaction Date (%s) ", TermData.transactionDate);
	state = getTransactionDate(&TermData);
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

	printf("\n Case 5 :  Date is NULL !! \n");
	StrCpy(TermData.transactionDate, " ");
	printf("Input Data : Transaction Date (%s) ", TermData.transactionDate);
	state = getTransactionDate(&TermData);
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
void isCardExpiredTest(void)
{
	printf("Tester Name: Saeed Alaa \n");
	printf("Function Name: isCardExpried \n");

	EN_terminalError_t state;
	ST_cardData_t CardData = { "0","0","11/22" };
	ST_terminalData_t TermData = { 0,0,"05/10/2022" };
	printf(" Case 1 : expire Date is not comen !! \n");
	printf("Input Data : %s     %s  \n", CardData.cardExpirationDate, TermData.transactionDate);
	state = isCardExpired(CardData, TermData);
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

	printf(" Case 2 : expire Date is OLD !! \n");
	StrCpy(CardData.cardExpirationDate, "08/22");
	StrCpy(TermData.transactionDate, "05/10/2022");

	printf("Input Data : %s     %s  \n", CardData.cardExpirationDate, TermData.transactionDate);
	state = isCardExpired(CardData, TermData);
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
void getTransactionAmountTest(void)
{
	printf("Tester Name: Saeed Alaa \n");
	printf("Function Name: GetTransactionAmount \n\n");

	ST_terminalData_t TermData;
	EN_terminalError_t state;

	printf(" Case 1 :  Trans Amount > 0 !! \n");
	//TermData.transAmount = 570;
	printf("Input Data : maxTransAmount(570) ");
	state = getTransactionAmount(&TermData);
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

	printf(" Case 2 :  Trans Amount = 0 !! \n");
	//TermData.transAmount = 0;
	printf("Input Data : maxTransAmount(0) ");
	state = getTransactionAmount(&TermData);
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

	printf(" Case 3 :  Trans Amount < 0 !! \n");
	//TermData.transAmount = -100;
	printf("Input Data : maxTransAmount(-100) ");
	state = getTransactionAmount(&TermData);
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
void setMaxAmountTest(void)
{
	EN_terminalError_t state;

	printf("Tester Name: Saeed Alaa \n");
	printf("Function Name: SetMaxAmount \n");

	ST_terminalData_t TermData = { 0,5000,"" };
	printf(" Case 1 :  Max Amount > 0 !! \n");
	printf("Input Data : maxTransAmount(%f) ", TermData.maxTransAmount);
	state = setMaxAmount(&TermData);
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
	TermData.maxTransAmount = 0;
	printf(" Case 2 :  Max Amount = 0 !! \n");
	printf("Input Data : maxTransAmount(%f)  ", TermData.maxTransAmount);
	state = setMaxAmount(&TermData);
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

	TermData.maxTransAmount = -1000;
	printf(" Case 3 :  Max Amount < 0 !! \n");
	printf("Input Data : maxTransAmount(%f)  ", TermData.maxTransAmount);
	state = setMaxAmount(&TermData);
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
void isBelowMaxAmountTest(void)
{
	printf("Tester Name: Saeed Alaa \n");
	printf("Function Name: IsBelowMaxAmount \n");

	EN_terminalError_t state;
	ST_terminalData_t TermData = { 1000,5000,"05/10/2022" };
	printf(" Case 1 : Trans AMount < Max Amount !! \n");
	printf("Input Data : transAmount (%f) maxTransAmount(%f)  \n", TermData.transAmount, TermData.maxTransAmount);
	state = isBelowMaxAmount(&TermData);
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

	printf(" Case 2 : Trans AMount = Max Amount !! \n");
	TermData.transAmount = 5000;
	printf("Input Data : transAmount (%f) maxTransAmount(%f)  \n", TermData.transAmount, TermData.maxTransAmount);
	state = isBelowMaxAmount(&TermData);
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

	printf(" Case 3 : Trans AMount > Max Amount !! \n");
	TermData.transAmount = 6000;
	printf("Input Data : transAmount (%f) maxTransAmount(%f)  \n", TermData.transAmount, TermData.maxTransAmount);
	state = isBelowMaxAmount(&TermData);
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