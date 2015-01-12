#include "Node.h"


int main(int argc, char** argv)
{
	//Take in command line argument for how many levels to spawn
	int sprout = atoi(argv[1]);
	//int sprout = 4;
	
	//Vector to pass in to the methods, adding in the root node
	std::vector<Node*> tree;
	Node *rootNode = new Node();
	tree.push_back(rootNode);

	//Generate and then print the tree
	genChild(tree, sprout, 1);
	printTree(tree, sprout, 1);
	
	//File writing stuff
	writeTree(tree, sprout, 1);
}
