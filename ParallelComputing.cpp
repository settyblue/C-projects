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
	vector<int> top_n;
	vector<int> bottom_n;
	vector<int> left_n;
	vector<int> right_n;
	float temperature;
};

void print_grid_block(grid_block box);

void print_grid_blocks(vector<grid_block>& grid_blocks);

void parse_input(vector<grid_block>& grid_blocks);

int main(){
	int num_of_grids,num_grid_rows,num_grid_columns;	
	string line;
	int id;
	vector<grid_block> grid_blocks;
	//parse input from the file.
	parse_input(grid_blocks);
	//print the parsed data.
	print_grid_blocks(grid_blocks);
	return 0;
}

void parse_input(vector<grid_block>& grid_blocks){
	int num_of_grids,num_grid_rows,num_grid_columns;
	int id;	
	string line;
	//vector<grid_block> grid_blocks;
	if (myfile.is_open()){
		getline (myfile,line);
		istringstream iss;
		iss.str(line);
	    iss>>num_of_grids;
	    iss>>num_grid_rows;
	    iss>>num_grid_columns;
		iss.clear();
		cout<<"num_of_grids num_grid_rows num_grid_columns"<<num_of_grids<<num_grid_rows<<num_grid_columns<<endl;
		
		//Lets get the grid parameters here.
		for (int i=0;i<num_of_grids;i++){
			//get the grid box id.
			getline (myfile,line);iss.str(line);
			//add a new grid block to the array of blocks.
		  	grid_blocks.push_back(grid_block());
		  	iss >> grid_blocks[i].box_id;
		  	iss.clear();
		  	//get coordinates of the box and its size.
		  	getline (myfile,line);iss.str(line);
		  	iss >> grid_blocks[i].up_left_x;
		  	iss >> grid_blocks[i].up_left_y;
		  	iss >> grid_blocks[i].height;
		  	iss >> grid_blocks[i].width;
		  	iss.clear();
		  	
		  	//get the details about neighbors.
		  	//get the details of the top neighbors.
		  	getline (myfile,line);iss.str(line);
		  	iss >> grid_blocks[i].num_top_n;
		  	for (int j=0;j<grid_blocks[i].num_top_n;j++){
		  		iss >> id;
		  		grid_blocks[i].top_n.push_back(id);
			}
			iss.clear();
			//get details of the bottom neighnbors.
			getline (myfile,line);iss.str(line);
		  	iss >> grid_blocks[i].num_bottom_n;
		  	for (int j=0;j<grid_blocks[i].num_bottom_n;j++){
		  		iss >> id;
		  		grid_blocks[i].bottom_n.push_back(id);
			}
			iss.clear();
			//get details of the right neighnbors.
			getline (myfile,line);iss.str(line);
		  	iss >> grid_blocks[i].num_left_n;
		  	for (int j=0;j<grid_blocks[i].num_left_n;j++){
		  		iss >> id;
		  		grid_blocks[i].left_n.push_back(id);
			}
			iss.clear();
			//get details of the left neighnbors.
			getline (myfile,line);iss.str(line);
		  	iss >> grid_blocks[i].num_right_n;
		  	for (int j=0;j<grid_blocks[i].num_right_n;j++){
		  		iss >> id;
		  		grid_blocks[i].right_n.push_back(id);
			}
			iss.clear();
			//get the temperature of the box.
			getline (myfile,line);iss.str(line);
			iss >> grid_blocks[i].temperature;
			iss.clear();
			//print the grid block.
			//print_grid_block(grid_blocks[i]);
		}
	    myfile.close();
	}else cout << "Unable to open file";
}

void print_grid_blocks(vector<grid_block>& grid_blocks){
	for (int i=0;i<grid_blocks.size();i++){
		print_grid_block(grid_blocks[i]);
	}
}

void print_grid_block(grid_block box){
	cout<<"--------------"<<endl;
	cout<<"box_id : "<<box.box_id<<endl;
	cout<<"up_left_x : "<<box.up_left_x<<" up_left_y : "<<box.up_left_y<<" height : "<<box.height<<" width : "<<box.width<<endl;
	cout<<"num_top_n : "<<box.num_top_n<<" ::: ";
	for (int i=0;i<box.num_top_n;i++){
		cout<<box.top_n[i]<<" , ";
	}
	cout<<endl;
	cout<<"num_bottom_n : "<<box.num_bottom_n<<" ::: ";
	for (int i=0;i<box.num_bottom_n;i++){
		cout<<box.bottom_n[i]<<" , ";
	}
	cout<<endl;
	cout<<"num_left_n : "<<box.num_left_n<<" ::: ";
	for (int i=0;i<box.num_left_n;i++){
		cout<<box.left_n[i]<<" , ";
	}
	cout<<endl;
	cout<<"num_right_n : "<<box.num_right_n<<" ::: ";
	for (int i=0;i<box.num_right_n;i++){
		cout<<box.right_n[i]<<" , ";
	}
	cout<<endl;
	cout<<"temperature : "<<box.temperature<<endl;
	cout<<"--------------"<<endl;
}
