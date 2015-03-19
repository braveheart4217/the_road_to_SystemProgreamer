#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

typedef int Type;

typedef struct _DLsitNode
{
	struct _DLsitNode* next;
	struct _DLsitNode* perv;

	void* data;
}DListNode;

typedef struct _DList
{
	struct _DLsitNode* first;
};

DList* dlist_create(void)
{
	DList* thiz=NULL;
	thiz=(DList *)malloc(sizeof(DList));
	if (thiz!=NULL)
	{
		thiz->first=NULL;
	}
	return thiz;
}

static DListNode* dlist_node_create(void* data)
{
	DListNode* node=NULL;
	node=(DListNode *)malloc(sizeof(DListNode));

	if (node!=NULL)
	{
		node->next=NULL;
		node->perv=NULL;
		node->data=data;
	}
	return node;
}

static void dlist_node_destroy(DListNode* node)
{
	if (node!=NULL)
	{
		node->next=NULL;
		node->perv=NULL;
		
		free(node);
	}
}

DListRet dlist_insert(DList* thiz, size_t index, void* data)
{
	DListRet ret= DLIST_RET_OK;
	if (thiz!=NULL)
	{
		DListNode* node=dlist_node_create(data);

		if (node!=NULL)
		{
			if (thiz->first==NULL)
			{
				thiz->first=node;
			}
			else
			{
 				if (index!=0)
 				{
					DListNode* temp=thiz->first;
					while (temp->next!=NULL && index>0)
					{
						temp=temp->next;
						index--;
					}
					if (index<=0)
					{
						temp->next->perv=node;
						node->next=temp->next;
					}
					temp->next=node;
					node->perv=temp;
				}
				else
				{
					node->next=thiz->first;
					thiz->first->perv=node;
					thiz->first=node;
				}
				
			}
		}
	}
	return ret;
}
DListRet dlist_prepend(DList* thiz, void* data)
{
	DListRet ret= DLIST_RET_OK;
	if (thiz!=NULL)
	{
		ret=dlist_insert(thiz,0,data);
	}
	return ret;
}
DListRet dlist_append(DList* thiz, void* data)
{
	DListRet ret= DLIST_RET_OK;
	if (thiz!=NULL)
	{
		size_t index=dlist_length(thiz);
		ret=dlist_insert(thiz,index,data);
	}
	return ret;
}

DListRet dlist_delete(DList* thiz, size_t index)
{
	DListRet ret= DLIST_RET_OK;
	DListNode *temp=thiz->first;

	index-=1;           //输入的下标总会比正常的大一号

	if (index==0)
	{
		thiz->first=temp->next;
	}
	else
	{
		while (temp->next!=NULL && index>0)
		{
			temp=temp->next;
			index--;
		}
		if (index<=0)
		{
			temp->next->perv=temp->perv;
			temp->perv->next=temp->next;
		}
		else
		{
			temp->perv->next=NULL;
		}
	}

	dlist_node_create(temp);
	return ret;
}
DListRet dlist_get_by_index(DList* thiz, size_t index, void** data)
{
	DListRet ret= DLIST_RET_OK;
	DListNode *temp=thiz->first;

	index-=1;           //输入的下标总会比正常的大一号

	while (temp->next!=NULL && index>0)
	{
		index--;
		temp=temp->next;
	}
	*data=temp->data;
	return ret;
}
DListRet dlist_set_by_index(DList* thiz, size_t index, void* data)
{
	DListRet ret= DLIST_RET_OK;
	DListNode *temp=thiz->first;

	index-=1;           //输入的下标总会比正常的大一号

	while (temp->next!=NULL && index>0)
	{
		temp=temp->next;
		index--;
	}
	temp->data=data;
	return ret;
}

size_t   dlist_length(DList* thiz)
{
	size_t index=0;
	DListNode* temp=thiz->first;
	if (thiz->first==NULL )
	{
		return index;
	}
	while (temp)
	{
		index++;
		temp=temp->next;
	}
	return index;
}

DListRet dlist_print(DList* thiz, DListDataPrintFunc print)
{
	DListRet ret= DLIST_RET_OK;
	DListNode *cursor=thiz->first;
	while (cursor!=NULL)
	{
		print(cursor->data);
		cursor=cursor->next;
	}
	return ret;
}

void dlist_destroy(DList* thiz)
{
	DListNode* iter =thiz->first;
	DListNode* next;
	while (iter->next!=NULL)
	{
		next=iter->next;
		dlist_node_destroy(iter);
		iter=next;
	}
	thiz->first=NULL;
	free(thiz);
}