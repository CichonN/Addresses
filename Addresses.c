// ------------------------------------------------------------------------------------------
// Name: Neina Cichon
// Abstract: Addresses
// Date: 2020-11-08
// ------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable : 4996)

// --------------------------------------------------------------------------------
// Constants
// --------------------------------------------------------------------------------
const int intARRAY_SIZE = 100;
#define true 1
#define false 0

// --------------------------------------------------------------------------------
// User Defined Types (UDTs)
// --------------------------------------------------------------------------------
typedef int boolean;

typedef struct
{
	long lngRecordID;
	char strFullName[50];
	char strFirstName[50];
	char strMiddleName[50];
	char strLastName[50];
	char strStreet[100];
	char strCity[50];
	char strState[50];
	char strZipCode[50];
} udtAddressType;


// --------------------------------------------------------------------------------
// Prototypes
// --------------------------------------------------------------------------------
//int OpenInputFile(char strFileName[], FILE** ppfilInput);

void InitializeAddressList(udtAddressType audtAddressList[]);
void InitializeAddress(udtAddressType* pudtAddress);

void PopulateAddressList(udtAddressType audtAddressList[]);
int OpenInputFile(char strFileName[], FILE** ppfilInput);
void AddAddressToArray(char strAddress[], udtAddressType* pudtAddress);
void GetNextField(char strNextField[], char strSource[], char chrDelimiter);
void SplitFullName(udtAddressType* pudtAddress, char strFullName[]);

void PrintAddressList(udtAddressType audtAddressList[]);
void PrintAddress(int intIndex, udtAddressType udtAddress);

void StringCopy(char strDestination[], char strSource[]);
int StringLength(char strSource[]);
void AppendString(char strDestination[], char strSource[]);
int FindLetterIndex(char strSource[], char chrLetterToFind);
void Trim(char strSource[]);
boolean IsWhiteSpace(char chrLetterToCheck);
int CountWords(char strSource[]);


// --------------------------------------------------------------------------------
// Name: main
// Abstract: This is where the program starts.
// --------------------------------------------------------------------------------
void main()
{
	udtAddressType audtAddressList[100];
	InitializeAddressList(audtAddressList);
	PopulateAddressList(audtAddressList);
	PrintAddressList(audtAddressList);

	system("pause");
}

// --------------------------------------------------------------------------------
// Name: InitializeAddressList
// Abstract: Initialize all the addresses in the list
// --------------------------------------------------------------------------------
void InitializeAddressList(udtAddressType audtAddressList[])
{
	int intIndex = 0;

	for (intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1)
	{
		//Pass a single array element  by pointer
		InitializeAddress(&audtAddressList[intIndex]);
	}
}

// --------------------------------------------------------------------------------
// Name: InitializeAddress
// Abstract: Set all the values to 0 or empty strings
// --------------------------------------------------------------------------------
void InitializeAddress(udtAddressType* pudtAddress)
{
	pudtAddress->lngRecordID = 0;

	StringCopy(pudtAddress->strFirstName, "");
	StringCopy(pudtAddress->strMiddleName, "");
	StringCopy(pudtAddress->strLastName, "");
	StringCopy(pudtAddress->strStreet, "");
	StringCopy(pudtAddress->strCity, "");
	StringCopy(pudtAddress->strState, "");
	StringCopy(pudtAddress->strZipCode, "");
}

// --------------------------------------------------------------------------------
// Name: PopulateAddressList
// Abstract: Load the addresses from a file into the array.
// --------------------------------------------------------------------------------
void PopulateAddressList(udtAddressType audtAddressList[])
{
	//Declare a file pointer
	FILE* pfillInput = 0;
	int intResultFlag = 0;
	char strBuffer[100] = "";
	char chrLetter = 0;
	int intIndex = 0;

	//Try to open the file for reading (notice you have to double up the backslashes)
	intResultFlag = OpenInputFile("c:\\temp\\Addresses1.txt", &pfillInput);

	//Was file opened?
	if (intResultFlag == 1)
	{
		//yes, read records until EOF
		while (feof(pfillInput) == 0)
		{
			//Read next line from file
			ReadNextLineFromFile(strBuffer, pfillInput);

			AddAddressToArray(strBuffer, &audtAddressList[intIndex]);
			intIndex += 1;

		}
		//clean up
		fclose(pfillInput);
	}

}


