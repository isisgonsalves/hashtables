#include <iostream>
#include <fstream>
#include <windows.h>
#include "HashTable.h"

using namespace std;

#define QUIT 7

//isis gonsalves
//816026980
//Asg 3

void showVideo (string URL) {
	
	cout<<URL;
	
	char cURL [50];
	int i;

	for (i = 0; i < URL.length(); i=i+1){
    	cURL[i] = URL[i];
	}

	cURL[URL.length()] = '\0';
    
    ShellExecute(NULL, "open", cURL, NULL, NULL, SW_SHOWNORMAL);
}



int menu () {

	int choice;
	bool validOption;
	
	validOption = false;
	
	while (!validOption) {
	cout << endl;
	cout<<"\t\t\tHash Table of Movies"<<endl;
	cout<<"-------------------------------------------------------------"<<endl;
	cout << "1. Insert a movie in the hash table." << endl;
	cout << "2. Check if the hash table contains a movie." << endl;
	cout << "3. Check the length of the list containing a movie." << endl;
	cout << "4. Delete a movie from the database." << endl;
	cout << "5. Display statistics of hash table." << endl;
	cout << "6. Load IMDB web page for a movie." << endl;
	cout << "7. Quit" << endl;
	cout << "Enter Choice:  ";
	cin  >> choice;
	cout<<endl;
	
		if (choice >= 1 && choice <= 7)	
			validOption = true;
		else{
			cout<<"\nSorry, option 1 to 7 must be entered. Please try again."<<endl;
		}
				
		return choice;
	}
}

int readMovies (HashTable * ht, char filename [100]){ 
	
	ifstream in;
	in.open(filename);
	
	int numMovies=0;
	int size=0;
	Movie input;
	string title;
	
	string ID;
	in>>ID;
	
	while(ID != "END"){
		
		input.ID= ID;
		in>>input.yearReleased;
		in>>input.duration;
		in>>input.genre;
		getline(in, title);
		input.title = title;
		
		cout<<endl<<endl; 

		insertHT(ht, input);
		
		numMovies++;
		in>>ID;
		
	}

	in.close();
	
	return numMovies;
}
	
int main () {
	
	int size=0;
	HashTable * ht = initHashTable(size);
	
	char filename [100] = "Movies.txt"; 
	int numMovies=readMovies(ht, filename);
	
	//cout<<"Number of movies: "<<numMovies<<endl;
	
	int choice = menu();
	
	while (choice != 7){
		
		if (choice == 1){
			 
			 Movie insert;
			 cout<<"Inserting a movie in the hash table..."<<endl<<endl;
			 
			 cout<<"\nMovie Title: ";
			 cin>>insert.title;
			 
			 cout<<"Movie Genre: ";
			 cin>>insert.genre;
			 
			 cout<<"Movie ID: ";
			 cin>>insert.ID;
			 
			 cout<<"Movie Year of Release: ";
			 cin>>insert.yearReleased;
			 
			 cout<<"Movie Duration: ";
			 cin>>insert.duration;
			 
			 insertHT(ht, insert);
			 cout<<"Size of Hash Table: "<<ht->sizeTable<<endl;
			 
		}
		else
			if (choice == 2){
				
				cout<<"Checking if the hash table contains a movie..."<<endl<<endl;
				
				string ID;
				cout<<"Enter ID of movie to begin search: ";
				cin>>ID;
				
				int found= containsHT(ht, ID);
				
				if (found == -1)
					cout<<"Movie not found in hash table."<<endl;
				else{
				
					cout<<"Movie found at location " << found<< "."<<endl;
					displayMovie(ht,found,ID);
				}
			}
			else
				if (choice == 3){
					
					cout<<"Checking the length of the list containing a movie..."<<endl<<endl;

					string ID;
					cout<<"Enter ID of movie to check the length of list: ";
					cin>>ID;
					
					int loc= containsHT(ht, ID);
					
					if(loc != -1){
						int length= lengthChain(ht,loc);
						cout<<"The length of the chain at location "<<loc<<" is: "<<length<<" ."<<endl;
					}
					else
						cout<<"Movie is not present in hash table. "<<endl;
					
				}
				else
					if (choice == 4){
						
						cout<<"Deleting a movie from the database..."<<endl<<endl;
						
						string ID;
						cout<<"Enter ID of movie to delete: ";
						cin>>ID;
						
						deleteHT(ht,ID);
						cout<<"Size of Hash Table: "<<ht->sizeTable<<endl;
						
					}
					else
						if (choice == 5){
							
							cout<<"Displaying occupancy statistics of hash table..." <<endl;
							
							statistics(ht);
							
						}
						else
							{
								
								cout<<"Loading IMDB web page for a movie..."<<endl<<endl;
								
								string movieID;
								cout<<"Enter the ID of a movie to load: ";
								cin>>movieID;
								
								int loc= containsHT(ht, movieID);
								
								if(loc != -1){
									string begin= "http://www.imdb.com/title/";
								
									string movie;
									movie = begin + movieID;
									
									showVideo(movie);
								}
								else
									cout<<"Movie is not present in hash table. "<<endl;
								
								
							}
										
		choice=menu();
	}
	
	cout<<"\nExit successful... "<<endl<<endl;

	return 0;
}
