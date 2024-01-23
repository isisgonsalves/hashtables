#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <conio.h>
#include <sstream>
#include "HashTable.h"
   using namespace std;


HashTable * initHashTable (int sizeTable) {
	
	HashTable * ht = new HashTable;
	
	for(int i=1; i<=MAX_ELEMENTS; i++){
		ht->elements[i] = EMPTY;
	}
	
	ht->sizeTable = sizeTable;
	
	return ht;
}

int hash(string ID){
	
	ID.erase(0,2);

	int newID;
				
	stringstream ss;  
	ss << ID;  
	ss >> newID; 
		
    return newID % 29501 + 1;
}

LLNode * createNode ( Movie movie) {
	
	LLNode * newNode; 
   
   newNode = new LLNode;
   newNode->data = movie;
   newNode->next = NULL;
  
   return newNode;

}


void insertHT (HashTable * ht, Movie movie) {

    int loc = containsHT(ht, movie.ID);

    if (loc != -1) {
	    cout << "Key already present" << endl;
    }
	else{
		
		LLNode * newNode;
		newNode=createNode(movie);
		
	    loc = hash(movie.ID);
	       
		    if (ht->elements[loc] == EMPTY ){
	
	            ht->elements[loc] = newNode;
	            ht->sizeTable += 1;
	        }
			else{
				LLNode * curr = ht->elements[loc];
			
				while(curr->next)
					curr=curr->next;
					
				curr->next = newNode;
			}
    }
	
}


void deleteHT (HashTable * ht, string key) {

	int loc = containsHT(ht, key);

    if (loc == -1)
        cout << "Key not present." << endl;

    else{

		//LLNode * curr = ht->elements[loc];
		
		while(ht->elements[loc] != NULL){
			
			if(ht->elements[loc]->data.ID == key){
				delete(ht->elements[loc]);
     			ht->sizeTable--;
			}
			ht->elements[loc]=ht->elements[loc]->next;
		}
        cout << "Key was deleted" << endl;
    }
}



int containsHT (HashTable * ht, string key) {
	
    int loc = hash(key);

	LLNode * curr = ht->elements[loc];
	
	if (ht->elements[loc] == EMPTY) // loc is empty
            return -1; 
	
    while (curr != NULL){

		if (curr->data.ID == key){ // found our key
	        return loc;
		}
		curr=curr->next;
    }
	return -1;
}


int lengthChain (HashTable * ht, int location) {

	int length=0;

	LLNode * curr = ht->elements[location];
		
	while(curr != NULL){
			
		length++;
		curr=curr->next;
	}
    return length;
}



void displayMovie (HashTable * ht, int loc, string key) {


    if (loc < -1 || loc >29501)
        cout << "Movie not present." << endl;

    else{

		LLNode * curr = ht->elements[loc];
		
		while(curr != NULL){
			
			if(curr->data.ID == key){
				cout<<"\nMovie Details\n"<<endl;
				
				cout<<"ID: "<<curr->data.ID<<endl;
				if(curr->data.title == "999")
					cout<<"Title: Unavailable"<<endl;
				else
					cout<<"Title: "<<curr->data.title<<endl;
				
				if(curr->data.genre == "999")	
					cout<<"Genre: Unavailable"<<endl;
				else
					cout<<"Genre: "<<curr->data.genre<<endl;
					
				if(curr->data.duration == 999)
					cout<<"Duration: Unavailable"<<endl;
				else
					cout<<"Duration: "<<curr->data.duration<<endl;
				
				if(curr->data.yearReleased == 999)	
					cout<<"Year Released: Unavailable"<<endl;
				else
					cout<<"Year Released: "<<curr->data.yearReleased<<endl;
			}
			curr=curr->next;
		}
    
    }
}


void statistics (HashTable * ht) {
	
	int max = 0;
	int empty=0;
	int filled=0;
	
	for(int loc=1;loc<=29501;loc++){
		
		if(ht->elements[loc] == EMPTY){
			empty++;
		}
		else
			if(ht->elements[loc] != EMPTY){
				filled++;
			}
		
		int len=lengthChain(ht, loc);
		
		if(len > max)
			max=len;
	}
	
	cout<<"\n\n\t\tStatistics"<<endl;
	cout<<"Size of Hash Table: "<<ht->sizeTable<<endl;
	cout<<"Number of Empty Locations: "<<empty<<endl;
	cout<<"Number of Filled Locations: "<<filled<<endl;
	cout<<"Length of Longest Chain: "<<max<<endl;
}		
