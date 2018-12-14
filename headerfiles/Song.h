#ifndef SONG_H_
#define SONG_H_
#include <string>
#include <vector>
#include "WordID.h"
using namespace std;
class Song {
private:
	string title;
	string artist;
	int minute;
	int second;
	string album;
	int releasedYear;
	vector<WordID> lyrics;
	string officialLyrics;
public:
	Song();
	Song(string t, string a, int m, int s, string al, int r, vector<WordID> ly,
			string off);
	/**Access Functions*/
	string get_title();
	string get_artist();
	int get_minute();
	int get_second();
	string get_album();
	int get_releasedYear();
	vector<WordID> get_lyrics();
	string get_officialLyrics();
	WordID getLyricsAt(int i);
	/**Manipulation Procedures*/
	void set_title(string t);
	void set_artist(string a);
	void set_minute(int m);
	void set_second(int s);
	void set_album(string al);
	void set_releasedYear(int year);
	void set_lyrics(vector<WordID> lyrics);
	void set_officialLyrics(string officialLyrics);
	void setLyricsAt(int i, int count);
	/**Additional Functions*/
	void print_song();
	void print_song_to_file(ostream& fout);
	bool operator==(Song& song);
	bool operator<(Song& song);
	bool operator>(Song& song);

};
#endif /* SONG_H_ */
