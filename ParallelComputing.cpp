#include<iostream>
#include<string>
#include<math.h>
#include<stack>
#include<fstream>
#include<sstream>
#include<vector>
#include<functional>
std::ifstream myfile("Numbers2.txt");
using namespace std;

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
	int perimeter;
};

void print_grid_block(grid_block box);

void print_grid_blocks(vector<grid_block>& grid_blocks);

void parse_input(vector<grid_block>& grid_blocks);

float sum_of_temp_on_perimeter(grid_block box,vector<grid_block>& grid_blocks);

float weightage(int id1, int id2, vector<grid_block>& grid_blocks);

float temperature_difference(int id1,vector<grid_block>& grid_blocks);

void compute_effective_perimeter(vector<grid_block>& grid_blocks);

int main(){
	int num_of_grids,num_grid_rows,num_grid_columns;	
	string line;
	int id;
	vector<grid_block> grid_blocks;
	//parse input from the file.
	parse_input(grid_blocks);
	//print the parsed data.
	//print_grid_blocks(grid_blocks);
	cout<<sum_of_temp_on_perimeter(grid_blocks[11],grid_blocks);
	compute_effective_perimeter(grid_blocks);
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
	cout<<"perimeter : "<<box.perimeter<<endl;
	cout<<"--------------"<<endl;
}

float sum_of_temp_on_perimeter(grid_block box,vector<grid_block>& grid_blocks){
	float temperature = 0.0;
	int id;
	//Add temperatures on the top neighbors.
	for (int i=0;i<box.num_top_n;i++){
		id = box.top_n[i];
		temperature += weightage(box.box_id,id,grid_blocks)*grid_blocks[id].temperature;
	}
	//Add temperatures on the bottom neighbors.
	for (int i=0;i<box.num_bottom_n;i++){
		id = box.bottom_n[i];
		temperature += weightage(box.box_id,id,grid_blocks)*grid_blocks[id].temperature;
	}
	//Add temperatures on the left neighbors.
	for (int i=0;i<box.num_left_n;i++){
		id = box.left_n[i];
		temperature += weightage(box.box_id,id,grid_blocks)*grid_blocks[id].temperature;
	}
	//Add temperatures on the right neighbors.
	for (int i=0;i<box.num_right_n;i++){
		id = box.right_n[i];
		temperature += weightage(box.box_id,id,grid_blocks)*grid_blocks[id].temperature;
	}
	return temperature;
}

float weightage(int id1, int id2, vector<grid_block>& grid_blocks){
	float weight = 0;
	if((grid_blocks[id1].up_left_x <= grid_blocks[id2].up_left_x) && (grid_blocks[id2].up_left_x < (grid_blocks[id1].up_left_x + grid_blocks[id1].width))){
		if((grid_blocks[id2].up_left_x + grid_blocks[id2].width) < (grid_blocks[id1].up_left_x + grid_blocks[id1].width)){
			weight =  grid_blocks[id2].width;cout<<"debug 1."<<endl;
		}else{
			weight =  grid_blocks[id1].up_left_x + grid_blocks[id1].width - grid_blocks[id2].up_left_x;cout<<"debug 2."<<endl;
			cout<<grid_blocks[id1].up_left_x<<" "<<grid_blocks[id1].width<<" "<<grid_blocks[id2].up_left_x<<endl;
		}
	}else if((grid_blocks[id2].up_left_x <= grid_blocks[id1].up_left_x ) && (grid_blocks[id1].up_left_x < (grid_blocks[id2].up_left_x + grid_blocks[id2].width))){
		if((grid_blocks[id1].up_left_x + grid_blocks[id1].width) < (grid_blocks[id2].up_left_x + grid_blocks[id2].width)){
			weight = grid_blocks[id1].width;cout<<"debug 3."<<endl;
		}else{
			weight = grid_blocks[id2].up_left_x + grid_blocks[id2].width - grid_blocks[id1].up_left_x;cout<<"debug 4."<<endl;
		}
	}else if((grid_blocks[id1].up_left_y <= grid_blocks[id2].up_left_y ) && ( grid_blocks[id2].up_left_y < (grid_blocks[id1].up_left_y + grid_blocks[id1].height))){
		if((grid_blocks[id2].up_left_y + grid_blocks[id2].height) < (grid_blocks[id1].up_left_y + grid_blocks[id1].height)){
			weight = grid_blocks[id2].height;
		}else{
			weight = grid_blocks[id1].up_left_y + grid_blocks[id1].height - grid_blocks[id2].up_left_y;
		}
	}else if((grid_blocks[id2].up_left_y <= grid_blocks[id1].up_left_y ) && (grid_blocks[id1].up_left_y < (grid_blocks[id2].up_left_y + grid_blocks[id2].height))){
		if((grid_blocks[id1].up_left_y + grid_blocks[id1].height) < (grid_blocks[id2].up_left_y + grid_blocks[id2].height)){
			weight = grid_blocks[id1].height;
		}else{
			weight = grid_blocks[id2].up_left_y + grid_blocks[id2].height - grid_blocks[id1].up_left_y;
		}
	}
	return weight;
}

float temperature_difference(int id1,vector<grid_block>& grid_blocks){
	float diff;
	diff = 
}

void compute_effective_perimeter(vector<grid_block>& grid_blocks){
	int id;
	for(int i=0;i<grid_blocks.size();i++){
		int perimeter = 0;
		for (int j=0;j<grid_blocks[i].num_top_n;j++){
			id = grid_blocks[i].top_n[j];
			perimeter += weightage(grid_blocks[i].box_id,id,grid_blocks);
		}
		//Add temperatures on the bottom neighbors.
		for (int j=0;j<grid_blocks[i].num_bottom_n;j++){
			id = grid_blocks[i].bottom_n[j];
			perimeter += weightage(grid_blocks[i].box_id,id,grid_blocks);
		}
		//Add temperatures on the left neighbors.
		for (int j=0;j<grid_blocks[i].num_left_n;j++){
			id = grid_blocks[i].left_n[j];
			perimeter += weightage(grid_blocks[i].box_id,id,grid_blocks);
		}
		//Add temperatures on the right neighbors.
		for (int j=0;j<grid_blocks[i].num_right_n;j++){
			id = grid_blocks[i].right_n[j];
			perimeter += weightage(grid_blocks[i].box_id,id,grid_blocks);
		}
		//
		grid_blocks[i].perimeter = perimeter;
	}
}
