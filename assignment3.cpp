
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

#pragma GCC optimize(3, "Ofast", "inline") //O3优化，由张睿豪提供

/////随机数范围
const int a = INT_MIN/2;
const int b = INT_MAX/2;

using namespace std;

//////需要用到的函数

void hint(); /////给出提示，返回输入模式
///1 退出的实现
///2 判断异常的输入->返回为零
//（1）除了0-4之外的字符（2）tab，空格，回车（3）复制的string?


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
    string in1, in2; /////////用来存输入
    int vlen = 0; ////两个vector里面数的个数
    ////////////////////////记得delete float!!!!!!!!!!!!!!!
    float *v1 = new float; // 向量1
    float *v2 = new float; // 向量2
    long double result = 0; //点乘的结果

    //提示选择模式
    hint();
    int mod;
    cin >> mod;
    /////////////////考虑mode不等于0，1，2，3，4或者控制mode只能等于0，1，2，3，4
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
    ///read from v1.txt to get string in1
        ifstream bfile1("v1.txt",ios::in|ios::binary);
        if(!bfile1){
            cout << "Oops! file\" v1.txt \" failed to open." << endl;}
        else{
            cout << "read from the file1" <<endl;
            getline(bfile1,in1);
        //cout << <<endl;
        bfile1.close();
        }
    ///read from v2.txt to get string in2
        ifstream bfile2("v2.txt",ios::in|ios::binary);
        if(!bfile2){
            cout << "Oops! file\" v2.txt \" failed to open." << endl;}
        else{
            cout << "read from the file2" <<endl;
            getline(bfile2,in2);
        //cout << <<endl;
        bfile2.close();
        }
    }
    
    //string 转float
    //如果没有进入mode1，2，3 in1 和in2就都会是零
    //那么v1和v2还都什么都没有
    if((mod!=4)&&(!StringIsNull(in1)) &&(!StringIsNull(in2)) ) ///判断in是否长度为零
    {
        if(isFloat(in1) && isFloat(in2)) //合理性验证待更新
        {

    // 去除空格
    string str1, str2;
    str1 = blank(in1);
    str2 = blank(in2);
    
    // string -> float*
    //分割标志：‘，’
     v1 = tofloat(str1);
     v2 = tofloat(str2);
        }else{
            cout << "invalid inputs!" << endl; 
        }

    }
    else{
        
        cout << "no input received! "<<endl;
    }
 
    //只能进到mod4中
    //直接在程序中生成v1和v2
    if(mod == 4){
        cout << "Please enter a positive integer 'n' to generate two n-length vectors: ";
        cin >> vlen; //////异常处理（1、如果输入不是正整数怎么办 2、科学计数法？输入）
        if(IsValid_m4input(vlen)){
        //因为float 比 int范围大所以可以把长度放在第一位
        v1[0] = vlen;
        v2[0] = vlen;
        srand((int)time(0));
        ///把数存入v1和v2
        for (int i = 1; i < vlen+1; i++) 
    {
         v1[i] = a + rand()%(b-a) + rand()/double(RAND_MAX);
         v2[i] = a + rand()%(b-a) + rand()/double(RAND_MAX);
    }

        }else{
            cout << "invalid input 'n" <<endl;
        }
        
     }

    //////得到v1和v2
    if( (v1[0]!=0) && (v2[0]!=0)){
        if(v1[0]==v2[0]){
            vlen = v1[0];
            //计算&计时
            if(v1[0]>10000000)  //////////////////五个线程
            {
    auto t1=std::chrono::steady_clock::now();   //测量时间,代码来自张睿豪

    //五个值用来分别储存
    long double result1 =0;
    long double result2 =0;
    long double result3 =0;
    long double result4 =0;
    long double result5 =0;
   
    //int innum = v1[0];

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

    result = result1 + result2+result3+result4+result5;
    auto t2=std::chrono::steady_clock::now();
    //毫秒级
    double time=std::chrono::duration<double,std::milli>(t2-t1).count();
   
    cout << result << endl;
    cout << "(time: " << time << "ms)" << endl;

            }
            else ///////直接算
            {
                auto t1=std::chrono::steady_clock::now();
                result = dot_product(v1,v2,vlen);
                auto t2=std::chrono::steady_clock::now();
                double time=std::chrono::duration<double,std::milli>(t2-t1).count();
                cout << result << endl;
                cout << "(time: " << time << "ms)" << endl;
            }

        }else{
           cout << "the two vectors do not have the same length" <<endl;
        }
    }else{
        cout << "no input received! "<<endl;
    }


    delete [] v1;
    delete [] v2;

    return 0;
}

void hint(){
    cout << "please enter the two vectors whose elements are separated by \',\'" <<endl; //提示输入两个向量
    cout << "for example: 1,2,3……" <<endl;
    cout << "there are four modes" << endl;
    cout << "press '1' : enter in terminal " <<endl;
    cout << "press '2' : enter in '.txt'file " <<endl;
    cout << "press '3' : enter in binary file" <<endl;
    cout << "press '4' : automatically generate two random vectors  " <<endl;
    cout << "press '0' : exit" << endl; ////////////////////怎么退出来着？

    //return mode;
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