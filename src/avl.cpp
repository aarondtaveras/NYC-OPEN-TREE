/*******************************************************************************
  Title          : avl.cpp
  Author         : Aaron D Taveras
  Created on     : March 8th, 2018
  Description    : Implementation for the avl tree class, which represents an 
  				   AVL tree object.
  Purpose        : To provide methods to manipulate an AVL tree.  
  Usage          : 
  Build with     : 
  Modifications  : 
 
*******************************************************************************/


#include "avl.h"

Tree NOT_FOUND = Tree(-1,-1,"","","",-1,"","",-1,-1);

AVL_Tree::AVL_Tree()
{
	root = nullptr;
}

AVL_Tree::AVL_Tree( const AVL_Tree & tree )
{
	copy(tree.root); 
}

AVL_Tree::~AVL_Tree()
{
	clear(root);
}

/** 
	The following are the basic recursive implementations of the public wrapper methods.
	The public wrapper methods make calls to the private methods that implement them in 
	order to hide the private data from the client. 
*/


int AVL_Tree::height( avl_node * t) const
{
	return (t == nullptr ? -1 : t->height);
}

int AVL_Tree::size() const
{
	return(size(root));
}


const Tree & AVL_Tree::find( const Tree & x ) const
{
	avl_node * t = find(x,root);	
	if(t!=nullptr){
		return t->element;
	}
	else return NOT_FOUND;
}

const Tree & AVL_Tree::findMin () const
{
	avl_node * t = findMin(root);
	if(t!=nullptr){
		return t->element;
	}
	else return NOT_FOUND;
}

const Tree & AVL_Tree::findMax () const
{
	avl_node * t = findMax(root);
	if(t!=nullptr){
		return t->element;
	}
	else return NOT_FOUND;
}

void AVL_Tree::insert( const Tree & x )
{
	insert(x,root);
}

void AVL_Tree::remove( const Tree & x )
{
	remove(x,root);
}

void AVL_Tree::print( ostream & out ) const
{
	in_order(root,out);
}

void AVL_Tree::in_order_zip( int zipcode, list<string> & l) const
{
	in_order_zip(root,zipcode,l);
}

void AVL_Tree::in_order_near( double lat, double lon, double distance, list<string> & l) const
{
	in_order_near( root, lat, lon, distance, l);
}

list<Tree> AVL_Tree::findallmatches( const Tree & x ) const
{
	list<Tree> matches;
	SpeciesName spec_name(x.common_name());
	in_order(root, matches, spec_name);
	
	return matches; 

}

/** 
	The following are the private implementations of all public wrapper functions.
*/

int AVL_Tree::size( avl_node * t ) const
{
	if(t == nullptr)
		return 0;
	else
		return(size(t->left) + 1 + size(t->right));
}

AVL_Tree::avl_node * AVL_Tree::find( const Tree & x, avl_node * t) const
{
	if(t == nullptr || t->element == x){
		return t;
	}	
	else if( t->element < x ){
		return find( x, t->right );
	}

	else 
		cout << "item found " << t->element << endl;
		return find( x, t->left ); 
	
}



AVL_Tree::avl_node * AVL_Tree::findMin ( avl_node * t ) const
{
	if( t == nullptr ){return nullptr;}
	if(t->left == nullptr){return t;}
	return findMin( t->left );
}


AVL_Tree::avl_node * AVL_Tree::findMax( avl_node * t ) const
{
	if( t == nullptr){return nullptr;}
	if( t-> right == nullptr){return t;}
	return findMax( t->right );
}

void AVL_Tree::in_order( avl_node * t, ostream & out ) const
{
	if(t == nullptr)
		return;
	in_order( t->left,out );
	out << t->element << endl;
	in_order( t->right,out );
}


void AVL_Tree::in_order( avl_node * t, list<Tree> & l, SpeciesName & s) const
{
	if(t == nullptr)
		return;
	in_order( t->left, l, s);
	if(s.matches( t->element.common_name() )){
		l.push_back(t->element);
	}
	in_order( t->right, l, s);
}

