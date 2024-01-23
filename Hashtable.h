#ifndef _HASHTABLE_H
#define _HASHTABLE_H
	using namespace std;

#define MAX_ELEMENTS 100000
#define EMPTY		 NULL

struct Movie {
	string ID;
	int yearReleased;
	int duration;
	string genre;
	string title;
};

struct LLNode {
	Movie data;
	LLNode * next;	
};

struct HashTable {
	LLNode * elements [MAX_ELEMENTS];
	int sizeTable;
};
	
HashTable * initHashTable (int sizeTable);
void insertHT (HashTable * ht, Movie movie);
void deleteHT (HashTable * ht, string key);
int containsHT (HashTable * ht, string key);
int lengthChain (HashTable * ht, int location);
void displayMovie (HashTable * ht, int location, string key);
void statistics (HashTable * ht);
LLNode * createNode ( Movie movie);
int hash(string ID);

#endif
