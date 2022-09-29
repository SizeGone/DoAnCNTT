#ifndef CONSOLEAPP_H
#define CONSOLEAPP_H

#include <iostream>
#include "Controller.cpp"
using namespace std;

int main(int argc, char** argv)
{
    List<string> main;
    readFile(main);
    //In thu nghiem ra thong tin tu dau tien:
    // WordInfo(main.GetHead());
    cout << "\nIn ra danh sach cac tu tieng anh:";
    main.PrintList();
    cout << "So luong tu: ";
    cout << main.Size() << endl;
    writeFile(main); //đang write test vào file words.txt
    //test chuc nang tim kiem
    cout << "Danh sach cac tu co chu cai dau la 'a': ";
    SearchTest<string>(main,"a");
    return 0;
}
#endif