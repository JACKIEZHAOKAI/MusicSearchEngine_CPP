#include "WordIDHashTable.h"
#include "WordID.h"
#include <iostream>
#include <iomanip>
using namespace std;

WordIDHashTable::WordIDHashTable(){
    //initialize all the bucket in the key word hash table -1
    for(int i=0;i< SIZE;i++)
    {
        Table[i]=-1;
    }
}

WordIDHashTable::~WordIDHashTable(){}

int WordIDHashTable::hash(string keyword)
{
    int sum = 0;

    for(int i = 0; i < keyword.length(); i++)
        sum += (int) keyword[i];

    return sum;
}

void WordIDHashTable::insert(WordID wordID)
{
    int index=hash(wordID.getWord());

    // print WordIDHashTable
    cout<<"insert in order, name:"<<setw(12)<<wordID.getWord()<<"  ID "<<wordID.getID()<<"  table index:"<<index<<endl;

    Table[index]=wordID.getID();
}

void WordIDHashTable::remove(WordID wordID)
{
    int index=hash(wordID.getWord());

    //set wordID to
    Table[index]=-1;
}

int WordIDHashTable::searchID(string keyWord)
{
	int index=hash(keyWord);
	return Table[index];
}


