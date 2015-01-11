#include <iostream>
#include <iomanip>
#include <vector>


struct Node{
	int value;
	int level;
	bool LR; //left = 1; right = 0
	bool visited;
	Node *parent;
	Node *leftChild;
	Node *rightChild;
		
	//Default
	Node()
	{
		visited = false;
		value = 1;
		level = 1;
		parent = NULL;
		leftChild = NULL;
		rightChild = NULL;
	}
	Node(int v, int lvl, Node* p)
	{
		visited = false;
		value = v;
		level = lvl;
		parent = p;
		leftChild = NULL;
		rightChild = NULL;
	}
};

//Global variables
int loops = 0;
Node *zeroNode = new Node(0, 0, NULL);

Node* findNeighbor(Node* n, bool b /*1 = left, 0 = right*/)
{
	Node *neighborNode;
	if(b)
	{
		//Mark visited
		n->visited = true;
		//Check if we can move left
		Node* parent = n->parent;
		if(parent)
		{
			if(parent->leftChild->visited)
			{
				//Unmark, move to parent
				n->visited = false;
				loops++;
				neighborNode = findNeighbor(parent, b);
			}
			else
			{
				//Move to left
				n->visited = false;
				n = parent->leftChild;
				//Then go right X-1 where X is # of times went up
				for(int i = 0; i < loops - 1; i++)
				{
					n = n->rightChild;
				}
				neighborNode = n;
				return neighborNode;
			}
		}
		else
		{
			loops = 0;
			n->visited = false;
			return zeroNode;
		}
	}
	else
	{
		//Mark visited
		n->visited = true;
		//Check if we can move right
		Node* parent = n->parent;
		if(parent)
		{
			if(parent->rightChild->visited)
			{
				//Unmark, move to parent
				n->visited = false;
				loops++;
				neighborNode = findNeighbor(parent, b);
			}
			else
			{
				//Move to right
				n->visited = false;
				n = parent->rightChild;
				//Then go left X-1 where X is # of times went up
				for(int i = 0; i < loops - 1; i++)
				{
					n = n->leftChild;
				}
				neighborNode = n;
				return neighborNode;
			}
		}
		else
		{
			loops = 0;
			n->visited = false;
			return zeroNode;
		}
	}
	return neighborNode;
}


std::pair<Node*, Node*> returnNeighbors(Node* n)
{
	Node *left, *right;
	//Given a node, find its neighbors
	//Left neighbor
	left = findNeighbor(n, 1);
	//Right neighbor
	right = findNeighbor(n, 0);
	return std::pair<Node*, Node*>(left, right);
}


void printTree(Node* n, int indent=0)
{
	if(n != NULL)
	{
		std::cout << n->value << "\n ";
		if(indent)
		{
			std::cout << std::setw(indent) << ' ';
		}
		if(n->leftChild)
		{
			printTree(n->leftChild, indent+4);
		}
		if(n->rightChild)
		{
			printTree(n->rightChild, indent+4);
		}
	}
}

void genChild(Node* parent, int levels, int j)
{
	std::vector<Node*> children;
	for(int i = j; i < levels; i++)
	{
		if(parent->leftChild && parent->rightChild)
		{
			//genChild(parent->leftChild, levels, i);
			//genChild(parent->rightChild, levels, i);

			//foreach item in list, genchild(item)
			for(Node* c : children)
			{
				genChild(c, levels, i);
			}
			//Clear
			children.clear();
		}
		else
		{
			std::pair<Node*, Node*> results = returnNeighbors(parent);
			int lValue = parent->value + results.first->value;
			parent->leftChild = new Node(lValue, i+1, parent);

			int rValue = parent->value + results.second->value;
			parent->rightChild = new Node(rValue, i+1, parent);

			//Add
			children.push_back(parent->leftChild);
			children.push_back(parent->rightChild);
		}
	}
}

void genChild(std::vector<Node*> parents, int levels, int j)
{
	std::vector<Node*> children;
	for(int i = 0; i < parents.size(); i++)
	{
		int lValue = parents[i]->value, rValue = parents[i]->value;
		//Left neighbor
		if((i-1) >= 0)
		{
			lValue += parents[i-1]->value;
		}
		//Right neighbor
		if((i+1) < parents.size())
		{
			rValue += parents[i+1]->value;
		}
		parents[i]->leftChild = new Node(lValue, parents[i]->level + 1, parents[i]);
		parents[i]->rightChild = new Node(rValue, parents[i]->level + 1, parents[i]);
			
		//std::cout << "L: " << lValue << ", R: " << rValue << std::endl;

		children.push_back(parents[i]->leftChild);
		children.push_back(parents[i]->rightChild);
	}
	j++;
	if(j < levels)
	{
		genChild(children, levels, j);
		//std::cout << "j: " << j << std::endl;
	}
}