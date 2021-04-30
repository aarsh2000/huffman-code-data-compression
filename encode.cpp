#include <iostream>
#include <string>
#include <vector>

using namespace std;

//----------------------------------------------------//
// nodes for binary trees                             //
//----------------------------------------------------//
struct Node;
typedef Node *node_pointer;
struct Node
{
	char c;
	int weight;
	node_pointer left;
	node_pointer right;
	string word;
	Node() {}
	Node(char c, int f, node_pointer l = nullptr, node_pointer r = nullptr, node_pointer p = nullptr)
		: c(c), weight(f), left(l), right(r) {}
};

// Min heap
struct MinHeap
{
private:
	vector<Node *> arr;

	int leftChild(int i)
	{
		return (2 * i + 1);
	}

	int rightChild(int i)
	{
		return (2 * i + 2);
	}

	int parent(int i)
	{
		return (i - 1) / 2;
	}

	void swap(Node *a, Node *b)
	{
		Node tmp = *a;
		*a = *b;
		*b = tmp;
	}

	void swim(int i)
	{
		if (i && arr[parent(i)]->weight > arr[i]->weight)
		{
			swap(arr[parent(i)], arr[i]);
			swim(parent(i));
		}
	}

	void sink(int i)
	{
		int l = leftChild(i);
		int r = rightChild(i);
		int min = i;

		if (l < size() && arr[l]->weight < arr[min]->weight)
		{
			min = l;
		}

		if (r < size() && arr[r]->weight < arr[min]->weight)
		{
			min = r;
		}

		if (min != i)
		{
			swap(arr[min], arr[i]);
			sink(min);
		}
	}

public:
	int size()
	{
		return arr.size();
	}

	Node *top()
	{
		if (size() > 0)
		{
			return arr.at(0);
		}
		return nullptr;
	}

	void push(char c, int weight, node_pointer l = nullptr, node_pointer r = nullptr)
	{
		Node *t = new Node(c, weight, l, r, nullptr);
		arr.push_back(t);
		swim(size() - 1);
	}

	void pop()
	{
		if (size() > 0)
		{
			arr[0] = arr.back();
			arr.pop_back();
			sink(0);
		}
	}
};

void setAllLeaves(vector<Node *> *L, Node *t, int depth = 0, string w = "")
{
	if (t == nullptr)
		return;
	if (t->left == nullptr && t->right == nullptr)
	{
		t->word = w;
		L->at(t->c) = t;
		cout << t->c << depth << " ";
	}

	if (t->left != nullptr)
	{
		setAllLeaves(L, t->left, depth + 1, w + "0");
	}

	if (t->right != nullptr)
	{
		setAllLeaves(L, t->right, depth + 1, w + "1");
	}
}

void prefixEncode(Node *t, string s)
{
	vector<Node *> L(255, nullptr);
	setAllLeaves(&L, t);
	cout << endl;

	while (s.length() > 0)
	{
		string w = "";
		Node *v = L[s[0]];
		s = s.substr(1);
		cout << v->word;
	}
	cout << endl;
}

void encode(string s)
{
	const int NUM_CHARACTER = 255;
	vector<int> f(NUM_CHARACTER, 0);

	for (int i = 0; i < s.length(); ++i)
	{
		f[int(s[i])]++;
	}

	MinHeap q;

	for (int i = 0; i < NUM_CHARACTER; ++i)
	{
		if (f[i] > 0)
		{
			q.push(i, f[i]);
		}
	}

	while (q.size() > 1)
	{
		Node *t1 = q.top();
		int f1 = t1->weight;
		q.pop();
		Node *t2 = q.top();
		int f2 = t2->weight;
		q.pop();
		q.push(0, f1 + f2, t1, t2);
	}

	Node *t = q.top();
	prefixEncode(t, s);
}

// add your code here

//----------------------------------------------------//
// main                                               //
//----------------------------------------------------//
int main()
{
	string text;
	getline(cin, text);
	encode(text);
}
