#include <iostream>
#include<ctime>
using namespace std;
#define MAX 4
#define MAX_THREAD 4

int matA[MAX][MAX];

int matB[MAX][MAX];

int matC[MAX][MAX];

int step_i = 0;
 

void* multi(void* arg)
{
    int i = step_i++; 

    for (int j = 0; j < MAX; j++) 

      for (int k = 0; k < MAX; k++) 

        matC[i][j] += matA[i][k] * matB[k][j];
}

int usingthreads()
{
clock_t start_time,end_time;
start_time=clock();
    for (int i = 0; i < MAX; i++) {

        for (int j = 0; j < MAX; j++) {

          matA[i][j]=rand()%10;

           matB[i][j]=rand()%10;

        }

    }

    cout << endl

         << "Matrix A" << endl;

    for (int i = 0; i < MAX; i++) {

        for (int j = 0; j < MAX; j++) 

            cout << matA[i][j] << " ";

        cout << endl;

    }

    cout << endl

         << "Matrix B" << endl;

    for (int i = 0; i < MAX; i++) {

        for (int j = 0; j < MAX; j++) 

            cout << matB[i][j] << " ";        

        cout << endl;

    }

    pthread_t threads[MAX_THREAD];
 

    for (int i = 0; i < MAX_THREAD; i++) {

        int* p;

        pthread_create(&threads[i], NULL, multi, (void*)(p));

    }

    for (int i = 0; i < MAX_THREAD; i++) 

        pthread_join(threads[i], NULL);    

    cout << endl

         << "Multiplication of A and B" << endl;

    for (int i = 0; i < MAX; i++) {

        for (int j = 0; j < MAX; j++) 

            cout << matC[i][j] << " ";        

        cout << endl;
    }
        end_time=clock();
cout<<"\nthreads time="<<(end_time-start_time)/(double)CLOCKS_PER_SEC<<endl<<endl;
    return 0;
}
int usingprocess()
{
	int mul[10][10],r,c,i,j,k;    
clock_t start_time,end_time;
start_time=clock();

cout<<"multiply of the matrixA and B=\n";    
for(i=0;i<MAX;i++)    
{    
for(j=0;j<MAX;j++)    
{    
mul[i][j]=0;    
for(k=0;k<MAX;k++)    
{    
mul[i][j]+=matA[i][k]*matB[k][j];    
}    
}    
}      
for(i=0;i<MAX;i++)    
{    
for(j=0;j<MAX;j++)    
{    
cout<<mul[i][j]<<" ";    
}    
cout<<"\n";    
}
end_time=clock();
cout<<"\nprocess time="<<(end_time-start_time)/(double)CLOCKS_PER_SEC<<endl; 
return 0;  
}
int main()
{
	usingthreads();
	usingprocess();
	return 0;
}