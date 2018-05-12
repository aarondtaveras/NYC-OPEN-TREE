/*******************************************************************************
  Title          : tree_collection.h
  Author         : Aaron D Taveras
  Created on     : March 8th, 2018
  Description    : Interface to the tree_collection class
  Purpose        : To define methods to encapsulate the data set within three 
  					containers. 
  Usage          : 
  Build with     : 
  Modifications  : 
 
*******************************************************************************/

#ifndef __TREECOLLECTION_H__
#define __TREECOLLECTION_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>  
#include <ctype.h>
#include "avl.h"
#include "tree_species.h"


class TreeCollection{

public:

	//Default constructor.
	TreeCollection();

	//Default destructor.
	~TreeCollection();

	/**
		add_to_collection() - is responsible for updating each container 
		in our class by parsing the given line from the CSV file. 
		@param 		string & s 		[inout] 		line to parse from CSV
		@pre 		all of our containers have been initialized properly
		@post 		our avl tree, species_container, and boroughnames containers
					will all have attempted to append data to their collection.
	*/
	void add_to_collection(string & treedata);

	/**
		total_tree_count() - returns the total number of trees stored in
		the collection.
		@param 		none 
		@pre 		none
		@post 		collection remains unchanged
	*/
	int total_tree_count() const;

	/**
		count_of_tree_species() - returns the number of Tree objects in the
		collection whose spc_common matches the specified parameter.
		@param 		string & species_name 	[inout] 	species to check against
		@pre 		none
		@post 		collection remains unchanged
	*/

	int count_of_tree_species( const string & species_name ) const;

	/**
		count_of_trees_in_boro() - returns the number of Tree objects in the 
		collection that are located in the borough specified by the parameter.
		@param  	string & species_name 	[inout] 	 species name to be searched for in boro
		@pre 		none
		@post 		collection remains unchanged
	*/

	int count_of_trees_in_boro( const string & boro_name ) const;

	/**
		get_matching_species() - returns a list<string> object containing a 
		list of all tree species that match a given parameter species_name.
		@param 		string & boro_name 		[inout] 		species name to be searched for
		@pre 		none
		@post 		collection remains unchanged
	*/

	list<string> get_matching_species( const string & species_name ) const;

	/**
		get_all_in_zipcode() - returns a list<string> object containing a list 
		of all of the actual tree species that are located in the given zip.
		@param 		int zipcode 		[in] 				zipcode to search trees within
		@pre 		none
		@post 		collection remains unchanged
	*/

	list<string> get_all_in_zipcode( int zipcode ) const;

	/** 
		print_all_names() - prints all unique species names in our collection to 
		the specified ostream.
		@param 	ostream & out 		[inout] 		ostream to write data to
		@pre 	out is open and ready for writing
		@post 	collection remains and unchanged, out remains open 

	*/

	void print_all_names( ostream & out ) const;

	/**
		get_all_near() - returns a list<string> object containing a list of all of the actual
		tree species within distance km from our current position.
		@param 		double latitude 		[in] 		coordinates for calculation
		@param 		double longitude 		[in] 		coordinates for calculation
		@param 		double distance 		[in] 		radius to be checked against.
		@pre 		none
		@post 		collection remains unchanged.
	*/

	list<string> get_all_near( double latitude, double longitude, double distance ) const;

private:

	/** 
		struct BoroughNames is a simple user defined struct meant to contain
		a running count of the number of trees within each borough. There is 
		a string representing each borough, and upon addition to the data set
		the corresponding string is incremented.
	*/
	struct BoroughNames{

		int staten_island,brooklyn,manhattan,queens,bronx;

		//initialize each borough to zero. 
		BoroughNames(){
			staten_island = 0;
			brooklyn = 0;
			manhattan = 0;
			queens = 0;
			bronx = 0;
		}
	}; 

	TreeSpecies spec_container; // container that stores all species names
	AVL_Tree avl; // AVL tree which will contain all tree objects
	BoroughNames boro_names; // user defined struct for keeping track of trees in boro
	// container that stores names of each borough and how many trees from 
	// the data set are in each borough 
	
};

#endif 
