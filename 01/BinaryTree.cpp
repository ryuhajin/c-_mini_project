#include <iostream>

typedef struct node *treePointer;

typedef struct node {
	int data;
	treePointer leftChild;
	treePointer rightChild;
} node;

// 전위 순회 1. 루트 2. 왼쪽 순회 3. 오른쪽 순회
void preorder(treePointer ptr) {
	if (ptr) {
		std::cout << "node: " << ptr->data << ' ';
		if (ptr->leftChild)
			std::cout << "left:" << ptr->leftChild->data << ' ';
		if (ptr->rightChild)
			std::cout << "right:" << ptr->rightChild->data << std::endl;
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

// 중위 순회 1. 왼쪽 순회 2. 루트 3. 오른쪽 순회
void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		std::cout << ptr->data << ' ';
		inorder(ptr->rightChild);
	}
}

// 후위 순회 1. 왼쪽 순회 2. 오른쪽 순회 3. 루트
void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		std::cout << ptr->data << ' ';
	}
}

void printOrder(node* nodes)
{
	std::cout << "================" << std::endl;
	std::cout << "preorder" << std::endl;
	std::cout << "================" << std::endl;
	preorder(nodes);

	std::cout << '\n' << std::endl;

	std::cout << "================" << std::endl;
	std::cout << "inorder" << std::endl;
	std::cout << "================" << std::endl;
	inorder(nodes);

	std::cout << '\n' << std::endl;

	std::cout << "================" << std::endl;
	std::cout << "postorder" << std::endl;
	std::cout << "================" << std::endl;
	postorder(nodes);

	std::cout << '\n' << std::endl;

}

int main(void)
{
	int number = 15;
	node nodes[number + 1];

	for (int i = 1; i <= number; i++)
	{
		nodes[i].data = i;
		nodes[i].leftChild = NULL;
		nodes[i].rightChild = NULL;
	}

	for (int i = 1; i <= number; i++)
	{
		if (i % 2 == 0)
			nodes[i / 2].leftChild = &nodes[i];
		else
			nodes[i / 2].rightChild = &nodes[i];
	}

	printOrder(&nodes[1]);
	return (0);
}
