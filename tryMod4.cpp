
#include<iostream>
#include<string>
#include<cstring>
#include<Windows.h>
#include <fstream>
#include <thread>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <float.h>
#include <stdexcept>

#pragma GCC optimize(3, "Ofast", "inline") //O3优化，由张睿豪提供

/////随机数范围

const int a = INT_MIN/2;
const int b = INT_MAX/2;
/*
const int a = -1;
const int b = 1;
*/
using namespace std;

//////需要用到的函数
bool isValid_mode4input(string);

void hint(); /////给出提示
bool isValid_modeinput(string); ///输入模式mode的判断，只有输入0-4 （不含 空格，回车，tab）才判对
long double dot_product(float*, float*,int); // 计算向量 //这里需要改成long double计算大数值
bool isFloat(string); //判断输入的数有没有除了float和，之外的东西
bool StringIsNull(string); //判断输入为空 ////////////////？如果是回车怎么办？
bool IsValid_m4input(int); //判断mode4中输入的数是否符合条件，先假设它是一个整数，再判断它是否大于等于零，其他情况还没想到
string blank(string); // 去除空格
float* tofloat(string); // 提取字符串中的float

///用于多线程计算
void dotProduct(int startp, int endp, float* v1, float* v2, long double &result){

    for(int i = startp; i < endp; i++){
        result += v1[i] * v2[i];
    }
}

int main(){
    int vlen = 0; ////两个vector里面数的个数
    long double result = 0; //点乘的结果
    long double IDresult = 0; //五线程
    long double Dresult = 0; // 直接算   

 
    //只能进到mod4中
    //直接在程序中生成v1和v2
 
        cout << "Please enter a positive integer 'n' to generate two n-length vectors(500M is the max): ";
        string input_vlen ;
        getline(cin,input_vlen);
        while(!isValid_mode4input(input_vlen)){
            cout << "Invalid input! please try again! "<<endl;
            getline(cin,input_vlen);
        }
        vlen = atoi(input_vlen.c_str());

        //cin.get();
        float *v1 = new float[vlen+1]; // 向量1
        float *v2 = new float[vlen+1]; // 向量2
       
        //因为float 比 int范围大所以可以把长度放在第一位

        v1[0] = vlen;
        v2[0] = vlen;

        srand((int)time(0));
        ///把数存入v1和v2
        try{
        for (int i = 1; i < vlen+1; i++) 
    {
         v1[i] = a + rand()%(b-a) + rand()/double(RAND_MAX);
         v2[i] = a + rand()%(b-a) + rand()/double(RAND_MAX);
    }

    cout << "start calculating... Please hold on a second... " <<endl;

    vlen = v1[0];
//////////////////五个线程
    if(vlen>5){
    cout << "calculating indirectly:" <<endl;
    auto t1=std::chrono::steady_clock::now();   //测量时间,代码来自张睿豪
    //cout << "here?" <<endl;

    //五个值用来分别储存
    long double result1 =0;
    long double result2 =0;
    long double result3 =0;
    long double result4 =0;
    long double result5 =0;

    int start1 = vlen/5;
    int start2 = 2*vlen/5;
    int start3 = 3*vlen/5;
    int start4 = 4*vlen/5;
    int start5 = vlen+1;

    thread first(dotProduct,1,start1,std::ref(v1),std::ref(v2),std::ref(result1));
    thread second(dotProduct,start1,start2,std::ref(v1),std::ref(v2),std::ref(result2));    
    thread third(dotProduct,start2,start3,std::ref(v1),std::ref(v2),std::ref(result3));
    thread forth(dotProduct,start3,start4,std::ref(v1),std::ref(v2),std::ref(result4));
    thread fifth(dotProduct,start4,start5,std::ref(v1),std::ref(v2),std::ref(result5));
 
    first.join(); //主线程要等待子线程执行完毕
    second.join();
    third.join();
    forth.join();
    fifth.join();

    IDresult = result1 + result2+result3+result4+result5;
    auto t2=std::chrono::steady_clock::now();
    //毫秒级
    double idtime=std::chrono::duration<double,std::milli>(t2-t1).count();
   
    cout << IDresult << endl;
    cout << "(time: " << idtime << "ms)" << endl;
    }

/////////////////////直接算
    cout << "calculating directly:" <<endl;
    auto t3=std::chrono::steady_clock::now();
    Dresult = dot_product(v1,v2,vlen);
    auto t4=std::chrono::steady_clock::now();
    double dtime=std::chrono::duration<double,std::milli>(t4-t3).count();
    cout << Dresult << endl;
    cout << "(time: " << dtime << "ms)" << endl;}
    catch(bad_alloc & e){
        cerr << e.what() << endl;
    }

    delete [] v1;
    delete [] v2;
    return 0;
}

//////函数
bool isValid_mode4input(string in)
{
    bool len = true;
    if(in.length()==0){
        len = false;
    
    }
    if(in[0]==0){
        len = false;
    }
    for(int i = 0 ; i< in.length();i++){
        if(in[i]>'9'||in[i]<'0')
        {
            len = false;
            break;
        }
    }
       
    
    return len;
}

bool isValid_modeinput(string in)
{
    bool right_mode = false;
    if(in.length()==1){
        if(in[0]<='4'&& in[0]>='0')
        {
            right_mode = true;
        }
    }
    return right_mode;
}

bool StringIsNull(string str){
    if(str.length()==0){
        return true;
    }
    return false;
}

bool IsValid_m4input(int len){
    if(len <=0){
        return false;
    }
    return true;
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
///////点乘运算，不是线程的方法
long double dot_product(float* v1, float*v2, int length){

    long double dp = 0;
    //cout << "length = " << length << endl;
    for(int i = 1; i< length+1;i++) //把第一个跳掉
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
///keep updating
bool isFloat(string in){
    bool back = true;
    int ascii = -1;
    //cout << in.length() << endl;
    for(int i = 0; i< in.length();i++){
        ascii = in[i];
        if(ascii<'0'|| ascii>'9'){
            if(ascii != '.' && ascii!=',' && ascii!='-'&& ascii!='+'&& ascii!='e'&& ascii!='E'){
                back = false;
                break;
            }            
        }
    }
    //cout << back <<endl;
    //return true;
    return back;
}