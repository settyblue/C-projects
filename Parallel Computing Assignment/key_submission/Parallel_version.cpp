#include <iostream>
#include <stdlib.h>
#include<vector>
#include <map>
#include<string>
using namespace std;
#include <fstream>
#include <sstream>
#include <iterator>
#include <numeric>
#include <time.h>
#define AFFECT_RATE 0.1
#define EPSILON 0.1
#include <pthread.h>
#define NUM_THREADS 8

//Global data
int num_boxes,num_rows,num_cols;
clock_t start,end;
float max_dsv,min_dsv;
float calculateNewDsv(int i);
float* new_dsv=0;

void parseData();
void *runner (void*);
//Box Definition :
class box{
public:
   int box_id;
   int upper_left_y;
   int upper_left_x;
   int height;
   int width;
   int num_top_neighbors;
   vector<int> top_neighbor_ids;
   int num_bottom_neighbors;
   vector<int> bottom_neighbor_ids;
   int num_left_neighbors;
   vector<int> left_neighbor_ids;
   int num_right_neighbors;
   vector<int> right_neighbor_ids;
   float box_dsv;	
};
vector<box> box_data;

//Split function:
vector<string> split(string str) {
  std::istringstream buffer(str);
    std::vector<std::string> ret;

    std::copy(std::istream_iterator<std::string>(buffer), 
              std::istream_iterator<std::string>(),
              std::back_inserter(ret));
    return ret;
}
//main function
int main()
{
	parseData();
	vector<box>::iterator it;
	new_dsv = (float*)malloc(sizeof(float) * num_boxes);
    long int num_conv_iter=0;
	start=clock();
		do{
		pthread_t threads[NUM_THREADS];
   		int num_threads = NUM_THREADS;
		num_conv_iter++;
		max_dsv=INT_MIN;
		min_dsv=INT_MAX;
		int i=0;
		int quo=box_data.size()/num_threads;
		int rem=box_data.size()%num_threads;
		int k;
  		for( k=0;k<box_data.size()-rem;)
   		{
   		for(int i=0;i<num_threads;i++)
   		{
      		pthread_create(&threads[i], NULL ,runner,(void *)(k+i));
  		}  	
  		for(int i=0; i < num_threads; i++ ){
   			pthread_join(threads[i], NULL );
  		}
  			k=k+num_threads;
  		} 
  		for(int i=0;i<rem;i++)
   		{
      		pthread_create(&threads[i], NULL ,runner,(void *)(k+i));
  		}  	
  		for(int i=0; i < rem; i++ ){
   			pthread_join(threads[i], NULL );
  		}
		  	
  		max_dsv = INT_MIN;
		min_dsv = INT_MAX;
		i=0;
		for(it=box_data.begin() ; it < box_data.end(); it++,i++)
		{
		float temp1 = (*it).box_dsv;
		if(temp1>new_dsv[i])
		(*it).box_dsv -= 0.1*(temp1-new_dsv[i]);
		else
		(*it).box_dsv += 0.1*(new_dsv[i]-temp1);
		max_dsv = std::max(max_dsv,(*it).box_dsv);
		min_dsv = std::min(min_dsv,(*it).box_dsv);
		}
	}while(max_dsv-min_dsv>0.1*max_dsv);
	end=clock();
	cout<<"Number of convergence loop iterations is "<< num_conv_iter<<"\n";
	cout<<"Final Maximum DSV: "<<max_dsv<<"\n"<<"Final Minimum DSV: "<<min_dsv<<"\n";
	cout<<"Time taken to converge: "<<end-start;
	return 0;
}
// calculate the temporary temperature values
float calculateNewDsv(int id)
{
		float temp;
		float weighted_sum =0;
		int surround_perimeter =0;
		vector<int>::iterator top_it;
		vector<int>::iterator bottom_it;
		vector<int>::iterator right_it;
		vector<int>::iterator left_it;
		int overlap =0;
		box current = box_data[id];
		for(top_it =current.top_neighbor_ids.begin();top_it<current.top_neighbor_ids.end();top_it++){
			if(box_data[(*top_it)].upper_left_x<current.upper_left_x && box_data[(*top_it)].upper_left_x+box_data[(*top_it)].width<current.upper_left_x+current.width)
				overlap = box_data[(*top_it)].upper_left_x+box_data[(*top_it)].width-current.upper_left_x;
			else if (box_data[(*top_it)].upper_left_x>current.upper_left_x && box_data[(*top_it)].upper_left_x+box_data[(*top_it)].width>current.upper_left_x+current.width)
				overlap = current.upper_left_x+current.width-box_data[(*top_it)].upper_left_x;
			else if (box_data[(*top_it)].upper_left_x<current.upper_left_x && box_data[(*top_it)].upper_left_x+box_data[(*top_it)].width>current.upper_left_x+current.width)
				overlap = current.width;
			else
			    overlap = box_data[(*top_it)].width;
			weighted_sum += box_data[(*top_it)].box_dsv*overlap;
			surround_perimeter += overlap; 	
		}
		for(bottom_it =current.bottom_neighbor_ids.begin();bottom_it<current.bottom_neighbor_ids.end();bottom_it++){
			if(box_data[(*bottom_it)].upper_left_x<current.upper_left_x && box_data[(*bottom_it)].upper_left_x+box_data[(*bottom_it)].width<current.upper_left_x+current.width)
				overlap = box_data[(*bottom_it)].upper_left_x+box_data[(*bottom_it)].width-current.upper_left_x;
			else if (box_data[(*bottom_it)].upper_left_x>current.upper_left_x && box_data[(*bottom_it)].upper_left_x+box_data[(*bottom_it)].width>current.upper_left_x+current.width)
				overlap = current.upper_left_x+current.width-box_data[(*bottom_it)].upper_left_x;
			else if (box_data[(*bottom_it)].upper_left_x<current.upper_left_x && box_data[(*bottom_it)].upper_left_x+box_data[(*bottom_it)].width>current.upper_left_x+current.width)
				overlap = current.width;
			else
			    overlap = box_data[(*bottom_it)].width;
			weighted_sum += box_data[(*bottom_it)].box_dsv*overlap;
			surround_perimeter += overlap; 
		}
		for(left_it =current.left_neighbor_ids.begin();left_it<current.left_neighbor_ids.end();left_it++){
			if(box_data[(*left_it)].upper_left_y<current.upper_left_y && box_data[(*left_it)].upper_left_y+box_data[(*left_it)].height<current.upper_left_y+current.height)
				overlap = box_data[(*left_it)].upper_left_y+box_data[(*left_it)].height-current.upper_left_y;
			else if (box_data[(*left_it)].upper_left_y>current.upper_left_y && box_data[(*left_it)].upper_left_y+box_data[(*left_it)].height>current.upper_left_y+current.height)
				overlap = current.upper_left_y+current.height-box_data[(*left_it)].upper_left_y;
			else if (box_data[(*left_it)].upper_left_y<current.upper_left_y && box_data[(*left_it)].upper_left_y+box_data[(*left_it)].height>current.upper_left_y+current.height)
				overlap = current.height;
			else
			    overlap = box_data[(*left_it)].height;
			weighted_sum += box_data[(*left_it)].box_dsv*overlap;
			surround_perimeter += overlap; 
		}
		for(right_it =current.right_neighbor_ids.begin();right_it<current.right_neighbor_ids.end();right_it++){
			if(box_data[(*right_it)].upper_left_y<current.upper_left_y && box_data[(*right_it)].upper_left_y+box_data[(*right_it)].height<current.upper_left_y+current.height)
				overlap = box_data[(*right_it)].upper_left_y+box_data[(*right_it)].height-current.upper_left_y;
			else if (box_data[(*right_it)].upper_left_y>current.upper_left_y && box_data[(*right_it)].upper_left_y+box_data[(*right_it)].height>current.upper_left_y+current.height)
				overlap = current.upper_left_y+current.height-box_data[(*right_it)].upper_left_y;
			else if (box_data[(*right_it)].upper_left_y<current.upper_left_y && box_data[(*right_it)].upper_left_y+box_data[(*right_it)].height>current.upper_left_y+current.height)
				overlap = current.height;
			else
			    overlap = box_data[(*right_it)].height;
			weighted_sum += box_data[(*right_it)].box_dsv*overlap;
			surround_perimeter += overlap; 
		}
		temp = (float)weighted_sum/surround_perimeter;
		return temp;
}

