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

#include <iomanip>
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

string line;

while( getline(fin,line )){
	tc.add_to_collection(line); 
}

int size = tc.total_tree_count();

while ( ! cmd_in.eof() ) {
        if ( ! command.get_next(cmd_in) ) {
            if ( ! cmd_in.eof() )
                cerr << "Could not get next command.\n";
            return 1;
        }
        command.get_args(treename, zipcode, latitude, longitude, 
                         distance, result);

        if( command.type_of() == tree_info_cmmd ){
			cout << "\nCommand: tree_info " << treename << endl;
			cout << "The matching species are:" << "\n \t" << endl;
		for(auto & n : tc.get_matching_species(treename)){
			cout << n << endl;
		}
		cout << "\nPopularity in the city:" << endl; 
		cout << setw(4) << "\nNew York City:" << tc.count_of_tree_species(treename) << "(" << size << ")"
		 << tc.count_of_tree_species(treename)/size * 100 << "%" << endl;
             
        }
        else if( command.type_of() == listall_names_cmmd){
          	cout << "\nCommand: listall_names: " << endl;
	  		tc.print_all_names(cout);
        }
        else if( command.type_of() == list_near_cmmd ){
          	list<string> tree_near = tc.get_all_near(latitude,longitude,distance);
	  		cout << "\nCommand: list_near: " << latitude  <<" "<< longitude << " " << distance <<"\n" << endl;
			tree_near.sort();
			string prev = tree_near.front();
			int sum = 1;
			auto final_iter = tree_near.end();
	  		-- final_iter;
         	for(auto it = tree_near.begin();it!=tree_near.end();++ it){
				auto & n = * it;
					if(n == prev){
						if(n != tree_near.front()){
				 			sum ++;
						}
					}

					if(n!=prev){
						cout << prev << ":" << setw(16)<< sum << endl;
						sum = 1; 
					}
           	 		prev = n;
					if(it == final_iter){
						cout << prev << ":" << setw(16) << sum << endl;
					}
          		}
        }

        else if( command.type_of() == listall_inzip_cmmd ){
       		list<string> tree_zips = tc.get_all_in_zipcode(zipcode);
	  		cout << "\nCommand: listall_inzip: " << zipcode << "\n" << endl;
	  		tree_zips.sort();
	  		string prev = tree_zips.front();
	  		int sum = 1;
	  		auto final_iter = tree_zips.end();
	  		-- final_iter;
	  		// A for loop with iterators to keep track of the previous element and output it
	  		// for easy calculations.
				for(auto it = tree_zips.begin(); it!=tree_zips.end();it ++){
					auto & n = * it;
					if(n == prev){
						if(n != tree_zips.front()){
				 		sum ++;
					}
				}
				if(n!=prev){
					cout << prev << ":" << setw(16) << sum << endl;
					sum = 1; 
				}
           		prev = n;
				if(it == final_iter){
					cout << "last iter" << endl;
					cout << prev << ":" << setw(16) << sum << endl;
				}
          	}	
       
        }
          
        else cout << "bad_cmmd" << endl; 
    }

fin.close();
cmd_in.close();

return 0;

}
