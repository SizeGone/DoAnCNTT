#include <iostream>
#include "List.hpp"
using namespace std;


//Implement EWord
template <class T>
EWord<T>::EWord(){
}
// Implement NODE
template <class T>
Node<T>::Node()
{
    next = nullptr;
    previous = nullptr;
}

template <class T>
Node<T>::Node(EWord<T>* item, Node<T> *linkNext, Node<T> *linkPrevious)
{
    data = item;
    next = linkNext;
    previous = linkPrevious;
}

// Implement LIST
template <class T>
Node<T> *List<T>::set_position(int position) const
{
    Node<T> *q = head;
    for (int i = 0; i < position; i++)
        q = q->next;
    return q;
}

template <class T>
List<T>::List()
{
    count = 0;
    head = nullptr;
}

template <class T>
List<T>::~List()
{
    Clear();
}

template <class T>
void List<T>::Clear()
{
    Node<T> *tmp;
    while (head != nullptr)
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    count = 0;
}

template <class T>
bool List<T>::IsEmpty() const
{
    return count == 0;
}

template <class T>
unsigned short int List<T>::Size() const
{
    return count;
}
//Thay đổi data ở vị trí position trong list
template <class T>
Error_Code List<T>::Replace(int position, EWord<T>* item)
{
    if (position < 0 || position > count)
        return Error_Code::range_error;
    Node<T> *tmp = set_position(position);
    tmp->data = item;
    return success;
}
//Lấy giá trị tại pos 
template <class T>
Error_Code List<T>::Retrieve(int position, Node<T>** item) const
{
    if (position < 0 || position > count)
        return Error_Code::range_error;
    Node<T> *tmp = set_position(position-1);
    *item = tmp;
    return success;
}
// Chèn dữ liệu mới vào vị trí bất kì trong List:
template <class T>
Error_Code List<T>::Insert(int position, EWord<T>* item)
{
    if (position < 0 || position > count) // position = 0, count = 0
        return Error_Code::range_error;
    Node<T> *new_node, *previous, *following;
    if (position > 0)
    {
        previous = set_position(position - 1);
        following = previous->next;
    }
    else
        following = head;
    new_node = new Node<T>(item, following, previous);
    following->previous = new_node;
    if (new_node == nullptr)
        return overflow;
    if (position == 0)
        head = new_node;
    else
        previous->next = new_node;
    count++;
    return success;
}
// Xoá dữ liệu ở vị trí bất kì trong List:
template <class T>
Error_Code List<T>::Remove(int position, T &item)
{
    Node<T> *q, *previous;

    if (position < 0 || position > count)
        return Error_Code::range_error;

    if (position > 0)
    {
        previous = set_position(position - 1);
        q = previous->next;
    }
    else
        q = head;

    if (position == 0)
        head = q->next;
    else
    {
        previous->next = q->next;
        q->next->previous = previous;
    }
    item = q->data->word;
    delete q;
    count--;
    return success;
}
// Xoá phần tử đầu List:
template <class T>
Error_Code List<T>::RemoveFront(T &item)
{
    Node<T> *q = head;
    head = head->next;
    head->previous = nullptr;
    item = q->data->word;
    delete q;
    count--;
    return success;
}
// Xoá phần tử cuối List:
template <class T>
Error_Code List<T>::RemoveBack(T &item)
{
    Node<T> *q = set_position(count - 1);
    q->previous->next = nullptr;
    item = q->data->word;
    delete q;
    count--;
    return success;
}
// Thêm dữ liệu vào sau List:
template <class T>
Error_Code List<T>::PushBack(EWord<T> *item)
{
    Node<T> *new_node = new Node<T>();
    new_node->data = item;
    new_node->next = nullptr;
    new_node->previous = nullptr;
    if (head == nullptr)
        (head) = new_node;
    else
    {
        Node<T> *ptemp = head;
        while (ptemp->next != nullptr)
            ptemp = ptemp->next;
        new_node->previous = ptemp;
        ptemp->next = new_node;
    }
    count++;
    return success;
}
// Thêm dữ liệu vào đầu List:
template <class T>
Error_Code List<T>::PushFront(EWord<T>* item)
{
    Node<T> *new_node = new Node<T>();
    new_node->data = item;
    new_node->next = head;
    new_node->previous = nullptr;
    if (head == nullptr)
        (head) = new_node;
    else
    {
        head->previous = new_node;
        head = new_node;
    }
    count++;
    return success;
}
// Lấy giá trị ở phần tử đầu List:
template <class T>
EWord<T>* List<T>::GetFront()
{
    if (head == nullptr)
    {
        return nullptr;
    }
    else
        return head->data;
}
// Lấy giá trị ở phần tử cuối List:
template <class T>
EWord<T>* List<T>::GetBack()
{
    Node<T> *ptemp = head;
    if (head == nullptr)
        return nullptr;
    else
    {
        while (ptemp->next != nullptr)
            ptemp = ptemp->next;
    }
    return ptemp->data;
}
// Lấy giá trị ở vị trí bất kì trong List:
template <class T>
T List<T>::GetValueAt(int position)
{
    if (head == nullptr)
    {
        return "No value exists";
    }
    if (position < 0 || position > count) // position = 0, count = 0
        return "No value exists";
    Node<T> *ptemp;
    if (position > 0)
    {
        ptemp = set_position(position-1);
        return ptemp->data->word;
    }
    if (position == 0)
        return head->data->word;
    return "No value exists";
}
// In ra toàn bộ List:
template <class T>
Error_Code List<T>::PrintList()
{
    Node<T> *tmp = head;
    while (tmp != nullptr)
    {
        cout << tmp->data->word << " ";
        cout << "\n";
        tmp = tmp->next;
    }
    cout << "\n";
    return success;
}
//Đảo ngược List:
template <class T>
Error_Code List<T>::Reverse()
{
    Node<T> *temp = nullptr;
    Node<T> *current = head;

    // Đổi chỗ next và previous
    while (current != nullptr)
    {
        temp = current->previous;
        current->previous = current->next;
        current->next = temp;
        current = current->previous;
    }
    if (temp != nullptr)
        head = temp->previous;
    return success;
}

template <class T>
Node<T> * List<T>::GetHead()
{
    return head;
}
