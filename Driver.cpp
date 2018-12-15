//-------------------------------
// Driver.cpp
// Jordan Pierson & Todd Muller
// COSC 2030, Fall 2018
// Project 2, Tracking Tree:
//  -Driver file
//-------------------------------


#include <cstdlib>
#include "Node.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional>
#include <string>
#include <math.h>


using namespace std;
using std::setw;

//---------------------------------------------
// Function Prototypes
//---------------------------------------------
string getRand(void); //returns random string
string hashFunc(string); //hashes string input and returns hash
void visualize(int, Node[]); //prints contents of the tree
int search(int, Node[], string); //searches for a node by ID value


int main()
{
	Node* tree = new Node[2];
	//Node* Array = new Node tree[2];

	//tree[0].setParentID("Hi");
	//cout << getRand();
	tree[1].setParentID(getRand());
	//cout << "Worked";
	//cout << tree[0].returnParentID();
	string input;
	bool exit = false;
	int level = 1;
	int index = 1;
	int sizeArray = 2;


	// Tell the user how to use the program
	cout << "-----------------------------------------------------------" << endl
		<< "                     TRACKING    TREE" << endl
		<< "-----------------------------------------------------------" << endl
		<< "Commands are:" << endl
		<< "'E'/'Exit' To Exit the Program"
		<< "\n'V'/'Visualize' to see all of the ID values of the nodes"
		<< "\n'S'/'Search' to search for a node using it's ID"
		<< "\n'U'/'Update' to search for, and update contents of a node"
		<< "\nIf anything else is entered, it will be taken as a "
		<< "\nnew raw event and create a new node in the tree." << endl;
	cout << "-----------------------------------------------------------" << endl << endl;

	while (exit == false)		//runs until the user exits
	{
		//take in input from user
		cin >> input; 

		if (input == "E" || input == "Exit" || input == "e")
		{
			exit = true; // exits the program
		}

		else if (input == "V" || input == "Visualize" || input == "v") 
		{
			// prints Index, Rawe, Id, and 
			// LHash and Rhash (updated) for each node
			visualize(index, tree); 
		}

		else if (input == "S" || input == "Search" || input == "s") 
		{
			// Searches for tree based on ID value
			// Returns RawE at the ID value
			cout << "\nType in and ID value to search for:" << endl;
			string sID;
			cin >> sID;
			int found = search(index, tree, sID);

			if (found >= 1)
			{
				cout << "\n" << sID << " found. Printing Histories:" << endl;
				tree[found].printRecord();
			}
			else
			{
				cout << "\nThe ID you searched for was not found.\n"
					<< "Returning to main command line." << endl;
				break;
			}
		}

		else if (input == "U" || input == "Update" || input == "u")
		{
			// still needs done
			cout << "Update Node: \nWhat Node do you want to update? (give ID value):" << endl;
			string iDVal;
			cin >> iDVal;
			int found = search(index, tree, iDVal);

			if (found >= 1)
			{
				cout << "\n" << iDVal << " found. Current contents are: "
					<< tree[found].returnRawE()
					<< "\nWhat would you like to change it's contents to? ('CANCEL' to cancel update)" << endl;
				string contents;
				cin >> contents;
				if (contents != "CANCEL")
				{
					tree[found].setRawE(contents);
					//
					// The following code was copied from the 'add new node' functionality
					// because both have a unique function to percolate up
					//
					tree[found].setID(hashFunc(tree[found].returnParentID() + tree[found].returnRawE()));

					//------------------------------------------------------
					// Now percolate up, update parents LHash / RHash
					//------------------------------------------------------
					//
					// These are preliminary things we need to keep track of
					// before entering the for loop.

					string relation;
					if (found % 2 == 0)
					{
						relation = "left";
					}
					if (found % 2 == 1)
					{
						relation = "right";
					}
					int prevChildI(found);
					//
					//For loop to percolate up:


					for (int i = found / 2; i >= 1; i /= 2) // finds parent(s) up to the root
					{
						if (relation == "left") // if the child is the left then update LHash
						{
							tree[i].newLHash(hashFunc( // Hash the following contents, store in current node's LHash & lHist
								tree[prevChildI].returnID()			//child ID
								+ tree[i].returnID()				// parent ID
								+ tree[prevChildI].returnRawE()		// child rawE
								+ tree[prevChildI].returnLHash()	// child lHash
								+ tree[prevChildI].returnRHash())); // child rHash

						}
						if (relation == "right") // if the child is the right then update RHash
						{
							tree[i].newRHash(hashFunc(	// Hash the following contents, store in current node's RHash & rHist
								tree[prevChildI].returnID()			//child ID
								+ tree[i].returnID()				// parent ID
								+ tree[prevChildI].returnRawE()		// child rawE
								+ tree[prevChildI].returnLHash()	// child lHash
								+ tree[prevChildI].returnRHash())); // child rHash
						}

						// Same as preliminary things, but now for the next time around. 
						//
						// find relation of current node to it's parent for next time around loop
						if (i % 2 == 0)
						{
							relation = "left";
						}
						if (i % 2 == 1)
						{
							relation = "right";
						}
						prevChildI = i; //save current node index for the next time around loop
					}
				}
				else
				{
					cout << "Update Cancelled. Returning to main command line." << endl;
					break;
				}
			}
			else
			{
				cout << "\nThe ID you searched for was not found.\n"
					<< "Returning to main command line." << endl;
				break;
			}
		}
		else
		{
			
			//If the level is full, make
			//a new array with +1 level, copy contents
			//from original array, then set the old array
			// to the new array
			

			
			if (index + 1 == sizeArray)
			{
				

				int storedsize = sizeArray;
				sizeArray = pow(2, level + 1);
				Node* temp = new Node[sizeArray];
				//memcpy(temp, tree, storedsize+1);
				for (int i = 1; i < storedsize; i++)
				{
					temp[i].setRawE(tree[i].returnRawE());
					temp[i].setID(tree[i].returnID());
					temp[i].newLHash(tree[i].returnLHash());
					temp[i].newRHash(tree[i].returnRHash());
					temp[i].setLHist(tree[i].getLHist());
					temp[i].setRHist(tree[i].getRHist());
				}

				delete[]tree;
				tree = temp;


				
				
				tree = temp;



				level++;
			}

			// now initialize a new node at the next available slot

			// set rawE to input
			tree[index].setRawE(input); 
			// set parent ID to it's parent using integer division (P= N/2)
			if (index != 1)
			{
				tree[index].setParentID(tree[index / 2].returnID());
			}
			
			// Now make the current node's ID by hashing parentID + rawE
			tree[index].setID(hashFunc(tree[index].returnParentID() + tree[index].returnRawE()));

			//------------------------------------------------------
			// Now percolate up, update parents LHash / RHash
			//------------------------------------------------------
			//
			// These are preliminary things we need to keep track of
			// before entering the for loop.
			
			string relation;
			if (index % 2 == 0)
			{
				relation = "left";
			}
			if (index % 2 == 1)
			{
				relation = "right";
			}
			int prevChildI(index);
			//
			//For loop to percolate up:
			

			for (int i = index / 2; i >= 1; i /= 2) // finds parent(s) up to the root
			{
				if (relation == "left") // if the child is the left then update LHash
				{
					tree[i].newLHash(hashFunc( // Hash the following contents, store in current node's LHash & lHist
						tree[prevChildI].returnID()			//child ID
						+ tree[i].returnID()				// parent ID
						+ tree[prevChildI].returnRawE()		// child rawE
						+ tree[prevChildI].returnLHash()	// child lHash
						+ tree[prevChildI].returnRHash())); // child rHash
					
				}
				if (relation == "right") // if the child is the right then update RHash
				{
					tree[i].newRHash(hashFunc(	// Hash the following contents, store in current node's RHash & rHist
						tree[prevChildI].returnID()			//child ID
						+ tree[i].returnID()				// parent ID
						+ tree[prevChildI].returnRawE()		// child rawE
						+ tree[prevChildI].returnLHash()	// child lHash
						+ tree[prevChildI].returnRHash())); // child rHash
				}

				// Same as preliminary things, but now for the next time around. 
				//
				// find relation of current node to it's parent for next time around loop
				if (i % 2 == 0)
				{
					relation = "left";
				}
				if (i % 2 == 1)
				{
					relation = "right";
				}
				prevChildI = i; //save current node index for the next time around loop
			}
			index++;
		}
	}


	system("pause");
	return 0;
}

