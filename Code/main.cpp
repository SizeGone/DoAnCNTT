#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include "Graphics.h"
#include "List.cpp"
using namespace std;

int main(int argc, char** argv)
{
	string st;
	List<string> test ;
	test.PushBack("1");
	test.PushFront("99");
	test.PushFront("47");
	test.PushBack("2");
	test.PushBack("77");
	test.PushBack("88");
	test.PushBack("57");
	test.Insert(1,"3");
	cout <<"Danh sach List hien tai la:";
	test.PrintList();
	cout << "So phan tu:" << test.Size() << endl;
	cout << "Phan tu dau:" << test.GetFront() << endl;
	cout << "Phan tu cuoi:" << test.GetBack() << endl;
	cout << "Phan tu o vi tri thu 5: " << test.GetValueAt(5)<< endl;
	cout << "Phan tu o vi tri thu 15: " << test.GetValueAt(15)<< endl;
	cout <<"Xoa phan tu o vi tri dau tien " ;
	test.RemoveFront(st);
	cout<<"\nPhan tu da bi xoa la: " << st << endl;
	cout <<"Xoa phan tu o vi tri cuoi cung " ;
	test.RemoveBack(st);
	cout<<"\nPhan tu da bi xoa la: " << st << endl;
	cout <<"Xoa phan tu o vi tri thu 1 " ;
	test.Remove(1, st);
	cout<<"\nPhan tu da bi xoa la: " << st << endl;
	cout <<"Danh sach List hien tai la:";
	test.PrintList();
	test.Reverse();
	cout <<"Danh sach List dao nguoc la:";
	test.PrintList();
    return 0;
}
#endif