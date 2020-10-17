#include <cstdlib>
#include <ctime>
#include <climits>
#include <float.h>
#include <iostream>

using namespace std;
const int a = 1;
const int b = 2;

int main(){
    srand((int)time(0));
    float r1 = a + rand()%(b-a) + rand()/double(RAND_MAX);
    float r2 = a + rand()%(b-a) + rand()/double(RAND_MAX);
    cout << r1 << " " << r2 <<endl;
    return 0;
}