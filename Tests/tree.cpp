/*******************************************************************************
  Title          : tree.cpp
  Author         : Aaron D Taveras
  Created on     : February 8th, 2018
  Description    : Implementation of the tree class
  Purpose        : To implement the methods provided in the tree interface.  
  Usage          : Include "tree.h" header file
  Build with     : 
  Modifications  : 
 
*******************************************************************************/

#include <vector>
#include "tree.h"

using namespace std;

Tree::Tree()
{
	// Default values for private data members.
	spc_common = "";
	tree_id = 0;
	tree_dbh = 0;
	status = "";
	health = "";
	address = "";
	boroname = "";
	zipcode = 0;
	latitude = 0.0;
	longitude = 0.0;
}

Tree::Tree(int id, int diam, string stat, string hlth, string spc, int zip,
			string addr, string boro, double lat, double lng)
{
	tree_id = id;
	tree_dbh = diam;
	status = stat;
	health = hlth;
	address = addr;
	boroname = boro;
	spc_common = spc;
	zipcode = zip;
	latitude = lat;
	longitude = lng;
}

Tree::Tree(const string & treedata)
{
	/** Parsing the given string by creating a vector that holds substrings
	 	which will represent the 41 fields within each line of tree data.
	*/

	stringstream tree_stream(treedata);
	vector<string> field;

	while( tree_stream.good()){
		string sub;
		while(getline(tree_stream,sub,',')){
			if(sub[0] == '"'){
				string sub2;
				getline(tree_stream,sub2,'"');
				sub += sub2;
			}
			else field.push_back(sub);
		}
	// Our vector now contains every field separated by a comma, indexed 0-40.
	}

	// Setting private data members to the substrings contained in our vector
	// based on their respective column index (0-40).
	tree_id = atoi(field[0].c_str()); // Conversion to c_str to avoid UDB.
	tree_dbh = atoi(field[3].c_str());
	status = field[6];
	health = field[7];
	spc_common = field[9];
	address = field[24];
	zipcode = atoi(field[25].c_str());
	if(field[29]=="Queens"||field[29]=="Brooklyn"||field[29]=="Manhattan"||field[29]=="Staten Island"||field[29]=="Bronx"){
			boroname = field[29];
	}
	else {boroname = "";}
	latitude = atof(field[37].c_str()); // Conversion to double as opposed to int.
	longitude = atof(field[38].c_str());
}

string Tree::common_name() const
{
	return spc_common;
}

string Tree::borough_name() const
{
	return boroname;
}

string Tree::get_address() const
{
	return address;
}

int Tree::diameter() const
{
	return tree_dbh;
}

int Tree::get_zipcode() const
{
	return zipcode;
}

void Tree::get_position(double & lat, double & lng) const
{
	lat = latitude;
	lng = longitude;
}

bool Tree::is_near(double lat1, double lon1, double distance) const
{
	int result = haversine( lat1, lon1, latitude, longitude);
	return result <= distance;
}

double Tree::haversine(  double lat1, double lon1, double lat2, double lon2) const
{
    lat1        = TO_RAD * lat1;
    lat2        = TO_RAD * lat2;
    lon1        = TO_RAD * lon1;
    lon2        = TO_RAD * lon2;
    double dLat = (lat2 - lat1)/2;
    double dLon = (lon2 - lon1)/2;
    double a    = sin(dLat);
    double b    = sin(dLon);
    return 2*R * asin(sqrt(a*a + cos(lat1) * cos(lat2) * b*b));
}

string Tree::write() const
{
		
	string tree_data = (spc_common + "\t" + to_string(tree_id) + "\t" + to_string(tree_dbh) + "\t" + status + "\t" 
			+ health + "\t" + address + "\t" + boroname + "\t" + to_string(zipcode) + "\t" + to_string(latitude) + "\t" + to_string(longitude));
	return tree_data;
	
}

ostream & operator<< (ostream & os, const Tree & t)
{
	os << t.spc_common << ',' << t.tree_id << ',' << t.tree_dbh << ',' 
	<< t.status << ',' << t.health << ',' << t.address << ',' << t.boroname
	<< ',' << t.zipcode << ',' << t.latitude << ',' << t.longitude << endl;
	// Creating a formatted string by calling our write function, then outputting
	// the result onto the given stream. 
	return os;
}	

bool operator<(const Tree & t1, const Tree & t2)
{
	if(islessname(t1,t2)){
		// cout << "names are: " << t1.spc_common << " " << t2.spc_common << endl;
		// cout << "sizes are: " << t1.spc_common.size() << " " << t2.spc_common.size() << endl;
		// cout << "less names!" << endl;
		return true;
	}
	else if(samename(t1,t2)){
		// cout << "names are: " << t1.spc_common << " " << t2.spc_common << endl;
		// cout << "sizes are: " << t1.spc_common.size() << " " << t2.spc_common.size() << endl;
		// cout << "same names!" << endl;
		if(t1.tree_id < t2.tree_id){
			// cout << "id is less!" << endl;
			return true;
		}
		else return false;
	}
	return false;
}

bool samename(const Tree & t1, const Tree & t2)
{
	if(t1.spc_common.size() == t2.spc_common.size()){
		return true;
	}
	return false;
}

bool islessname(const Tree & t1, const Tree & t2)
{
	if(t1.spc_common.size() < t2.spc_common.size()){
		return true;
	}
	return false;
}

bool operator==(const Tree & t1, const Tree & t2)
{
	if(t1.spc_common == t2.spc_common && t1.tree_id == t2.tree_id){
		return true;
	}
	return false;
}
