/*
모든 원소는 유일한 키 값을 가진다.
왼쪽 서브트리의 모든 원소들은 루트의 키보다 작은 값을 갖는다.
오른쪽 서브트리의 모든 원소들은 루트의 키보다 큰 값을 갖는다.
왼쪽 서브트리와 오른쪽 서브트리도 이진탐색트리이다.
 -> 즉 어떤 노드를 루트로 잡던지 위 조건이 항상 참이 되어야 한다.
*/

#include <iostream>

typedef struct Node {
	int key;
	struct Node* left;
	struct Node* right;
} node;

node* createNode(int x)
{
	node* newNode = new node;
	newNode->key = x;
	newNode->left = NULL;
	newNode->right = NULL;

	return (newNode);
}

// search (root, tofindKey)
node* searchBST(node* root, int x)
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
node* insertBST(node* root, int x)
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
node* deleteBST(node* root, int x)
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
		node* succ_parent = ptr;
		node* succ = ptr->right;

		// 오른쪽 서브 트리에서 가장 작은 노트 찾기
		while (succ->left != NULL)
		{
			succ_parent = succ;
			succ = succ->left;
		}
	
		ptr->key = succ->key; // 삭제할 노드의 키를 후계자 노드의 키로 교체

		// 노드 정리
		if (succ_parent->left == succ)
			succ_parent->left = succ->right; // 후계자의 오른쪽 자식을 부모와 연결
		else
			succ_parent->right = succ->right; // 특수 케이스. 오른쪽 서브 트리에 오른쪽 노드들만 있을 경우 이 쪽으로 빠지게 됨
		
		// 값 교체했으니 삭제할 노드에 후계자 노드 넣어주기
		ptr = succ;
	}

	delete ptr;
	return (root);
}

// 전위 순회 1. 루트 2. 왼쪽 순회 3. 오른쪽 순회 (Root -> Left -> Right)
void preorder(node* ptr) {
	if (ptr) {
		std::cout << "node: " << ptr->key << ' ';
		if (ptr->left)
			std::cout << "left:" << ptr->left->key << ' ';
		if (ptr->right)
			std::cout << "right:" << ptr->right->key << std::endl;
		preorder(ptr->left);
		preorder(ptr->right);
	}
}

// 중위 순회 1. 왼쪽 순회 2. 루트 3. 오른쪽 순회 (Left -> Root -> Right)
void inorder(node* ptr) {
	if (ptr) {
		inorder(ptr->left);
		std::cout << ptr->key << ' ';
		inorder(ptr->right);
	}
}

// 후위 순회 1. 왼쪽 순회 2. 오른쪽 순회 3. 루트 (Left -> Right -> Root)
void postorder(node* ptr) {
	if (ptr) {
		postorder(ptr->left);
		postorder(ptr->right);
		std::cout << ptr->key << ' ';
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
    node* root = NULL; // 루트 노드를 초기화

    // 반복문을 사용하여 여러 노드를 트리에 삽입
    int keys[] = {50, 30, 80, 20, 40, 60}; // 삽입할 키 값들
    int size = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < size; ++i) {
        if (root == NULL) {
            root = insertBST(root, keys[i]); // 첫 번째 삽입은 루트 노드를 생성
        } else {
            insertBST(root, keys[i]); // 이후에는 트리에 삽입
        }
    }

    // 삽입된 노드를 다양한 순회 방식으로 출력
    printOrder(root);

    return 0;
}
