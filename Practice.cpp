#include<iostream>
#include<math.h>
#include<fstream>
#include<string>
using namespace std;

void showResult(int a[],int length){
	cout<<"Length:"<<length<<"\n";
	for(int i = 0; i< length; i++){
		cout<<a[i]<<" ";
	}
}

void readData(){
	fstream file("result.txt");
	string data;
	while(!file.eof()){
		file>>data;
		cout<<data<<"\n";
	}
	file.close();
}

void writeToFile(int a[],int length){
	fstream file("result.txt");
	file<<"Ket Qua"<<"\n";
	for(int i=0; i<length; i++){
		file<<a[i]<<"\n";
	}
	file.close();
}

void swap(int &a,int &b){
	int t = a;
	a = b;
	b = t;
}

void quickSort(int a[], int low, int high){
	int i = low, j = high;
	int center = a[(i+j)/2];
	cout<<"QS:"<<low<<","<<high<<"\n";
	while(i<=j){
		while(a[i] < center) i++;
		while(a[j] > center) j--;
		if(i<=j) {
			swap(a[i],a[j]);
			i++;
			j--;
		}
		if(i<high) quickSort(a,i,high);
		if(j>low) quickSort(a,low,j);
	}
}

char numberToChar(int number){
	char c = (char)(number+48);
	return c;
}

int charToNumber(char c){
	return c - '0';
}

void normalize(string &a, string &b){
	int l1 = a.length(), l2 = b.length();
	if(l1>=l2) b.insert(0,l1-l2,'0');
	else       a.insert(0,l2-l1,'0');
}

int compare2Number(string a, string b){
	if(a.length() > b.length()) return 1;
	
	if(a.length() < b.length()) return -1;
	
	for(int i = 0; i < a.length(); i++){
		if(charToNumber(a[i]) > charToNumber(b[i]))return 1;
		if(charToNumber(a[i]) < charToNumber(b[i])) return -1;
		continue;
	}
	
	return 0;
}

string sum(string a, string b){
	string s = "";
	normalize(a,b);
	int temp = 0;
	for(int i=a.length()-1; i>=0; i--){
		temp = temp + charToNumber(a[i]) + charToNumber(b[i]);
		s.insert(0,1,numberToChar(temp%10));
		temp = temp/10;
	}
	
	if(temp > 0) s.insert(0,1,numberToChar(temp));
	
	return s;
}

string subtract(string a, string b){
	string s = "";
	normalize(a,b);
	int temp = 0;
	for(int i = a.length()-1; i>=0; i--){
		int x = charToNumber(a[i]), y = charToNumber(b[i]) + temp;
		if(x >= y){
			s.insert(0,1,numberToChar(x-y));
			temp = 0;
		}else{
			s.insert(0,1,numberToChar(10+x-y));
			temp = 1;
		}
	}
	if(temp > 0) s.insert(0,1,'-');
	return s;
}

string multiSmall(char c, string a){
	string s = "";
	int temp = 0;
	for(int i=a.length()-1; i>=0; i--){
		temp = temp + (charToNumber(c) * charToNumber(a[i])) ;
		s = s.insert(0,1,numberToChar(temp%10));
		temp = temp/10;
	}
	if(temp > 0) s.insert(0,1,numberToChar(temp));
	cout<<s<<"\n";
	return s;
}

string multil(string a, string b){
	string s = "0";
	int lenght = a.length();
	
	for(int i = lenght-1; i>=0; i--){
		 string s1 = multiSmall(a[i],b);
		 s1.insert(s1.length(),lenght-i-1,'0');
		 s = sum(s,s1);
	}
	
	return s;
	
}

string xauDoiXung(string ss){
	string s1 = "", s2 = "";
	int arr[ss.length()][ss.length()];
	for(int i = 0; i < ss.length(); i++)
		for(int j = 0; j < ss.length(); j++) arr[i][j] = 1;
		
	for(int i = ss.length() - 2; i >= 0; i--){
		for(int j = i+1; j < ss.length(); j++){
			if(ss[i] == ss[j]) arr[i][j] = arr[i+1][j-1] + 2;
			else arr[i][j] = max(arr[i+1][j], arr[i][j-1]);
		}
	}
	
	int i = 0, j = ss.length() - 1;
	
	while(i<=j){
		if(ss[i] == ss[j]){
			s1 = s1 + ss[i];
			s2 = ss[j] + s2;
			i++;
			j--;
		}else{
			if(arr[i+1][j] == arr[i][j]) i++;
			else j--;
		}
	}
	cout<<s1 << "----"<<s2<<"\n";
	if(arr[1][ss.length()-1] % 2 == 1) s2.erase(0,1);
	s1 = s1 + s2;
	return s1;
}

main(){
//	int arr[] = {110, 5, 10,3 ,22, 100, 1, 23};
//	int length = sizeof(arr)/sizeof(arr[0]) - 1;
//	quickSort(arr,0,length);
//	showResult(arr,length);

//	readData();
//	writeToFile(arr,length);
	
	
	// Big integer
	
	string a,b;
	getline(cin, a);
    getline(cin, b);
	
	cout<<"Tong a+b = "<<sum(a,b)<<"\n";
	cout<<"Tich a*b ="<<multil(a,b)<<"\n";
	cout<<compare2Number(a,b)<<"\n";
	switch (compare2Number(a,b)){
		case 1:{
			cout<<"Hieu a-b = "<<subtract(a,b);
			break;
		}
		case 0:{
			cout<<"Hieu a-b = "<<0;
			break;
		}
		case -1:{
			cout<<"Hieu a-b = -"<<subtract(b,a);
			break;
		}
	}
	
}
