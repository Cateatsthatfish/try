
#include<iostream>
#include<string>
#include<cstring>
#include <Windows.h>
#include <fstream>
#include <thread>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <float.h>
#include <stdexcept>

#pragma GCC optimize(3, "Ofast", "inline") //O3优化，由张睿豪提供


using namespace std;

//////需要用到的函数

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


///// 主函数

int main(){
    string in1, in2; /////////用来存输入
    int vlen = 0; ////两个vector里面数的个数
    float *v1 = new float; // 向量1
    float *v2 = new float; // 向量2
    long double result = 0; //点乘的结果

    //terminal 读入

    cout << "please enter vector 1:" ;
    getline(cin,in1);
    cout << "please enter vector 2:" ;
    getline(cin,in2);

    //string 转float
    if((!StringIsNull(in1)) &&(!StringIsNull(in2)) ) ///判断in是否长度为零
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
    


    //////得到v1和v2
    //try{
    if( (v1[0]!=0) && (v2[0]!=0)){ //判断输入是否为零
        if(v1[0]==v2[0]){ //判断长度是否相当
            vlen = v1[0];
            //计算&计时
            cout << "start calculating... Please hold on a second... " <<endl;
            if(vlen>1000000)  //////////////////五个线程
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

        }
        else{
           cout << "the two vectors do not have the same length" <<endl;
        }
    }
    else{
        cout << "no input received! "<<endl;
    }
    /*}
    catch(bad_alloc & e){
        cerr << e.what() << endl;
    }*/


    delete [] v1;
    delete [] v2;
    


    return 0;
}



bool StringIsNull(string str){
    if(str.length()==0){
        return true;
    }
    return false;
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
        dp += v1[i]*v2[i];
        //cout << "dp"<<i<<"="<<dp <<endl;
    }
    return dp;
    delete[] v1;
    delete[] v2;
}

/////判断其中是否有错误的输入
///keep updating
//允许科学计数法
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
    return back;
}