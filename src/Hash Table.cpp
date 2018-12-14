#include "Hash Table.h"
#include <string>
#include <iostream>
using namespace std;


Hash_Table::Hash_Table(){}
//constructor

Hash_Table::~Hash_Table(){}
//destructor


void Hash_Table::insert(Song song, int& count, WordIDHashTable& searchTable)
{
    //use a loop to check existed keyword
    // also update the WordIDHashTable
    for(int i=0;i<song.get_lyrics().size();i++)
    {
        //for new key words, offer an ID
    	//if the keyword existed in former songs, not offer new ID

    	//check if the keyword is in the WordIDHashTable
        if (searchTable.searchID(song.getLyricsAt(i).getWord()) == -1)
        {
        	//assign ID
            song.setLyricsAt(i,count);

            //insert new WordID into the WordIDHashTable !!!
            searchTable.insert(song.getLyricsAt(i));

            count++;
        }
        else
        {
        	 int ID = searchTable.searchID(song.getLyricsAt(i).getWord());
        	 song.setLyricsAt(i,ID);
        }

    }

    //add the song including the keyword into the hash table
     for(int i=0;i<song.get_lyrics().size();i++)
    {
        int ID=song.getLyricsAt(i).getID();
        int check=0;	//to check if songs already existed
        				//existed: check=0		else check=1

        Table[ID].begin_cursor();

        for(int j=0; j<Table[ID].get_length();j++)
        {
            //if duplicated song
            if( Table[ID].get_cursor()==song)
            {
                check=1;
            }
            Table[ID].move_cursor();
        }

        Table[ID].begin_cursor();
        //add the song into the bucket (only if no duplicated song in the bucket)
        if(check==0)
        {
        	//if the bucket is empty
        	if(Table[ID].get_length()==0)
        	{
        		Table[ID].add_start(song);
        	}
        	// add ahead of the list
        	else if (Table[ID].get_start().get_title() > song.get_title())
        	{
        		Table[ID].add_start(song);
        	}
        	//add to the end of the list
        	else if( Table[ID].get_end().get_title() <= song.get_title() )
        	{
        		Table[ID].add_end(song);
        	}
        	else
        	{
        		while(!Table[ID].off_end())
				{

					if( Table[ID].get_cursor().get_title() > song.get_title())
					{
						Table[ID].add_cursor(song);
					}
					else
					{
						Table[ID].move_cursor();
					}

				}

        	}

        }
    }

}


void Hash_Table::remove(Song song, WordIDHashTable& searchTable)
{
    //loop to run for all the key words in the lyrics
    for(int i=0;i<song.get_lyrics().size();i++)
    {
    	string RemovedWord=song.getLyricsAt(i).getWord();
        int ID=searchTable.searchID(RemovedWord);

        // delete the song from the key word bucket
		Table[ID].begin_cursor();

		for(int j=0; j<Table[ID].get_length();j++)
		{
			if( Table[ID].get_cursor()==song)
			{
				Table[ID].remove_cursor();
			}
			else
			{
				Table[ID].move_cursor();
			}
		}


    }

}

void Hash_Table::search(string keyWord, WordIDHashTable& searchTable)
{
	//all the ID in the WordIDHashTable are initialized to be -1, if return -1,
	//means the keyword is not found

	int ID=searchTable.searchID(keyWord);

	if(ID!=-1)
	{
		print_bucket( ID,keyWord);
	}
	else
	{
		cout<<"Sorry, the keyword <"<<keyWord<<"> is not found in any songs."<<endl;
	}

}


void Hash_Table::print_bucket(int ID,string keyword)
{
    assert(0<=ID && ID<SIZE);

    cout<<"The following songs contain the word: "<<keyword<<endl;
    cout<<"there are "<<Table[ID].get_length()<<" songs that have this keyword."<<endl;


    if(Table[ID].get_length()>0)
    {
        Table[ID].begin_cursor();

        for(int i=1;i<=Table[ID].get_length();i++)
        {
            cout<<i<<". "<<Table[ID].get_cursor().get_title()<<endl;
            Table[ID].move_cursor();
        }

        cout<<endl;
    }

}







