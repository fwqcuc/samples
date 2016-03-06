/************************************************************************

单链表

FUNCTIONS :
ListCreate			- 创建一个新的链表。
ListInsertAt		- 插入节点到链表。
ListPushFront		- 在链表头部插入节点。
ListPushBack		- 在链表尾部插入节点。
ListPopFront		- 删除链表头部节点。
ListPopBack			- 删除链表尾部节点。
ListGetFront		- 获得第一个节点
ListGetBack			- 获得最后一个节点。
ListGetNodeAt		- 根据序号获得节点。
ListDeleteNodeAt	- 根据序号删除节点。
ListDestroy			- 删除整个链表。
ListDestroyAndFree	- 删除整个链表，并释放数据。
ListClear			- 删除链表中的所有节点。
ListClearAndFree	- 清除链表中的所有节点，并释放数据。
ListGetSize			- 获得当前链表大小（节点数量）。


************************************************************************/

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