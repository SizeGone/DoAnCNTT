#ifndef CONSOLEAPP_H
#define CONSOLEAPP_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include "List.cpp"

#define MAX_MEAN 5	   // so nghia toi da cua mot tu
#define MAX_ROW 50	   // chieu rong khung tim kiem
#define MAX_DISPLAY 15 // so tu hien thi toi da o man hinh chinh

bool change = false; // bien ghi nhan du lieu co thay doi hay khong
string APP_NAME = "TU DIEN ANH VIET - NHOM 02";

using namespace std;

/* cac ham xu ly giao dien */
// Ham di chuyen con tro den vi tri nao do trong Console
void gotoxy(short x, short y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = {x, y};
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

// Ham thay doi textcolor va backgroundcolor
template <class T>
void setColor(T x)
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, x);
}

// xac dinh xem 1 tu thuoc ve tap tu dien nao
template <class T>
int DictCollect(T p)
{
	return p[0] - 97;
}

void ClrScr()
{
	system("cls");
}

template <class T>
void InsertExToTopList(NodeEx<T> *&first, T vidu)
{
	// tao node moi trung gian
	NodeEx<T> *p = new NodeEx<T>();
	p->info = vidu;
	p->next = NULL;
	// truong hop ds chua co phan tu nao
	if (first == NULL)
	{
		first = p;
	}
	else
	{
		// truong hop ds da co it nhat 1 phan tu
		p->next = first;
		first = p;
	}
}

// chuyen du lieu tung line thanh cau truc du lieu
template <class T>
EWord<T> *convert(T line)
{
	EWord<T> *p = new EWord<T>();
	int i, pos;
	i = 0;

	// about/pho tu/khoang chung;sap;gan;/He is about to die;We're about to start;How about this?;

	// tach tu
	T word = "";
	while (line[i] != '/')
	{
		word += line[i++];
	}
	i++;
	p->word = word;
	// tach loai tu
	T type = "";
	while (line[i] != '/')
	{
		type += line[i++];
	}
	i++;
	p->type = type;

	// tach nghia
	T mean = "";
	pos = 0;
	while (line[i] != '/')
	{
		mean += line[i];
		i++;
		// nghia moi
		if (line[i] == ';')
		{
			p->mean[pos++] = mean;
			mean = "";
			i++;
		}
	}
	i++;

	// tach vi du
	p->first = NULL;
	T vidu = "";
	while (line[i] != '/')
	{
		vidu += line[i++];
		if (line[i] == ';')
		{
			InsertExToTopList(p->first, vidu);
			vidu = "";
			i++;
		}
	}
	return p;
}

// doc tap tin tung line mot
template <class T>
void readFile(List<T> &dict)
{
	ifstream fi("words.txt"); // tim tap tin
	T line;

	if (fi.is_open())
	{ // mo tap tin, kiem tra tap tin co ton tai hay khong...
		while (getline(fi, line))
		{
			// cout << line << endl;
			if (line == "")
				continue;
			EWord<T> *p = convert(line);
			dict.PushBack(p);
		}
		fi.close(); // line tap tin
	}
}
template <class T>
void writeFile(List<T> &dict)
{
	ofstream fo("wordst.txt");
	if (fo.is_open())
	{
		for (int i = 0; i < 26; i++)
		{
			Node<T> *p = dict.GetHead();
			if (p == NULL)
				continue;
			while (p != NULL)
			{
				fo << p->data->word << "/";
				fo << p->data->type << "/";

				for (int i = 0; i < MAX_MEAN; i++)
				{
					if (p->data->mean[i] == "")
						break;
					fo << p->data->mean[i] << ";";
				}
				fo << "/";

				NodeEx<T> *vd = p->data->first;
				while (vd != NULL)
				{
					fo << vd->info << ";";
					vd = vd->next;
				}
				fo << "/\n";
				p = p->next;
			}
		}
		fo.close();
	}
}

//Ve giao dien chi tiet:
template <class T>
void WordInfo(Node<T> *p) {
	ClrScr();
	int currline = 0;
	
	// in ra cac huong dan
	// o man hinh chi tiet tu
	cout << " " << char(254) << " Esc      : Ve lai man hinh chinh" << endl;
	cout << " " << char(254) << " Tab      : Sua tu nay" << endl;
	cout << " " << char(254) << " Backspace: Xoa tu nay" << endl;
	
	// in ra cac chi tiet cua tu
	cout << endl << " " << p->data->word;
	cout << endl << " ---";
	cout << endl << " (" << p->data->type << "): ";
	for (int i = 0; i < MAX_MEAN; i++) {
		if (p->data->mean[i] == "") break;
		cout << p->data->mean[i] << "; ";
	}

	cout << endl << " ---";
	
	NodeEx<T> *v = p->data->first;
	while (v != NULL) {
		cout << endl << " " <<  v->info;
		v = v->next;
	}
}

// so sanh input voi mot tu cu the
template<class T> 
bool Compare(T input, Node<T> *p) {
	T word = p->data->word;	
	// khi tu nhap ngan hon tu can so
	for (int i = 0; i < input.size(); i++) {
		if (input[i] != word[i]) {
			return false;
		}
	}
	return true;
}

//Timkiem
template <class T>
Node<T>* Search(List<T> dict, T input) {

	Node<T> *p = dict.GetHead();
	while (p != NULL) {
		if (Compare(input, p)) {
			return p;
		}
		p = p->next;
	}
	return NULL;	
}

