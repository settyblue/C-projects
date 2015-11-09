
#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <omp.h>
#define DELTA 0.005


using namespace std;

int main(){
	omp_set_num_threads(5);
	int actualThreadCount = 0;
	#pragma omp parallel
        {
            int threadId = omp_get_thread_num();
            actualThreadCount = omp_get_num_threads();
            cout<<threadId<<"hello World\n";
        }
        cout<<"number of threads :"<<actualThreadCount;
    return 0;
}
