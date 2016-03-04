
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
void NodeDistory(PNODE);
void ListPushBack(PLIST list, void* data);
void ListPushFront(PLIST list, void* data);
void* ListPopBack(PLIST list);
void* ListPopFront(PLIST list);
int ListInsertAt(PLIST list, unsigned int n, void* data);
void* ListDeleteAt(PLIST list, int n);
void ListClearAndFree(PLIST list);
void ListDistoryAndFree(PLIST list);
void ListDistory(PLIST list);
int ListSize(PLIST list);
void* ListGetAt(PLIST list, unsigned int n);

#endif