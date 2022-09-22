typedef int List_entry;
typedef int Node_entry;
enum Error_Code {success, overflow, range_error};

template <class T> struct Node {
	T data;
	Node<T> * next;
	Node<T> * previous;
	Node();
	Node(T item, Node<T> * linkNext=nullptr, Node<T>* linkPrevious=nullptr);
};

template <class T> class List {
	protected:
		unsigned short int count = 0;
		Node<T>* head;
		Node<T>* set_position(int position)const;
	public:
		List();
		~List();
		void Clear ();
		bool IsEmpty () const;
		unsigned short int Size () const;
		//Method:
		Error_Code Replace (int position, const T& item);
		Error_Code Retrieve (int position,T& item)const;
		Error_Code Reverse ();
		Error_Code Insert (int position, T item);
		Error_Code Remove (int position, T& item);
		Error_Code PushBack (T item);
		Error_Code PushFront (T item);
		Error_Code PrintList ();
		T GetFront ();
		T GetBack ();
		T GetValueAt(int position);
		Error_Code RemoveFront (T& item);
		Error_Code RemoveBack (T& item);
};
