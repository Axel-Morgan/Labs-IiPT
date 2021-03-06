#include <iostream>

using namespace std;

template<typename typeGo>
class MyList
{
private:

	template<typename typeGo>
	class Node
	{
	public:

		typeGo data;
		Node *next;
		Node *prev;

		Node(typeGo data, Node *next, Node *prev)
		{
			this->data = data;
			this->next = next;
			this->prev = prev;
		}
	};

	size_t size;
	Node<typeGo> *head;
	Node<typeGo> *tail;


public:

	MyList()
	{
		size = 0;
		head = nullptr;
	}

	typeGo& operator[](const size_t index)
	{
		Node<typeGo> *cur;

		if (index <= size / 2)
		{
			cur = head;

			for (size_t i = 0; i < index; i++)
			{
				cur = cur->next;
			}

			return cur->data;
		}
		else
		{
			cur = tail;

			for (size_t i = size - 1; i > index; i--)
			{
				cur = cur->prev;
			}

			return cur->data;
		}
	}

	void Put(typeGo data)
	{
		if (head == nullptr)
		{
			head = new Node<typeGo>(data, nullptr, nullptr);
			tail = head;
		}
		else
		{
			Node<typeGo> *cur = new Node<typeGo>(data, nullptr, tail);
			tail->next = cur;
			tail = cur;
		}

		size++;
	}

	void Delete(size_t index)
	{

		if (index == 0)
		{
			Node<typeGo>* t = head;
			head = head->next;
			delete t;
			size--;
			return;
		}

		if (index == size - 1)
		{
			Node<typeGo>* t = tail;
			tail = tail->prev;
			delete t;
			size--;
			return;
		}

		Node<typeGo> *go;

		if (index < size / 2)
		{
			go = head;

			for (size_t i = 0; i < index; i++)
			{
				go = go->next;
			}

			go->prev->next = go->next;
			go->next->prev = go->prev;

			delete go;
		}
		else
		{
			go = tail;

			for (size_t i = size - 1; i > index; i--)
			{
				go = go->prev;
			}

			go->prev->next = go->next;
			go->next->prev = go->prev;

			delete go;
		}

		size--;
	}

	void Clear()
	{
		for (size_t i = 0; i < size; i++)
		{
			Node<typeGo> *t = head;
			head = head->next;
			delete t;
		}

		size = 0;
	}

	size_t Size()
	{
		return size;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");

	MyList<int> list;


	for (int i = 0; i < 10; i++)
	{
		list.Put(i);
	}

	for (size_t i = 0; i < list.Size(); i++)
	{
		cout << list[i];
	}

	list.Delete(5);

	for (size_t i = 0; i < list.Size(); i++)
	{
		cout << list[i];
	}

	list.Clear();
	list.Put(228);
	list.Put(12);
	list.Put(2546);

	for (size_t i = 0; i < list.Size(); i++)
	{
		cout << list[i];
	}

	std::cin.get();
	return 0;
}