//Timkiem
template <class T>
void SearchTest(List<T> &dict, T input) {
	Node<T> *p = dict.GetHead();
	while (p != NULL) {
		if (Compare<T>(input, p)) {
			cout << p->data->word << "; ";
		}
		p = p->next;
	}	
}
//In danh sach tu ra man hinh
template<class T>
Node<T>* printList(List<T> &dict, T input, int pos) {
	Node<T> *curword = NULL; // tu dang duoc highlight trong man hinh chinh	
	// neu khung tim kiem k co gia tri, thi in het cac tu ra
	int index = -1;
	if (input != "") {
		index = DictCollect(input);
	}
	
	int count = 0;
	for (int i = 0; i < 26; i++) {
		if (dict.GetHead() == NULL) continue; // tap tu dien nay khong tu nao, bo qua
		Node<T> *p = dict.GetHead();
		if (index != -1) {
			p = Search<T>(dict, input);
		}
		while (true) {
			while (pos > 0 && p != NULL) {
				pos--;
				p = p->next;
			}
			if (p == NULL) break;
			if (count == 0) {
				curword = p;
				setColor(207);	
			} else {
				setColor(15);	
			}
			cout << endl << " " << p->data->word << " ";
			for (int j = 0; j < MAX_ROW - p->data->word.size(); j++) {
				cout << " ";
			}
			count++;
			p = p->next;
			if (p == NULL) {
				break;
			}
		}
		if (index != -1) break;
		if (count >= MAX_DISPLAY) break;
	}
	setColor(15);
	return curword;
}

// ve man hinh chinh
// tra ve tu dang duoc highlight
template<class T>
Node<T>* mainGraphics(List<T> &dict, T input, int pos) {
	ClrScr();
	int currline = 0;
	
	// in ra cac huong dan
	// o man hinh chinh
	cout << " " << APP_NAME << endl;	
	cout << " " << char(254) << " Esc  : Thoat chuong trinh" << endl;
	cout << " " << char(254) << " Tab  : Them tu moi" << endl;
	cout << " " << char(254) << " Enter: Xem nghia cua tu" << endl;
	
	// ve khung tim kiem
	cout << char(218);
	for (int i = 0; i < MAX_ROW; i++) {
		cout << char(196);
	}
	cout << char(191) << endl;
	
	cout << char(179) << input;
	for (int i = 0; i < MAX_ROW - input.size(); i++) {
		cout << char(255);
	}
	cout << char(179);
	
	cout << endl << char(192);
	for (int i = 0; i < MAX_ROW; i++) {
		cout << char(196);
	}
	cout << char(217);
	
	Node<T> *currword = printList(dict, input, pos);
	
	// neu dang o man hinh chinh,
	// dua con tro nhap nhay ve lai khung tim kiem
	gotoxy(1 + input.size(), 5);
	
	return currword;
}
template <class T> 
EWord<T>* EnterData(){
	EWord<T> *e = new EWord<T>();
	cout << "Nhap tu tieng anh: ";
	cin >> e->word;
	cout << "Nhap nghia: ";
	cin >> e->mean[0];
	return e;
}
/* ham xu ly chinh cua chuong trinh */
template <class T>
void DictProcessing(List<T> &dict) {
	Node<T> *curr = NULL;
	string input = ""; // noi dung hien tai cua khung tim kiem
	int keyCode = 0;
	int pos = 0; // vi tri cua tu hien tai, vi tri thah sang (highlight)
	int count = dict.Size(); // dem so luong tu co trong tu dien
	
	while (true) { // vong lap vo tan
		curr = mainGraphics(dict, input, pos);	// ve toan bo giao dien
		keyCode = getch(); // tam dung chuong trinh, nhan ky tu nhap vao		
		switch (keyCode) {
			case 8: // BACKSPACE
				input = input.substr(0, input.size() - 1); // xoa ky tu cuoi
				break;
			case 9: // TAB
				dict.Insert(1,EnterData<string>());
				break;
			case 13: // ENTER
				// vao man hinh chi tiet tu
				WordInfo(curr);
				int k;
				do {
					k = getch();
					if (k == 8) { // BACKSPACE
						// xoa tu nay
						T test;
						dict.Remove(1, test);
						input = ""; pos = 0;
						break; // ve man hinh chinh
					}
					if (k == 9) { // TAB
						// sua tu nay
						dict.Insert(1,EnterData<string>());
						input = ""; pos = 0;
						break; // ve man hinh chinh
					}
					if (k == 27) { // ESCAPE
						input = ""; // reset gia tri trong khung tim kiem
						pos = 0;
						break; // ve man hinh chinh
					}
				} while (true);
				break;
			case 27: // ESCAPE
				gotoxy(2, 25);
//				if (dulieuThaydoi == true) { // neu du lieu co thay doi
//					cout << "Du lieu thay doi!!! Tien hanh ghi file..." << endl;
//					ghiFile(tudien);
//				}
				exit(EXIT_SUCCESS); // thoat chuong trinh
				break;
			case 224: {
				int key = getch();
				if (key == 72) { pos--; } // UP
				if (key == 80) { pos++; } // DOWN
				if (pos < 0) pos = 0;
				if (pos > count - 1) pos = count - 1;
				break;
			}
			default:
				if (keyCode >= 97 && keyCode <= 122) { // a-z
					input += char(keyCode);
				}
		}
	};
}
int main(int argc, char** argv)
{
    List<string> main;
    readFile(main);
    DictProcessing(main);
    return 0;
}
#endif