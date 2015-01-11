#include "Node.h"


int main(int argc, char** argv)
{
	int sprout = atoi(argv[1]);
	
	std::vector<Node*> tree;
	Node *rootNode = new Node();
	tree.push_back(rootNode);
	
	int blah;
	//std::cin >> blah;
	//genChild(rootNode, 6, 1);
	//genChild(tree, 5, 1);
	genChild(tree, sprout, 1);

	printTree(rootNode, 5);
	//std::cin >> blah;
}
