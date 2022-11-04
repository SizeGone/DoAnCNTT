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
string APP_NAME = "LIST TU DIEN ANH VIET - NHOM 02 - NGUYEN TRUNG HIEU - MAI BAO LONG";

using namespace std;

/* cac ham xu ly giao dien */
// Ham di chuyen con tro den vi tri nao do trong Console
void gotoxy(short x, short y) {
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = {x, y};
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

// Ham thay doi textcolor va backgroundcolor
template <class T>
void setColor(T x) {
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, x);
}

//// xac dinh xem 1 tu thuoc ve tap tu dien nao
//template <class T>
//int DictCollect(T p)
//{
//	return p[0] - 97;
//}

void ClrScr() {
	system("cls");
}

template <class T>
void InsertExToTopList(NodeEx<T> *&first, T vidu) {
	// tao node moi trung gian
	NodeEx<T> *p = new NodeEx<T>();
	p->info = vidu;
	p->next = NULL;
	// truong hop ds chua co phan tu nao
	if (first == NULL) {
		first = p;
	} else {
		// truong hop ds da co it nhat 1 phan tu
		p->next = first;
		first = p;
	}
}

// chuyen du lieu tung line thanh cau truc du lieu
template <class T>
EWord<T> *convert(T line) {
	EWord<T> *p = new EWord<T>();
	int i, pos;
	i = 0;

	// about/pho tu/khoang chung;sap;gan;/He is about to die;We're about to start;How about this?;

	// tach tu
	T word = "";
	while (line[i] != '/') {
		word += line[i++];
	}
	i++;
	p->word = word;
	// tach loai tu
	T type = "";
	while (line[i] != '/') {
		type += line[i++];
	}
	i++;
	p->type = type;

	// tach nghia
	T mean = "";
	pos = 0;
	while (line[i] != '/') {
		mean += line[i];
		i++;
		// nghia moi
		if (line[i] == ';') {
			p->mean[pos++] = mean;
			mean = "";
			i++;
		}
	}
	i++;

	// tach vi du
	p->first = NULL;
	T vidu = "";
	while (line[i] != '/') {
		vidu += line[i++];
		if (line[i] == ';') {
			InsertExToTopList(p->first, vidu);
			vidu = "";
			i++;
		}
	}
	return p;
}

