
///// this is a program to product random float numbers

#include<Windows.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <float.h>
#include <string>
#pragma GCC optimize(3, "Ofast", "inline") 

const int a = INT_MIN/2;
const int b = INT_MAX/2;
using namespace std;

int main()
{
    fstream randomNum1("v1_T20M.txt",ios::in | ios::out|ios::trunc);
    //v1中生成随机数
    if(randomNum1.is_open())
    {
        cout << "file v1 is open."<<endl;
    //读入随机数
         srand((int)time(0));  // 产生随机种子  把0换成NULL也行
    for (int i = 0; i < 20000000; i++) 
    {
        
        //float r = a + rand()%(b-a) + rand()/double(RAND_MAX);
        float r1 = rand()/double(RAND_MAX);
        randomNum1 << r1 <<",";

    }

        randomNum1.clear();
        randomNum1.seekg(0);

    }else{
        cout <<"something in v1 is wrong." <<endl;
    }
    //v2中生成随机数
    fstream randomNum2("v2_T20M.txt",ios::in | ios::out|ios::trunc);
    if(randomNum2.is_open())
    {
        cout << "file v2 is open."<<endl;
    //读入随机数

    for (int i = 0; i < 20000000; i++) 
    {
        
        //float r = a + rand()%(b-a) + rand()/double(RAND_MAX);
        float r2 = rand()/double(RAND_MAX);
        randomNum2 << r2 <<",";
 
    }

        randomNum2.clear();
        randomNum2.seekg(0);

    }else{
        cout <<"something in v2 is wrong." <<endl;
    }
    
    return 0;
}