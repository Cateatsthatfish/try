#include <iostream>
using namespace std;
bool isValid_mode1input(string str);

int main(){
    /*tring dot = "1..1.";
    cout <<  isValid_mode1input(dot) <<endl;*/

    /*string dot = "1.1,2.1";
    cout <<  isValid_mode1input(dot) <<endl;*/

    /*
    string dot1 = "1.,2";
    cout <<  isValid_mode1input(dot1) <<endl;

    string dot2 = ".1";
    cout <<  isValid_mode1input(dot2) <<endl;
    */

   /*
    string sci1 = "eE";
    string sci2 = "22e+1";
    cout << isValid_mode1input(sci1) << " " << isValid_mode1input(sci2) << endl;
    */
   /*
   string commas = "1,,1.1";
   cout << isValid_mode1input(commas) ;*/

   /*
   string plus = "++1";
   cout << isValid_mode1input(plus) ;
   */

    string sci1 = "3e+1";
    string sci2 = "3e1";
    string sci3 = "3E-1";
    string sci4 = "3.0e+2";
    string sci5 = "-3e-1";
    string sci6 = "-3e--1";
    
    string ap1 = "+-1,2";
    string ap2 = "--1,3.9";
    string ap3 = "-1";
    string ap4 = "+2";
    string ap5 = "2-";
    string ap6 = "3+,4";
    string ap7 = "1,2+";
    cout << isValid_mode1input(ap1) << " " << endl;
    cout << isValid_mode1input(ap2) << " " << endl;
    cout << isValid_mode1input(ap3) << " " << endl;
    cout << isValid_mode1input(ap4) << " " << endl;
    cout << isValid_mode1input(ap5) << " " << endl;
    cout << isValid_mode1input(ap6) << " " << endl;
    cout << isValid_mode1input(ap7) << " " << endl;


    


    

    return 0;
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
        }
        else{
            if(nplus + nmis > 1 ){
                return false;
            }
            if(nplus == 1 && iplus != preComma +1){
                return false;
            }
        
            if(nmis == 1 && imis != preComma +1){
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