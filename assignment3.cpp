
#include<iostream>
#include<string>
#include<cstring>
#include<Windows.h>
#include <fstream>
#include <thread>
#include <numeric>
#pragma GCC optimize(3, "Ofast", "inline") //O3优化，由张睿豪提供

using namespace std;

//////需要用到的函数

int hint(); /////给出提示，返回输入模式
///1 退出的实现
///2 判断异常的输入->返回为零
//（1）除了0-4之外的字符（2）tab，空格，回车（3）复制的string?


float dot_product(float*, float*,int); // 计算向量 //这里需要改成long double计算大数值
bool isFloat(string); //判断输入的数有没有除了float和，之外的东西
string blank(string); // 去除空格
float* tofloat(string); // 提取字符串中的float
///用于多线程计算
void dotProduct(int startp, int endp, float* v1, float* v2, float &result){

    for(int i = startp; i < endp; i++){
        result += v1[i] * v2[i];
    }
}



int main(){
    string in1, in2; /////////用来存输入
    int mod = hint();
    //退出程序
    if(mod == 0){ exit(0);} ////////////?确认用0是否合适
    //terminal 读入
    if(mod == 1) 
    { 
    cout << "please enter vector 1:" ;
    getline(cin,in1);
    cout << "please enter vector 2:" ;
    getline(cin,in2);
    }
    //txt 读入
    if(mod == 2)
    {
    cout << "please put the vectors into 'v1.txt' and 'v2.txt'separately" <<endl;
    ifstream myfile1("v1.txt");
    if(myfile1.is_open()){
        cout << "read from the file1" <<endl;
        getline(myfile1,in1);
        //cout <<frofile <<endl;
        myfile1.close();
    }
    else{
        cout << "failed to open the file1";
    }
    //cout << in1 <<endl;

    ifstream myfile2("v2.txt");
    if(myfile2.is_open()){
        cout << "read from the file2" <<endl;
        getline(myfile2,in2);
        //cout << <<endl;
        myfile2.close();
    }
    else{
        cout << "failed to open the file2";
    }   
    
    }
    //binary 读入
    if(mod == 3)
    {
        cout << "please put the vectors into two binary file 'v1.txt' and 'v2.txt'separately" <<endl;
    }
    //直接在程序中生成
    if(mod == 4){}
    /////////////mode1 terminal 输入


    

    //cout << in2 << endl;

    // 合理性验证
    //cout << "here?" <<endl;
    if(isFloat(in1) && isFloat(in2)){
    //cout << "here" <<endl;
    // 去除空格
    string str1, str2;
    str1 = blank(in1);
    str2 = blank(in2);
    
    // string -> float*
    //分割标志：‘，’
    float* v1 = tofloat(str1);
    float* v2 = tofloat(str2);

    //cout << v1[0] <<endl;
    //cout << v2[0] <<endl;


    //计算
    if(v1[0]==v2[0]){
    //测量时间,代码来自张睿豪
    double time = 0;
    double counts = 0;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime); 

    //计算
    //float result = dot_product(v1,v2,v1[0]);
    //多线程用于计算
    //五个值用来分别储存
    float result1 =0;
    float result2 =0;
    float result3 =0;
    float result4 =0;
    float result5 =0;
   

    int innum = v1[0];

    int start1 = innum/5;
    int start2 = 2*innum/5;
    int start3 = 3*innum/5;
    int start4 = 4*innum/5;
    int start5 = innum+1;

    /*
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
    */
      thread first(dotProduct,1,start1,std::ref(v1),std::ref(v2),std::ref(result1));
    
    //cout << result1 << endl;

    thread second(dotProduct,start1,start2,std::ref(v1),std::ref(v2),std::ref(result2));
    
    //cout << result2 << endl;
    
    thread third(dotProduct,start2,start3,std::ref(v1),std::ref(v2),std::ref(result3));
    
    //cout << result3 << endl;

    thread forth(dotProduct,start3,start4,std::ref(v1),std::ref(v2),std::ref(result4));
    
    //cout << result4 << endl;

    thread fifth(dotProduct,start4,start5,std::ref(v1),std::ref(v2),std::ref(result5));
    
    //cout << result5 << endl; 

    first.join(); //主线程要等待子线程执行完毕
    second.join();
    third.join();
    forth.join();
    fifth.join();

    float result = result1 + result2+result3+result4+result5;
   //cout << r <<endl;
    


    QueryPerformanceCounter(&nEndTime);                                                //停止计时
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s
    cout << result << endl;
    cout << "(time: " << time * 1000 << "ms)" << endl;
    }else{
        cout << "the two vectors do not have the same length" <<endl;
    }


    delete [] v1;
    delete [] v2;
    }
    else{
        cout << "invalid inputs!" << endl; 
    }

    return 0;
}

