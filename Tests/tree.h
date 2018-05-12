/*******************************************************************************
  Title          : tree.h
  Author         : Aaron D Taveras
  Created on     : February 8th, 2018
  Description    : Interface to the tree class
  Purpose        : To define methods to manipulate and create a tree object,
  				   which is a representation of a single line of data in the csv. 
  Usage          : 
  Build with     : 
  Modifications  : 
 
*******************************************************************************/

#ifndef __TREE_H__
#define __TREE_H__



#include <iostream>
#include <sstream>
#include <string>
#include <cmath>


#define R 6372.8
#define TO_RAD (3.1415926536 / 180)

using namespace std;

class Tree{

public:
	Tree(); //Default constructor
	/**	Tree(const string &) - 
		Single parameter constructor that creates a Tree object using a 
		a line from a given csv file.
		@param 	string & treedata 	[inout]		line from csv file to be read
		@pre 	the string provided is valid and is in proper csv format.
		@post 	tree is assigned all valid values
	*/
	Tree(const string & treedata);

	Tree( int id, int diam, string status, string health, string spc,
		 int zip, string addr, string boro, double latitude, double longitude);

	string common_name() const;

	string borough_name() const;

	string get_address() const;

	int diameter() const;

	int get_zipcode() const;

	void get_position(double & latitude, double & longitude) const;

	bool is_near(double latitude, double longitude, double distance) const;

	double haversine( double lat1, double lon1, double lat2, double lon2 ) const;

	/**	write() const - returns a formatted string of specific tree data as
		outlined in the project notes.
		@param 	none
		@pre 	"this" must have properly initialized private members.
		@post 	correctly formatted string will be returned. 
	*/ 
	string write() const;

	/**	operator<< () - outputs the current tree object in the format given 
		by the "write" command to the given output stream.
		@param 	ostream & os 		[inout] 	stream to be written to
		@param 	tree    & t 		[inout] 	tree whos contents will be written
		@pre 	the specified ostream must be open for writing, and the tree object
				must be initialized.
		@post 	formatted text will be sent to the output stream in accordance 
				with the formatting specifications.		  
	*/
	friend ostream & operator<< (ostream & os, const Tree & t);

	friend bool operator==(const Tree & t1, const Tree & t2);

	friend bool operator<(const Tree & t1, const Tree & t2);

	friend bool samename(const Tree & t1, const Tree & t2);

	friend bool islessname(const Tree & t1, const Tree & t2);

private:
	string spc_common; //Common name of tree
	int tree_id; // Non-negative integer and unique identifier
	int tree_dbh; // Non-negative integer that represents diameter
	string status; // Alive, Dead, Stump, or empty string 
	string health; // Good, Fair, Poor, or empty string
	string address; // String, may contain spaces
	string boroname; // Manhattan, Bronx, Brooklyn, Queens, or Staten Island
	int zipcode; // Positive five digit integer
  	double latitude; // GPS latitude in decimal degrees
	double longitude; // GPS longitude in decimal degrees
	
};


#endif 
