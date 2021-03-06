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
#define AFFECT_RATE 0.0001
#define EPSILON 0.02
#include <pthread.h>
#define NUM_THREADS 10

float* new_dsvs;
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
std::map<int, box> box_id_map;


//Split function:
vector<string> split(string str) {
  std::istringstream buffer(str);
    std::vector<std::string> ret;

    std::copy(std::istream_iterator<std::string>(buffer), 
              std::istream_iterator<std::string>(),
              std::back_inserter(ret));
    return ret;
}
struct arguments{
		box* it;
	    int i;
};
void* runner(void * arg)
{
		cout << "entered function"<<"\n";
		arguments *a = (arguments *)arg;
		box *it=a->it;
		int i=a->i;
		float weighted_sum =0;
		int surround_perimeter =0;
		vector<int>::iterator top_it;
		vector<int>::iterator bottom_it;
		vector<int>::iterator right_it;
		vector<int>::iterator left_it;
		int overlap =0;
		
		//iterating over top neighbors
		for(top_it =(*it).top_neighbor_ids.begin();top_it<(*it).top_neighbor_ids.end();top_it++){
			//cout<<(*top_it)<<"DEBUGGING\n";
			if(box_id_map[(*top_it)].upper_left_x<(*it).upper_left_x && box_id_map[(*top_it)].upper_left_x+box_id_map[(*top_it)].width<(*it).upper_left_x+(*it).width)
				overlap = box_id_map[(*top_it)].upper_left_x+box_id_map[(*top_it)].width-(*it).upper_left_x;
			else if (box_id_map[(*top_it)].upper_left_x>(*it).upper_left_x && box_id_map[(*top_it)].upper_left_x+box_id_map[(*top_it)].width>(*it).upper_left_x+(*it).width)
				overlap = (*it).upper_left_x+(*it).width-box_id_map[(*top_it)].upper_left_x;
			else if (box_id_map[(*top_it)].upper_left_x<(*it).upper_left_x && box_id_map[(*top_it)].upper_left_x+box_id_map[(*top_it)].width>(*it).upper_left_x+(*it).width)
				overlap = (*it).width;
			else
			    overlap = box_id_map[(*top_it)].width;
			weighted_sum += box_id_map[(*top_it)].box_dsv*overlap;
			surround_perimeter += overlap; 
			
		}
		for(bottom_it =(*it).bottom_neighbor_ids.begin();bottom_it<(*it).bottom_neighbor_ids.end();bottom_it++){
			if(box_id_map[(*bottom_it)].upper_left_x<(*it).upper_left_x && box_id_map[(*bottom_it)].upper_left_x+box_id_map[(*bottom_it)].width<(*it).upper_left_x+(*it).width)
				overlap = box_id_map[(*bottom_it)].upper_left_x+box_id_map[(*bottom_it)].width-(*it).upper_left_x;
			else if (box_id_map[(*bottom_it)].upper_left_x>(*it).upper_left_x && box_id_map[(*bottom_it)].upper_left_x+box_id_map[(*bottom_it)].width>(*it).upper_left_x+(*it).width)
				overlap = (*it).upper_left_x+(*it).width-box_id_map[(*bottom_it)].upper_left_x;
			else if (box_id_map[(*bottom_it)].upper_left_x<(*it).upper_left_x && box_id_map[(*bottom_it)].upper_left_x+box_id_map[(*bottom_it)].width>(*it).upper_left_x+(*it).width)
				overlap = (*it).width;
			else
			    overlap = box_id_map[(*bottom_it)].width;
			weighted_sum += box_id_map[(*bottom_it)].box_dsv*overlap;
			surround_perimeter += overlap; 
		}
		for(left_it =(*it).left_neighbor_ids.begin();left_it<(*it).left_neighbor_ids.end();left_it++){
			if(box_id_map[(*left_it)].upper_left_y<(*it).upper_left_y && box_id_map[(*left_it)].upper_left_y+box_id_map[(*left_it)].height<(*it).upper_left_y+(*it).height)
				overlap = box_id_map[(*left_it)].upper_left_y+box_id_map[(*left_it)].height-(*it).upper_left_y;
			else if (box_id_map[(*left_it)].upper_left_y>(*it).upper_left_y && box_id_map[(*left_it)].upper_left_y+box_id_map[(*left_it)].height>(*it).upper_left_y+(*it).height)
				overlap = (*it).upper_left_y+(*it).height-box_id_map[(*left_it)].upper_left_y;
			else if (box_id_map[(*left_it)].upper_left_y<(*it).upper_left_y && box_id_map[(*left_it)].upper_left_y+box_id_map[(*left_it)].height>(*it).upper_left_y+(*it).height)
				overlap = (*it).height;
			else
			    overlap = box_id_map[(*left_it)].height;
			weighted_sum += box_id_map[(*left_it)].box_dsv*overlap;
			surround_perimeter += overlap; 
		}
		for(right_it =(*it).right_neighbor_ids.begin();right_it<(*it).right_neighbor_ids.end();right_it++){
			if(box_id_map[(*right_it)].upper_left_y<(*it).upper_left_y && box_id_map[(*right_it)].upper_left_y+box_id_map[(*right_it)].height<(*it).upper_left_y+(*it).height)
				overlap = box_id_map[(*right_it)].upper_left_y+box_id_map[(*right_it)].height-(*it).upper_left_y;
			else if (box_id_map[(*right_it)].upper_left_y>(*it).upper_left_y && box_id_map[(*right_it)].upper_left_y+box_id_map[(*right_it)].height>(*it).upper_left_y+(*it).height)
				overlap = (*it).upper_left_y+(*it).height-box_id_map[(*right_it)].upper_left_y;
			else if (box_id_map[(*right_it)].upper_left_y<(*it).upper_left_y && box_id_map[(*right_it)].upper_left_y+box_id_map[(*right_it)].height>(*it).upper_left_y+(*it).height)
				overlap = (*it).height;
			else
			    overlap = box_id_map[(*right_it)].height;
			weighted_sum += box_id_map[(*right_it)].box_dsv*overlap;
			surround_perimeter += overlap; 
		}
		new_dsvs[i] = (float)weighted_sum/surround_perimeter;
}

