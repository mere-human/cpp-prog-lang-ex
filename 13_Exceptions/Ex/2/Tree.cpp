/*
[2] (*3) Write a function that searches a binary tree of nodes based on a char*
field for a match. If a node containing hello is found, find("hello") will
return a pointer to that node. Use an exception to indicate "not found."
*/

#include <string>
#include <list>
#include <iostream>

struct TreeNode
{
	std::string str;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;

	TreeNode(const std::string& s) : str{ s }
	{}
};

void find(TreeNode* p, const std::string& s)
{
	if (p->str == s) throw p;
	if (p->left) find(p->left, s);
	if (p->right) find(p->right, s);
}

void print_node(TreeNode* p)
{
	std::cout << p->str << " at " << p << "\n";
}

int main()
{
	std::list<TreeNode> nodes;

	nodes.push_back(TreeNode{ "world" });
	TreeNode* root = &nodes.back();
	print_node(root);

	nodes.push_back(TreeNode{ "hello" });
	root->left = &nodes.back();
	print_node(root->left);

	nodes.push_back(TreeNode{ "!" });
	root->right = &nodes.back();
	print_node(root->right);

	try
	{
		find(root, "hello");
	}
	catch (TreeNode* p)
	{
		std::cout << "found: ";
		print_node(p);
	}

	try
	{
		find(root, "hey");
		std::cout << "not found\n";
	}
	catch (TreeNode* p)
	{
		std::cout << "found: ";
		print_node(p);
	}

	return 0;
}