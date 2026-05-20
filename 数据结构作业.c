#define _CRT_SECURE_NO_WARNINGS
//实验一
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 10000

//定义图书信息结构体
typedef struct
{
    char no[20];
    char name[50];
    float price;
} Book;

typedef struct LNode
{
    Book data;
    struct LNode* next;
} LNode, * LinkList;

//创建图书信息表
LinkList createBookList() 
{
    LinkList head = NULL;
    LinkList current = NULL;
	LinkList prev = NULL;
	char no[20];
	char name[50];
	float price;
	char input[100];
    while (1) 
	{
		fgets(input, sizeof(input), stdin);
		if (input[0] == '0' && input[1] == ' ' && input[2] == '0' && input[3] == ' ' && input[4] == '0')
			break;
		sscanf(input, "%s %s %f", no, name, &price);

        LNode* newBook = (LNode*)malloc(sizeof(LNode));
        if (newBook == NULL) {
            printf("Error: memory allocation failed.\n");
            return NULL;
        }

        strcpy(newBook->data.no, no);
        strcpy(newBook->data.name, name);
        newBook->data.price = price;
        newBook->next = NULL;

        if (head == NULL) {
            head = newBook;
            current = head;
        }
		else
		{
			current->next = newBook;
			current = newBook;
		}
    }
    return head;
}

//求图书表长
int listlength(LinkList head)
{
	LNode* current = head;
	int count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return count;
}

//输出图书数目
void Listlength(LinkList head)
{
	LNode* current = head;
	int count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	printf("%d\n", count);
}

// 输出图书信息表
void printBookList(LinkList head) 
{
    LNode* current = head;
    while (current != NULL) {
        printf("%s %s %.2f\n", current->data.no, current->data.name, current->data.price);
        current = current->next;
    }
}
//释放内存
void ClearList(LinkList head)
{
	LNode* temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

//图书插入
void insertBook(LinkList* head, int position, char* no, char* name, float price) {
	LNode* newBook = (LNode*)malloc(sizeof(LNode));
	if (newBook == NULL) {
		printf("Error: memory allocation failed.\n");
		return;
	}

	strcpy(newBook->data.no, no);
	strcpy(newBook->data.name, name);
	newBook->data.price = price;

	if (*head == NULL || position == 0) {
		newBook->next = *head;
		*head = newBook;
		return;
	}

	LNode* current = *head;
	int i = 0;
	while (current != NULL && i < position-1) {
		current = current->next;
		i++;
	}

	if (current == NULL) {
		printf("很抱歉，插入位置非法！\n");
		free(newBook);
		return;
	}

	newBook->next = current->next;
	current->next = newBook;
}

//图书删除
void deleteBook(LinkList* head, int position) {
	if (*head == NULL) {
		printf("很抱歉,图书表为空,无法删除!\n");
		return;
	}

	LNode* current = *head;
	LNode* prev = NULL;
	int i = 0;

	// 找到要删除的图书节点
	while (current != NULL && i < position) {
		prev = current;
		current = current->next;
		i++;
	}

	// 若位置非法,则输出错误信息并返回
	if (current == NULL) {
		printf("很抱歉,输入位置非法!\n");
		return;
	}

	// 修改指针删除该节点
	if (prev == NULL) {
		*head = current->next;
	}
	else {
		prev->next = current->next;
	}

	// 释放该节点内存
	free(current);
}

//利用哈希表来记录已出现图书的编号
#define HASH_TABLE_SIZE 101  // 素数的长度可以减少哈希冲突

typedef struct HashNode {
	char* key;
	struct HashNode* next;
} HashNode;

typedef struct HashTable {
	HashNode* buckets[HASH_TABLE_SIZE];
} HashTable;

//创建哈希表
HashTable* createHashTable() {
	HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		ht->buckets[i] = NULL;
	}
	return ht;
}

//除留余数法解决冲突
unsigned int hash(char* key) {
	unsigned int hash = 0;
	while (*key != '\0') {
		hash = (hash * 31 + *key++) % HASH_TABLE_SIZE;
	}
	return hash;
}

//检查是否存在指定的键
int containsKey(HashTable* ht, char* key) {
	unsigned int index = hash(key);
	HashNode* curr = ht->buckets[index];
	while (curr != NULL) {
		if (strcmp(curr->key, key) == 0) {
			return 1;
		}
		curr = curr->next;
	}
	return 0;
}

//插入一个新的键
void insertKey(HashTable* ht, char* key) {
	unsigned int index = hash(key);
	HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
	newNode->key = _strdup(key);
	newNode->next = ht->buckets[index];
	ht->buckets[index] = newNode;
}

