
/*
* Data Structures in C
* Reverse the singly linked list
* 20160319
* LuoYingYing
*/

#include <stdio.h>
typedef struct Node *NodePtr;
struct Node{
	int data;
	NodePtr next;
};

void PrintLinkList(NodePtr L);
NodePtr Reverse(NodePtr L);

int main(int argc, char const *argv[])
{
	int num[5] = {1,2,3,4,5};
	NodePtr link = NULL, reverseLink = NULL;
	int i;
	for ( i = 0; i < 5; ++i)
	{
		NodePtr newNode = (NodePtr)malloc(sizeof(struct Node));
		newNode->data = i+1;
		newNode->next = link;
		link = newNode;
	}
	PrintLinkList(link);
	reverseLink = Reverse(link);
	PrintLinkList(reverseLink);
	return 0;
}

void PrintLinkList(NodePtr L)
{
	NodePtr temp;
	temp = L;
	while(temp)
	{
		printf("%d\n", temp->data);
		temp = temp->next;
	}
}

NodePtr Reverse(NodePtr L)
{
	NodePtr p, q, t;
	p = L;
	q = NULL;
	while(p != NULL)
	{
		t = p->next;
		p->next = q;
		q = p;
		p = t;
	}
	return q;
}