// --------------------------------------------------------------------------------
// Name: OpenInputFile
// Abstract: Open the file for reading.  Return true if successful.
// --------------------------------------------------------------------------------
int OpenInputFile(char strFileName[], FILE** ppfilInput)
{

	int intResultFlag = 0;

	// Open the file for reading
	*ppfilInput = fopen(strFileName, "rb");

	// Success?
	if (*ppfilInput != 0)
	{
		// Yes
		intResultFlag = 1;
	}
	else
	{
		// No
		printf("Error opening %s for reading!!!\n", strFileName);
	}

	return intResultFlag;

}

// --------------------------------------------------------------------------------
// Name: ReadNextLineFromFile
// Abstract: Read until end of line or end of file
// --------------------------------------------------------------------------------
int ReadNextLineFromFile(char strBuffer[], FILE* pfilInput)
{
	char chrLetter = 0;
	int intIndex = 0;



	while (feof(pfilInput) == 0)
	{
		chrLetter = fgetc(pfilInput);
		strBuffer[intIndex] = chrLetter;
		intIndex += 1;

		if (chrLetter == '\n')
		{
			//stop reading
			break;
		}

	}
	//terminate
	strBuffer[intIndex] = 0;

}



// --------------------------------------------------------------------------------
// Name: PrintAddressList
// Abstract: Print all the addresses
// --------------------------------------------------------------------------------
void PrintAddressList(udtAddressType audtAddressList[])
{
	int intIndex = 0;

	for (intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1)
	{
		if (audtAddressList[intIndex].lngRecordID >= 1)
		{
			//Pass a single array element
			PrintAddress(intIndex, audtAddressList[intIndex]);

		}
	}
}

// --------------------------------------------------------------------------------
// Name: PrintAddress
// Abstract: Print all the addresses
// --------------------------------------------------------------------------------
void PrintAddress(int intIndex, udtAddressType udtAddress)
{
	printf("\n");
	printf("Address #%2d ---------------------------------------\n", intIndex + 1);
	printf("\tRecord ID     : %ld\n", udtAddress.lngRecordID);
	printf("\tFirst Name    : %s\n", udtAddress.strFirstName);
	printf("\tMiddle Name   : %s\n", udtAddress.strMiddleName);
	printf("\tLast Name     : %s\n", udtAddress.strLastName);
	printf("\tAddress       : %s\n", udtAddress.strStreet);
	printf("\tCity          : %s\n", udtAddress.strCity);
	printf("\tState         : %s\n", udtAddress.strState);
	printf("\tZipcode       : %s\n", udtAddress.strZipCode);

}

// --------------------------------------------------------------------------------
// Name: String Copy
// Abstract: Copy the source to the destination
// --------------------------------------------------------------------------------
void StringCopy(char strDestination[], char strSource[])
{
	int intIndex = 0;

	//Copy each character
	while (strSource[intIndex] != 0)
	{
		strDestination[intIndex] = strSource[intIndex];
		intIndex += 1;
	}
	//Terminate
	strDestination[intIndex] = 0;
}

// --------------------------------------------------------------------------------
// Name: AddAddressToArray
// Abstract: Add address to the array
// --------------------------------------------------------------------------------
void AddAddressToArray(char strAddress[], udtAddressType* pudtAddress)
{
	char strNextField[50] = "";

	// Add comma to the end of string
	AppendString(strAddress, ",");

	// Record ID
	GetNextField(strNextField, strAddress, ',');
	pudtAddress->lngRecordID = atol(strNextField);

	// Full Name
	GetNextField(strNextField, strAddress, ',');
	SplitFullName(pudtAddress, strNextField);
	//StringCopy(pudtAddress->strFullName, strNextField);

	// Street Address
	GetNextField(strNextField, strAddress, ',');
	StringCopy(pudtAddress->strStreet, strNextField);

	// City
	GetNextField(strNextField, strAddress, ',');
	StringCopy(pudtAddress->strCity, strNextField);

	// State
	GetNextField(strNextField, strAddress, ',');
	StringCopy(pudtAddress->strState, strNextField);

	// Zip Code
	GetNextField(strNextField, strAddress, ',');
	StringCopy(pudtAddress->strZipCode, strNextField);
}


