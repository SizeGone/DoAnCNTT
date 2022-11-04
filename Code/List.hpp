typedef int List_entry;
typedef int Node_entry;
enum Error_Code {success, overflow, range_error};

/* cac cau truc du lieu chinh cua chuong trinh */
template <class T> struct NodeEx {
	T info;
	NodeEx<T> * next;
};

template <class T> struct EWord {
	T word;
	T type;
	T mean[5];
	NodeEx<T> * first;
	EWord();	
};

template <class T> struct Node {
	EWord<T>* data;
	Node<T> * next;
	Node<T> * previous;
	Node();
	Node(EWord<T>* item, Node<T> * linkNext=nullptr, Node<T>* linkPrevious=nullptr);
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
		Error_Code Replace (int position, EWord<T>* item);
		Error_Code Retrieve (int position,EWord<T>** item)const; 
		Error_Code Reverse ();
		Error_Code Insert (int position, EWord<T>* item);
		Error_Code Remove (int position, T& item);
		Error_Code PushBack (EWord<T> *item);
		Error_Code PushFront (EWord<T>* item); //need to used
		Error_Code PrintList (); //need to used
		EWord<T>* GetFront (); //need to used
		EWord<T>* GetBack (); //need to used
		T GetValueAt(int position);
		Error_Code RemoveFront (T& item); //need to used
		Error_Code RemoveBack (T& item);//need to used
		Node<T> * GetHead();
};
