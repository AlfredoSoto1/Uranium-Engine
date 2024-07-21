#pragma once

namespace Uranium::DataStructures::Trees {

	template<class Element> class TreeNode {
	public:
		TreeNode(const Element& data);
		TreeNode(const Element& data, TreeNode* left, TreeNode* right);
		TreeNode(const Element& data, TreeNode* parent, TreeNode* left, TreeNode* right);
		virtual ~TreeNode();

		TreeNode* getLeft();
		TreeNode* getRight();
		TreeNode* getParent();

		Element* getData();

		bool isLeaf();

		void setLeft(TreeNode* left);
		void setRight(TreeNode* right);
		void setParent(TreeNode* parent);

	private:
		/*
		* private members
		*/
		TreeNode* left;
		TreeNode* right;
		TreeNode* parent;

		Element actualData;
	};

#define TREE_NODE(returnType) template<class Element> returnType TreeNode<Element>
	
	TREE_NODE()::TreeNode(const Element& data) :
		actualData(data),
		left(nullptr),
		right(nullptr),
		parent(nullptr)
	{

	}

	TREE_NODE()::TreeNode(const Element& data, TreeNode* left, TreeNode* right) :
		actualData(data),
		left(left),
		right(right),
		parent(nullptr)
	{

	}

	TREE_NODE()::TreeNode(const Element& data, TreeNode* parent, TreeNode* left, TreeNode* right) :
		actualData(data),
		left(left),
		right(right),
		parent(parent)
	{
	
	}

	TREE_NODE()::~TreeNode() {
	
	}

	TREE_NODE(void)::setLeft(TreeNode* left) {
		this->left = left;
	}

	TREE_NODE(void)::setRight(TreeNode* right) {
		this->right = right;
	}

	TREE_NODE(void)::setParent(TreeNode* parent) {
		this->parent = parent;
	}

	TREE_NODE(TreeNode<Element>*)::getLeft() {
		return left;
	}

	TREE_NODE(TreeNode<Element>*)::getRight() {
		return right;
	}

	TREE_NODE(TreeNode<Element>*)::getParent() {
		return parent;
	}

	TREE_NODE(Element*)::getData() {
		return &actualData;
	}

	TREE_NODE(bool)::isLeaf() {
		return left == nullptr && right == nullptr;
	}

}