// doc tap tin tung line mot
template <class T>
void readFile(List<T> &dict) {
	ifstream fi("words.txt"); // tim tap tin
	T line;

	if (fi.is_open()) {
		// mo tap tin, kiem tra tap tin co ton tai hay khong...
		while (getline(fi, line)) {
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
void writeFile(List<T> &dict) {
	ofstream fo("wordst.txt", ios::out | ios::trunc);
	if (fo.is_open()) {
		Node<T> *p = dict.GetHead();
		if (p == NULL)
			return;
		while (p != NULL) {
			fo << p->data->word << "/";
			fo << p->data->type << "/";

			for (int i = 0; i < MAX_MEAN; i++) {
				if (p->data->mean[i] == "")
					break;
				fo << p->data->mean[i] << ";";
			}
			fo << "/";

			NodeEx<T> *vd = p->data->first;
			while (vd != NULL) {
				fo << vd->info << ";";
				vd = vd->next;
			}
			fo << "/\n";
			p = p->next;
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
Node<T>* Search(Node<T> *p, T input) {
//	Node<T> *p = dict.GetHead();
	while (p != NULL) {
		if (Compare(input, p)) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

//In danh sach tu ra man hinh
template<class T>
Node<T>* printList(List<T> &dict, T input, int pos) {
	Node<T> *curword = NULL; // tu dang duoc highlight trong man hinh chinh
	int count = 0;

	Node<T> *p = dict.GetHead();

	// neu khung tim kiem k co gia tri, thi in het cac tu ra va nguoc lai
	while (true) {
		p = Search(p,input);
		while (pos > 0 && p != NULL) {
			pos--;
			p=p->next;
		}
		if (p == NULL) break;
		if (count == 0) {
			curword = p;
			setColor(206);
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
	cout << " " << char(254) << " Esc   : Thoat chuong trinh" << endl;
	cout << " " << char(254) << " Tab   : Them tu moi" << endl;
	cout << " " << char(254) << " Enter : Xem nghia cua tu" << endl;
	cout << " " << char(254) << " Phim 1: Dao nguoc danh sach" << endl;
	cout << " " << char(254) << " Phim 2: Xem tu tieng anh o vi tri bat ky trong danh sach" << endl;
	cout << " " << char(254) << " Phim 3: Xem chi tiet tu tieng anh o vi tri bat ky trong danh sach " << endl;
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
	gotoxy(1 + input.size(), 8);

	return currword;
}
template <class T>
EWord<T>* EnterData() {
	ClrScr();
	EWord<T> *p = new EWord<T>();
	p->first = NULL;

	string temp = "";
	// nhap tu
	cout << "Nhap tu: ";
	getline(cin, temp);
	if (temp == "") return p;
	else {
		p->word = temp;
	}
	// nhap loai tu
	temp = "";
	cout << "Nhap loai tu: ";
	getline(cin, temp);
	p->type = temp;
	// nhap toi da 5 nghia
	for (int i = 0; i < MAX_MEAN; i++) {
		temp = "";
		cout << "Nhap nghia " << i + 1 << ": ";
		getline(cin, temp);
		if (temp == "") break;
		p->mean[i] = temp;
	}

	int count = 0;
	while (true) {
		temp = "";
		cout << "Nhap vi du " << ++count << ": ";
		getline(cin, temp);
		if (temp == "") break;
		InsertExToTopList(p->first, temp);
	};

	change = true;

	return p;
}

template <class T>
int GetPos(Node<T> *curr, List<T> &dict) {
	Node<T> *p = dict.GetHead();
	int pos = 0;
	while (p != curr) {
		pos++;
		p=p->next;
	}
	return pos;
}
template <class T>
void DeleteWord(List<T> &dict, Node<T> *curr) {
	ClrScr();
	cout << "Ban co chac muon xoa tu '" << curr->data->word << "' (y/n)?";
	char c = getch();

	if (c != 'y') {
		return;
	}
	T test;
	dict.Remove(GetPos(curr, dict), test);
	change = true;
}

template <class T>
void Reverse(List<T> &dict){
	ClrScr();
	cout << "Ban co chac muon dao nguoc danh sach nay (y/n)?";
	char c = getch();

	if (c != 'y') {
		return;
	}
	dict.Reverse();
	change = true;
}
template <class T>
EWord<T>* EditWord(EWord<T>* p) {
	ClrScr();

	cout << "Sua tu: '" << p->word << "':" << endl;

	string temp = "";
	cout << "Sua loai tu (" << p->type << "): ";
	getline(cin, temp);
	if (temp == "") return p;
	p->type = temp;

	for (int i = 0; i < MAX_MEAN; i++) {
		temp = "";
		cout << "Sua nghia " << i + 1 << " (" << p->mean[i] << "): ";
		getline(cin, temp);
		if (temp == "") break;
		p->mean[i] = temp;
	}

	NodeEx<T> *vd = p->first;
	int count = 0;
	if (vd == NULL) {
		// tu nay chua co vi du nao
		while (true) {
			cout << "Them vi du " << ++count << ": ";
			getline(cin, temp);
			if (temp == "") break;
			InsertExToTopList(p->first, temp);
		};
	} else {
		// tu nay da co it nhat 1 vi du
		while (vd != NULL) {
			cout << "Sua vi du " << ++count << " (" << vd->info << "): ";
			getline(cin, temp);
			if (temp == "") break;
			vd->info = temp;
			vd = vd->next;
		}
	}

	change = true;
	return p;
}

int enterPos(){
	ClrScr();
	int input;
	cout << "Nhap vi tri ban muon lay gia tri:";
	cin >> input;
	return input;
}

/* ham xu ly chinh cua chuong trinh */
template <class T>
void DictProcessing(List<T> &dict) {
	Node<T> *curr = NULL;
	T input = ""; // noi dung hien tai cua khung tim kiem
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
				dict.PushBack(EnterData<string>());
				count = dict.Size();
				break;
			case 49: //1
				Reverse(dict);
				break;
			case 50: //2
				input = dict.GetValueAt(enterPos());
				break;
			case 51: //3
				EWord<T> *tamp;
				dict.Retrieve(1, &tamp);
				input = tamp -> word;
				break;
			case 13: // ENTER
				// vao man hinh chi tiet tu
				if(curr != NULL) {
					WordInfo(curr);
					int k;
					do {
						k = getch();
						if (k == 8) { // BACKSPACE
							// xoa tu nay
							DeleteWord(dict,curr);
							input = "";
							pos = 0;
							break; // ve man hinh chinh
						}
						if (k == 9) { // TAB
							// sua tu nay
							dict.Replace(GetPos(curr,dict),EditWord<string>(curr->data));
							input = "";
							pos = 0;
							break; // ve man hinh chinh
						}
						if (k == 27) { // ESCAPE
							input = ""; // reset gia tri trong khung tim kiem
							pos = 0;
							break; // ve man hinh chinh
						}
					} while (true);
				}
				break;
			case 27: // ESCAPE
				gotoxy(2, 25);
				if (change == true) { // neu du lieu co thay doi
					cout << "Du lieu thay doi!!! Tien hanh ghi file..." << endl;
					writeFile(dict);
				}
				exit(EXIT_SUCCESS); // thoat chuong trinh
				break;
			case 224: {
				int key = getch();
				if (key == 72) {
					pos--;    // UP
				}
				if (key == 80) {
					pos++;    // DOWN
				}
				if (pos < 0) pos = 0;
				if (pos > count - 1) pos = count - 1;
				break;
			}
			default:
				if (keyCode >= 97 && keyCode <= 122) { // a-z
					input += char(keyCode);
					pos=0;
				} else if (keyCode >=65 && keyCode <=90) { // A-Z
					input += char(keyCode+32);
					pos=0;
				}
		}
	};
}
int main(int argc, char** argv) {
	List<string> main;
	readFile(main);
	DictProcessing(main);
	return 0;
}
#endif