// --------------------------------------------------------------------------------
// Name: StringLength
// Abstract: Return the string length
// --------------------------------------------------------------------------------
int StringLength(char strSource[])
{
	int intIndex = 0;
	int intLength = 0;

	// Pre-test because string may be empty
	while (strSource[intIndex] != 0)
	{
		intIndex += 1;
	}

	intLength = intIndex;

	return intLength;
}



//// --------------------------------------------------------------------------------
//// Name: GetNextField
//// Abstract: Get next field in record and remove info up to delimiter
//// --------------------------------------------------------------------------------
void GetNextField(char strNextField[], char strSource[], char chrDelimiter)
{
	int intDelimiterIndex = 0;
	int intIndex = 0;
	char strBuffer[100] = "";

	//Find delimiter
	intDelimiterIndex = FindLetterIndex(strSource, chrDelimiter);

	if (intDelimiterIndex >= 0)
	{
		//Copy everything up to comma into next field
		for (intIndex = 0; intIndex < intDelimiterIndex; intIndex += 1)
		{
			strNextField[intIndex] = strSource[intIndex];
		}

		//terminate
		strNextField[intIndex] = 0;

		intIndex = 0;

		//Copy everything from comma up to end of string
		while (strSource[intDelimiterIndex + intIndex + 1] != 0)
		{
			strBuffer[intIndex] = strSource[intDelimiterIndex + intIndex + 1];
			intIndex += 1;
		}
		//terminate
		strBuffer[intIndex] = 0;

		//copy back to address
		StringCopy(strSource, strBuffer);

		Trim(strSource);
		Trim(strNextField);
	}


}

//// --------------------------------------------------------------------------------
//// Name: SplitFullName
//// Abstract: Split Name into First Middle Last
//// --------------------------------------------------------------------------------
void SplitFullName(udtAddressType* pudtAddress, char strFullName[])
{
	int intWordCount = 0;
	char strNextField[50] = "";

	intWordCount = CountWords(strFullName);

	//Add comma to end to make it uniform
	AppendString(strFullName, " ");

	if (intWordCount == 3)
	{
		//First Name
		GetNextField(strNextField, strFullName, ' ');
		StringCopy(pudtAddress->strFirstName, strNextField);

		//Middle Name
		GetNextField(strNextField, strFullName, ' ');
		StringCopy(pudtAddress->strMiddleName, strNextField);

		//Last Name
		StringCopy(pudtAddress->strLastName, strFullName);
	}
	else if (intWordCount == 2)
	{
		//First Name
		GetNextField(strNextField, strFullName, ' ');
		StringCopy(pudtAddress->strFirstName, strNextField);

		//Last Name
		StringCopy(pudtAddress->strLastName, strFullName);
	}
}




//// --------------------------------------------------------------------------------
//// Name: StringCopy
//// Abstract: Copy the source to the destination
//// --------------------------------------------------------------------------------
//void StringCopy(char strDestination[], char strSource[])
//{
//	int intIndex = 0;
//
//	// Copy each character
//	while (strSource[intIndex] != 0)
//	{
//		strDestination[intIndex] = strSource[intIndex];
//		intIndex += 1;
//	}
//
//	// Terminate
//	strDestination[intIndex] = 0;
//
//}


// --------------------------------------------------------------------------------
// Name: AppendString
// Abstract: Append the source to the end of the destinatoin.
// --------------------------------------------------------------------------------
void AppendString(char strDestination[], char strSource[])
{
	int intDestinationLength = 0;
	int intIndex = 0;

	// Find the length
	intDestinationLength = StringLength(strDestination);

	// Copy each character
	while (strSource[intIndex] != 0)
	{
		strDestination[intDestinationLength + intIndex] = strSource[intIndex];

		intIndex += 1;
	}

	// Terminate
	strDestination[intDestinationLength + intIndex] = 0;

}


