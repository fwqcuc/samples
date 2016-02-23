/************************************************************************

双链表

FUNCTIONS :
ListCreate   - 创建一个新的链表。
ListInsertAt  - 插入节点到链表。
ListPushFront  - 在链表头部插入节点。
ListPushBack  - 在链表尾部插入节点。
ListPopFront  - 删除链表头部节点。
ListPopBack   - 删除链表尾部节点。
ListGetFront  - 获得第一个节点
ListGetBack   - 获得最后一个节点。
ListGetNodeAt  - 根据序号获得节点。
ListDeleteNodeAt - 根据序号删除节点。
ListDestroy   - 删除整个链表，并释放内存。
ListCleaer   - 清楚链表中的所有节点和数据。
ListGetError  - 获得错误编号
ListGetSize   - 获得当前链表大小（节点数量）。


************************************************************************/
#include <stdlib.h> // 使用到了malloc(), free()等函数。
#include "LinkList.h"

//-- 检测指针是否为0
#define CHECK_POINTER( ppNode ) \
  if( ppNode == 0L ) {  \
  return( pList->ListError = LIST_ERROR_DEREFERENCE_NULL ); \
        }

PNODE NodeCreate(void* data)
{
	PNODE pnode = (PNODE) malloc(sizeof(NODE));
	pnode->data = data; 
	pnode->next = 0;
	return pnode;
}

void NodeDestory(PNODE node)
{
	free(node->data);
	free(node);
}

int ListSize(PLIST list)
{
	int  cnt;
	PNODE node = list->first;

	cnt = 0;
	while (node)
	{
		cnt++;
		node = node->next;
	}
	return (cnt);
}


void* ListDeleteAt(PLIST list, int n)
{
	int  i;
	PNODE tmp;
	PNODE prev;

	tmp = list->first;
	if (n < 1)
		return (NULL);
	if (n == 0)
	{
		return ListPopFront(list);
	}
	i = 1;
	while (i < n)
	{
		prev = tmp;
		tmp = tmp->next;
		if (!tmp)
			return (NULL);
		++i;
	}
	prev->next = tmp->next;
	return (tmp->data);
}


void* ListGetAt(PLIST list, unsigned int n)
{
	unsigned int   i;
	PNODE node = list->first;

	if (!node)
		return (NULL);
	
	for (i = 1; i <= n; i++)
	{
		node = node->next;
		if (!node)
			return (NULL);
	}
	return (node->data);
}

PLIST ListCreate(void* list_data)
{
	PLIST new_list;

	new_list = NULL;
	new_list = (PLIST)malloc(sizeof(LIST));
	if (new_list != NULL)
	{
		new_list->list_data = list_data;
		new_list->first = NULL;
	}
	return (new_list);
}

void ListDestory(PLIST list)
{
	if (list != NULL)
	{
		ListClear(list);
		free(list);
	}
}

void* ListPopFront(PLIST list)
{
	PNODE tmp;
	void*  data = NULL;
	if (list != NULL)
	{
		if (list->first != NULL)
		{
			tmp = list->first;
			data = tmp->data;
			list->first = tmp->next;
			free(tmp);
		}
	}
	return (data);
}


void* ListPopBack(PLIST list)
{
	PNODE previous;
	PNODE current;
	PNODE node = list->first;
	void* data;

	if (!node)
		return (NULL);
	if (!(node)->next)
	{
		data = (node)->data;
		free(node);
		node = NULL;
		return (data);
	}
	previous = node;
	current = (node)->next;
	while (current->next)
	{
		previous = current;
		current = current->next;
	}
	data = current->data;
	free(current);
	previous->next = NULL;
	return (data);
}


void ListPushBack(PLIST list, void* data)
{
	PNODE tmp;
	PNODE new_node = NodeCreate(data);

	if (new_node)
	{
		if (list)
		{
			if (list->first)
			{
				tmp = list->first;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = new_node;
			}
			else
				list->first = new_node;
		}
	}
}


void ListPushFront(PLIST list, void* data)
{
	PNODE new_node;

	if (list != NULL)
	{
		new_node = NodeCreate(data);
		if (new_node != NULL)
		{
			new_node->next = list->first;
			list->first = new_node;
		}
	}
}



void ListClear(PLIST list)
{
	PNODE tmp;
	PNODE node;

	if (list != NULL)
	{
		node = list->first;
		while (node)
		{
			tmp = node->next;
			NodeDestory(node);
			node = tmp;
		}
		list->first = 0;
	}
}


