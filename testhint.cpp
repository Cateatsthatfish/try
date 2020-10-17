//////这里其实是解决输入mode异常的问题
/////其实和hint没有什么关系了
/////改用assignment 1 的方法来判断第一次读入
/////读入为string 
//////string转int
/*test
回车 -》回车不会存进Mode里面
空格 -》 空格不会存进 mode里面
tab -》 tab不会被存进mode里面
数字 -》 用2 3 只会存入2

小数： 0.1     2.354 
科学计数法： 3e+1

*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;
void hint();
bool isValid_modeinput(string);
string blank(string); // 去除空格

int main()
{
    hint();
    string mode;
    do{
        cin >> mode; /////cin在输入string之前的tab ' '和回车都会忽略掉

    }while(!isValid_modeinput(mode));
    cout <<mode <<endl;
    //cin.sync(); ///清空缓冲区(不知道有没有必要)

    /*
    string mode2;
    cin >> mode2;
    cout << "mode = " << mode <<endl;
    cout << "mode = " << mode2 <<endl;
    */

    return 0;
}
bool isValid_modeinput(string m_in)
{
    string in = blank(m_in); //////空格后面如果还有输入就不要了
    bool right_mode = false;
    ///除掉空格和tab？
    if(in.length()==1){
        if(in[0]<='4'&& m_in[0]>='0')
        {
            right_mode = true;
        }
    }
    return right_mode;
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
void hint(){
    cout << "please enter the two vectors whose elements are separated by \',\'" <<endl; //提示输入两个向量
    cout << "for example: 1,2,3……" <<endl;
    cout << "there are four modes" << endl;
    cout << "press '1' : enter in terminal " <<endl;
    cout << "press '2' : enter in '.txt'file " <<endl;
    cout << "press '3' : enter in binary file" <<endl;
    cout << "press '4' : automatically generate two random vectors  " <<endl;
    cout << "press '0' : exit" << endl; ////////////////////怎么退出来着？
    cout << "--------------------------------------------" <<endl;
    cout << "press \'enter\' to continue" << endl; 
}