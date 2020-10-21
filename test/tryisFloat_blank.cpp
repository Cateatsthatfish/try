#include<iostream>
#include<string>
#include<cstring>

using namespace std;

bool isFloat(string); //判断输入的数有没有除了float和，之外的东西
string blank(string); // 去除空格
bool isValid_mode1input(string str);

int main(){
    string in ="1 ,2";
    string processed = blank(in);
    cout << processed <<endl;
    cout << isFloat(processed) <<endl;
    cout << isValid_mode1input(processed) <<endl;
    cout << (isValid_mode1input(processed)  && isFloat(processed)) << endl;
    return 0;
}

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