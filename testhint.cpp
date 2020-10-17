//////这里其实是解决输入mode异常的问题
/////其实和hint没有什么关系了
/*test
回车
空格
tab

*/
#include <iostream>
using namespace std;
void hint();

int main()
{
    hint();
    int mode;
    cin >> mode;
    cout << "mode = " << mode <<endl;

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
}