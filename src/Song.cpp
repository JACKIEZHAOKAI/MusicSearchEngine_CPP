#include "Song.h"
#include <iostream>
#include <iomanip>

Song::Song() :
		title(""), artist(""), minute(0), second(0), album(""), releasedYear(0),
		lyrics(), officialLyrics("") {
}
;

Song::Song(string t, string a, int m, int s, string al, int r, vector<WordID> ly,
		string off) {
	title = t;
	artist = a;
	minute = m;
	second = s;
	album = al;
	releasedYear = r;
	lyrics = ly;
	officialLyrics = off;
}

/**Access Functions*/

string Song::get_title() {
	return title;
}

string Song::get_artist() {
	return artist;
}

int Song::get_minute() {
	return minute;
}

int Song::get_second() {
	return second;
}

int Song::get_releasedYear() {
	return releasedYear;
}

string Song::get_album() {
	return album;
}

vector<WordID> Song::get_lyrics() {
	return lyrics;
}

string Song::get_officialLyrics() {
	return officialLyrics;
}

/**Manipulation Procedures*/

void Song::set_title(string t) {
	title = t;
}

void Song::set_artist(string a) {
	artist = a;
}

void Song::set_minute(int m) {
	minute = m;
}

void Song::set_second(int s) {
	second = s;
}

void Song::set_album(string al) {
	album = al;
}

void Song::set_releasedYear(int r) {
	releasedYear = r;
}

void Song::set_lyrics(vector<WordID> ly) {
	lyrics = ly;
}

void Song::set_officialLyrics(string off) {
	officialLyrics = off;
}

/**Additional Functions*/
void Song::print_song() {
	cout << title << endl;

	cout << " by " << artist << endl;
	cout << "Album: " << album << endl;
	cout << "Released Year: " << releasedYear << endl;
	cout << "Length: " << minute << " minutes " << second << " seconds."
			<< endl;
	cout << "Lyrics: " << officialLyrics << endl;
}

bool Song::operator==(Song& song) {
	return (title == song.title && artist == song.artist
			&& minute == song.minute && second == song.second
			&& album == song.album && releasedYear == song.releasedYear
			&& officialLyrics == song.officialLyrics);
}

bool Song::operator<(Song& song) {
	return (title < song.title);
}

bool Song::operator>(Song& song) {
	return (title > song.title);
}


//added functions

WordID  Song::getLyricsAt(int i)
{
	return lyrics[i];
}

void  Song::setLyricsAt(int i, int count)
{
	lyrics.at(i).setID(count);
}





