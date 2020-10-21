#include <iostream>
using namespace std;
int main(){
    //string in ="1234";
    //string in ="##1234";
     //string in = "#123.23#.";
     //string in ="12e+3,1234.314,qwe";
     string in ="12e+3,1234.314,";
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
    cout << back;
    return 0;
}