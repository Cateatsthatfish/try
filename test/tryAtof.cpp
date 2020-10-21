#include <iostream>
using namespace std;
int main(){
	//string num = "123E-20";
	string num = "-2.3e-2";
	float afnum = atof(num.c_str());
	cout << afnum <<endl;
	
return 0;

}