#include <vector>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

//----------------------------------------------------//
// nodes for binary trees                             //
//----------------------------------------------------//
struct Node;
typedef Node *node_pointer;
struct Node
{
	// you can add attributes here
	char c;
	int weight; //depth
	int pos;
	node_pointer left;
	node_pointer right;

	Node() {}
	Node(char c, int f, int p, node_pointer l = nullptr, node_pointer r = nullptr) : c(c), weight(f), pos(p), left(l), right(r) {}
};

// Max heap
struct MaxHeap
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
		if (i && arr[parent(i)]->weight == arr[i]->weight)
		{
			if (arr[parent(i)]->pos > arr[i]->pos)
			{
				swap(arr[parent(i)], arr[i]);
				swim(parent(i));
			}
		}
		else if (i && arr[parent(i)]->weight < arr[i]->weight)
		{
			swap(arr[parent(i)], arr[i]);
			swim(parent(i));
		}
	}

	void sink(int i)
	{
		int l = leftChild(i);
		int r = rightChild(i);
		int max = i;
		if (l < size() && arr[l]->weight == arr[max]->weight)
		{
			if (arr[l]->pos < arr[max]->pos)
			{
				max = l;
			}
		}
		else if (l < size() && arr[l]->weight > arr[max]->weight)
		{
			max = l;
		}

		if (r < size() && arr[r]->weight == arr[max]->weight)
		{
			if (arr[r]->pos < arr[max]->pos)
			{
				max = r;
			}
		}
		else if (r < size() && arr[r]->weight > arr[max]->weight)
		{
			max = r;
		}

		if (max != i)
		{
			swap(arr[max], arr[i]);
			sink(max);
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

	void push(char c, int depth, int pos, node_pointer l = nullptr, node_pointer r = nullptr)
	{
		Node *t = new Node(c, depth, pos, l, r);
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

// add your code here

void prefixDecode(Node *t, string code)
{
	string copy = code;
	Node *top = t;
	Node *tracer = t;
	while (copy.length() > 0)
	{
		if (tracer->left == nullptr && tracer->right == nullptr)
		{
			cout << tracer->c;
			tracer = top;
		}
		else
		{
			if (copy[0] == '0')
			{
				if (tracer->left != nullptr)
				{
					tracer = tracer->left;
					copy = copy.substr(1);
				}
				else
				{
					cout << tracer->c;
					tracer = top;
				}
			}
			if (copy[0] == '1')
			{
				if (tracer->right != nullptr)
				{
					tracer = tracer->right;
					copy = copy.substr(1);
				}
				else
				{
					cout << tracer->c;
					tracer = top;
				}
			}
		}
	}
	cout << tracer->c << endl;
}

bool isNumber(char n)
{
	return n >= 48 && n <= 57;
}

void decode(string tree, string code)
{
	MaxHeap q;
	int pos_counter = 0;
	string num = "";
	int i = 0;
	while (i < tree.length())
	{
		if (tree[i] == ' ' && i != 0 && !isNumber(tree[i + 1]))
		{
			i = i + 1;
			num = "";
		}
		else
		{
			int j = i + 1;
			while (j < tree.length() && isNumber(tree[j]))
			{
				num = num + tree[j];
				j = j + 1;
			}
			q.push(tree[i], stoi(num), pos_counter);
			pos_counter = pos_counter + 1;
			num = "";
			i = j + 1;
		}
	}

	while (q.size() > 1)
	{
		Node *t1 = q.top();
		int depth1 = t1->weight;
		int pos1 = t1->pos;
		q.pop();
		Node *t2 = q.top();
		int depth2 = t2->weight;
		int pos2 = t2->pos;
		q.pop();
		int minPos = pos1;
		if (pos2 < minPos)
		{
			minPos = pos2;
		}
		q.push('0', depth1 - 1, minPos, t1, t2);
	}

	Node *t = q.top();
	prefixDecode(t, code);
}

//----------------------------------------------------//
// main                                               //
//----------------------------------------------------//
int main()
{
	string tree, code;
	getline(cin, tree);
	getline(cin, code);
	// add your code here
	decode(tree, code);
}
