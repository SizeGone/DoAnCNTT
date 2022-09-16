#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include "Graphics.h"
#include "List.cpp"
using namespace std;

int main(int argc, char** argv)
{
	List<string> test ;
	test.AddItem("1");
	test.AddItem("2");
	test.Insert(1,"3");
	cout << "So phan tu:" << test.Size() << endl;
	cout <<"Danh sach List hien tai la:";
	test.PrintList();
	string st;
	cout <<"Xoa phan tu o vi tri thu 1 " ;
	test.Remove(1, st);
	cout<<"\nPhan tu da bi xoa la: " << st[0] << endl;
	cout <<"Danh sach List hien tai la:";
	test.PrintList();
    return 0;
}
#endif