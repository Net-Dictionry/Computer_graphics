#ifndef HEADER_H
#define HEADER_H

typedef struct Node *PNODE;

typedef struct Node{
	int x;
	double delta;
	int ymax;
	struct Node *pNext;
} Node;

typedef struct PolyLine{
	int x1;
	int y1;
	int x2;
	int y2;
} PolyLine;

extern void insert(PNODE head, PNODE node);

extern void deletenode(PNODE pos);

extern void sort(PNODE head);

extern void destroy(PNODE head);

#endif