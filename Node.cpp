//-------------------------------
// Node.cpp
// Jordan Pierson & Todd Muller
// COSC 2030, Fall 2018
// Project 2, Tracking Tree:
//  -Function definitions for the Node class
//-------------------------------

#include "Node.h"



// Accessor Functions
string Node::returnID(void)
{
	return iD;
}

string Node::returnParentID(void)
{
	return parentID;
}
string Node::returnRawE(void)
{
	return rawE;
}

string Node::returnLHash(void)
{
	return lHash;
}

string Node::returnRHash(void)
{
	return rHash;
}

void Node::printRecord(void)
{
	cout << "Left History (Earliest record to current Left Hash):" << endl;
	for (int i = 0; i < lHist.size(); i++)
	{
	cout <<	lHist[i] << endl;
	}
	cout << "Right History (Earliest record to current Right Hash):" << endl;
	for (int i = 0; i < rHist.size(); i++)
	{
		cout << rHist[i] << endl;
	}
}

void Node::newLHash(string input)
{
	input.resize(8);
	lHash = input;
	lHist.push_back(input);
}

void Node::newRHash(string input)
{
	input.resize(8);
	rHash = input;
	rHist.push_back(input);
}

void Node::setParentID(string input)
{
	input.resize(8);
	parentID = input;
}
void Node::setID(string input)
{
	input.resize(8);
	iD = input;
}
void Node::setRawE(string input)
{
	rawE = input;
}

void Node::setLHist(vector<string> oldLHist)
{
	lHist = oldLHist;
}
void Node::setRHist(vector<string> oldRHist)
{
	rHist = oldRHist;
}

vector<string> Node::getLHist(void)
{
	return lHist;
}

vector<string> Node::getRHist(void)
{
	return rHist;
}