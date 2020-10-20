#include <iostream>
using namespace std;
bool isValid_mode1input(string str);

int main(){
    /*tring dot = "1..1.";
    cout <<  isValid_mode1input(dot) <<endl;*/

    /*string dot = "1.1,2.1";
    cout <<  isValid_mode1input(dot) <<endl;*/

    string dot1 = "1.,2";
    cout <<  isValid_mode1input(dot1) <<endl;

    string dot2 = ".1";
    cout <<  isValid_mode1input(dot2) <<endl;
    return 0;
}

bool isValid_mode1input(string str){
    //cout << "in function ! " <<endl;
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
    
    if(str[str.length()-1]!=','){
       // cout << "no comma!" << endl;
    str = str + ","; }

    int preComma = -1; //前一个逗号
    int posComma; //后一个逗号
    int idot; //index of dot
    int ndot = 0; // num of dot between two comma
    int imis; //index of minus
    int nmis = 0; // num of minus between two comma

    
    for(int i = 0; i< str.length();i++){
       // cout << "in loop!" <<endl;
        if(str[i]==','){
            posComma = i;
           //cout << "i=" <<i <<endl;
            //cout << "preComma=" << preComma <<endl;
            //cout << "posComma=" << posComma <<endl;
            
        
        for(int j = preComma+1; j < posComma; j++){
            if(str[j] == '.'){
                ndot = ndot + 1;
                idot = j;
            }
            //if(str[j] == '-'){}
        }

        cout << "number of dots: " <<  ndot << endl;
        if(ndot > 1){
            format = false;
            //cout << "format = " << format << endl;
            return format;
        }
        if(ndot == 1) //if there is a dot but in the wrong position
        {
            if( idot == preComma +1 || idot == posComma -1 ){
            format = false;
            //cout << "format = " << format << endl;
            return format;
            }
        }
        

        
        preComma = posComma;

        ndot = 0;

        }
    }

    return format;
}