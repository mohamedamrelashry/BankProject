#pragma warning(disable : 4996)
#pragma once


#include<iostream>
#include<string>
#include "clsString.h"
#include "clsDate.h"

using namespace std;

class clsUtil
{
public: 


	/*		Srand()
			RandomNumber
			GetRandomCharacter
			GenerateWord
			GenerateKey
			GenerateKeys

			FillArrayWithRandomNumbers
			FillArrayWithRandomWords
			FillArrayWithRandomKeys
			Swap -> int , double , bool , char string, clsDate
			ShuffleArray(int arr[100]), int arrLength)	
			ShuffleArray(string arr[100]), int arrLength)	
			Tabs
			EncryptText
			DecryptText	*/


	enum enCharType {
		SmallLetter = 1, CapitalLetter = 2,
		Digit = 3, MixChars = 4, SpecialCharacter = 5
	};
	static void  Srand()
	{
		//Seeds the random number generator in C++, called only once
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int From, int To)
	{ 
		int RandNum = rand() % (To - From + 1) + From;
		return RandNum;		
	}
	
	static char GetRandomCharacter(enCharType CharType)
	{

		if (CharType == MixChars)
		{
			//Capital/Samll/Digits only
			CharType = (enCharType)RandomNumber(1, 3);

		}
		switch (CharType)
		{

		case enCharType::SmallLetter:
		{
			return char(RandomNumber(97, 122)); // char( 110 ) = n 
			break;
		}

		case enCharType::CapitalLetter:
		{
			return char(RandomNumber(65, 90));
			break;
		}

		case enCharType::SpecialCharacter:
		{
			return char(RandomNumber(33, 47));
			break;
		}

		case enCharType::Digit:
		{
			return char(RandomNumber(48, 57));
			break;
		}

		}
	}
	static string GenerateWord(enCharType CharType, short Length)
	{
		string Word;
		for (int i = 1; i <= Length; i++)  // 1 <= 4 ? | 2 <= 4 ... 
		{
			Word += GetRandomCharacter(CharType);
		}
		return Word;
	}
	static string GenerateKey(short Length = 4 ,enCharType CharType = enCharType::MixChars)
	{
		string Key = "";
		Key = GenerateWord(CharType, Length) + "-";
		Key = Key + GenerateWord(CharType, Length) + "-";
		Key = Key + GenerateWord(CharType, Length) + "-";
		Key = Key + GenerateWord(CharType, Length);
		return Key;
	}
	static void GenerateKeys(short NumberOfKeys , enCharType CharType)
	{
		for (int i = 1; i <= NumberOfKeys; i++)
		{
			cout << "Kay [" << i << "] : " << GenerateKey(CharType) << endl;
		}
	}
	//
	static void Swap(int& A, int& B)
	{
		int Temp;

		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(double& A, double& B)
	{
		double Temp;

		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(string& A, string& B)
	{
		string Temp;

		Temp = A;
		A = B;
		B = Temp;
	}
	//shuffle
	static void ShuffleArray(int arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1,
				arrLength) - 1]);
		}
	}
	static void ShuffleArray(string arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1,
				arrLength) - 1]);
		}
	} 
	
	static void FillArrayWithRandomNumbers(int arr[100], int arrLength , int from ,int to )
	{
	
		for (int i = 0; i < arrLength; i++)
			arr[i] = RandomNumber(from, to);
	}
	static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType ,short wordLength )
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateWord(CharType, wordLength);
	}
	static void FillArrayWithRandomKeys(string arr[100], int arrLength , enCharType CharType, short Length  = 4) {
		for (int i = 0; i < arrLength; i++)
		{
			arr[i] = GenerateKey(Length,CharType);
		}
	}
	
	
	static string EncryptText(string Text, short EncryptionKey = 5)
	{
		
		for (int i = 0; i <= Text.length(); i++)
		{  

			Text[i] = char((int)Text[i] + EncryptionKey);
		}
		return Text;  
	}
	static string DecryptText(string Text, short EncryptionKey = 5)
	{
		for (int i = 0; i <= Text.length(); i++)
		{
			Text[i] = char((int)Text[i] - EncryptionKey);
			
		}
		return Text;  
	}
	static string NumberToText(int Number)
	{

		if (Number == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
		"Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
		  "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

			return  arr[Number] + " ";

		}

		if (Number >= 20 && Number <= 99)
		{
			string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return  arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return  "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return  "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return  "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return  "One Billion " + NumberToText(Number % 1000000000);
		}
		else
		{
			return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}


	}



};

