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

	TreeCollection();

	~TreeCollection();

	void add_to_collection(string & treedata);

	int total_tree_count() const;

	int count_of_tree_species( const string & species_name ) const;

	int count_of_trees_in_boro( const string & boro_name ) const;

	list<string> get_matching_species( const string & species_name ) const;

	list<string> get_all_in_zipcode( int zipcode ) const;

	list<string> get_all_near( double latitude, double longitude, double distance ) const;

private:

	struct BoroughNames{

		int staten_island,brooklyn,manhattan,queens,bronx;

		BoroughNames(){
			staten_island = 0;
			brooklyn = 0;
			manhattan = 0;
			queens = 0;
			bronx = 0;
		}
	}; 

	int size;
	TreeSpecies spec_container;
	AVL_Tree avl; 
	BoroughNames boro_names;
	// container that stores names of each borough and how many trees from 
	// the data set are in each borough 
	
};

#endif 