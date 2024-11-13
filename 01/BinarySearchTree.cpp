/*
모든 원소는 유일한 키 값을 가진다.
왼쪽 서브트리의 모든 원소들은 루트의 키보다 작은 값을 갖는다.
오른쪽 서브트리의 모든 원소들은 루트의 키보다 큰 값을 갖는다.
왼쪽 서브트리와 오른쪽 서브트리도 이진탐색트리이다.
 -> 즉 어떤 노드를 루트로 잡던지 위 조건이 항상 참이 되어야 한다.
*/

//https://www.youtube.com/watch?v=ESqeK-ACHkU

#include <iostream>

typedef char data;

typedef struct Node {
	char key;
	struct Node* left;
	struct Node* right;
} node;

node* createNode(char x)
{
	node* newNode = new node;
	newNode->key = x;
	newNode->left = NULL;
	newNode->right = NULL;

	return (newNode);
}

// search (root, tofindKey)
node* searchBST(node* root, char x)
{
	node* ptr = root;
	while(ptr != NULL)
	{
		if (ptr->key == x) // 키를 찾았다면 노드 반환
			return (ptr);
		else if (ptr->key < x) // 키 값보다 x가 더 크면 노드의 오른쪽으로
			ptr = ptr->right;
		else // 키 값보다 x가 작으면 노드의 왼쪽으로
			ptr = ptr->left;
	}

	return (NULL);
}

// 탐색 실패시 실패한 위치에 노드 삽입
node* insertBST(node* root, char x)
{
	node* ptr = root;
	node* parent = NULL;
	
	while(ptr != NULL)
	{
		parent = ptr; // 삽입하기 전 미리 이전 노드 주소 저장하기

		if (ptr->key == x)
		{
			std::cout << "Error: duplicate key." << std::endl;
			return (ptr);
		}
		else if (ptr->key < x) // 키 값보다 x가 더 크면 노드의 오른쪽으로
			ptr = ptr->right;
		else // 키 값보다 x가 작으면 노드의 왼쪽으로
			ptr = ptr->left;
	}
	// 아무것도 못 찾았다면 새로운 키 삽입
	node* newNode = createNode(x); 

	if (parent != NULL)
	{
		if (parent->key < x) // 이전 노드의 값이 x보다 작으면 오른쪽에 새로운 노드 생성
			parent->right = newNode;
		else // 이전 노드의 값이 x보다 크면 왼쪽에 새로운 노드 생성
			parent->left = newNode;
	}
	
	return (newNode);
}

// 삽입보다 삭제가 더 까다롭다! 중간의 노드가 삭제될 수 있기 때문
node* deleteBST(node* root, char x)
{
	node* ptr = root;
	node* parent = NULL;

	while ((ptr != NULL) && (ptr->key != x))
	{
		parent = ptr;
		if (ptr->key < x)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	if (ptr == NULL)
	{
		std::cout << "Error: not found." << std::endl;
		return (root);
	}

	if (ptr->left == NULL && ptr->right == NULL) // 노드에 연결된 하위 노드가 없는 경우 (차수 = 0)
	{
		if (parent == NULL) // 한번도 while을 돌지 않았을 경우 (root 노드 삭제)
			root = NULL;
		else
		{
			if (parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
	}
	else if (ptr->left == NULL || ptr->right == NULL) // 노드의 한쪽에만 하위 노드가 연결된 경우 (차수 = 1)
	{
		node* child = (ptr->left == NULL) ? ptr->right : ptr->left;

		if (parent == NULL) // 한번도 while을 돌지 않았을 경우 (root 노드 삭제)
			root = child;
		else
		{
			if (parent->left == ptr)
				parent->left = child;
			else
				parent->right = child;
		}
	}
	else // 노드의 양쪽에 하위 노드가 연결된 경우 (차수 = 2)
	{
		
	}

}