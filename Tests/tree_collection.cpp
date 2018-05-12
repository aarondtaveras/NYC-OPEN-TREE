#include "tree_collection.h"


TreeCollection::TreeCollection()
{
	
}

TreeCollection::~TreeCollection()
{
	
}

void TreeCollection::add_to_collection(string & treedata)
{	
	// Construct Tree from treedata string, and insert into tree1`
	Tree temp = Tree(treedata);
	avl.insert(temp);
	if(temp.borough_name()!=""){
		if(temp.borough_name()[0]=='Q' || 
			temp.borough_name()[0]=='q'){
			boro_names.queens ++;
		}
		else if(temp.borough_name()[0]=='S' ||
				temp.borough_name()[0]=='s'){
			boro_names.staten_island ++;
		}
		else if(temp.borough_name()[0]=='B' || 
				temp.borough_name()[0]=='b'){
			boro_names.brooklyn ++;
		}
		else if(temp.borough_name()[1]=='R' || 
				temp.borough_name()[1]=='r'){
			boro_names.bronx ++;
		}
		else if(temp.borough_name()[0]=='M' || 
				temp.borough_name()[0]=='m'){
			boro_names.manhattan ++;
		}
	}
	
//	cout << "before adding to spec container." << endl;
	//If the name isn't empty, add the species to spec_container
	if(temp.common_name()!=""){
		spec_container.add_species(temp.common_name());
	}	
}

int TreeCollection::total_tree_count() const
{
	return avl.size();
}

int TreeCollection::count_of_tree_species( const string & species_name ) const
{
	string species_name_copy = species_name;
	// Because our string is marked as const.

	// Case insensitivity
	for(auto & c: species_name_copy){
		c = tolower(c);
	}
	list<string> matches;
	// avl.findallmatches();
	return 0;
}

int TreeCollection::count_of_trees_in_boro( const string & boro_name ) const
{
	string boro_name_copy = boro_name;
	// Because our string is marked as const.

	// Case insensitivity
	for(auto & c: boro_name_copy){
		c = tolower(c);
	}
	cout << boro_name_copy << endl;
	if(boro_name_copy == "brooklyn"){
		return boro_names.brooklyn;
	}
	else if(boro_name_copy == "bronx"){
		return boro_names.bronx;
	}
	else if(boro_name_copy == "queens"){
		return boro_names.queens;
	}
	else if(boro_name_copy == "manhattan"){
		return boro_names.manhattan;
	}
	else if(boro_name_copy == "staten island"){
		return boro_names.staten_island;
	}
	else return 0;
}

list<string> TreeCollection::get_matching_species( const string & species_name ) const
{
	return spec_container.get_matching_species(species_name);
}

list<string> TreeCollection::get_all_in_zipcode( int zipcode ) const
{
	list<string> all_in_zip;
	avl.in_order_zip(zipcode, all_in_zip);
	return all_in_zip; 
}

list<string> TreeCollection::get_all_near( double latitude, double longitude, double distance) const
{
	list<string> all_near;
	avl.in_order_near(latitude,longitude,distance,all_near);
	return all_near;	
}