//释放哈希表
void freeHashTable(HashTable* ht) {
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		HashNode* curr = ht->buckets[i];
		while (curr != NULL) {
			HashNode* temp = curr;
			curr = curr->next;
			free(temp->key);
			free(temp);
		}
	}
	free(ht);
}

// 图书去重
LinkList cheakBookList(LinkList head) {
	if (head == NULL || head->next == NULL) {
		return head;
	}

	// 使用哈希表存储已经出现过的编号
	HashTable* ht = createHashTable();

	LinkList curr = head;
	LinkList prev = NULL;
	while (curr != NULL) {
		// 如果当前编号在哈希表中,说明已经出现过,删除当前节点
		if (containsKey(ht, curr->data.no)) {
			LinkList temp = curr;
			if (prev == NULL) {
				// 删除头节点
				head = curr->next;
			}
			else {
				prev->next = curr->next;
			}
			curr = curr->next;
			free(temp);
		}
		else {
			// 否则,将当前编号加入哈希表,并移动到下一个节点
			insertKey(ht, curr->data.no);
			prev = curr;
			curr = curr->next;
		}
	}

	freeHashTable(ht);
	return head;
}

// 求图书平均价格修改价格
void modifyBookPrice(LinkList head) {
    LNode* current = head;
    double totalPrice = 0.0;
    int count = 0;

    // 计算总价格和图书数量
    while (current != NULL) {
        totalPrice += current->data.price;
        count++;
        current = current->next;
    }

    double avgPrice = totalPrice / count;
    printf("%.2f\n", avgPrice);

    // 修改价格
    current = head;
    while (current != NULL) {
		LNode* next = current->next;
        if (current->data.price < avgPrice) {
            current->data.price *= 1.2; // 低于平均价格的图书价格提高 20%
        }
        else {
            current->data.price *= 1.1; // 高于或等于平均价格的图书价格提高 10%
        }
        current = next;
    }
}

//找到最贵的图书信息
void findMostExpensiveBooks(LinkList head) {
	LNode* current = head;
	double maxPrice = 0.0;
	int count = 0;

	// 找到最贵图书的价格
	while (current != NULL) {
		if (current->data.price > maxPrice) {
			maxPrice = current->data.price;
		}
		current = current->next;
	}

	// 输出最贵图书的信息
	current = head;
	while (current != NULL) {
		if (current->data.price == maxPrice) {
			count++;
		}
		current = current->next;
	}
	printf("%d\n", count);
	current = head;
	while (current != NULL) {
		if (current->data.price == maxPrice) {
			printf("%s %s %.2f\n", current->data.no, current->data.name, current->data.price);
		}
		current = current->next;
	}
}

int main() {
	int n, m, a;
	printf("请先创建图书目录！\n");
	LinkList bookList = createBookList();
	if (bookList == NULL) {
		return 1; // 创建图书信息表失败,退出程序
	}
	int position;
	char no[20], name[50];
	float price;
	printf("想要实现什么功能？\n");
	printf("---1.直接输出图书目录---\n");
	printf("---2.修改图书目录---\n");
	printf("---3.查找最贵图书---\n");
	printf("---4.对图书插入---\n");
	printf("---5.对图书删除---\n");
	printf("---6.图书去重操作---\n");
	scanf("%d", &a);
	switch (a) {
	case 1:
		printf("现在的图书目录为：\n");
		Listlength(bookList);
		printBookList(bookList);
		ClearList(bookList);
		break;
	case 2:
		printf("平均价格为：\n");
		modifyBookPrice(bookList);
		printf("修改价格后的图书信息如下：\n");
		Listlength(bookList);
		printBookList(bookList);
		ClearList(bookList);
		break;
	case 3:
		printf("图书总数：\n");
		Listlength(bookList);
		printf("最贵图书信息：\n");
		findMostExpensiveBooks(bookList);
		ClearList(bookList);
		break;
	case 4:
		printf("请输入要插入的位置：\n");
		scanf("%d", &position);
		printf("请输入要插入的图书信息：\n");
		scanf("%s %s %f", no, name, &price);
		printf("插入后的图书信息为：\n");
		insertBook(&bookList, position - 1, no, name, price);
		Listlength(bookList);
		printBookList(bookList);
		ClearList(bookList);
		break;
	case 5:
		printf("请输入要删除位置：\n");
		scanf("%d", &position);
		deleteBook(&bookList, position - 1);
		printf("删除后的图书数量为：\n");
		Listlength(bookList);
		printf("删除后的图书信息为：\n");
		printBookList(bookList);
		ClearList(bookList);
		break;
	case 6:
		bookList=cheakBookList(bookList);
		printf("去重后的图书数目：\n");
		Listlength(bookList);
		printBookList(bookList);
		ClearList(bookList);
		break;
	}
	return 0;
}*/
