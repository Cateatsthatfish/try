#include <iostream>
using namespace std;
int main(){
    return 0;
}

bool isValid_mode1input(string str){
    bool format = true;
    /////已有条件：在去掉空格之后且长度不为零的时候
    //////逗号之间：（逗号的个数等于总共的元素的个数，float*中的元素的个数为n+1）
    //////最多只有在中间一个.
    //////最多只有在开头有一个负号
    //////不能为空
    //////科学计数法(中间可以有负号)
    //////1.1e+3
    //////1.1e3
    //////1E3

    ///在最末尾加上，如果没有的话
    int len = str.length();
    if(str[len-1]!=','){
    str = str + ","; }

    int preComma = -1; //前一个逗号
    int posComma; //后一个逗号
    int idot; //index of dot
    int ndot = 0; // num of dot between two comma
    int imis; //index of minus
    int nmis = 0; // num of minus between two comma

    //int 
    for(int i = 0; i< len;i++){
        if(str[i]==','){
            posComma = i;
            
        
        for(int j = preComma+1; j < posComma; i++){
            if(str[j] == '.'){
                ndot = ndot + 1;
                idot = i;
            }
            if(str[j] == '-'){

            }
        }


        
        if(ndot > 1){
            format = false;
            return format;
        }

        
        preComma = posComma;

        }
    }

    return format;
}