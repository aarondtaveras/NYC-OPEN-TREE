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


#define R 6372.8 	// Globals to be used for haversine calculation.
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

	/**	Tree(int id, int diam, string status, string health, string spc,
		 int zip, string addr, string boro, double latitude, double longitude) - 
		Manual constructor for creating a Tree object with desired values.
		@param 	int id			[in]		id of tree
		@param 	int diam 		[in] 		diameter of tree
		@param 	string status 	[in] 		current status of the tree (alive, dead)
		@param 	string health 	[in]  		tree's current health
		@param 	string spc 		[in] 		tree's common species name
		@param 	int zip 		[in] 		zipcode of tree
		@param 	string addr 	[in]		approximate address of tree
		@param 	string boro 	[in]		borough that the tree resides
		@param 	double latitude [in] 		tree's coordinates
		@param 	double longitude[in]		tree's coordinates	
		@pre 	None.
		@post 	tree is assigned all valid values
	*/

	Tree( int id, int diam, string status, string health, string spc,
		 int zip, string addr, string boro, double latitude, double longitude);
	/** 
		common_name() const 
		Accessor function that returns tree's common name.
		@pre tree has been defined with valid values
		@post a valid string matching the object's common name is returned.
	*/
	string common_name() const;

	/** 
		borough_name() const 
		Accessor function that returns tree's current borough.
		@pre tree has been defined with valid values
		@post a valid string matching the object's borough is returned.
	*/

	string borough_name() const;

	/** 
		get_address() const 
		Accessor function that returns tree's approximate address.
		@pre tree has been defined with valid values
		@post a valid string matching the object's address is returned.
	*/

	string get_address() const;

	/** 
		diameter() const 
		Accessor function that returns tree's diameter .
		@pre tree has been defined with valid values
		@post a valid int matching the object's diameter is returned.
	*/

	int diameter() const;

	/** 
		get_zipcode() const 
		Accessor function that returns tree's zipcode.
		@pre tree has been defined with valid values
		@post a valid int matching the tree's zipcode is returned.
	*/

	int get_zipcode() const;

	/** 
		get_position() const 
		Accessor function that accepts two doubles as a reference
		and assigns them the trees private data members.
		@param 	double & latitude 	[inout] 	latitude to be changed
		@param 	double & longitude 	[inout] 	longitude to be changed
		@pre tree has been defined with valid values
		@post latitude and longitude will be set to tree's private data members.
	*/

	void get_position(double & latitude, double & longitude) const;

	/** 
		is_near() const 
		Returns a boolean based on whether or not the current tree object
		is within the provided radius of the given point.
		@param 		double latitude 	[in] 		coordinates to compare
		@param 		double longitude 	[in] 		coordinates to compare
		@param 		double distance 	[in] 		radius to be compared
		@pre none
		@post boolean value will be properly returned based on calculations.
	*/

	bool is_near(double latitude, double longitude, double distance) const;

	/** 
		Courtesy of Stewart Weiss.
	*/

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

	/**	operator== () - equivalence operator. Returns true if and only if t1 & t2 have equal
		species names and id's.
		@param 	Tree 	& t1 		[inout] 	tree whos contents will be compared
		@param 	Tree    & t2 		[inout] 	tree whos contents will be compared
		@pre 	Trees to be compared have been properly initialized.
		@post 		  
	*/

	friend bool operator==(const Tree & t1, const Tree & t2);

	/**	operator< () - Comparison operator. Compares species common names first, then
		tree ids.
		@param 	Tree 	& t1 		[inout] 	tree whos contents will be compared
		@param 	Tree    & t2 		[inout] 	tree whos contents will be compared
		@pre 	Trees to be compared have been properly initialized.
		@post 		  
	*/

	friend bool operator<(const Tree & t1, const Tree & t2);

	/**	samename () - checks for identical species names in t1 and t2.
		@param 	Tree  	& t			[inout] 	tree whos contents will be compared
		@param 	Tree    & t 		[inout] 	tree whos contents will be compared
		@pre 	Trees to be compared have been properly initialized.
		@post 			  
	*/
	friend bool samename(const Tree & t1, const Tree & t2);

	/**	islessname () - compares sizes of solely species names of t1 and t2.
		@param 	Tree  	& t			[inout] 	tree whos contents will be compared
		@param 	Tree    & t 		[inout] 	tree whos contents will be compared
		@pre 	Trees to be compared have been properly initialized.
		@post 			  
	*/

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
