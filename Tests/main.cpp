/*******************************************************************************
  Title          : main.cpp
  Author         : Aaron D Taveras
  Created on     : March 15th, 2018
  Description    : Main method and driver for the project.
  Purpose        : To allow for testing and production of proper output.  
  Usage          : 
  Build with     : 
  Modifications  : 
 
*******************************************************************************/

#include "command.h"
#include "tree.h"
#include "tree_species.h"
#include "tree_collection.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <list>

int main( int argc, char * argv[] ){


TreeCollection tc; 	
ifstream fin;
ifstream cmd_in;     
Command   command;
string    treename;
int       zipcode;
double    latitude, longitude, distance;
bool      result;

if(argc < 3){
	cerr << "Incorrect number of arguments provided." << endl;
	return 1;
}

fin.open(argv[1]);

if(fin.fail()){
	cerr << "Could not open " << argv[1] << endl;
	return 1;
}

cmd_in.open(argv[2]);

if(cmd_in.fail()){
	cerr << "Could not open " << argv[2] << endl;
	return 1;
}

int count = 1;
string line;

while( getline(fin,line )){
	tc.add_to_collection(line);
//	cout << count << endl;
	count ++ ; 
}

int size = tc.total_tree_count();
int species_in_boro = 0;

while ( ! cmd_in.eof() ) {
        if ( ! command.get_next(cmd_in) ) {
            if ( ! cmd_in.eof() )
                cerr << "Could not get next command.\n";
            return 1;
        }
        command.get_args(treename, zipcode, latitude, longitude, 
                         distance, result);

        if( command.type_of() == tree_info_cmmd ){
	int species_in_b = 0, species_in_b = 0, species_in_si= 0,species_in_queens=0,species_in_man=0;
		cout << "All matching species:" << endl;
		for(auto & n: avl.findallmatches(treename)){
			cout << n << endl;
			if(n.borough_match("brooklyn"){
				species_in_bk ++;
			}
			else if(n.borough_match("staten island"){
				species_in_bk ++;
			}
			else if(n.borough_match("bronx"){
				species_in_bx ++;
			}
			else if(n.borough_match("queens"){
				species_in_queens ++;
			}
			else if(n.borough_match("manhattan"){
				species_in_man ++;
			}
		}
		cout << "Frequency by borough:" << endl;
		cout << "Total in NYC:\t" << tc.count_of_tree_species(treename) << "\t(" << size << ")" << 
	        "\t" <<(tc.count_of_tree_species(treename)/size) * 100 << "%" << endl;
		cout << "Manhattan:\t" << species_in_man << "\t(" << tc.count_of_trees_in_boro("manhattan")<<
		")" << "\t" << (species_in_man/tc.count_of_trees_in_boro("manhattan")) * 100 << "%" << endl;		     cout << "Bronx:\t" << species_in_bx << "\t(" << tc.count_of_trees_in_boro("bronx")<<
                ")" << "\t" << (species_in_man/tc.count_of_trees_in_boro("bronx")) * 100 << "%" << endl;
               // cout << "tree_info" << treename << " " << size << endl;
        }
        else if( command.type_of() == listall_names_cmmd){
          cout << "listall_names_cmmd" << endl;
        }
        else if( command.type_of() == list_near_cmmd ){
          list<string> tree_near = tc.get_all_near(latitude,longitude,distance);
          for(auto & n: tree_near){
            cout << n << ":" << endl;
          }
	 cout << "list_near" << endl;
        }
        else if( command.type_of() == listall_inzip_cmmd ){
          list<string> tree_zips = tc.get_all_in_zipcode(zipcode);
          for(auto & n: tree_zips){
            cout << n << ":" << endl;
          }
		cout << "list zip" << endl;
        }
        else cout << "bad_cmmd" << endl; 
    }
cout << "test" << endl;
cout << 0 << tc.count_of_trees_in_boro("qUeEnS") << endl;

fin.close();
cmd_in.close();

return 0;

}
