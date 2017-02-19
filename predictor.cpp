//============================================================================
// Name        : predictor.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool initDictionary()
{
	ifstream inFile;
	inFile.open("light_a.txt");

	//Check for error
	if (inFile.fail())
	{
		cerr<<"Error opening dictionay"<<endl;
		return false;
	}

	ofstream outFile;
	string word;
	string filename;
	const char *constFilename;
	char currentC = 0;


	while(!inFile.eof())
	{
		inFile >> word;

		if(word.at(0) > currentC) //Detect next letter
		{
			//Create a file for each letter
			if(outFile.is_open())
				outFile.close();

			currentC = word.at(0);

			filename = ".txt";
			filename.insert(0,1,currentC);

			constFilename=filename.c_str();
			outFile.open(constFilename);
		}

		if(outFile.is_open())
		{
			//Write the words in the corresponding file
			outFile<<word<<endl;
		}
	}

	if(outFile.is_open())
		outFile.close();

	return true;
}

vector<string> loadWordsWith(char c)
{
	vector<string> wordsWithCh;
	ifstream inFile;
	const char *constFilename;
	string filename;
	string word;

	filename = ".txt";
	filename.insert(0,1,c);
	constFilename=filename.c_str();
	inFile.open(constFilename);

	while(!inFile.eof())
	{
		inFile >> word;
		wordsWithCh.push_back(word);
	}

	inFile.close();

	return wordsWithCh;
}

void discardWordsWithAt(char c,int pos, vector<string> &wordsVec)
{
	vector<string> wordsVecTemp;
	string word;
	for(int i=0;i<wordsVec.size();i++)
	{
		word = wordsVec[i];
		cout<<word.size()<<" "<<pos<<endl;
		if(word.size() > pos)
		{
			if(word.at(i) == c)
				wordsVecTemp.push_back(word);
		}
	}
	wordsVec=wordsVecTemp;
}

int main(int argc,char *argv[])
{
	bool initRes = initDictionary();
	const char stopC = '0';
	char inputC;
	bool isFirstC = true;
	vector<string> wordsWithCh, wordsWithChCopy;
	int pos = 0;


	if(initRes)
	{
		inputC=getchar();
		getchar();
		while(inputC != stopC)
		{
			if (isFirstC)
			{
				//Load letters with the first letter of the word
				wordsWithCh = loadWordsWith(inputC);
				wordsWithChCopy = wordsWithCh;
				isFirstC = false;
			}
			else
			{
				discardWordsWithAt(inputC,pos,wordsWithChCopy);
			}

			//Print prediction
			int limit = 10;
			if(wordsWithChCopy.size() < limit)
				limit = wordsWithChCopy.size();


			for(int i=0;i<limit;i++)
			{
				cout<<wordsWithChCopy[i]<<endl;
			}

			pos++;
			inputC=getchar();
			getchar();
		}
	}

	return 0;
}

