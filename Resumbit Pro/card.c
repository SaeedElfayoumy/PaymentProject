# include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("\n Please,Enter your name : ");

	gets(cardData->cardHolderName);

	if ((strlen(cardData->cardHolderName) > 24) || (strlen(cardData->cardHolderName) < 10) || (strlen(cardData->cardHolderName) == 0))
	{
		return WRONG_NAME;
	}
	else
	{
		return CARD_OK;
	}
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	int f1 = 0, f2 = 0, f3 = 0, f;
	printf("\n Please,Enter Expiary Date in (MM/YY) Form : ");
	gets(cardData->cardExpirationDate);
	if (cardData->cardExpirationDate[0] == '0')
	{
		if (cardData->cardExpirationDate[1] >= '1' && cardData->cardExpirationDate[0] <= '9')
		{
			f1 = 1;
		}
	}
	else if (cardData->cardExpirationDate[0] == '1')
	{
		if (cardData->cardExpirationDate[1] >= '0' && cardData->cardExpirationDate[0] <= '2')
		{
			f1 = 1;
		}
	}
	else
	{
		f1 = 0;
	}

	if (cardData->cardExpirationDate[2] == '/')
		f2 = 1;
	else
		f2 = 0;

	if (cardData->cardExpirationDate[3] == '2')
	{
		if (cardData->cardExpirationDate[4] >= '2')
		{
			f3 = 1;
		}
	}
	else
	{
		f3 = 0;
	}


	f = f1 && f2 && f3;


	if (f == 0)
	{
		return WRONG_EXP_DATE;
	}
	else
	{
		return CARD_OK;
	}
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("\n Please,Enter your PAN : ");
	gets(cardData->primaryAccountNumber);



	if ((strlen(cardData->primaryAccountNumber) > 19) || (strlen(cardData->primaryAccountNumber) < 10) || (strlen(cardData->primaryAccountNumber) == 0))
	{
		return WRONG_PAN;
	}
	else
	{
		return CARD_OK;
	}


}

void StrCpy(char arr1[], char arr2[])
{
	int i = 0;
	while (arr2[i] != '\0')
	{
		arr1[i] = arr2[i];
		i++;
	}
	arr1[i] = '\0';

}

void getCardHolderNameTest(void)
{
	ST_cardData_t CardData;
	EN_cardError_t state;

	printf("Tester Name: Saeed Alaa \n");
	printf("Function Name: GetCardHolderName \n\n");

	printf(" Case 1 : Name is right !! \n");
	StrCpy(CardData.cardHolderName, "Saeed Alaa Mohamed");
	printf("Input Data : GetCardHolderName (%s) ", CardData.cardHolderName);
	state = getCardHolderName(&CardData);
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
	//***************************************************//
	printf(" Case 2 : Name is too short !! \n");
	StrCpy(CardData.cardHolderName, "Saeed ");
	printf("Input Data : GetCardHolderName (%s) ", CardData.cardHolderName);
	state = getCardHolderName(&CardData);
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
	//***************************************************//
	printf(" Case 3 : Name is too long !! \n");
	StrCpy(CardData.cardHolderName, "Saeed Alaa Alaa Mohamed Mohamed");
	printf("Input Data : GetCardHolderName (%s) ", CardData.cardHolderName);
	state = getCardHolderName(&CardData);
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
	//***************************************************//
	printf(" Case 4 : Name is NULL !! \n");
	StrCpy(CardData.cardHolderName, " ");
	printf("Input Data : GetCardHolderName (%s) ", CardData.cardHolderName);
	state = getCardHolderName(&CardData);
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
void getCardExpiryDateTest(void)
{
	ST_cardData_t CardData;
	EN_cardError_t state;

	printf("Tester Name: Saeed Alaa \n");
	printf("Function Name: getCardExpiryDate \n\n");

	printf(" Case 1 : Date is right !! \n");
	StrCpy(CardData.cardExpirationDate, "06/25");
	printf("Input Data : cardExpirationDate (%s) ", CardData.cardExpirationDate);
	state = getCardExpiryDate(&CardData);
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
	//***************************************************//
	printf(" Case 2 : Format is Wrong !! \n");
	StrCpy(CardData.cardExpirationDate, "6/25");
	printf("Input Data : cardExpirationDate (%s) ", CardData.cardExpirationDate);
	state = getCardExpiryDate(&CardData);
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
	//***************************************************//
	printf(" Case 3 : Date is OLD !! \n");
	StrCpy(CardData.cardExpirationDate, "06/21");
	printf("Input Data : cardExpirationDate (%s) ", CardData.cardExpirationDate);
	state = getCardExpiryDate(&CardData);
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
	//***************************************************//
	printf(" Case 4 : Date is NULL !! \n");
	StrCpy(CardData.cardExpirationDate, " ");
	printf("Input Data : cardExpirationDate (%s) ", CardData.cardExpirationDate);
	state = getCardExpiryDate(&CardData);
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
	//***************************************************//
}
void getCardPANTest(void)
{

	ST_cardData_t CardData;
	EN_cardError_t state;

	printf("Tester Name: Saeed Alaa \n");
	printf("Function Name: getCardPAN \n\n");

	printf(" Case 1 : PAN is right !! \n");
	StrCpy(CardData.primaryAccountNumber, "123456789123456789");
	printf("Input Data :  primaryAccountNumber (%s) ", CardData.primaryAccountNumber);
	state = getCardPAN(&CardData);
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
	//***************************************************//
	printf(" Case 2 : PAN is too short !! \n");
	StrCpy(CardData.primaryAccountNumber, "1234");
	printf("Input Data :  primaryAccountNumber (%s) ", CardData.primaryAccountNumber);
	state = getCardPAN(&CardData);
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
	//***************************************************//
	printf(" Case 3 : PAN is too long !! \n");
	StrCpy(CardData.primaryAccountNumber, "12345678912345678912345678");
	printf("Input Data :  primaryAccountNumber (%s) ", CardData.primaryAccountNumber);
	state = getCardPAN(&CardData);
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
	//***************************************************//
	printf(" Case 3 : PAN is NULL !! \n");
	StrCpy(CardData.primaryAccountNumber, "  ");
	printf("Input Data :  primaryAccountNumber (%s) ", CardData.primaryAccountNumber);
	state = getCardPAN(&CardData);
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
	//***************************************************//
}



