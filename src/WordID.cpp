#include <iostream>

using namespace std;

WordID:: WordID(string s)
{
    ID=-1;
    word= s;
}

void WordID::setID(int theID)
{
	ID = theID;
}

void WordID::setWord(string theWord)
{ word = theWord; }

int WordID::getID()
{  return ID;}

string WordID::getWord()
{   return word;}