void AVL_Tree::in_order_zip( avl_node * t, int zipcode, list<string> & l) const
{
	if(t == nullptr)
		return;
	in_order_zip( t->left, zipcode, l );
	if( t->element.get_zipcode() == zipcode ){
		l.push_back( t->element.common_name() );
	}
	in_order_zip( t->right, zipcode, l );
}

void AVL_Tree::in_order_near( avl_node * t, double lat, double lon, double distance, list<string> & l) const
{
	if(t==nullptr)
		return;
	in_order_near( t->left, lat, lon, distance, l);
	if(t->element.is_near(lat,lon,distance)){
		l.push_back( t->element.common_name() );
	}
	in_order_near( t->right, lat, lon, distance, l);
}

void AVL_Tree::clear( avl_node *& t)
{
	if(t!=nullptr){
		remove(t->left->element,t->left);
		remove(t->right->element,t->right);
		delete t;
	}
	t = nullptr;
}


AVL_Tree::avl_node* AVL_Tree::copy( avl_node * t)
{
	if(t == nullptr){return nullptr;}
	else return new avl_node(t->element, copy(t->left), copy(t->right),t->height);
}


void AVL_Tree::insert( const Tree & x, avl_node *& t)
{
	if(t == nullptr){
		t = new avl_node(x, nullptr, nullptr,0);
	}
	else if(x < t->element){
		insert(x,t->left);
		if(height(t->left) - height(t->right) == 2){
			if(x < t->left->element){
				t = LL_rotate(t);
			}
			else t = LR_rotate(t);
		}
	}
	else if(t->element < x){
		insert(x,t->right);
		if(height(t->right) - height(t->left) == 2){
			if(t->right->element < x){
				t = RR_rotate(t);
			}
			else t = RL_rotate(t);
		}
	}
	else if(x == t->element){
		cout << "duplicate not added to tree." << endl;
		return;
	}
	t->height = max( height(t->left), height(t->right) ) + 1;
}


void AVL_Tree::remove( const Tree & x, avl_node *& t)
{
	if(t == nullptr) return;
	
	if(x < t->element){
		remove( x, t->left );
		if( height(t->right) - height(t->left) == 2 ){
			if(height((t->right)->right) >= height((t->right)->left) ){
				t = RR_rotate(t);
			}
			else 
				t = RL_rotate(t);
		}
	}
	else if( t->element < x ){
		remove( x, t->right );
		if( height(t->left) - height(t->right) == 2){
			if( height((t->left)->left) >= height((t->left)->right) ){
				t = LL_rotate(t);
			}
			else t = LR_rotate(t);
		}
	}
	else {
		if((t->left != nullptr) && (t->right!=nullptr) ){
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
			if(height(t->left) - height(t->right) == 2 ){
				if(height( (t->left)->left) >= height((t->left)->right) ){
					t = LL_rotate(t);
				}
				else 
					t = LR_rotate(t);
			}
		}
		else {
			avl_node * old_node = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete old_node;
		}
	}
	if(nullptr != t)
		t->height = max( height(t->left),height(t->right) ) + 1;
}


AVL_Tree::avl_node * AVL_Tree::LL_rotate( avl_node *& k2 )
{
	avl_node * k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k1->right))+1;
	k1->height = max(height(k1->left),k2->height)+ 1;
	return k1;
}


AVL_Tree::avl_node * AVL_Tree::LR_rotate( avl_node *& k2 )
{
	k2->left = RR_rotate(k2->left);
	return LL_rotate(k2);
}


AVL_Tree::avl_node * AVL_Tree::RR_rotate( avl_node *& k2 )
{
	avl_node * k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max(height(k2->right), height(k1->right))+1;
	k1->height = max(height(k1->right),k2->height)+1;
	return k1;
}


AVL_Tree::avl_node * AVL_Tree::RL_rotate( avl_node *& k2 )
{
	k2->right = LL_rotate(k2->right);
	return RR_rotate(k2);
}
