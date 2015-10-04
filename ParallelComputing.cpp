#include<iostream>
#include<string>
#include<math.h>
#include<stack>
#include<fstream>
#include<sstream>
#include<vector>
std::ifstream myfile("Numbers.txt");
using namespace std;

//

struct grid_block{
	int box_id;
	int up_left;
	int up_right;
	int height;
	int width;
	int num_top_n;
	int num_bottom_n;
	int num_left_n;
	int num_right_n;
	vector<grid_block> top_n;
	vector<grid_block> bottom_n;
	vector<grid_block> left_n;
	vector<grid_block> right_n;
	float temperature;
};
int main(){
	int num_of_grids,num_grid_rows,num_grid_columns;	
	string line;
	
	if (myfile.is_open()){
	    while ( getline (myfile,line) ){
	      cout << line << '\n';
	      
	      //Lets get the number of grids and the total grid dimension here.
	      if (line_number == 0){
		      istringstream iss;
			  iss.str(line);
		      for (int i=0;i<3;i++){
		      	iss>>num_of_grids;
		      	iss>>num_grid_rows;
		      	iss>>num_grid_columns;
			  }
			  vector<grid_block> grid_blocks;
			  cout<<"num_of_grids num_grid_rows num_grid_columns"<<num_of_grids<<num_grid_rows<<num_grid_columns<<endl;
			  continue;
		  }
	      else {
	      	//Lets get the grid parameters here.
		    for (int i=0;i<num_of_grids;i++){
		  		grid_blocks.push_back(grid_block());
		  		
		  	}
		  }
		  
		  //
    	  //int a;
    	  //if (!(iss >> a)) { break; }
    	  //cout<<"h "<<a<<" h"<<endl;
    	  //
	    }
	    myfile.close();
	}else cout << "Unable to open file"; 
	
	return 0;
}
