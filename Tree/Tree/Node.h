#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>


/*A node knows the following things:
	Its value
	The level of the tree it's in
	Its parent node
	Its left and right children nodes
*/
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
		parent = NULL;
		leftChild = NULL;
		rightChild = NULL;
	}
	//Parameters for value, the level it's at, and the parent node
	Node(int v, int lvl, Node* p)
	{
		value = v;
		level = lvl;
		parent = p;
		leftChild = NULL;
		rightChild = NULL;
	}
};

//Parameters:  List of parents at a level, total depth of the tree, index of 1
void printTree(std::vector<Node*> parents, int depth, int j)
{
	//Arbitrary indentation formula to make the tree print out nicely
	int indent = pow(2, depth) / pow(2, j-1);
	//If we hit the total depth of the tree, then we stop, otherwise keep printing values
	if(j <= depth)
	{
		//Vector for storing children in a list to eventually pass in again in a recursive call
		std::vector<Node*> children;
		//Print out arbitrary amount of spaces, the parent's value, then the spaces again
		for(int i = 0; i < parents.size(); i++)
		{
			for(int j = 0; j < indent; j++)
			{
				std::cout << "--";
			}
			std::cout  << parents[i]->value;
			for(int j = 0; j < indent; j++)
			{
				std::cout <<  "--";
			}

			//Add the current parent's children to the list
			children.push_back(parents[i]->leftChild);
			children.push_back(parents[i]->rightChild);
		}
		//Next line for next level, increment index, recursive call
		std::cout << std::endl;
		j++;
		printTree(children, depth, j);
	}
}

//Parameters:  List of parents at a level, total depth of the tree, index of 1
void writeTree(std::vector<Node*> parents, int depth, int j)
{
	//Arbitrary indentation formula to make the tree print out nicely
	int indent = pow(2, depth) / pow(2, j-1);
	//File writing
	std::ofstream output("tree.txt", std::ios::app);
	//If we hit the total depth of the tree, then we stop, otherwise keep printing values
	if(j <= depth)
	{
		//Vector for storing children in a list to eventually pass in again in a recursive call
		std::vector<Node*> children;
		//Print out arbitrary amount of spaces, the parent's value, then the spaces again
		for(int i = 0; i < parents.size(); i++)
		{
			for(int j = 0; j < indent; j++)
			{
				output << "..";
			}
			output << parents[i]->value;
			for(int j = 0; j < indent; j++)
			{
				output << "..";
			}
			//Add the current parent's children to the list
			children.push_back(parents[i]->leftChild);
			children.push_back(parents[i]->rightChild);
		}
		//Next line for next level, increment index, recursive call
		output << "\n";
		j++;
		writeTree(children, depth, j);
	}
	output << "\n";
	output.close();
}

//Parameters: A list of all parents at that level, how many levels in the tree total, index of 1
void genChild(std::vector<Node*> parents, int levels, int j)
{
	//If index >= levels, we've made enough branches, so stop
	if(j < levels)
	{
		//Vector for storing all children at a level to eventually pass in again in a recursive call
		std::vector<Node*> children;
		//For every parent in the vector, find the values and make children
		for(int i = 0; i < parents.size(); i++)
		{
			int lValue = parents[i]->value, rValue = parents[i]->value;
			//Left neighbor is the node before it in the vector, and right neighbor is the node right after it
			//If not applicable, the value is simply the parent's value
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
			//Making the children nodes
			parents[i]->leftChild = new Node(lValue, parents[i]->level + 1, parents[i]);
			parents[i]->rightChild = new Node(rValue, parents[i]->level + 1, parents[i]);

			//Add the children to the vector (left to right order)
			children.push_back(parents[i]->leftChild);
			children.push_back(parents[i]->rightChild);
		}
		//Increase the index (so we know when to stop), and then recursive call
		j++;
		genChild(children, levels, j);
	}
}