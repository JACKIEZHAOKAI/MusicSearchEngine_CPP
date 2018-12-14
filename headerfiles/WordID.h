/*
 * WordID.h
 *
 *  Created on: Dec 6, 2016
 *      Author: xuzhaokai
 */

#ifndef WORDID_H_
#define WORDID_H_

#include <string>
using namespace std;

class WordID{

private:
    int ID;
    string word;

public:

    //constructor
    WordID(string s);

    void setID(int theID);

    void setWord(string theWord);

    int getID();

    string getWord();

};


#endif /* WORDID_H_ */
