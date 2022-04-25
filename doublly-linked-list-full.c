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
/* 필요한 헤더파일 추가 if necessary */

typedef struct Node {       //key 값과 다음 노드를 가리키는 rlink, llink를 가진 구조체
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {       //첫번째 노드를 가리키는 first를 가진 구조체
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
/* head노드를 리턴하는 것이 아니고 head노드의 주소에 접근하여
   first의 값을 변경하기 때문에 이중포인터를 매개변수로 받음*/
int initialize(headNode** h);		//head노드 생성(리스트 생성)


/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);			//생성된 리스트의 노드들과 head노드 메모리 해제
int insertNode(headNode* h, int key);	//입력받은 key값보다 크거나 같은 key를 가진 노드의 앞에 노드 삽입
int insertLast(headNode* h, int key);	//리스트의 마지막에 노드 삽입
int insertFirst(headNode* h, int key);	//리스트의 첫번째에 노드 삽입
int deleteNode(headNode* h, int key);	//입력받은 key값과 같은 key를 가진 노드 삭제
int deleteLast(headNode* h);			//리스트의 마지막 노드 삭제
int deleteFirst(headNode* h);			//리스트의 첫번째 노드 삭제
int invertList(headNode* h);			//리스트의 노드들의 순서를 역순으로 재 배치
void printList(headNode* h);			//리스트 출력

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("[----- [염중화] [2019038062] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");			//메뉴 출력
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");			//메뉴 선택
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);		//리스트 생성
			break;
		case 'p': case 'P':
			printList(headnode);		//리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");		//삽입할 노드의 key값 입력
			scanf("%d", &key);
			insertNode(headnode, key);	//입력한 key값보다 크거나 같은 key를 가진 노드앞에 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");		//삭제할 노드의 key값 입력
			scanf("%d", &key);
			deleteNode(headnode, key);	//입력한 key같은 key를 가진 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");		//삽입할 노드의 key값 입력
			scanf("%d", &key);
			insertLast(headnode, key);	//리스트의 마지막에 노드 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode);		//리스트의 마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");		//삽입할 노드의 key값 입력
			scanf("%d", &key);
			insertFirst(headnode, key);	//리스트의 첫번째에 노드 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode);		//리스트의 첫번째 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);		//리스트의 노드들의 순서를 역순으로 재 배치
			break;
		case 'q': case 'Q':
			freeList(headnode);			//리스트에 할당된 모든 메모리 해제 후 반복문 종료
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");		//메뉴 이외의 다른 값 입력 시 에러문구 출력
			break;
		}

	}while(command != 'q' && command != 'Q');		//q나 Q를 입력받으면 반복문 종료

	return 1;
}

int initialize(headNode** h) {		//head노드 생성

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));	//head노드의 주소로 접근하여 메모리 할당(singly-linked-list-full의 코드와 다른점이다)
	(*h)->first = NULL;		//head노드의 first가 가리키는 노드가 없도록 만듦
	return 1;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;		//첫번째노드는 p(p는 다음으로 삭제할 노드)

	listNode* prev = NULL;		//삭제할 노드를 임시 저장할 prev
	while(p != NULL) {			//삭제할 노드 p가 없을때까지 반복
		prev = p;				//prev에 p를 저장
		p = p->rlink;			//p는 다음 노드를 저장
		free(prev);				//prev 메모리 해제
	}
	free(h);					//마지막으로 head노드 메모리 해제
	return 0;
}

