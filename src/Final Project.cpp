#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "Song.h"
#include "Hash Table.h"
#include "BinarySearchTree2.h"
#include "List.h"
#include "WordID.h"

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;

void Print_menu() {
	cout << "\n\t      Team 3: _COUNTRY SONGS_ PROJECT" << endl << endl;
	cout << "\t. ======================================== ." << endl;
	cout << "\t|   Please enter your choice from 1-->7    |" << endl;
	cout << "\t| 1. Add a new song                        |" << endl;
	cout << "\t| 2. Delete song   :                       |" << endl;
	cout << "\t| 3. Search engine:                        |" << endl;
	cout << "\t| 4. List songs   :                        |" << endl;
	cout << "\t| 5. Write data to file:                   |" << endl;
	cout << "\t| 6. Statistics:                           |" << endl;
	cout << "\t| 7. Quit                                  |" << endl;
	cout << "\t. ======================================== ." << endl;
	cout << endl;
}

int CountWords(string s) {
	int word_count(0);
	stringstream ss(s);
	string word;
	while (ss >> word)
		++word_count;
	return word_count;
}

string removePunc(string &my_input)
{
     for(int i=0; i <my_input.length(); i++)
     {
             if(ispunct(my_input[i]))
                  my_input[i]= ' ';
     }

      return my_input;
}

void remove_words(int wordsCount, string keywords[]) {
	ifstream removeFile;
	string wordsFile = "WordsToRemove.txt";
	removeFile.open("WordsToRemove.txt");
	string toRemove;
	while (getline(removeFile, toRemove)) {
		for (int b = 0; b < wordsCount; b++) {

			if (toRemove == keywords[b]) {
				keywords[b].erase(0, keywords[b].length());
			} else {
				continue;
			}
		}
	}
}

void print_song(ofstream& fout, BinarySearchTree BST) {
	BST.in_order_print_to_file(fout);

}

string to_string(int i) {
	std::stringstream ss;
	return ss.str();
}