int hint(){
    cout << "hint: please enter the two vectors whose elements are separated by ',':" <<endl; //提示输入两个向量
    cout << "for example: 1,2,3……" <<endl;
    cout << "there are four models to enter" << endl;
    cout << "press '1' : enter in terminal " <<endl;
    cout << "press '2' : enter in '.txt'file " <<endl;
    cout << "press '3' : enter in binary file" <<endl;
    cout << "press '4' : enter an integer to generate two random vectors automatically: " <<endl;
    cout << "press '0' : exit" << endl; ////////////////////怎么退出来着？

    /////////////////////////选择模型
    int model = cin.get();/////////////////////////////////考虑输入异常情况（数值不对，空格回车tab）
    /*switch(model){
        case 1: 
    }*/
    return model;
}
////// 提取float
float* tofloat(string str)
{
    int len = str.length();
    if(str[len-1]!=','){
    str = str + ","; }// str = "1,2,3,"
    int num = 0;
     for(int i = 0; i < str.length();i++){
      if(str[i]==','){
          num += 1;
      }
    }
    // int num = 3

    float* v = new float[num+1]; //得到的一串浮点数
    // 第一位是浮点数的个数
    //其他是float
    v[0] = num;

    
    int pre = 0 ;  //记录前一个逗号的位置
    int end ;  //记录后一个逗号的位置
    int index = 1;
    for(int i = 0; i < str.length();i++)
    {
        if(str[i]==','){
            end = i;
            //cout << "end =" << end << endl;
            string temp(str,pre,end-pre);
            //cout << "temp = " << temp << endl;
            v[index] = atof(temp.c_str());
            index++;
            pre = i+1;
        }
    }

    return v;
    delete[] v;
    
}

/////////去除空格，思路来源张睿豪assignment2
string blank(string in)
{
    string nblank = "";
    for(int i = 0; i < in.length();i++){
        if(in[i]!=' '){
            nblank += in[i];
        }
    }
    return nblank;
}
///////点乘运算
float dot_product(float* v1, float*v2, int length){

    float dp = 0;
    //cout << "length = " << length << endl;
    for(int i = 1; i< length+1;i++) //把第一个去掉
    {
        //cout << "v1["<<i<<"]=" << v1[i] <<endl;
        //cout << "v2["<<i<<"]=" << v2[i] <<endl;
        dp += v1[i]*v2[i];
        //cout << "dp"<<i<<"="<<dp <<endl;
    }
    return dp;
    delete[] v1;
    delete[] v2;
}

/////判断其中是否有错误的输入
bool isFloat(string in){
    bool back = true;
    int ascii = -1;
    //cout << in.length() << endl;
    for(int i = 0; i< in.length();i++){
        ascii = in[i];
        if(ascii<'0'|| ascii>'9'){
            if(ascii != '.' && ascii!=',' && ascii!='-'){
                back = false;
                break;
            }            
        }
    }
    //cout << back <<endl;
    return true;
    //return back;
}