void printList(headNode* h) {	//리스트 출력
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {				//head노드가 없다면 에러문구 출력
		printf("Nothing to print....\n");
		return;					//함수 종료
	}

	p = h->first;			//p는 첫번째노드(출력할 노드)

	while(p != NULL) {		//출력할 노드 p가 없을때까지 반복
		printf("[ [%d]=%d ] ", i, p->key);	//노드 번호와 key값 출력
		p = p->rlink;		//다음노드를 다시 p로 만듦
		i++;
	}

	printf("  items = %d\n", i);			//노드의 개수
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {		//생성된 노드는 리스트의 가장 오른쪽 노드가 됨

	listNode* node = (listNode*)malloc(sizeof(listNode));		//동적 메모리 할당으로 노드 생성
	node->key = key;			//입력받은 key값을 노드의 key에 저장
	node->rlink = NULL;			//생성된 노드가 가리키는 노드는 아직 없음
	node->llink = NULL;			//생성된 노드가 가리키는 노드는 아직 없음

	if (h->first == NULL)		//첫번째 노드가 없다면
	{
		h->first = node;		//생성된 노드는 head노드가 가리키는 첫번째 노드가 됨
		return 0;				//함수 종료
	}

	listNode* n = h->first;		//n은 첫번째노드
	while(n->rlink != NULL) {	//오른쪽 노드의 다음 노드가 없을때까지 반복
		n = n->rlink;			//n에 n의 다음노드가 됨
	}
	n->rlink = node;			//n의 오른쪽 노드는 새로 생성된 노드가 됨
	node->llink = n;			//생성된 노드의 왼쪽노드에 n을 저장
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {		//가장 오른쪽노드(마지막 노드) 삭제

	if (h->first == NULL)		//삭제할 노드가 없다면(==head노드의 first가 가리키는 첫번째 노드가 없다면)
	{
		printf("nothing to delete.\n");			//에러문구 출력
		return 0;
	}

	listNode* n = h->first;		//n은 첫번째 노드
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {		//첫번째 노드의 다음 노드가 없다면
		h->first = NULL;		//head노드의 first가 가리키는 노드가 없게 만들고
		free(n);				//n(첫번째 노드)의 메모리 해제
		return 0;				//함수 종료
	}

	/* 마지막 노드까지 이동 */	//n은 마지막 노드
	while(n->rlink != NULL) {	//n의 다음 오른쪽 노드가 없을때까지 반복
		trail = n;				//trail에 n저장
		n = n->rlink;			//n은 n의 다음노드가 됨
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL;	//n의 이전 노드가 마지막 노드가 되므로 trail의 rlink는 NULL
	free(n);		//n에 할당된 메모리 해제

	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {		//첫번째에 새로운 노드 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode));	//동적 메모리 할당으로 노드 생성
	node->key = key;			//입력받은 key값을 노드의 key에 저장
	node->rlink = NULL;			//생성된 노드가 가리키는 노드는 아직 없음
	node->llink = NULL;			//생성된 노드가 가리키는 노드는 아직 없음	

	if(h->first == NULL)		//head노드의 first가 가리키는 노드가 없을때
	{
		h->first = node;		//생성된 노드를 첫번째노드로 만듦
		return 1;				//함수 종료
	}

	node->rlink = h->first;		//생성된 노드의 rlink는 기존의 첫번째 노드를 가리킴
	node->llink = NULL;			//생성된 노드의 llink가 가리키는 노드는 없음(첫번째 노드이기 때문)

	listNode *p = h->first;		//p는 기존의 첫번째 노드
	p->llink = node;			//기존의 첫번째 노드의 llink는 생성된 노드를 가리킴
	h->first = node;			//head노드의 first는 생성된 노드를 카리킴

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {	//가장 왼쪽노드(첫번째 노드) 삭제

	if (h->first == NULL)		//삭제할 노드가 없다면(==head노드의 first가 가리키는 첫번째 노드가 없다면)
	{
		printf("nothing to delete.\n");		//에러문구 출력
		return 0;				//함수 종료
	}
	listNode* n = h->first;		//n은 첫번째노드
	h->first = n->rlink;		//head노드의 first는 n(첫번째 노드)의 다음 오른쪽노드를 가리킴

	free(n);		//n에 할당된 메모리 해제

	return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {			//리스트의 순서를 역순으로 재 배치


	if(h->first == NULL) {					//head노드의 first가 가리키는 첫번째 노드가 없다면
		printf("nothing to invert...\n");	//에러문구 출력
		return 0;		//함수 종료
	}
	listNode *n = h->first;		//n은 첫번째 노드
	listNode *trail = NULL;		//
	listNode *middle = NULL;	//

	while(n != NULL){			//n이 NULL이 아니면 반복
		trail = middle;			//이전 노드는 중간 노드가 됨
		middle = n;				//중간 노드는 n이 됨
		n = n->rlink;			//n은 n의 다음 오른쪽 노드가 됨
		middle->rlink = trail;	//중간 노드의 다음 오른쪽 노드는 이전노드가 됨
		middle->llink = n;		//중간 노드의 이전 왼쪽 노드는 n이 됨
	}

	h->first = middle;			//첫번째노드는 변경전 마지막 노드가 됨

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	//동적 메모리 할당으로 노드 생성
	node->key = key;			//입력받은 key값을 노드의 key에 저장
	node->llink = node->rlink = NULL;			//생성된 노드가 가리키는 노드는 아직 없음

	if (h->first == NULL)		//head노드의 first가 가리키는 첫번째 노드가 없다면
	{
		h->first = node;		//생성된 노드는 첫번째 노드가 됨
		return 0;		//함수 종료
	}

	listNode* n = h->first;		//n은 첫번째노드

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {			//n이 NULL이 아니면 반복
		if(n->key >= key) {		//n의 key값이 삽입할 노드의 key값보다 크거나 작고
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {	//n이 첫번째 노드일 때
				insertFirst(h, key);		//생성된 노드를 첫번째 노드로 만듦
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;			//삽입할 노드의 rlink는 다음 노드 n을 가리킴
				node->llink = n->llink;		//삽입할 노드의 llink는 n의 llink(기존의 n의 이전노드)를 가리킴
				n->llink->rlink = node;		//기존의 n의 이전 노드의 rlink는 삽입할 노드를 가리킴
			}
			return 0;		//함수 종료
		}

		n = n->rlink;		//n은 n의 다음 노드가 됨
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);		//마지막 노드로 만듦
	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {		//리스트에서 입력받은 key이 있는 노드 삭제

	if (h->first == NULL)	//head노드의 first가 가리키는 첫번째 노드가 없다면
	{
		printf("nothing to delete.\n");		//에러문구 출력
		return 1;			//함수 종료
	}

	listNode* n = h->first;		//n은 첫번째 노드

	while(n != NULL) {			//n이 NULL이 아니면 반복
		if(n->key == key) {		//n의 key값이 입력 받은 key값과 같고
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);	//첫번째 노드 삭제
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h);	//마지막 노드 삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;		//n의 이전 노드의 rlink는 n의 다음노드를 가리킴
				n->rlink->llink = n->llink;		//n의 다음 노드의 llink는 n의 이전노드를 가리킴
				free(n);			//n에 할당된 메모리 해제
			}
			return 1;			//함수 종료
		}

		n = n->rlink;			//n은 n의 다음노드
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);		//에러문구 출력
	return 1;
}