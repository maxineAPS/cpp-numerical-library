#ifndef __MyToolset_h__
#define __MyToolset_h__
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include "MyMatrix.h"
using namespace std;

void Write_To_File_Sample()
{
	cout<<"Write to file sample"<<endl;
	string file_name="test.txt";
	ofstream out(file_name);
	if(!out){cout<<"Cannot open file "<<file_name<<endl;return;}
	out<<1<<endl;
	out<<2<<endl;
	out<<3<<endl;
	cout<<"Finish writting to file "<<file_name<<endl;
}

void Random_Number_Sample()
{
	cout<<"Generate random numbers between -1 to 1"<<endl;
	for(int i=0;i<10;i++){
		double rand_n=(double)(rand()%20000-10000)/(double)10000;
		cout<<"rand "<<rand_n<<endl;
	}
	cout<<"Finish generating random numbers"<<endl;
}

void Timing_Sample()
{
	clock_t start = clock();
    Matrix A(1000, 1000);
    Matrix B(1000, 1000);
    A.Random();
    B.Random();
    Matrix C = A*B;
	//Do something
	for (int i = 0; i < 1000; i++) { int a = 1; int b = 2; int c = a * b; }
	clock_t end = clock();
	cout << "Time cost:" << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
}



#endif
