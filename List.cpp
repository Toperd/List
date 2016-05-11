#include <iostream>

using namespace std;

ostream& operator<<(ostream& o, string& s)
{
    o << s.c_str();
    return o;
}
 
istream& operator>>(istream& i, string& s)
{
    char buf[256];
    i >> buf;
    string tmp(buf);
    s = tmp;   
    return i;
}
template<typename T>
class AbstractList
{
protected:
	T _default;
public:
	virtual void sort(bool (*f)(T* first, T* second)) = 0;
	virtual T get(int index) = 0;
	virtual void set(int index, T data) = 0;	//óñòàíàâëèâàåò çíà÷åíèå â ýëåìåíò index
	virtual void insert(int index, T data) = 0;	//äîáàâëÿåò ýëåìåíò ïåðåä ýëåìåíòîì index
	virtual T remove(int index) = 0;
	virtual int len() = 0;
	virtual bool empty()
	{
		return this->len() == 0;
	}
	virtual void push(T data)
	{
		this->insert(0, data);
	}
	virtual T pop()
	{
		if(this->empty())
		{
			return _default;
		}
		else
		{
			return this->remove(0);
		}
	}
	virtual ostream& print(ostream& o)
	{
		for(int i = 0; i < this->len(); i++)
		{
			o << this->get(i) << '\n';
		}
		return o;
	}
	virtual istream& read(istream& in)
	{
		int count;
		in >> count;
		T tmp;
		for(int i = 0; i < count; i++)
		{
			in >> tmp;
			this->insert(this->len(), tmp);
		}
		return in;
	}	
};

template<typename T>
class List : public AbstractList<T>
{
	T data;
	List* next;
	List(T data)
	{
		this->data = data;
		this->next = NULL;
	}
public:
	List(T def, T data, bool empty)
	{
		if(empty)
		{
			this->data = def;
			this->next = new List(def);
		}
		else
		{
			this->data = def;
			this->next = new List(data);
			this->next->next = new List(def);
		}
	}
	~List()
	{}
	int len()
	{
		List* now = this->next;
		int l = 0;
		while(now->next != NULL)
		{
			now = now->next;
			l += 1;
		}
		return l;
	}
	void set(int index, T data)
	{
		if(index < 0)
		{
			index = 0;
		}
		if(index > this->len() - 1)
		{
			index = this->len() - 1;
		}
		List* now = this->next;
		for(int i = 0; i < index; i++)
		{
			now = now->next;
		}
		now->data = data;
	}
	void insert(int index, T data)
	{		
		if(index < 0)
		{
			index = 0;
		}
		if(index > this->len())
		{
			index = this->len();
		}
		List* now = this->next;
		List* prev = this;
		for(int i = 0; i < index; i++)
		{
			prev = now;
			now = now->next;
		}
		List* add = new List(data);
		prev->next = add;
		add->next = now;
	}
	T get(int index)
	{
		if(index < 0)
		{
			index = 0;
		}
		if(index > this->len() - 1)
		{
			index = this->len() - 1;
		}
		List* now = this->next;
		for(int i = 0; i < index; i++)
		{
			now = now->next;
		}
		return now->data;
	}
	T remove(int index)
	{
		if(index < 0)
		{
			index = 0;
		}
		if(index > this->len() - 1)
		{
			index = this->len() - 1;
		}
		List* now = this->next;
		List* prev = this;
		for(int i = 0; i < index; i++)
		{
			prev = now;
			now = now->next;
		}
		T tmp = now->data;
		prev->next = now->next;
		delete now;
		return tmp;
	}
	void swap_(int first, int second)
	{
		T tmp = this->get(first);
		this->set(first, this->get(second));
		this->set(second, tmp);
	}
	void sort (bool (*f)(T* first, T* second))
	{
		T a;
		T b;
		for(int i = 0; i < this->len(); i++)
		{
			for(int j = 0; j < this->len() - 1; j++)
			{
				a = (this->get(j));
				b = (this->get(j + 1));
				if(f(&a, &b))
				{
					this->swap_(j, j + 1);
				}
			}
		}
	}
};

List<string>* get_init() //
{
	List<string>* tmp = new List<string>("Empty", "1", true);
	return tmp;
}
/*bool criterion(int* first, int* second)
{
	return (*first) <= (*second);
}
int main()
{
	List<int>* test = get_init(12);
	test->insert(0, 2);
	test->insert(0, 9);
	test->insert(0, 5);
	test->insert(0, 25);	
	//cout << test->len() << '\n';
	test->print(cout);

	cout << '\n' << '\n';

	test->sort(criterion);
	test->print(cout);
	cout << '\n' << '\n';

	int s =	test->remove(3);
	cout << s << '\n';
	cout << '\n' << '\n';
	test->print(cout);

	for(int i = 0; i < 100000000; i++)
	{
		test->insert(0, 12);
		s = test->remove(0);
	}
	
	return 0;
}*/