// --------------------------------------------------------------------------------
// Name: FindLetterIndex
// Abstract: Find first occurence of letter (case-sensitive) from left to right.
// --------------------------------------------------------------------------------
int FindLetterIndex(char strSource[], char chrLetterToFind)
{
	int intLetterToFindIndex = -1;
	int intIndex = 0;

	// Check character
	while (strSource[intIndex] != 0)
	{
		// Is this the character for which we are looking
		if (strSource[intIndex] == chrLetterToFind)
		{
			// Yes, save the index
			intLetterToFindIndex = intIndex;

			// Stop searching
			break;
		}
		intIndex += 1;
	}

	return intLetterToFindIndex;
}



// --------------------------------------------------------------------------------
// Name: Trim
// Abstract: Remove leading and trailing whitespace (space, tab or newline)
// --------------------------------------------------------------------------------
void Trim(char strSource[])
{

	int intIndex = 0;
	int intFirstNonWhitespaceIndex = -1;
	int intLastNonWhitespaceIndex = 0;
	int intSourceIndex = 0;
	int intDestinationIndex = 0;

	// Default first non-whitespace character index to end of string in case string is all whitespace
	// Bug fix.  Not in video.
	intFirstNonWhitespaceIndex = StringLength(strSource);

	// Find first non-whitespace character
	while (strSource[intIndex] != 0)
	{
		// Non-whitespace character?
		if (IsWhiteSpace(strSource[intIndex]) == false)
		{
			// Yes, save the index
			intFirstNonWhitespaceIndex = intIndex;

			// Stop searching!
			break;
		}

		// Next character
		intIndex += 1;
	}

	// Find the last non-whitespace character
	while (strSource[intIndex] != 0)
	{
		// Non-whitespace character?
		if (IsWhiteSpace(strSource[intIndex]) == false)
		{
			// Yes, save the index
			intLastNonWhitespaceIndex = intIndex;
		}

		// Next character
		intIndex += 1;
	}

	// Any non-whitepsace characters?
	if (intFirstNonWhitespaceIndex >= 0)
	{
		// Yes, copy everything in between
		for (intSourceIndex = intFirstNonWhitespaceIndex; intSourceIndex <= intLastNonWhitespaceIndex; intSourceIndex += 1)
		{
			// Copy next character
			strSource[intDestinationIndex] = strSource[intSourceIndex];

			intDestinationIndex += 1;
		}
	}

	// Terminate 
	strSource[intDestinationIndex] = 0;
}



// --------------------------------------------------------------------------------
// Name: IsWhiteSpace
// Abstract: Return true if letter is a space, tab, newline or carriage return
// --------------------------------------------------------------------------------
boolean IsWhiteSpace(char chrLetterToCheck)
{
	boolean blnIsWhiteSpace = false;

	// Space
	if (chrLetterToCheck == ' ') blnIsWhiteSpace = true;

	// Tab
	if (chrLetterToCheck == '\t') blnIsWhiteSpace = true;

	// Carriarge return
	if (chrLetterToCheck == '\r') blnIsWhiteSpace = true;

	// Line feed
	if (chrLetterToCheck == '\n') blnIsWhiteSpace = true;

	return blnIsWhiteSpace;
}


// --------------------------------------------------------------------------------
// Name: CountWords
// Abstract: Count the words in a string
// --------------------------------------------------------------------------------
int CountWords(char strSource[])
{
	int intWordCount = 0;
	int intIndex = 0;
	char chrCurrentLetter = 0;
	char chrPreviousLetter = ' ';

	// Copy each character
	while (strSource[intIndex] != 0)
	{
		chrCurrentLetter = strSource[intIndex];

		// Word boundary (space followed by non-space)?
		if (chrPreviousLetter == ' ' && chrCurrentLetter != ' ')
		{
			// Yes, count it
			intWordCount += 1;
		}

		// Save current character
		chrPreviousLetter = chrCurrentLetter;

		// Next
		intIndex += 1;
	}

	return intWordCount;
}