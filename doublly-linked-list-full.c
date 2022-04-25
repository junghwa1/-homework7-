/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� if necessary */

typedef struct Node {       //key ���� ���� ��带 ����Ű�� rlink, llink�� ���� ����ü
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {       //ù��° ��带 ����Ű�� first�� ���� ����ü
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         lab3�� initialize�� �������� ���� �Ұ� */
/* head��带 �����ϴ� ���� �ƴϰ� head����� �ּҿ� �����Ͽ�
   first�� ���� �����ϱ� ������ ���������͸� �Ű������� ����*/
int initialize(headNode** h);		//head��� ����(����Ʈ ����)


/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
int freeList(headNode* h);			//������ ����Ʈ�� ����� head��� �޸� ����
int insertNode(headNode* h, int key);	//�Է¹��� key������ ũ�ų� ���� key�� ���� ����� �տ� ��� ����
int insertLast(headNode* h, int key);	//����Ʈ�� �������� ��� ����
int insertFirst(headNode* h, int key);	//����Ʈ�� ù��°�� ��� ����
int deleteNode(headNode* h, int key);	//�Է¹��� key���� ���� key�� ���� ��� ����
int deleteLast(headNode* h);			//����Ʈ�� ������ ��� ����
int deleteFirst(headNode* h);			//����Ʈ�� ù��° ��� ����
int invertList(headNode* h);			//����Ʈ�� ������ ������ �������� �� ��ġ
void printList(headNode* h);			//����Ʈ ���

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("[----- [����ȭ] [2019038062] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");			//�޴� ���
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");			//�޴� ����
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);		//����Ʈ ����
			break;
		case 'p': case 'P':
			printList(headnode);		//����Ʈ ���
			break;
		case 'i': case 'I':
			printf("Your Key = ");		//������ ����� key�� �Է�
			scanf("%d", &key);
			insertNode(headnode, key);	//�Է��� key������ ũ�ų� ���� key�� ���� ���տ� ����
			break;
		case 'd': case 'D':
			printf("Your Key = ");		//������ ����� key�� �Է�
			scanf("%d", &key);
			deleteNode(headnode, key);	//�Է��� key���� key�� ���� ��� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");		//������ ����� key�� �Է�
			scanf("%d", &key);
			insertLast(headnode, key);	//����Ʈ�� �������� ��� ����
			break;
		case 'e': case 'E':
			deleteLast(headnode);		//����Ʈ�� ������ ��� ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");		//������ ����� key�� �Է�
			scanf("%d", &key);
			insertFirst(headnode, key);	//����Ʈ�� ù��°�� ��� ����
			break;
		case 't': case 'T':
			deleteFirst(headnode);		//����Ʈ�� ù��° ��� ����
			break;
		case 'r': case 'R':
			invertList(headnode);		//����Ʈ�� ������ ������ �������� �� ��ġ
			break;
		case 'q': case 'Q':
			freeList(headnode);			//����Ʈ�� �Ҵ�� ��� �޸� ���� �� �ݺ��� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");		//�޴� �̿��� �ٸ� �� �Է� �� �������� ���
			break;
		}

	}while(command != 'q' && command != 'Q');		//q�� Q�� �Է¹����� �ݺ��� ����

	return 1;
}

int initialize(headNode** h) {		//head��� ����

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (headNode*)malloc(sizeof(headNode));	//head����� �ּҷ� �����Ͽ� �޸� �Ҵ�(singly-linked-list-full�� �ڵ�� �ٸ����̴�)
	(*h)->first = NULL;		//head����� first�� ����Ű�� ��尡 ������ ����
	return 1;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;		//ù��°���� p(p�� �������� ������ ���)

	listNode* prev = NULL;		//������ ��带 �ӽ� ������ prev
	while(p != NULL) {			//������ ��� p�� ���������� �ݺ�
		prev = p;				//prev�� p�� ����
		p = p->rlink;			//p�� ���� ��带 ����
		free(prev);				//prev �޸� ����
	}
	free(h);					//���������� head��� �޸� ����
	return 0;
}

