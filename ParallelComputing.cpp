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
	int up_left_x;
	int up_left_y;
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

void print_grid_block(grid_block box);

int main(){
	int num_of_grids,num_grid_rows,num_grid_columns;	
	string line,line1,line2;
	
	if (myfile.is_open()){
		getline (myfile,line);
		istringstream iss;
		iss.str(line);
	    iss>>num_of_grids;
	    iss>>num_grid_rows;
	    iss>>num_grid_columns;
		iss.clear();
		vector<grid_block> grid_blocks;
		cout<<"num_of_grids num_grid_rows num_grid_columns"<<num_of_grids<<num_grid_rows<<num_grid_columns<<endl;
		
		//Lets get the grid parameters here.
		for (int i=0;i<num_of_grids;i++){
			//get the grid box id.
			getline (myfile,line);iss.str(line);
			cout<<line<<" hello "<<endl;
		  	grid_blocks.push_back(grid_block());
		  	iss >> grid_blocks[i].box_id;
		  	iss.clear();
		  	
		  	//get coordinates of the box and its size.
		  	getline (myfile,line);iss.str(line);
		  	cout<<line<<" hello "<<endl;
		  	iss >> grid_blocks[i].up_left_x;
		  	iss >> grid_blocks[i].up_left_y;
		  	iss >> grid_blocks[i].height;
		  	iss >> grid_blocks[i].width;
		  	print_grid_block(grid_blocks[i]);
		  	iss.clear();
		  	
		}
	    myfile.close();
	}else cout << "Unable to open file"; 
	
	return 0;
}

void print_grid_block(grid_block box){
	cout<<"--------------"<<endl;
	cout<<"box_id : "<<box.box_id<<endl;
	cout<<"up_left_x : "<<box.up_left_x<<" up_left_y : "<<box.up_left_y<<" height : "<<box.height<<" width : "<<box.width<<endl;
	cout<<"--------------"<<endl;
}
