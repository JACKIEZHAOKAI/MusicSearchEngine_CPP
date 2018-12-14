/*
 * Hash Table.h
 *
 *  Created on: Dec 6, 2016
 *      Author: xuzhaokai
 */

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include "WordID.h"
#include "WordIDHashTable.h"
#include "Song.h"
#include "List.h"
#include <string>
#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

class Hash_Table {

public:
    /**Constructors*/

    Hash_Table();
    //constructor

    ~Hash_Table();
    //destructor

    /**Access Functions*/

    void search(string keyWord,  WordIDHashTable& searchTable);
    //call WordIDHashTable to searches for index of a keyword
    //returns the ID of the keyword

    /**Manipulation Procedures*/

    //every time insert new songs OR remove old songs, update the WordIDHashTable

    void insert(Song song, int& count, WordIDHashTable& searchTable);
    //inserts the song into the key word bucket
    // if no keyword, build it first




    /**Additional Functions*/

    void print_bucket(int ID,string keyword);
    //after successfully searched the keyword in the hash table and
    //find its corresponding ID, print all the titles of songs containing this bucket

    void remove(string songtitle, WordIDHashTable& searchTable, vector<Song> Vsong);
    //remove the song from the key word bucket


private:
    static const int SIZE = 2000;

    BinarySearchTree Table[SIZE];

};



#endif /* HASH_TABLE_H_ */