int main() {

	BinarySearchTree BST;
	BinarySearchTree2 BST2;
	int count=0;
	Hash_Table TableOfSongs;
	WordIDHashTable KeyWordIDSearchTable;
	Song song[1000];
	string title, artist, album, length, year;
	int minute, second;
	int released_year;
	string officialLyrics; // ONLY used to display
	vector<Song> Vsong;

	string s;
	int index = -1; // keep track of # of songs
	for (int i = 1; i <= 15; i++) {
		ifstream infile;
		string fileName = SSTR(i)+ ".txt";
		infile.open(fileName.c_str());
		if (infile.fail()) {
			cout << "Input file failed to open!" << endl;
			exit(-1);
		}
		getline(infile, s);
		title = s;
		getline(infile, s);
		artist = s;
		getline(infile, s);
		album = s;
		getline(infile, s);
		year = s;
		istringstream(year) >> released_year;
		getline(infile, s);
		length = s;
		istringstream(length) >> minute;
		getline(infile, s);
		length = s;
		istringstream(length) >> second;
		string lyrics = ""; // used to remove words, find by keywords
		while (!infile.eof()) {
			getline(infile, s);
			lyrics = lyrics + s + "\n";
		}
		officialLyrics = lyrics;

		int wordsCount = CountWords(lyrics);
		string keywords[wordsCount];
		stringstream ssin(lyrics);
		int j = 0;
		while (ssin.good() && j < wordsCount) {
			ssin >> keywords[j];
			j++;
		}

		for (int a = 0; a < wordsCount; a++) {
			for (int j = 0; j < keywords[a].length(); j++) {
				keywords[a][j] = tolower(keywords[a][j]);
			}
		}

		string temp[wordsCount];

				for (int a = 0; a < wordsCount; a++) {
					temp[a] = keywords[a];
					keywords[a] = removePunc(temp[a]);

					//cout << keywords[a] << endl;
				}

		/* WORDS REMOVAL */
		ifstream removeFile;
		string wordsFile = "WordsToRemove.txt";
		removeFile.open("WordsToRemove.txt");
		string toRemove;
		while (getline(removeFile, toRemove)) {
			for (int b = 0; b < wordsCount; b++) {

				if (toRemove == keywords[b]) {
					keywords[b].erase(0, keywords[b].length());
				} else {
					continue;
				}
			}
		}
		removeFile.close();

		vector<WordID> keys; // VECTORRRRRRRRRRRRRRRRR

		for (int a = 0; a < wordsCount; a++) {
			WordID x(keywords[a]);
			keys.push_back(x);
			//cout << keys[a].getWord() << endl;

		}

		song[i - 1].set_title(title);
		song[i - 1].set_artist(artist);
		song[i - 1].set_album(album);
		song[i - 1].set_lyrics(keys);
		song[i - 1].set_releasedYear(released_year);
		song[i - 1].set_minute(minute);
		song[i - 1].set_second(second);
		song[i - 1].set_officialLyrics(officialLyrics);
		BST.insert(song[i-1]);
		BST2.insert(song[i-1]);
		TableOfSongs.insert(song[i-1], count, KeyWordIDSearchTable);
		Vsong.push_back(song[i-1]);

		index++;
		infile.close();
	}

	ofstream outfile;
	outfile.open("CountrySongs.txt");
	if (outfile.fail()) {
				cout << "Output file failed to open!" << endl;
				//exit(-1);
			}

	string choice;
	int intChoice;
	string songToDelete;
	do {

		Print_menu();
		do {
			cout << "\tYour choice: ";
			cin >> intChoice;
		} while (intChoice > 7 || intChoice < 1);

		switch (intChoice) {

		case 1: {	//Add a new song

			cout << "\t Enter information" << endl;
			cin.ignore();
			cout << "\t Title: ";
			getline(cin, title);
			cout << "\t Artist's name: ";
			getline(cin, artist);
			cout << "\t Album: ";
			getline(cin, album);
			string min, sec;
			cout << "\t Length: minute: ";
			getline(cin, min);
			istringstream(min) >> minute;
			cout << "\t second:  ";
			getline(cin, sec);
			istringstream(sec) >> second;
			cout << "\t Released Year: ";
			getline(cin, year);
			istringstream(year) >> released_year;
			string lyrics;
			cout << "\t (Please enter @ in a new line to end lyrics) Lyrics: ";
			while (s != "@") {
				getline(cin, s);
				lyrics = lyrics + s + "\n";
			}
			officialLyrics = lyrics;
			officialLyrics.replace(officialLyrics.end()-2,officialLyrics.end(),"");
			int wordsCount = CountWords(lyrics);
			string keywords[wordsCount];
			stringstream ssin(lyrics);
			int j = 0;
			while (ssin.good() && j < wordsCount) {
				ssin >> keywords[j];
				j++;
			}

			for (int a = 0; a < wordsCount; a++) {
				for (int j = 0; j < keywords[a].length(); j++) {
					keywords[a][j] = tolower(keywords[a][j]);
				}
			}

			/* WORDS REMOVAL */
			ifstream removeFile;
			string wordsFile = "WordsToRemove.txt";
			removeFile.open("WordsToRemove.txt");
			string toRemove;
			while (getline(removeFile, toRemove)) {
				for (int b = 0; b < wordsCount; b++) {
					if (toRemove == keywords[b]) {
						keywords[b].erase(0, keywords[b].length());
					} else {
						continue;
					}
				}
			}
			removeFile.close();

			vector<WordID> keys; // VECTORRRRRRRRRRRRRRRRR

			for (int a = 0; a < wordsCount; a++) {
				WordID x = WordID(keywords[a]);
				keys.push_back(x);
			}
			song[index].set_title(title);
			song[index].set_artist(artist);
			song[index].set_album(album);
			song[index].set_lyrics(keys);
			song[index].set_releasedYear(released_year);
			song[index].set_minute(minute);
			song[index].set_second(second);
			song[index].set_officialLyrics(officialLyrics);
			BST.insert(song[index]);
			BST2.insert(song[index]);
			TableOfSongs.insert(song[index], count, KeyWordIDSearchTable);
			Vsong.push_back(song[index]);

			index++;

			break;
		}

			//delete song
		case 2: {
			cin.ignore();
			cout << "Enter a song title to delete: ";
			getline(cin, songToDelete);
			BST.remove(songToDelete);
			BST2.remove(songToDelete);
			TableOfSongs.remove(songToDelete, KeyWordIDSearchTable, Vsong);
			//TableOfSongs.remove(songToDelete, KeyWordIDSearchTable);
			index--;
			break;
		}
		case 3: {
			char chose;
			cout << "\t  a. Search by title " << endl;
			cout << "\t  b. Search by artist " << endl;
			cout << "\t  c. Search by key word " << endl;
			cout << "\t  d. Back to main menu" << endl;
			cout << "\tChoose a, b, c or d: ";
			cin >> chose;
			do {
				switch (chose) {
				case 'a': {
					cout << "Enter your title: ";
					cin.ignore();
					getline(cin, title);

					BST.find(title);

					break;
				}
				case 'b': {
					cout << "Enter your artist: ";
					cin.ignore();
					getline(cin, artist);

					BST2.findArtist(artist);

					break;
				}
				case 'c': {
					cout << "Enter your keyword: ";
					cin.ignore();
					getline(cin, s);
					TableOfSongs.search(s, KeyWordIDSearchTable);
					break;
				}
				case 'd': {
					break;
				}
				}
				break;
			} while (chose != 'd');
			break;
		}
			// list song
		case 4: {
			char chose2;
			cout << "\t  d. Sorted by Title  " << endl;
			cout << "\t  e. Sorted by Artist " << endl;
			cout << "\t  f. Back to main menu" << endl;
			cout << "\tYour choice: ";
			cin >> chose2;
			do {
				switch (chose2) {
				case 'd': {
					BST.inOrderPrint();
					break;
				}
				case 'e': {
					BST2.inOrderPrint();
					break;
				}
				case 'f': {
					break;
				}
				}
				break;

			} while (chose2 != 'f');
			break;
		}

			// write file
		case 5: {
			BST.in_order_print_to_file(outfile);
			break;
		}

			//statistic
		case 6: {
			BST.statistic();
			continue;
		}

		case 7: {
			return 0;
			break;
		}
		}
	} while (intChoice != 7);

	outfile.close();
}

