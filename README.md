# MusicSearchEngine_CPP
Music Search Engine implemented in Tree and Hashtable to support searching by title, author and lyrics 

A sample music song in a text file contains title, artist, year, album, length and lyrics.

Implemented Binary Search Tree to support searching songs by name and by author.

Applied Hash Table to support searching songs by keywords. 
Filtered out unimportant words such as 'a' 'the' 'to'
Assigned word ID each key words and guranteed no ID conflict. 
Used separate chaining to resolve the conflict of one keyword associated to many songs,
appended music name to the block of each keyWord ID, stored in linked list structure.
By searching a keyword, print out all the music related to it.
