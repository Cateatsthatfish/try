#include <cstdlib>
#include <ctime>
#include <climits>
#include <float.h>
#include <iostream>

using namespace std;
const int a = 1;
const int b = 2;

int main(){
    float * v1 = new float;
    float * v2 = new float;
    //float r1,r2;

    srand((int)time(0));
    for (int i = 0; i < 2; i++) 
    {
         v1[i] = a + rand()%(b-a) + rand()/double(RAND_MAX);
         v2[i] = a + rand()%(b-a) + rand()/double(RAND_MAX);
    }
    for (int i = 0; i < 2; i++) 
    {
         cout << v1[i] << " ";
         cout << v2[i] ;
         cout << endl;
    }
    delete [] v1;
    delete [] v2;
     
    //cout << r1 << " " << r2 <<endl;
    return 0;
}