void printList(headNode* h) {	//����Ʈ ���
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {				//head��尡 ���ٸ� �������� ���
		printf("Nothing to print....\n");
		return;					//�Լ� ����
	}

	p = h->first;			//p�� ù��°���(����� ���)

	while(p != NULL) {		//����� ��� p�� ���������� �ݺ�
		printf("[ [%d]=%d ] ", i, p->key);	//��� ��ȣ�� key�� ���
		p = p->rlink;		//������带 �ٽ� p�� ����
		i++;
	}

	printf("  items = %d\n", i);			//����� ����
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {		//������ ���� ����Ʈ�� ���� ������ ��尡 ��

	listNode* node = (listNode*)malloc(sizeof(listNode));		//���� �޸� �Ҵ����� ��� ����
	node->key = key;			//�Է¹��� key���� ����� key�� ����
	node->rlink = NULL;			//������ ��尡 ����Ű�� ���� ���� ����
	node->llink = NULL;			//������ ��尡 ����Ű�� ���� ���� ����

	if (h->first == NULL)		//ù��° ��尡 ���ٸ�
	{
		h->first = node;		//������ ���� head��尡 ����Ű�� ù��° ��尡 ��
		return 0;				//�Լ� ����
	}

	listNode* n = h->first;		//n�� ù��°���
	while(n->rlink != NULL) {	//������ ����� ���� ��尡 ���������� �ݺ�
		n = n->rlink;			//n�� n�� ������尡 ��
	}
	n->rlink = node;			//n�� ������ ���� ���� ������ ��尡 ��
	node->llink = n;			//������ ����� ���ʳ�忡 n�� ����
	return 0;
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {		//���� �����ʳ��(������ ���) ����

	if (h->first == NULL)		//������ ��尡 ���ٸ�(==head����� first�� ����Ű�� ù��° ��尡 ���ٸ�)
	{
		printf("nothing to delete.\n");			//�������� ���
		return 0;
	}

	listNode* n = h->first;		//n�� ù��° ���
	listNode* trail = NULL;

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->rlink == NULL) {		//ù��° ����� ���� ��尡 ���ٸ�
		h->first = NULL;		//head����� first�� ����Ű�� ��尡 ���� �����
		free(n);				//n(ù��° ���)�� �޸� ����
		return 0;				//�Լ� ����
	}

	/* ������ ������ �̵� */	//n�� ������ ���
	while(n->rlink != NULL) {	//n�� ���� ������ ��尡 ���������� �ݺ�
		trail = n;				//trail�� n����
		n = n->rlink;			//n�� n�� ������尡 ��
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->rlink = NULL;	//n�� ���� ��尡 ������ ��尡 �ǹǷ� trail�� rlink�� NULL
	free(n);		//n�� �Ҵ�� �޸� ����

	return 0;
}

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {		//ù��°�� ���ο� ��� ����

	listNode* node = (listNode*)malloc(sizeof(listNode));	//���� �޸� �Ҵ����� ��� ����
	node->key = key;			//�Է¹��� key���� ����� key�� ����
	node->rlink = NULL;			//������ ��尡 ����Ű�� ���� ���� ����
	node->llink = NULL;			//������ ��尡 ����Ű�� ���� ���� ����	

	if(h->first == NULL)		//head����� first�� ����Ű�� ��尡 ������
	{
		h->first = node;		//������ ��带 ù��°���� ����
		return 1;				//�Լ� ����
	}

	node->rlink = h->first;		//������ ����� rlink�� ������ ù��° ��带 ����Ŵ
	node->llink = NULL;			//������ ����� llink�� ����Ű�� ���� ����(ù��° ����̱� ����)

	listNode *p = h->first;		//p�� ������ ù��° ���
	p->llink = node;			//������ ù��° ����� llink�� ������ ��带 ����Ŵ
	h->first = node;			//head����� first�� ������ ��带 ī��Ŵ

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {	//���� ���ʳ��(ù��° ���) ����

	if (h->first == NULL)		//������ ��尡 ���ٸ�(==head����� first�� ����Ű�� ù��° ��尡 ���ٸ�)
	{
		printf("nothing to delete.\n");		//�������� ���
		return 0;				//�Լ� ����
	}
	listNode* n = h->first;		//n�� ù��°���
	h->first = n->rlink;		//head����� first�� n(ù��° ���)�� ���� �����ʳ�带 ����Ŵ

	free(n);		//n�� �Ҵ�� �޸� ����

	return 0;
}

/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {			//����Ʈ�� ������ �������� �� ��ġ


	if(h->first == NULL) {					//head����� first�� ����Ű�� ù��° ��尡 ���ٸ�
		printf("nothing to invert...\n");	//�������� ���
		return 0;		//�Լ� ����
	}
	listNode *n = h->first;		//n�� ù��° ���
	listNode *trail = NULL;		//
	listNode *middle = NULL;	//

	while(n != NULL){			//n�� NULL�� �ƴϸ� �ݺ�
		trail = middle;			//���� ���� �߰� ��尡 ��
		middle = n;				//�߰� ���� n�� ��
		n = n->rlink;			//n�� n�� ���� ������ ��尡 ��
		middle->rlink = trail;	//�߰� ����� ���� ������ ���� ������尡 ��
		middle->llink = n;		//�߰� ����� ���� ���� ���� n�� ��
	}

	h->first = middle;			//ù��°���� ������ ������ ��尡 ��

	return 0;
}

/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	//���� �޸� �Ҵ����� ��� ����
	node->key = key;			//�Է¹��� key���� ����� key�� ����
	node->llink = node->rlink = NULL;			//������ ��尡 ����Ű�� ���� ���� ����

	if (h->first == NULL)		//head����� first�� ����Ű�� ù��° ��尡 ���ٸ�
	{
		h->first = node;		//������ ���� ù��° ��尡 ��
		return 0;		//�Լ� ����
	}

	listNode* n = h->first;		//n�� ù��°���

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {			//n�� NULL�� �ƴϸ� �ݺ�
		if(n->key >= key) {		//n�� key���� ������ ����� key������ ũ�ų� �۰�
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {	//n�� ù��° ����� ��
				insertFirst(h, key);		//������ ��带 ù��° ���� ����
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n;			//������ ����� rlink�� ���� ��� n�� ����Ŵ
				node->llink = n->llink;		//������ ����� llink�� n�� llink(������ n�� �������)�� ����Ŵ
				n->llink->rlink = node;		//������ n�� ���� ����� rlink�� ������ ��带 ����Ŵ
			}
			return 0;		//�Լ� ����
		}

		n = n->rlink;		//n�� n�� ���� ��尡 ��
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);		//������ ���� ����
	return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {		//����Ʈ���� �Է¹��� key�� �ִ� ��� ����

	if (h->first == NULL)	//head����� first�� ����Ű�� ù��° ��尡 ���ٸ�
	{
		printf("nothing to delete.\n");		//�������� ���
		return 1;			//�Լ� ����
	}

	listNode* n = h->first;		//n�� ù��° ���

	while(n != NULL) {			//n�� NULL�� �ƴϸ� �ݺ�
		if(n->key == key) {		//n�� key���� �Է� ���� key���� ����
			if(n == h->first) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h);	//ù��° ��� ����
			} else if (n->rlink == NULL){ /* ������ ����� ��� */
				deleteLast(h);	//������ ��� ����
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink;		//n�� ���� ����� rlink�� n�� ������带 ����Ŵ
				n->rlink->llink = n->llink;		//n�� ���� ����� llink�� n�� ������带 ����Ŵ
				free(n);			//n�� �Ҵ�� �޸� ����
			}
			return 1;			//�Լ� ����
		}

		n = n->rlink;			//n�� n�� �������
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);		//�������� ���
	return 1;
}