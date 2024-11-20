#include <iostream>

#define SIZE 10

typedef struct Node {
	int key;
	int value;
	Node* next;
} node;

typedef struct Bucket {
	node* head;
	int count;
} bucket;

bucket* hashTable = NULL;

node* creatNode(int key, int value) // 노드 만들기
{
	node* newNode = new node;

	newNode->key = key;
	newNode->value = value;
	newNode->next = NULL;

	return (newNode);
}

int hashFunction(int key)
{
	return key&SIZE;
}

void insert(int key, int value)
{
	int hashIndex = hashFunction(key);

	node* node = creatNode(key, value);

	// 인덱스에 아무 노드가 없는 경우
	if (hashTable[hashIndex].count == 0)
	{
		hashTable[hashIndex].head = node;
		hashTable[hashIndex].count = 1;
	}
	else // 인덱스에 이미 값이 있는 경우
	{
		node->next = hashTable[hashIndex].head; // 새로운 노드의 다음은 헤드를 가르킴
		hashTable[hashIndex].head = node; //새로운 노드를 헤드로 만들기
		hashTable[hashIndex].count++;
	}

	std::cout << "hashIndex:" << hashIndex << std::endl;
	std::cout << "[node]" << std::endl;
	std::cout << "key: " << node->key << "\n" << "value: " << node->value << std::endl;
	return ;
}

void remove(int key)
{
	int hashIndex = hashFunction(key);
	node* node;
	Node* temp;

	node = hashTable[hashIndex].head;

	if(node == NULL)
	{
		std::cout << "no key found." << std::endl;
		return ;
	}

	while(node != NULL)
	{
		if(node->key == key)
		{
			if(node == hashTable[hashIndex].head) // 찾는 노드가 헤드라면
			{
				hashTable[hashIndex].head = node->next; // 헤드를 헤드 다음 노드로 변경
			}
			else
			{
				temp->next = node->next; // 삭제할 노드의 이전 노드의 넥스트를 삭제할 노드의 넥스트로 변경
			}
			
			hashTable[hashIndex].count--;
			delete node;
			return ;
		}
		
		temp = node;
		node = node->next;
	}

	return ;
}

node* search(int key)
{
	int hashIndex = hashFunction(key);
	node* node = hashTable[hashIndex].head;

	if(node == NULL)
	{
		std::cout << "no key found." << std::endl;
		return (NULL);
	}

	while(node != NULL)
	{
		if(node->key == key)
		{
			std::cout << "[node]" << std::endl;
			std::cout << "key: " << node->key << "\n" << "value: " << node->value << std::endl;
			return (node);
		}
		node = node->next;
	}

	return (NULL);
}

void displayAll(void)
{
	node* node;

	for (int i = 0; i < SIZE; i++)
	{
		node = hashTable[i].head;
		std::cout << "\nBucket[" << i << "] ";

		while(node != NULL)
		{
			std::cout << "[node]" << std::endl;
			std::cout << "key: " << node->key << "\n" << "value: " << node->value << std::endl;
			node = node->next;
		}
	}

	return ;
}

int main()
{
	hashTable = new bucket[SIZE];

	insert(0, 1); //0
	insert(1, 10); //0
	insert(11, 90);
	insert(21, 64); //0
	insert(31, 23);
	insert(6, 25);
	insert(97, 4); //0
	
	node* temp = search(0);
	if (temp->next == NULL)
		std::cout << "what";
	else
		std::cout << temp->value;
	// displayAll();

	// remove(21);

	// displayAll();

	return (0);
}