//Runner function
void *runner (void* i){
	int k = *((int*) (&i));
	float diff = calculateNewDsv(k);
	new_dsv[k] = diff;
}

//Parsing the data
void parseData()
{
  string line;
  ifstream infile("C:\\Users\\chkee\\Downloads\\testgrid_1");  
  infile >> num_boxes>> num_rows >> num_cols;
  getline(infile, line);
   for(int i=0;i<num_boxes;i++){
    	box inputBox;
    do{
    	getline(infile, line);
	}while(line.empty() || line == "\t");
    inputBox.box_id = atoi(line.c_str());
    getline(infile, line);
    vector<string> sep = split(line);
    inputBox.upper_left_y = atoi(sep[0].c_str());
    inputBox.upper_left_x = atoi(sep[1].c_str());
    inputBox.height = atoi(sep[2].c_str());
    inputBox.width = atoi(sep[3].c_str());
    getline(infile, line);
    vector<string> sep1 = split(line);
    inputBox.num_top_neighbors = atoi(sep1[0].c_str());
    for(int i=0;i<atoi(sep1[0].c_str());i++){
    	inputBox.top_neighbor_ids.push_back(atoi(sep1[i+1].c_str()));
	}
    getline(infile, line);
    vector<string> sep2 = split(line);
    inputBox.num_bottom_neighbors = atoi(sep2[0].c_str());
    for(int i=0;i<atoi(sep2[0].c_str());i++){
    	inputBox.bottom_neighbor_ids.push_back(atoi(sep2[i+1].c_str()));
	}
    getline(infile, line);
    vector<string> sep4 = split(line);
    inputBox.num_left_neighbors = atoi(sep4[0].c_str());
    for(int i=0;i<atoi(sep4[0].c_str());i++){
    	inputBox.left_neighbor_ids.push_back(atoi(sep4[i+1].c_str()));
	}
    getline(infile, line);
	vector<string> sep3 = split(line);
    inputBox.num_right_neighbors = atoi(sep3[0].c_str());
    for(int i=0;i<atoi(sep3[0].c_str());i++){
    	inputBox.right_neighbor_ids.push_back(atoi(sep3[i+1].c_str()));
	}
    getline(infile, line);
    inputBox.box_dsv = (float)atoi(line.c_str());   
    box_data.push_back(inputBox);
	}
}
