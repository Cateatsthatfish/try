
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
bool isValid_mode1input(string);
bool isValid_mode4input(string);
//////需要用到的函数

void hint(); /////给出提示
bool isValid_modeinput(string); ///输入模式mode的判断，只有输入0-4 （不含 空格，回车，tab）才判对
long double dot_product(float*, float*,int); // 计算向量 /
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
    long double IDresult = 0; //五线程
    long double Dresult = 0; // 直接算 
    
    long double result = 0; //点乘的结果

    //terminal 读入

    cout << "please enter vector 1:" ;
    getline(cin,in1);
    cout << "please enter vector 2:" ;
    getline(cin,in2);

    //string 转float
    if((!StringIsNull(in1)) &&(!StringIsNull(in2)) ) ///判断in是否长度为零
    {
    string str1, str2;
    str1 = blank(in1);
    str2 = blank(in2);
    cout << str1 << endl;
        if(isFloat(in1) && isFloat(in2) && isValid_mode1input(str1) && isValid_mode1input(str2)) //合理性验证
        {

    // string -> float*
    //分割标志：‘，’
     v1 = tofloat(str1);
     v2 = tofloat(str2);
        
    

    if( (v1[0]!=0) && (v2[0]!=0)){ //判断输入是否为零
        if(v1[0]==v2[0]){ //判断长度是否相当
            vlen = v1[0];
            //计算&计时
            cout << "start calculating... Please hold on a second... " <<endl;
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
        else{
           cout << "the two vectors do not have the same length" <<endl;
        }
    }
    else{
        cout << "no valid input received! "<<endl;
    }


    delete [] v1;
    delete [] v2;
    }else{
            cout << "invalid inputs!" << endl; 
        }
    }
    else{
        cout << "no input received! "<<endl;
    }
    
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

bool isValid_mode1input(string str){
    //cout << "in function ! " <<endl;
    //bool format = true;
    /////已有条件：在去掉空格之后且长度不为零的时候
    //////逗号之间：（逗号的个数等于总共的元素的个数，float*中的元素的个数为n+1）
    //////最多只有在中间一个.[实现]
    //////最多只有在开头有一个负号
    //////不能为空[实现]
    //////科学计数法(中间可以有负号)
    //////1.1e+3
    //////1.1e3
    //////1E3
    ///////零在最前面

    ///在最末尾加上，如果没有的话
    
    if(str[str.length()-1]!=','){
       // cout << "no comma!" << endl;
    str = str + ","; }

    int preComma = -1; //前一个逗号
    int posComma; //后一个逗号
    int idot; //index of dot
    int ndot = 0; // num of dot between two comma
    int imis[2]; //index of minus
    int nmis = 0; // num of minus between two comma
    int iplus[2] ;
    int nplus  = 0;
    int isci ; // 科学计数法的坐标（E）
    int nsci = 0; // 科学计数法的的个数（e）
    bool sci = false;


    
    for(int i = 0; i< str.length();i++){
       // cout << "in loop!" <<endl;
        if(str[i]==','){
            posComma = i;
           //cout << "i=" <<i <<endl;
            //cout << "preComma=" << preComma <<endl;
            //cout << "posComma=" << posComma <<endl;
        
        if(posComma == preComma+1 ){
            return false;
        }else{
        
        for(int j = preComma+1; j < posComma; j++){
            if(str[j] == '.'){
                ndot = ndot + 1;
                idot = j;
            }
            if(str[j]=='e'||str[j] == 'E'){
                nsci = nsci + 1 ;
                isci = j;
                sci = true;
            }
            if (str[j] == '-'){
                imis[nmis] = j;
                nmis = nmis + 1 ;
                
            }
            if (str[j] == '+'){
                iplus[nplus] = j;
                nplus = nplus +1 ;
                
            }
            
            //if(str[j] == '-'){}
        }

        //cout << "number of dots: " <<  ndot << endl;
        if(sci == true){
            if(nplus + nmis > 2 ){
                return false;
            }
            for(int k = 0; k < nplus; k++){
                if(iplus[k]!=preComma+1 && iplus[k]!= isci+1){
                    return false;
                }
            }
             for(int k = 0; k < nmis; k++){
                if(imis[k]!=preComma+1 && imis[k]!= isci+1){
                    return false;
                }
            }
        }
        else{
            if(nplus + nmis > 1 ){
                return false;
            }
            if(nplus == 1 && iplus[0] != preComma +1){
                return false;
            }
        
            if(nmis == 1 && imis[0] != preComma +1){
                return false;
            }

        }

        if(ndot > 1 || nsci > 1 || nplus > 1){
            //format = false;
            //cout << "format = " << format << endl;
            return false;
        }
        if(ndot == 1) //if there is a dot but in the wrong position
        {
            if( idot == preComma +1 || idot == posComma -1 ){
            //format = false;
            //cout << "format = " << format << endl;
            return false;
            }
        }
                
        preComma = posComma;

        ndot = 0;
        nplus = 0;
        nsci = 0;
        nmis = 0;
        }

        }
    }

    return true;
}