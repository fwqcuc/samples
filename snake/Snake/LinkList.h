
#ifndef LIST_H
#define LIST_H

typedef struct _NODE
{
	void* data;
	struct _NODE* next;
}NODE, *PNODE;

typedef struct _LIST
{
 void* list_data;
 PNODE first;
}LIST, *PLIST;



PLIST ListCreate(void* list_data);
PNODE NodeCreate(void* data);// private;
void NodeDestory(PNODE);
void ListPushBack(PLIST list, void* data);
void ListPushFront(PLIST list, void* data);
void* ListPopBack(PLIST list);
void* ListPopFront(PLIST list);
void ListInsertAt(PLIST list, unsigned int n, void* data);
void* ListDeleteAt(PLIST list, int n);
void ListClear(PLIST list);
void ListDestory(PLIST list);
int ListSize(PLIST list);
void* ListGetAt(PLIST list, unsigned int n);

#endif