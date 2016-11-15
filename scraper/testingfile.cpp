#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<string>

using namespace std;
char a;
string line;

int main(){
	ifstream fin;
	fin.open("resultlist.txt");	
	getline(fin, line); 
	//read each character individually and check to see if they match the format
	while(!fin.eof()){
		
		for(int i =0; i<4; i++){
			if (line[i] == '0'||line[i]=='1'||line[i]=='2'||line[i]=='3'||line[i]=='4'||line[i]=='5'||line[i]=='6'||line[i]=='7'||line[i]=='8'||line[i] =='9' || line[i] == '.'){

				cout<<line[i];
				
			}else if (line[i] == '*'){
				cout<<line[i];
				
			}else{
				cout<<endl<<endl<<line[i];
			cout<< "error2: format error in text file"<<endl;
				break;
			}
		}
		
		int x =4;
		while (line[x]!='\0'){
			cout<<line[x];
			if(isdigit(line[x])){
				cout<<"teacher name format is not correct."<<endl;
				break;			}
		x++;
		}
		getline(fin, line); 
		getline(fin, line);
		//cout<<endl<<line<<endl; 	// i will ignore this line, not necessary for the use of the file
		cout<<endl;
		
	}
	
	fin.close();
	cout<<"file above follows correct format!"<<endl;
	return 0;
}