int main()
{  
  int num_boxes,num_rows,num_cols;
  std::map<int, box> box_id_map;
  vector<box> box_data;
  string line;
  clock_t start,end;
  ifstream infile("C:\\Users\\chkee\\Downloads\\testgrid_2");  
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
    //creating vector of boxes.
    cout << "creating vector of boxes:"<<"\n";
    box_data.push_back(inputBox);
    box_id_map[inputBox.box_id] = inputBox;
	}
	//By the end of this box_data has all the data of all the boxes:
	///////////////////////////////////////////////////////////////////////////////////
	//After hashmp and vector of boxes are created while parsing the textfile.
	vector<box>::iterator it;
	float new_dsvs[num_boxes];
	float max_dsv;
	float min_dsv;
	int num_conv_iter =0;
	start=clock();
	do{
		max_dsv=INT_MIN;
		min_dsv=INT_MAX;
		num_conv_iter++;
		//cout<<num_conv_iter<<"NumConv\n";
	//finding new dsvs of each of the boxes and storing them in a array new_dsvs;
		//
		int k=0;
		pthread_t threads[NUM_THREADS];
		for(it=box_data.begin() ; it < box_data.end(); it++,k++){
			struct arguments a;
			box it1=*it;
			a.it=&it1;
			a.i=k; 
      		pthread_create(&threads[k], NULL ,runner,(void *)&a);
      		cout<<"thread created";
  		}
  		for(int i=0; i < 9; i++ ){
   			pthread_join(threads[i], NULL );
  		}
	
	//updating the dsvs
	int i=0;
	for(it=box_data.begin() ; it < box_data.end(); it++,i++) {
		float temp = (*it).box_dsv;
		if(temp>new_dsvs[i])
		(*it).box_dsv -= 0.1*(temp-new_dsvs[i]);
		else
		(*it).box_dsv += 0.1*(new_dsvs[i]-temp);
		max_dsv = std::max(max_dsv,(*it).box_dsv);
		min_dsv = std::min(min_dsv,(*it).box_dsv);
		box dummy = box_id_map[(*it).box_id] ;
		dummy.box_dsv = (*it).box_dsv;
		box_id_map[(*it).box_id] = dummy;
		cout<<"For box: "<<i<<" PREVIOUS DSV: "<<temp<<" UPDATED DSV: "<<new_dsvs[i]<<"\n";
	}
	cout<<"************************************************************\n";
	}while(max_dsv-min_dsv>0.1*max_dsv);
	end = clock();
	cout<<"Time taken for convergence is  "<<end-start<<"\n";
	cout<<"Number of convergence loop iterations is "<< num_conv_iter<<"\n";
	cout<<"Final Maximum DSV: "<<max_dsv<<"\n"<<"Final Minimum DSV: "<<min_dsv;	
}