// returns random string used for the first node
string getRand(void)
{
	const int len = 8;
	char s[len];
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	s[len-1] = 0;
	return s;
}

// Hash function. Currently uses STL std::hash
// create own function for bonus points
string hashFunc(string input)
{
	//-------------------------------------
	// HEY PROFESSOR BOROWCZAK THIS IS A 
	// UNIQUE HASH FUNCTION BECAUSE WE 
	// MULTIPLY IT BY (~= π)
	//
	// Have a good break! 
	// -Jordan and Todd
	//-------------------------------------

	size_t h1 = hash<string>{}(input);
	h1 = h1 * 3.14159265359;
	return to_string(h1);


}

// Prints contents of the tree
void visualize(int index, Node theArray[])
{
	cout << "\nPrinting Contents of the Tree:" << endl
		<< "----------------------------------------------------------" << endl
		<< "Node" << setw(12) << "RawE" << setw(12) << "ID" << setw(15) << "R-Hash" << setw(12) << "L-Hash" << endl;
	cout << "----------------------------------------------------------" << endl;
	for (int i = 1; i < index; i++)
	{
		cout << setw(2) << i << setw(14) << theArray[i].returnRawE()
			<< setw(16) << theArray[i].returnID() << setw(12) 
			<< theArray[i].returnRHash() << setw(12) 
			<< theArray[i].returnLHash() << endl;
	}
}

// Searches for a node based on ID value
// once found it returns that nodes index in the array
int search(int index, Node theArray[], string sID)
{
	int result = 0;// 0th element contains nothing,
				   // used here more as a SENTINEL

	for (int i = 1; i <= index; i++)
	{
		if (theArray[i].returnID() == sID) //if the ID is found:
		{
			result = i; // return the index value of the element
			i = index + 1; //exit the for loop;
		}
	}
	return result; //result will equal either index of found element or 0;
}