/*
 * TEST for removed keywords
 *
 * Enter your keyword: are
Sorry, the keyword <are> is not found in any songs.

TEST FOR HASHTABLE

Enter your keyword: Remember
The following songs contain the word: remember
Came Here To Forget
 by Blake Shelton
Album: If I'm Honest
Released Year: 2016


TEST RUN


	      Team 3: _COUNTRY SONGS_ PROJECT

	. ======================================== .
	|   Please enter your choice from 1-->7    |
	| 1. Add a new song                        |
	| 2. Delete song   :                       |
	| 3. Search engine:                        |
	| 4. List songs   :                        |
	| 5. Write data to file:                   |
	| 6. Statistics:                           |
	| 7. Quit                                  |
	. ======================================== .

	Your choice: 4
	  d. Sorted by Title
	  e. Sorted by Artist
	  f. Back to main menu
	Your choice: d
Came Here To Forget
By Blake Shelton
Album: If I'm Honest
Released Year: 2016
Length: 3 minutes 40 seconds.
Lyrics: Girl getting over him and I'm getting over her
The eyes have it made, ain't gotta say a word
Misery loves company, that's why it's you and me
Buying each other drinks, back at the bar, thick as thieves
Stealing these little sips
Doing our best to make the best of the worst of it

Keep playing them songs, keep singing along
Keep leaning it on in closer
Keep salting the rim, getting even with her
And with him before the night is over
That first kiss was like a Colorado hit
You better keep on keeping it lit
'Til we can't remember
Can't remember what we came here to forget

Go ahead and check your phone, like I've been checking mine
Nobody's ex is texting for a rewind
Looks like it's just me and you
Falling in love just enough to get us through
While we're getting through

Keep playing them songs, keep singing along
Keep leaning it on in closer
Keep salting the rim, getting even with her
And with him before the night is over
That first kiss was like a Colorado hit
We better keep on keeping it lit
'Til we can't remember
Can't remember what we came here to forget

Yeah, first of all we came here to forget
Looks like it's just me and you
Falling in love just enough to get us through
While we're getting through

Keep playing them songs, keep singing along
Keep leaning it on in closer
Keep salting the rim, getting even with her
And with you before the night is over
That first kiss was like a Colorado hit
You better keep on keeping it lit
'Til we can't remember
Can't remember what we came here to forget

What we came here to forget
What we came here to forget
Baby, baby
That's what we came here to forget


Don't Blink
By Kenny Chesney
Album: Just Who I Am: Poets & Pirates
Released Year: 2007
Length: 4 minutes 18 seconds.
Lyrics: I turned on the evening news
Saw a old man being interviewed
Turning a hundred and two today
Asked him what's the secret to life
He looked up from his old pipe
Laughed and said "All I can say is"

Don't blink
Just like that you're six years old and you take a nap and you
Wake up and you're twenty-five and your high school sweetheart becomes your wife
Don't blink
You just might miss your babies growing like mine did
Turning into moms and dads next thing you know your "better half"
Of fifty years is there in bed
And you're praying God takes you instead
Trust me friend a hundred years goes faster than you think
So don't blink

I was glued to my TV when it looked like he looked at me and said
"Best start putting first things first"
Cause when your hourglass runs out of sand
You can't flip it over and start again
Take every breathe God gives you for what it's worth

Don't blink
Just like that you're six years old and you take a nap and you
Wake up and you're twenty-five and your high school sweetheart becomes your wife
Don't blink
You just might miss your babies growing like mine did
Turning into moms and dads next thing you know your "better half"
Of fifty years is there in bed
And you're praying God takes you instead
Trust me friend a hundred years goes faster than you think
So don't blink

So I've been tryin' to slow it down
I've been tryin' to take it in
In this here today, gone tomorrow world we're livin' in

Don't blink
Just like that you're six years old and you take a nap and you
Wake up and you're twenty-five and your high school sweetheart becomes your wife
Don't blink
You just might miss your babies growing like mine did
Turning into moms and dads next thing you know your "better half"
Of fifty years is there in bed
And you're praying God takes you instead
Trust me friend a hundred years goes faster than you think
So don't blink

Naw, don't blink
Life goes faster than you think


Give It Away
By George Strait
Album: It Just Comes Natural
Released Year: 2006
Length: 3 minutes 30 seconds.
Lyrics: She was stormin' through the house that day
And I could tell she was leavin'
And I thought, 'aw, she'll be back.'
Until we turned around and pointed at the wall and said

That picture from out honeymoon
That night in 'Frisco Bay
Just give it away
She said give it away

That big four poster king sized bed
Where so much love was made
Just give it away
She said just give it away

Just give it away
There ain't nothing in this house worth fightin' over
Oh, we're both tired of fightin' anyway
Just give it away

Oh, I tried to move on
But I found that each woman I held
Just reminded me of that day

When that front door swung wide open
She flung her diamond ring
Said, give it away
Just give it away

And I said, now honey
Don't you even want your half of everything
She said give it away
Just give it away

Just give it away
There ain't nothing in this house worth fightin' over
Oh, we're both tired of fightin' anyway
Just give it away

So, I'm still right here where she left me
Along with all the other things that she don't care about anymore
Hmm

Like that picture from our honeymoon
That night in 'Frisco Bay
She said give it away
Well, I can't give it away
That big four poster king sized bed
Where all our love was made
She said give it away
Well, I can't give it away

I've got furnished house
A diamond ring
And a lonely, broken heart
Full of love
And I can't even give it away


Huntin', Fishin' & Lovin' Every Day
By Luke Bryan
Album: Kill The Lights
Released Year: 2015
Length: 4 minutes 31 seconds.
Lyrics: If I could make a living from walking in the woods
You could bet I'd be sitting pretty good
High on a hill looking at a field downwind
If I could make a nickel off a turning in bass
Never worry about the price of gas
I'd be wheeling and dealing and sitting there reeling 'em in
Huntin', fishin', and lovin' every day
That's the prayer that a country boy prays
Thank God He made me this way
Huntin' and fishin' and lovin' every day
Early in the morning and late in the evening
I'm getting red dirt rich and Flint River pay
Huntin' and fishin' and lovin' every day
Well I'd get a little farm ? bus
Sound of gravel when I back it up
And pulling the string on a nine point nine two stroke
I love it when my baby wants to roll with me
Throws her boots on, climbs in a tree
Tuckin' her hair in my hat and she's ready to go
We get to huntin', fishin' and lovin' every day
That's the prayer that a country boy prays
Thank God He made me this way
Huntin', fishin' and lovin' every day
Early in the morning and late in the evening
I'm getting red dirt rich, Flint River pay
Huntin' and fishin' and lovin' every day
Well huntin' and fishin' and lovin' every day
I wanna see them tall pines sway
Y'all close them eyes, let's go there in our minds
Huntin', fishin', and lovin' every day
That's the prayer this country boy prays
Thank God He made me this way
Huntin', fishin' and lovin' every day
Black coffee in the morning dark whiskey in the evening
I get red dirt rich and Flint River pay
Huntin', fishin' and lovin' every day
Won't you come along with me
Won't you come along with me
I know you'll wanna see
Huntin' and fishin' and lovin' every day


I Hope You Dance
By Lee Ann Womack
Album: I Hope You Dance
Released Year: 2000
Length: 4 minutes 54 seconds.
Lyrics: I hope you never lose your sense of wonder
You get your fill to eat but always keep that hunger
May you never take one single breath for granted
God forbid love ever leave you empty handed
I hope you still feel small when you stand beside the ocean
Whenever one door closes I hope one more opens
Promise me that you'll give faith a fighting chance
And when you get the choice to sit it out or dance

I hope you dance
I hope you dance

I hope you never fear those mountains in the distance
Never settle for the path of least resistance
Livin' might mean takin' chances, but they're worth takin'
Lovin' might be a mistake, but it's worth makin'
Don't let some Hellbent heart leave you bitter
When you come close to sellin' out, reconsider
Give the heavens above more than just a passing glance
And when you get the choice to sit it out or dance

I hope you dance (Time is a wheel in constant motion always rolling us along)
I hope you dance

I hope you dance (Tell me who wants to look back on their years and wonder)
I hope you dance (Where those years have gone?)

I hope you still feel small when you stand beside the ocean
Whenever one door closes I hope one more opens
Promise me that you'll give faith a fighting chance
And when you get the choice to sit it out or dance

Dance

I hope you dance
I hope you dance (Time is a wheel in constant motion always rolling us along)
I hope you dance (Tell me who wants to look back on their years and wonder?)


I Told You So
By Carrie Underwood
Album: Carnival Ride
Released Year: 2007
Length: 4 minutes 17 seconds.
Lyrics: Suppose I called you up tonight and told you that I loved you
And suppose I said "I wanna come back home".
And suppose I cried and said "I think I finally learned my lesson"
And I'm tired a-spendin' all my time alone.

If I told you that I realized you're all I ever wanted
And it's killin' me to be so far away.
Would you tell me that you loved me too and would we cry together?
Or would you simply laugh at me and say

"I told you so, oh I told you so
I told you some day you'd come crawling back and asking me to take you in
I told you so, but you had to go
Now I found somebody new and you will never break my heart in two again".

If I got down on my knees and told you I was yours forever
Would you get down on yours too and take my hand?

Would we get that old time feelin', would we laugh and talk for hours
The way we did when our love first began?

Would you tell me that you'd missed me too and that you've been so lonely
And you waited for the day that I return.
And we'd live in love forever and that I'm your one and only
Or would you say the tables finally turned?

Would you say

"I told you so, oh I told you so
I told you some day you come crawling back and asking me to take you in
I told you so, but you had to go
Now I found somebody new and you will never break my heart in two again".

"Now I found somebody new and you will never break my heart in two again".


If You're Going Through Hell
By Rodney Atkins
Album: If You're Going Through Hell
Released Year: 2006
Length: 3 minutes 37 seconds.
Lyrics: Well, you know those times when you feel like there's a sign there on your back
Says I don't mind if ya kick me seems like everybody has
Things go from bad to worse, you'd think they can't get worse than that
And then they do

You step off the straight and narrow and you don't know where you are
Use the needle of your compass to sew up your broken heart
Ask directions from a genie in a bottle of Jim Beam
And she lies to you
That's when you learn the truth

If you're going through hell
Keep on going, don't slow down
If you're scared, don't show it
You might get out before the devil even knows you're there

Well, I been deep down in that darkness I been down to my last match
Felt a hundred different demons breathing fire down my back
And I knew that if I stumbled I'd fall right into the trap
That they were laying, yeah

But the good news is there's angels everywhere out on the street
Holding out a hand to pull you back upon your feet
The one's that you been dragging for so long you're on your knees
You might as well be praying
Guess what I'm saying

If you're going through hell
Keep on going, don't slow down
If you're scared, don't show it
You might get out before the devil even knows you're there

Yeah, if you're going through hell
Keep on moving, face that fire
Walk right through it
You might get out before the devil even knows you're there

If you're going through hell
Keep on going, don't slow down
If you're scared, don't show it
You might get out before the devil even knows you're there

Yeah, if you're going through hell
Keep on moving, face that fire
Walk right through it
You might get out before the devil even knows you're there
Yeah, you might get out before the devil even knows you're there, yeah


It's Five O'Clock Somewhere
By Alan Jackson
Album: Greatest Hits Volume II
Released Year: 2003
Length: 3 minutes 49 seconds.
Lyrics: The sun is hot and that old clock is movin' slow,
An' so am I.
Work day passes like molasses in wintertime,
But it's July.
I'm gettin' paid by the hour, an' older by the minute.
My boss just pushed me over the limit.
I'd like to call him somethin',
I think I'll just call it a day.

Pour me somethin' tall an' strong,
Make it a "Hurricane" before I go insane.
It's only half-past twelve but I don't care.
It's five o'clock somewhere.

Oh, this lunch break is gonna take all afternoon,
An' half the night.
Tomorrow mornin', I know there'll be hell to pay,
Hey, but that's all right.
I ain't had a day off now in over a year.
Our Jamaican vacation's gonna start right here.
Hit the 'phones for me,
You can tell 'em I just sailed away.

An' pour me somethin' tall an' strong,
Make it a "Hurricane" before I go insane.
It's only half-past twelve but I don't care.
It's five o'clock somewhere.

I could pay off my tab, pour myself in a cab,
An' be back to work before two.
At a moment like this, I can't help but wonder,
What would Jimmy Buffet do?

Funny you should ask that because I'd say:
Pour me somethin' tall an' strong,
Make it a "Hurricane" before I go insane.
It's only half-past twelve but I don't care.

Pour me somethin' tall an' strong,
Make it a "Hurricane" before I go insane.
It's only half-past twelve but I don't care.
He don't care.
I don't care.
It's five o'clock somewhere.

What time zone am on? What country am I in?
It doesn't matter, it's five o'clock somewhere.
It's always on five in Margaritaville, come to think of it.
Yeah, I heard that.
You been there haven't you.
Yes sir.

I seen your boat there.
I've been to Margaritaville a few times.
All right, that's good.
Stumbled all the way back.
OK. Just wanna make sure you can keep it between the navigational beacons.
Bring the booze, I tell you.
All right. Well, it's five o'clock. Let's go somewhere.
I'm ready, crank it up.
Let's get out of here.
I'm gone.
Let's get out of here.


Live Like You Were Dying
By Tim McGraw
Album: Live Like You Were Dying
Released Year: 2004
Length: 4 minutes 58 seconds.
Lyrics: He said
"I was in my early forties
With a lot of life before me
And a moment came that stopped me on a dime
I spent most of the next days
Looking at the x-rays
Talkin' 'bout the options
And talkin' 'bout sweet time"
I asked him
"When it sank in
That this might really be the real end
How's it hit you
When you get that kind of news?
Man, what'd you do?"

He said
"I went skydiving
I went Rocky Mountain climbing
I went 2.7 seconds on a bull named Fumanchu
And I loved deeper
And I spoke sweeter
And I gave forgiveness I'd been denying"
And he said
"Someday I hope you get the chance
To live like you were dying"

He said
"I was finally the husband
That most of the time I wasn't
And I became a friend a friend would like to have
And all of a sudden going fishin'
Wasn't such an imposition
And I went three times that year I lost my dad
I finally read the Good Book, and I
Took a good, long, hard look
At what I'd do if I could do it all again
And then

I went skydiving
I went Rocky Mountain climbing
I went 2.7 seconds on a bull named Fumanchu
And I loved deeper
And I spoke sweeter
And I gave forgiveness I'd been denying"
And he said
"Someday I hope you get the chance
To live like you were dying
Like tomorrow was a gift
And you've got eternity
To think about
What you'd do with it
What could you do with it
What did I do with it?
What would I do with it?

Skydiving
I went Rocky mountain climbing
I went 2.7 seconds on a bull named Fumanchu
And I loved deeper
And I spoke sweeter
And I watched an eagle as it was flying"
And he said
"Someday I hope you get the chance
To live like you were dying
To live like you were dying
To live like you were dying"


Love Story
By Taylor Swift
Album: Fearless
Released Year: 2008
Length: 3 minutes 57 seconds.
Lyrics: We were both young when I first saw you.
I close my eyes and the flashback starts,
I'm standing there on a balcony in summer air.

See the lights, see the party, the ball gowns.
See you make your way through the crowd
And say hello

Little did I know
That you were Romeo, you were throwing pebbles,
And my daddy said, "Stay away from Juliet."
And I was crying on the staircase,
Begging you, Please, don't go.

And I said,
"Romeo, take me somewhere we can be alone.
I'll be waiting, all there's left to do is run.
You'll be the prince and I'll be the princess
It's a love story, baby just say yes.

So I sneak out to the garden to see you.
We keep quiet 'cause we're dead if they knew.
So close your eyes; escape this town for a little while.
Cause you were Romeo, I was a scarlet letter,
And my daddy said "Stay away from Juliet, "
But you were everything to me, I was begging you, please, don't go

And I said,
"Romeo, take me somewhere we can be alone.
I'll be waiting, all there's left to do is run.
You'll be the prince and I'll be the princess
It's a love story, baby just say yes.

Romeo save me, they're trying to tell me how to feel;
This love is difficult, but it's real.
Don't be afraid, we'll make it out of this mess.
It's a love story, baby just say "Yes.'"

Oh.

I got tired of waiting,
Wondering if you were ever coming around.
My faith in you was fading
When I met you on the outskirts of town,

And I said,
"Romeo save me, I've been feeling so alone.
I keep waiting for you but you never come.
Is this in my head? I don't know what to think-"

He knelt to the ground and pulled out a ring and said,
"Marry me, Juliet, you'll never have to be alone.
I love you and that's all I really know.
I talked to your dad, you'll pick out a white dress,
It's a love story, baby just say Yes."

Oh, oh.

We were both young when I first saw you


My Wish
By Rascal Flatts
Album: Me and My Gang
Released Year: 2006
Length: 4 minutes 8 seconds.
Lyrics: I hope the days come easy and the moments pass slow,
And each road leads you where you wanna go,
And if you're faced with a choice, and you have to choose,
I hope you choose the one that means the most to you.
And if one door opens to another door closed,
I hope you keep on walkin' till you find the window,
If it's cold outside, show the world the warmth of your smile.
But more than anything, more than anything

My wish, for you, is that this life becomes all that you want it to,
Your dreams stay big, your worries stay small,
You never need to carry more than you can hold,
And while you're out there getting where you're getting to,
I hope you know somebody loves you, and wants the same things too,
Yeah, this, is my wish.

I hope you never look back, but you never forget,
All the ones who love you, in the place you live,
I hope you always forgive, and you never regret,
And you help somebody every chance you get,
Oh, you find God's grace, in every mistake,
And always give more than you take.
But more than anything, yeah, more than anything

My wish, for you, is that this life becomes all that you want it to,
Your dreams stay big, your worries stay small,
You never need to carry more than you can hold,
And while you're out there getting where you're getting to,
I hope you know somebody loves you, and wants the same things too,
Yeah, this, is my wish. Yeah, yeah.

My wish, for you, is that this life becomes all that you want it to,
Your dreams stay big, your worries stay small,
You never need to carry more than you can hold,
And while you're out there getting where you're getting to,
I hope you know somebody loves you, and wants the same things too,
Yeah, this, is my wish (my wish, for you).

This is my wish (my wish, for you)
I hope you know somebody loves you (my wish, for you).
May all your dreams stay big (my wish, for you)


Remember When
By Alan Jackson
Album: Greatest Hits Volume II
Released Year: 2003
Length: 4 minutes 30 seconds.
Lyrics: Remember when I was young and so were you
And time stood still and love was all we knew
You were the first, so was I
We made love and then you cried
Remember when

Remember when we vowed the vows and walked the walk
Gave our hearts, made the start, it was hard
We lived and learned, life threw curves
There was joy, there was hurt
Remember when

Remember when old ones died and new were born
And life was changed, disassembled, rearranged
We came together, fell apart
And broke each other's hearts
Remember when

Remember when the sound of little feet
Was the music we danced to week to week
Brought back the love, we found trust
Vowed we'd never give it up
Remember when

Remember when thirty seemed so old
Now lookin' back, it's just a steppin' stone
To where we are, where we've been
Said we'd do it all again
Remember when

Remember when we said when we turned gray
When the children grow up and move away
We won't be sad, we'll be glad
For all the life we've had
And we'll remember when

Remember when
Remember when


She's Got A Way With Words
By Blake Shelton
Album: If I'm Honest
Released Year: 2016
Length: 3 minutes 14 seconds.
Lyrics: When you put two and two together
You figure out love's got four letters
I shoulda known that when I met her
But she had to spell it out for me
After all that second guessing
It's been a long hard history lesson
Hell that's a class I got an F in
But now I understand perfectly
She put the her in hurt
She put the why in try
She put the S.O.B. in sober
She put the hang in hangover (hangover)
She put the ex in sex
She put the low in blow
She put a big F.U. in my future
Yeah she's got a way
She's got a way with words
Yeah she's got a way with words
Little words like "I" and "do"
Lying, cheating, screwed
Yeah all the words I thought I knew
They got a brand new meaning now
She put the her in hurt
She put the why in try
She put the S.O.B. in sober
She put the hang in hangover (hangover)
She put the ex in sex
She put the low in blow
She put a big F.U. in my future
Yeah she's got a way
She's got a way with words
(Oh-oh-oh-oh, oh-oh-oh-oh)
Yeah she's got a way with words
(Oh-oh-oh-oh, oh-oh-oh-oh)
She put the her in hurt
She put the why in try
She put the S.O.B. in sober
She put the hang in hangover (hangover)
She put the ex in sex
She put the low in blow
She put a big F.U. in my future
Yeah she's got a way
She's got a way with words
(Oh-oh-oh-oh, oh-oh-oh-oh)
Yeah she's got a way with words
(Oh-oh-oh-oh, oh-oh-oh-oh)
She's got a way with words
She's got a way with words
Yeah she's got a way with words


Somebody Like You
By Keith Urban
Album: Golden Road
Released Year: 2002
Length: 5 minutes 23 seconds.
Lyrics: There's a new wind blowing like I've never known
I'm breathing deeper than I've even done
And it sure feels good to finally feel the way I do
And I want to love somebody, love somebody like you

And I let go of all my lonely yesterdays
I've forgiven myself for the mistakes I've made
Now there's just one thing the only thing I want to do
I want to love somebody, love somebody like you

Yeah I want to feel the sunshine
Shining down on me and you
When you put your arms around me
You let me know there's nothing in this world I can't do

I used to run in circles going nowhere fast
I'd take one step forward and took two steps back
I couldn't walk a straight line even if I wanted to
I want to love somebody, love somebody like you

Oh here we go now, ooo, yeah,
Hey I want to love ya baby,
Oh oh, oh oh

Yea I want to feel the sunshine
Shining down on me and you
When you put your arms around me
Well baby there ain't nothing in this world I can't do

Sometime it's hard for me to understand
But your teaching me to be a better man
I don't want to take this life for granted like I used to do, no no
I want to love somebody, love somebody like you

I'm ready to love somebody, love somebody like you
I want to love somebody, love somebody like you

Hey I want to love ya baby, ah uh

I want to be the man in the middle of the night shining like it's true
I wanna to be the man that you run to whenever I call on you
When everything that loved someone finally found it's way
I wanna be a better man I can see it in you yeah

Hey I want to love you baby

Ah ah yeah, na na na na na


Take Your Time
By Sam Hunt
Album: Montevallo
Released Year: 2014
Length: 4 minutes 2 seconds.
Lyrics: I don't know if you were looking at me or not
You probably smile like that all the time
And I don't mean to bother you but
I couldn't just walk by
And not say hi
And I know your name
'Cause everybody in here knows your name
And you're not looking for anything right now
So I don't wanna come on strong
But don't get me wrong
Your eyes are so intimidating
My heart is pounding but
It's just a conversation
No girl I'm not gonna waste it
You don't know me
I don't know you but I want to
And I don't wanna steal your freedom
I don't wanna change your mind
I don't have to make you love me
I just want to take your time
I don't wanna wreck your Friday
I ain't gonna waste my lines
I don't have to take your heart
I just wanna take your time
And I know it starts with hello
And the next thing you know you're trying to be nice
And some guys getting too close
Trying to pick you up
Trying to get you drunk
And I'm sure one of your friends is about to come over here
'Cause she's supposed to save you from random guys
That talk too much and wanna stay too long
It's the same old song and dance but I think you know it well
You could have rolled your eyes
Told me to go to hell
Could have walked away
But you're still here
And I'm still here
Come on let's see where it goes
I don't wanna steal your freedom
I don't wanna change your mind
I don't have to make you love me
I just wanna take your time
I don't have to meet your mother
We don't have to cross that line
I don't wanna steal your covers
I just wanna take your time
Woah, I don't wanna go home with you
Woah, I just wanna be alone with you
I don't wanna steal your freedom
I don't wanna change your mind
I don't have to make you love me
I just wanna take your time
And I don't wanna blow your phone up
I just wanna blow your mind
I don't have to take your heart
I just wanna take your time
No, I ain't gotta call you baby
And I ain't gotta call you mine
I don't have to take your heart
I just wanna take your time, ooh




	      Team 3: _COUNTRY SONGS_ PROJECT

	. ======================================== .
	|   Please enter your choice from 1-->7    |
	| 1. Add a new song                        |
	| 2. Delete song   :                       |
	| 3. Search engine:                        |
	| 4. List songs   :                        |
	| 5. Write data to file:                   |
	| 6. Statistics:                           |
	| 7. Quit                                  |
	. ======================================== .

	Your choice: 2
Enter a song to delete: Take Your Time
Song has been deleted!

	      Team 3: _COUNTRY SONGS_ PROJECT

	. ======================================== .
	|   Please enter your choice from 1-->7    |
	| 1. Add a new song                        |
	| 2. Delete song   :                       |
	| 3. Search engine:                        |
	| 4. List songs   :                        |
	| 5. Write data to file:                   |
	| 6. Statistics:                           |
	| 7. Quit                                  |
	. ======================================== .

	Your choice: 6
Total songs: 14
Total length: 58 minutes 46 seconds
Average length: 4 minutes 11 seconds

	      Team 3: _COUNTRY SONGS_ PROJECT

	. ======================================== .
	|   Please enter your choice from 1-->7    |
	| 1. Add a new song                        |
	| 2. Delete song   :                       |
	| 3. Search engine:                        |
	| 4. List songs   :                        |
	| 5. Write data to file:                   |
	| 6. Statistics:                           |
	| 7. Quit                                  |
	. ======================================== .

	Your choice: 5

	      Team 3: _COUNTRY SONGS_ PROJECT

	. ======================================== .
	|   Please enter your choice from 1-->7    |
	| 1. Add a new song                        |
	| 2. Delete song   :                       |
	| 3. Search engine:                        |
	| 4. List songs   :                        |
	| 5. Write data to file:                   |
	| 6. Statistics:                           |
	| 7. Quit                                  |
	. ======================================== .

	Your choice: 7

 */

