#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <numeric>
#include <chrono>
#pragma GCC optimize(3, "Ofast", "inline") 

using namespace std;
 
//线程要做的事情就写在这个线程函数中
void GetSumT(vector<int>::iterator first,vector<int>::iterator last,int &result) //头两个形参指定要累加的元素范围，第三个形参则是累加的初值。
{
    result = accumulate(first,last,0); //调用C++标准库算法
}

void dotProduct(int startp, int endp, float* v1, float* v2, long double &result){

    for(int i = startp; i < endp; i++){
        result += v1[i] * v2[i];
    }
}



void tryInt(int a){
    cout << "a = " << a << endl;
}

void tryFloat(float *v1,float* v2,int len){
    //float* temp1 = new float;
    //float* temp2 = new float;
    //temp = v;
    //temp[0] = 2;
    float sum = 0;
    for(int i = 0; i<len;i++){
        sum += v1[i]*v2[i];
    }
    cout << sum <<endl;

    
    //cout << &temp[0] <<endl;
    //delete [] v1;
    //delete [] v2;
}

int main() //主线程
{
    /* try to pass a float * to a thread 
    float * v0= new float[2];
    v0[0] = 1;
    v0[1] = 2;
    float * v1 = new float[2];
    v1[0] = 1;
    v1[1] = 2;
    thread t1(tryFloat, std::ref(v0),v1,2);
    t1.join();
    cout << "outside v0[0] =  "<< v0[0] <<endl;
    thread t2(tryFloat, v1,v0,2);
    t2.join();
    cout << "outside v1[0] =  "<< v1[0] <<endl;
    delete [] v1;
    delete [] v0;
    */
    
    /* try to pass an int to a thread;
    thread first(tryInt,11);
    first.join();

    thread sec(tryInt,12);
    sec.join();
    */

/* try 5 thread */
    long double result1 =0;
    long double result2 =0;
    long double result3 =0;
    long double result4 =0;
    long double result5 =0;
   
    long long innum = 100000000;
    float* v1 = new float[innum+1];
    float* v2 = new float[innum+1];

    //cout << "here?" <<endl;
    v1[0]  = 0;
    v2[0] =0;
    for(int i=1;i<innum+1;i++)
    {
        v1[i] = 1;
        v2[i] = 1;
    }
    //cout << v1[1] << endl;

    //////简单粗暴的方法
    long double sum = 0;
    auto t1 = std::chrono::steady_clock::now(); 

    int i;
    for(i = 1; i < innum +1; i++){
        sum += v1[i]*v2[i];
    }
    cout << "sum:" << sum << "i:" << i<< endl;
    //exit(1);
    auto t2 = std::chrono::steady_clock::now(); 
    double period1 = std::chrono::duration<double, std::milli>(t2-t1).count();
    cout << "period1 costs "<< period1 << "ms" << endl;

    //////多线程的方法

    
    int start1 = innum/5;
    //cout << "start1 = " << start1 <<endl;
    int start2 = 2*innum/5;
     //cout << "start2 = " << start2 <<endl;
    int start3 = 3*innum/5;
    int start4 = 4*innum/5;
    int start5 = innum+1;


    auto t3 = std::chrono::steady_clock::now(); 
    
    thread first(dotProduct,1,start1,std::ref(v1),std::ref(v2),std::ref(result1));
    first.join(); //主线程要等待子线程执行完毕
    //cout << result1 << endl;

    thread second(dotProduct,start1,start2,std::ref(v1),std::ref(v2),std::ref(result2));
    second.join();
    //cout << result2 << endl;
    
    thread third(dotProduct,start2,start3,std::ref(v1),std::ref(v2),std::ref(result3));
    third.join();
    //cout << result3 << endl;

    thread forth(dotProduct,start3,start4,std::ref(v1),std::ref(v2),std::ref(result4));
    forth.join();
    //cout << result4 << endl;

    thread fifth(dotProduct,start4,start5,std::ref(v1),std::ref(v2),std::ref(result5));
    fifth.join();
    //cout << result5 << endl;   
    
   #if 0
   thread first(dotProduct,1,start1,std::ref(v1),std::ref(v2),std::ref(result1));
    
    cout << result1 << endl;

    thread second(dotProduct,start1,start2,std::ref(v1),std::ref(v2),std::ref(result2));
    
    cout << result2 << endl;
    
    thread third(dotProduct,start2,start3,std::ref(v1),std::ref(v2),std::ref(result3));
    
    cout << result3 << endl;

    thread forth(dotProduct,start3,start4,std::ref(v1),std::ref(v2),std::ref(result4));
    
    cout << result4 << endl;

    thread fifth(dotProduct,start4,start5,std::ref(v1),std::ref(v2),std::ref(result5));
    
    cout << result5 << endl; 

    first.join(); //主线程要等待子线程执行完毕
    second.join();
    third.join();
    forth.join();
    fifth.join();
#endif


   /*
   thread first(dotProduct,0,start1,ref(v1),ref(v2),std::ref(result1));
    first.join(); //主线程要等待子线程执行完毕
    cout << result1 << endl;

    thread second(dotProduct,start1,start2,ref(v1),ref(v2),std::ref(result2));
    second.join();
    cout << result2 << endl;
    
    thread third(dotProduct,start2,start3,ref(v1),ref(v2),std::ref(result3));
    third.join();
    cout << result3 << endl;

    thread forth(dotProduct,start3,start4,ref(v1),ref(v2),std::ref(result4));
    forth.join();
    cout << result4 << endl;

    thread fifth(dotProduct,start4,start5,ref(v1),ref(v2),std::ref(result5));
    fifth.join();
    cout << result5 << endl;   
    */

/*
    thread first(dotProduct,0,start1,v1,v2,std::ref(result1));
    first.join(); //主线程要等待子线程执行完毕
    cout << result1 << endl;
    

    thread second(dotProduct,start1,start2,v1,v2,std::ref(result2));
    second.join();
    cout << result2 << endl;
    
    thread third(dotProduct,start2,start3,v1,v2,std::ref(result3));
    third.join();
    cout << result3 << endl;

    thread forth(dotProduct,start3,start4,v1,v2,std::ref(result4));
    forth.join();
    cout << result4 << endl;

    thread fifth(dotProduct,start4,start5,v1,v2,std::ref(result5));
    fifth.join();
    cout << result5 << endl;

*/
    long double r = result1 + result2+result3+result4+result5;
    cout << r <<"= "<< result1 << "+" << result2 << "+" << result3 << "+" << result4 << "+" << result5  <<endl;

    auto t4 = std::chrono::steady_clock::now(); 
    double period2 = std::chrono::duration<double, std::milli>(t4-t3).count();
    cout << "period2 costs "<< period2 << "ms" << endl;

   
    
    
    delete [] v1;
    delete [] v2;
    //cout << "after delete" <<endl;
    
    

/*
    thread first(GetSumT,largeArrays.begin(),
        largeArrays.begin()+20000000,std::ref(result1)); //子线程1
    thread second(GetSumT,largeArrays.begin()+20000000,
        largeArrays.begin()+40000000,std::ref(result2)); //子线程2
    thread third(GetSumT,largeArrays.begin()+40000000,
        largeArrays.begin()+60000000,std::ref(result3)); //子线程3
    thread fouth(GetSumT,largeArrays.begin()+60000000,
        largeArrays.begin()+80000000,std::ref(result4)); //子线程4
    thread fifth(GetSumT,largeArrays.begin()+80000000,
        largeArrays.end(),std::ref(result5)); //子线程5
 
    first.join(); //主线程要等待子线程执行完毕
    second.join();
    third.join();
    fouth.join();
    fifth.join();
 
    int resultSum = result1+result2+result3+result4+result5; //汇总各个子线程的结果
    cout << resultSum << endl;
    */
    return 0;
}