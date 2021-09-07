#include <omp.h>
#include <stdio.h>
#define SIZE 3000  
#define NUM_THREADS 8

using namespace std;

int main()
{
	
	
	int** matrix1 = new int*[SIZE];
	int** matrix2 = new int*[SIZE];
	int** res = new int*[SIZE];
	
	double time = omp_get_wtime();
	
	for (int i = 0; i < SIZE; i++) {
        matrix1[i] = new int[SIZE];
    	matrix2[i] = new int[SIZE];
    	res[i] = new int[SIZE];
	}
	
	omp_set_num_threads(NUM_THREADS);
	
	#pragma omp for schedule(dynamic, 500) nowait
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			matrix1[i][j] = 2;
			matrix2[i][j] = 3;
		}
	}
	
	// using static schedule with different chunks
	#pragma omp for schedule(dynamic, 500)
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			res[i][j] = matrix1[i][j]+matrix2[i][j];
		}
	}
	
	
	for(int i=0; i<SIZE; i++)
		for(int j=0; j<SIZE; j++)
			printf(" %d ", res[i][j]);
	
	printf("Calculated in %f time\n", omp_get_wtime()-time);

	delete[] matrix1;
	delete[] matrix2;
	delete[] res;
		
	return 0;
}
