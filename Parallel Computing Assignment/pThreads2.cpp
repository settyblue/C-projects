#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

int sum = 0;
void *add(void *);
pthread_mutex_t mut;

int main ()
{
   pthread_t threads[10];
   int num_threads = 5;
   long count = 3;
   
   for(int i=0; i < num_threads; i++ ){
      	//for each thread we are doing something here.
      	cout << "main() : creating thread, " << i << endl;
      	pthread_create(&threads[i], NULL ,add,(void *)count);
   }
   
   for(int i=0; i < num_threads; i++ ){
   		pthread_join(threads[i], NULL );
   }
   
   cout<<sum<<endl;
   return 0;
   
}

void *add (void *count){
	long num;
	num = *((long*) (&count));
	
	pthread_mutex_lock(&mut);
	
	for(long x=1; x <= num; x++){
		sum += x;
		cout<<sum<<"\t"<<x<<endl;
	}
	
	pthread_mutex_unlock(&mut);
}
