#include <iostream>
#include "List.h"
using namespace std;
// Implement NODE
template<class T> Node<T>::Node() {
	next = nullptr;
	previous = nullptr;
}

template<class T> Node<T>::Node(T item, Node<T> * linkNext, Node<T>* linkPrevious) {
	data = item;
	next = linkNext;
	previous = linkPrevious;
}

// Implement LIST
template<class T> Node<T>* List<T>::set_position(int position) const {
	Node<T>* q = head;
	for (int i=0; i<position; i++)
		q = q->next;
	return q;
}

template<class T> List<T>::List() {
	count = 0;
	head = nullptr;
}

template<class T> List<T>::~List() {
	//clear();
}

template<class T> void List<T>::Clear() {
	Node<T>* tmp;
	while (head != nullptr) {
		tmp = head;
		head = head->next;
		delete tmp;
	}
	count = 0;
}

template<class T> bool List<T>::IsEmpty() const {
	return count == 0;
}

template<class T> unsigned short int List<T>::Size() const {
	return count;
}

template<class T> Error_Code List<T>::Replace (int position, const T& item) {
	if (position < 0 || position > count)
		return Error_Code::range_error;
	Node<T>* tmp = set_position(position);
	tmp->data = item;
	return success;
}

template<class T> Error_Code List<T>::Retrieve (int position,T& item) const {
	if (position < 0 || position > count)
		return Error_Code::range_error;
	Node<T>* tmp = set_position(position);
	item = tmp->data;
	return success;
}
//Chèn dữ liệu mới vào vị trí bất kì trong List:
template<class T> Error_Code List<T>::Insert (int position, T item){
    if (position < 0 || position > count)//position = 0, count = 0
        return Error_Code::range_error;
    Node<T>* new_node, *previous, *following;
    if (position > 0)
    {
        previous = set_position (position - 1);
        following = previous->next;
    }
    else
        following = head;
    new_node = new Node<T>(item, following, previous);
    if (new_node == nullptr)
        return overflow;
    if (position == 0)
        head = new_node;
    else
        previous->next = new_node;
    count++;
    return success;
}
//Xoá dữ liệu ở vị trí bất kì trong List:
template<class T> Error_Code List<T>::Remove (int position, T& item){
    Node<T>* q, *previous;

    if (position < 0 || position >= count)
        return Error_Code::range_error;

    if (position > 0)
    {
        previous = set_position (position - 1);
        q = previous->next;
    }
    else
        q = head;

    if (position == 0)
        head = q->next;
    else
        previous->next = q->next;

    item = q->data;
    delete q;

    count--;

    return success;
}
//Xoá phần tử đầu List:
template<class T> Error_Code List<T>::RemoveFront (T& item){
    Remove(0, item);
    return success;
}
//Xoá phần tử cuối List:
template<class T> Error_Code List<T>::RemoveBack (T& item){
    Remove(count-1, item);
    return success;
}
//Thêm dữ liệu vào sau List:
template<class T> Error_Code List<T>::PushBack ( T item){
	Node<T>* new_node = new Node<T>();
    new_node->data = item;
    new_node->next = nullptr;
    new_node->previous = nullptr;
    if(head == nullptr)
		(head) = new_node;
	else
	{
		Node<T>* ptemp= head;
		while (ptemp->next!=nullptr)
			ptemp = ptemp->next;
        new_node->previous = ptemp;
		ptemp->next= new_node;
	}
    count++;
	return success;
}
//Thêm dữ liệu vào đầu List:
template<class T> Error_Code List<T>::PushFront ( T item){
	Node<T>* new_node = new Node<T>();
    new_node->data = item;
    new_node->next = head;
    new_node->previous = nullptr;
    if(head == nullptr)
		(head) = new_node;
	else
	{
		head->previous = new_node;
        head = new_node;
	}
    count++;
	return success;
}
//Lấy giá trị ở phần tử đầu List:
template<class T> T List<T>::GetFront (){
	if (head == nullptr)
    {
        return "No value exists";
    }else
        return head->data;
}
//Lấy giá trị ở phần tử cuối List:
template<class T> T List<T>::GetBack (){
    Node<T>* ptemp= head;
	if(head == nullptr)
		return "No value exists";
	else
	{
		while (ptemp->next!=nullptr)
			ptemp = ptemp->next;
	}
	return ptemp->data;
}
//Lấy giá trị ở vị trí bất kì trong List:
template<class T> T List<T>::GetValueAt (int position){
    if (head == nullptr)
    {
        return "No value exists";
    }
    if (position < 0 || position > count)//position = 0, count = 0
        return "No value exists";
    Node<T>* ptemp;
    if (position > 0)
    {
        ptemp = set_position (position - 1);
        return ptemp->data;
    }
    if (position == 0)
        return head->data;
    return "No value exists";
}
//In ra toàn bộ List:
template<class T> Error_Code List<T>::PrintList (){
    Node<T> *tmp = head;
	while (tmp != NULL)
    {
        cout << tmp->data << " ";
        tmp = tmp->next;
    }
    cout << "\n";
	return success;
}
//Đảo ngược List:
template<class T> Error_Code List<T>::Reverse () {
    //khởi tạo Node hiện tại:
    Node<T>* current = head;
    //khởi tạo Node trước Node hiện tại:
    Node<T>* prev = NULL;
    //hởi tạo Node sau Node hiện tại:
    Node<T>* next = NULL;
    //Duyệt:
    while (current != NULL) {
        //Gắn next bằng node phía sau node hiện tại
        next = current->next;
        //Gắn con trỏ next của node hiện tại về node phía sau nó
        current->next = prev;
        //Gắn node phía sau bằng node hiện tại
        prev = current;
        //Gắn node hiện tại bằng node phía sau
        current = next;
    }
    //Gắn lại node:
    head = prev;
    return success;
}