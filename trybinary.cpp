#include<stdio.h> 
#include<iostream>
#include<fstream>
#include<cstring>
#include<string>


using namespace std;

int main() 
{ 
    ///写字符
    /*
FILE*fp; 
char ch; 
if((fp=fopen("string","wt+"))==NULL) { 
printf("Cannot open file string any key exit!\n"); 
    getchar(); 
    exit(1); 
   } 
printf("input a string:\n"); 
   ch=getchar(); 
   while(ch!='\n') { 
   fputc(ch,fp); 
   ch=getchar(); 
     } 
rewind(fp); 
ch=fgetc(fp); 
while(ch!=EOF){ 
putchar(ch); 
ch=fgetc(fp); 
} 
printf("\n"); 
fclose(fp); 
*/

FILE * fp = fopen("v1.txt", "wb");
if(fp)
    {
        cout << "file v1 is open."<<endl;
    float r1 = 1;
    for (int i = 0; i < 20; i++) 
    {      
        fprintf(fp, "%f,",  r1+1);
      }
    fclose(fp);

    }else{
        cout <<"something in v1 is wrong." <<endl;
    }

string in1;
ifstream infile("v1.txt",ios::in|ios::binary);
if(!infile){
    cout << "Oops! file\" v1.txt \" failed to open." << endl;
}else{
    cout << "read from the file1" <<endl;
        getline(infile,in1);
        //cout << <<endl;
        infile.close();
}
cout << in1 <<endl;


return 0; 
} 