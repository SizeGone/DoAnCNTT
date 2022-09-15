enum Error_Code {success, overflow, range_error};

template <class T> class Node
{
    public:
    T data;
    Node<T> * next;
    Node<T> * previous;
    // public:
        Node();
        Node(T item, Node<T> * linkNext=nullptr, Node<T>* linkPrevious=nullptr);
};

template <class T> class List
{
    protected:
        unsigned short int count;
        Node<T>* head;
        Node<T>* set_position(int position)const;
    public:
        List();
        ~List();
        void Clear ();
        bool IsEmpty () const;
        unsigned short int Size () const;
        Error_Code Replace (int position, const T& item);
        Error_Code Retrieve (int position,T& item)const;
        Error_Code Insert (int position, const T& item);
        Error_Code Remove (int position, T& item);
};

// Implement NODE
template<class T> Node<T>::Node()
{
    next = nullptr;
    previous = nullptr;
}

template<class T> Node<T>::Node(T item, Node<T> * linkNext, Node<T>* linkPrevious)
{
    data = item;
    next = linkNext;
    previous = linkPrevious;
}

// Implement LIST
template<class T> Node<T>* List<T>::set_position(int position) const
{
    Node* q = head;
     for (int i=0; i<position; i++)
        q = q->next;
    return q;
}

template<class T> List<T>::List()
{
    count = 0;
    head = nullptr;
}

template<class T> List<T>::~List()
{
    clear();
}

template<class T> void List<T>::Clear()
{
    Node* tmp;
    while (head != nullptr)
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    count = 0;
}

template<class T> bool List<T>::IsEmpty() const
{
    return count == 0;
}

template<class T> unsigned short int List<T>::Size() const
{
    return count;
}

template<class T> Error_Code List<T>::Replace (int position, const T& item)
{
    if (position < 0 || position > count)
        return range_error;
    Node* tmp = set_position(position);
    tmp->data = item;
    return success;
}

template<class T> Error_Code List<T>::Retrieve (int position,T& item) const
{
    if (position < 0 || position > count)
        return range_error;
    Node* tmp = set_position(position);
    item = tmp->data;
    return success;
}