#include<stdlib.h>
#include<stdio.h>
#include"header.h"

void insert(PNODE head, PNODE node)
{
	if (head->pNext == NULL)
		head->pNext = node;
	else{
		PNODE temp = head;
		while (temp->pNext != NULL && temp->pNext->x < node->x){
			temp = temp->pNext;
		}
		node->pNext = temp->pNext;
		temp->pNext = node;
	}
}

void deletenode(PNODE pos)
{
	PNODE temp = pos->pNext;
	pos->pNext = pos->pNext->pNext;
	free(temp);
}

void sort(PNODE head){
	PNODE temphead = (PNODE) malloc(sizeof(Node));
	temphead->x = 0;
	temphead->delta = 0;
	temphead->ymax = 0;
	temphead->pNext = NULL;

	PNODE temp = head;
	while (temp->pNext != NULL){
		PNODE temp2 = (PNODE) malloc(sizeof(Node));
		temp2->x = temp->pNext->x;
		temp2->delta = temp->pNext->delta;
		temp2->ymax = temp->pNext->ymax;
		temp2->pNext = NULL;
		insert(temphead, temp2);
		temp = temp->pNext;
	}
	destroy(head);
	head->pNext = temphead->pNext;
}

void destroy(PNODE head){
	head = head->pNext;
	PNODE temp = NULL;
	while (head != NULL)
	{
		temp = head;
		head = head->pNext;
		free(temp);
	}
}