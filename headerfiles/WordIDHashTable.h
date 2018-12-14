/*
 * WordIDHashTable.h
 *
 *  Created on: Dec 6, 2016
 *      Author: xuzhaokai
 */

#ifndef WORDIDHASHTABLE_H_
#define WORDIDHASHTABLE_H_



#include "WordID.h"
#include <string>
using namespace std;
/*      THIS class is supposed to be initialized in main()
        and updating info after adding or deleting songs

 EX
    index for keyword       ID
    0       (hello)         12
    1      (fantasy)        67
    ...
 */

class WordIDHashTable{

public:

    WordIDHashTable();
    //constructor

    ~WordIDHashTable();
    //destructor

    int hash(string keyword);

    void insert(WordID wordID);

    void remove(WordID wordID);

    int searchID(string keyWord);
    //Input the keyword and find the WordID


private:
    static const int SIZE = 2000;

    int Table[SIZE];

};


#endif /* WORDIDHASHTABLE_H_ */
