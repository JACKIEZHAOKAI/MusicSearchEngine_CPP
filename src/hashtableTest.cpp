/*
 * hashtableTest.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: xuzhaokai
 */


#include <iostream>
#include "Hash Table.h"
#include "WordID.h"
#include "Song.h"

int main() {

    //Example code! will be added into main()

    int count=0;
    Hash_Table TableOfSongs;
    WordIDHashTable KeyWordIDSearchTable;


    //add songs
    vector<WordID> lyrics1;
    vector<WordID> lyrics2;
    vector<WordID> lyrics3;

    WordID word0("Hello");
    WordID word1("cows");
    WordID word2("friends");
    WordID word3("gives");
    WordID word4("beautiful");
    lyrics1.push_back(word0);
    lyrics1.push_back(word1);
    lyrics1.push_back(word2);
    lyrics1.push_back(word3);
    lyrics1.push_back(word4);

    WordID word02("goodbye");
    WordID word12("my");
    WordID word22("beautiful");
    WordID word32("friends");
    WordID word42("beautiful");
    WordID word52("life");
    lyrics2.push_back(word02);
    lyrics2.push_back(word12);
    lyrics2.push_back(word22);
    lyrics2.push_back(word32);
    lyrics2.push_back(word42);
    lyrics2.push_back(word52);


    WordID word03("distance");
    WordID word13("come");
    WordID word23("beautiful");
    WordID word33("cows");
    WordID word43("not");
    WordID word53("money");
    lyrics3.push_back(word03);
    lyrics3.push_back(word13);
    lyrics3.push_back(word23);
    lyrics3.push_back(word33);
    lyrics3.push_back(word43);
    lyrics3.push_back(word53);

    //initialize  songs
    Song song1("Hello World","CN", 2, 30, "alb",23, lyrics1, "xys");
    Song song2("Good bye","America", 3, 32, "ved",23, lyrics2, "xys");
    Song song3("Countryside life","UK", 3, 65, "ved",23, lyrics3, "xys");

    cout<<"Here is the KeyWordIDSearchTable"<<endl;

    TableOfSongs.insert(song1, count, KeyWordIDSearchTable);
    TableOfSongs.insert(song2, count, KeyWordIDSearchTable);
    TableOfSongs.insert(song3, count, KeyWordIDSearchTable);


    //search for a word and print
    cout<<endl<<endl;
    string WordForSearch1="beautiful";
    TableOfSongs.search(WordForSearch1,  KeyWordIDSearchTable);
    string WordForSearch2="friends";
    TableOfSongs.search(WordForSearch2,  KeyWordIDSearchTable);
    string WordForSearch3="cows";
    TableOfSongs.search(WordForSearch3,  KeyWordIDSearchTable);

	//Remove songs
	TableOfSongs.remove(song2, KeyWordIDSearchTable);

	cout<<"After removing: "<<song2.get_title()<<endl;

	 string WordForSearchR1="beautiful";
	 string WordForSearchR2="life";
	 TableOfSongs.search(WordForSearchR1,  KeyWordIDSearchTable);
	 TableOfSongs.search(WordForSearchR2,  KeyWordIDSearchTable);



    return 0;
}

/*test results
Here is the KeyWordIDSearchTable
insert in order, name:       Hello  ID 0  table index:500
insert in order, name:        cows  ID 1  table index:444
insert in order, name:         man  ID 2  table index:316
insert in order, name:       gives  ID 3  table index:542
insert in order, name:   beautiful  ID 4  table index:961
insert in order, name:     goodbye  ID 5  table index:745
insert in order, name:          my  ID 6  table index:230
insert in order, name:     friends  ID 7  table index:747
insert in order, name:        life  ID 8  table index:416
insert in order, name:    distance  ID 9  table index:843
insert in order, name:        come  ID 10  table index:420
insert in order, name:         not  ID 11  table index:337
insert in order, name:       money  ID 12  table index:552


The following songs contain the word: beautiful
there are 3 songs that have this keyword.
1. #1 Hello World
2. #2 Good bye
3. #3 Countryside life

The following songs contain the word: life
there are 1 songs that have this keyword.
1. #2 Good bye

After removing: #2 Good bye
The following songs contain the word: beautiful
there are 2 songs that have this keyword.
1. #1 Hello World
2. #3 Countryside life

The following songs contain the word: life
there are 0 songs that have this keyword.



 * */

