#include<iostream>
using namespace std;

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight) {}
		~Element() { cout << "EDestructor: " << this << endl; }
		friend class Tree;

	}*Root;
public:
	int counter;
	Element* getRoot()const
	{
		return Root;
	}
	Tree() { this->Root = nullptr; }
	Tree(const initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			insert(*it, this->Root);
		}
	}
	~Tree()
	{
		clear(Root);
		cout << "TDestructor: " << this << endl;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	void print()const
	{
		print(this->Root);
		cout << endl;
	}
	int count()const
	{
		return count(this->Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}

private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight)insert(Data, Root->pRight);
			else Root->pRight = new Element(Data);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr) return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == nullptr && Root->pRight == nullptr)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root)const
	{
		/*if (Root->pLeft == nullptr) return Root->Data;
		else return minValue(Root->pLeft);*/
		return Root->pLeft ? minValue(Root->pLeft) : Root->Data;
	}
	int maxValue(Element* Root)const
	{
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int count(Element* Root)const
	{
		return Root ? count(Root->pLeft) + count(Root->pRight) + 1 : 0;
	}
	int sum(Element* Root)const
	{
		return Root ? sum(Root->pLeft) + sum(Root->pRight) + Root->Data : 0;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Enter the tree's size : "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << "Min Value in tree: " << tree.minValue() << endl;
	cout << "Max Value in tree: " << tree.maxValue() << endl;
	cout << "Count of Value in tree: " << tree.count() << endl
	cout << "Sum of Value in tree: " << tree.sum() << endl;
	cout << "Average Value in tree: " << tree.avg() << endl;
#endif // BASE_CHECK

	Tree tree = { 50,25,80,16,32,64,85,58,75,84,91 };
	tree.print();
	int n;
	cout << "Enter the deleting Value : " << endl;
	cin >> n;
	tree.erase(n);
	tree.print();
}