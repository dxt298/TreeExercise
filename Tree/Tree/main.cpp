#include <iostream>
#include <iomanip>
#include <vector>

struct Node{
	int value;
	int level;
	Node *parent;
	Node *leftChild;
	Node *rightChild;
		
	//Default
	Node()
	{
		value = 1;
		level = 1;
		parent = 0;
	}
	Node(int v, int lvl, Node* p)
	{
		value = v;
		level = lvl;
		parent = p;
		leftChild = NULL;
		rightChild = NULL;
	}
};

int findNeighbor(Node* n)
{
	//Given a node, find its neighbor
	return 0;
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
			printTree(n->leftChild, indent);
		}
		if(n->rightChild)
		{
			printTree(n->rightChild, indent);
		}

	}
}

int main(int argc, char** argv)
{
	int sprout = atoi(argv[1]);
	
	std::vector<Node*> tree;
	Node *rootNode = new Node();
	int level = 1;

	for(int i = 0; i < sprout; i++)
	{
		if(i == 0)
		{
			rootNode->leftChild = new Node(2, level, rootNode);
			rootNode->rightChild = new Node(3, level, rootNode);
		}
		else
		{

		}
		level++;
	}

	printTree(rootNode, 5);


	//for(int i = 0; i < sprout; i++)
	//{
	//	if(i == 0)
	//	{
	//		//Root node is always 1
	//		tree.push_back(new Node());
	//	}
	//	else
	//	{
	//		for(Node* n : tree)
	//		{
	//			if(n->level = level - 1)
	//			{
	//				n->leftChild = new Node(2, level, n);
	//				n->rightChild = new Node(3, level, n);

	//				tree.push_back(n->leftChild);
	//				tree.push_back(n->rightChild);
	//			}
	//		}
	//	}
	//	level++;
	//}

	//for(Node* n : tree)
	//{
	//	std::cout << n->value << std::endl;
	//}
}
