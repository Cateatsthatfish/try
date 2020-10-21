#include <iostream>
using namespace std;
int main(){
    float* v1;
    float * v1 = new float[3];
    v1[0] = 3;
    cout << v1[0] <<endl;
    delete [] v1;
    return 0;
}