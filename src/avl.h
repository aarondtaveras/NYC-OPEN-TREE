/*******************************************************************************
  Title          : avl.h
  Author         : Aaron D Taveras
  Created on     : March 8th, 2018
  Description    : Header file for the avl tree class, which represents an 
  				   AVL tree object.
  Purpose        : To represent and encapsulate an AVL tree.  
  Usage          : 
  Build with     : 
  Modifications  : 
 
*******************************************************************************/
#ifndef __AVL_H__
#define __AVL_H__

#include <iostream>
#include <algorithm>
#include <list>
#include "tree.h"
#include "tree_species.h"


// The tree object to be returned when a tree is not found in a search.

using namespace std;

extern Tree NOT_FOUND;

class AVL_Tree
{
	public:
		AVL_Tree (); // Default constructor 
		AVL_Tree ( const AVL_Tree & tree); // Copy constructor
		~AVL_Tree (); // Destructor 

		//Search methods:
		const Tree & find ( const Tree & x ) const;
		const Tree & findMin () const;
		const Tree & findMax () const;
		list<Tree> findallmatches ( const Tree & x ) const;

		/**	Traversals:
			prints the Tree objects onto the ostream using inorder traversal.
			Each of the members of the Tree object is printed, in the exact
			same order as they are above, e.g. with the tree spc_common name
			first, then the tree_id. Fields should be separated by commas
			in the output stream.
		*/
		void print ( ostream & out ) const; // prints the Tree objects

		void in_order_zip ( int zipcode, list<string> & l ) const;

		void in_order_near ( double lat, double lon, double distance, list<string> & l) const; 
		
		//Size function

		int size() const;

		//Tree modifiers:
		void clear(); 				   // empty the tree
		void insert( const Tree & x ); // insert element x 
		void remove( const Tree & x ); // remove element x
		 
	private:

		struct avl_node{ 
		Tree 		element;
		avl_node* 	left;
		avl_node* 	right;
		int height;

		// Node constructor
		avl_node( const Tree & item, avl_node * lt, avl_node * rt,int ht){
			element = item;
			left = lt;
			right = rt;
			height = ht;
		}
			
		};
		
		int height( avl_node * t) const; //accessor for height of node

		avl_node * root;	// Our only private data member
		
		//Private recursive methods called by public methods
		avl_node * find ( const Tree & x, avl_node * t) const;
		avl_node * findMin( avl_node * t) const;
		avl_node * findMax( avl_node * t) const;
		avl_node * copy( avl_node * t);
		int size(avl_node * t) const;
		void clear( avl_node *& t);
		void insert( const Tree & x, avl_node *& t);
		void remove( const Tree & x, avl_node *& t);
		void in_order( avl_node * t, ostream & out) const;
		void in_order_zip( avl_node * t, int zipcode, list<string> & l) const;
		void in_order( avl_node * t, list<Tree> & l, SpeciesName & s) const;
		void in_order_near( avl_node * t, double lat, double lon, double distance, list<string> & l) const;
		
		
		//Rotations 
		avl_node * LL_rotate( avl_node *& t);
		avl_node * LR_rotate( avl_node *& t);
		avl_node * RR_rotate( avl_node *& t);
		avl_node * RL_rotate( avl_node *& t);


}; 

#endif
