#include <stdio.h>
#include <assert.h>
#include "dlist.h"

DListRet print_int(void* data)
{
	DListRet ret= DLIST_RET_OK;
	printf("%d ",(int)data);
	return ret;
}

DListRet print_str(void* data)
{
	DListRet ret= DLIST_RET_OK;
	printf("%d ",(int)data);
	return ret;
}

int main(int argc, char* argv[])
{
	int i = 0;
	int n = 100;
//	int temp2=0;
	int *temp=NULL;

	DList* dlist = dlist_create();

	for(i = 0; i < n; i++)
	{
		assert(dlist_append(dlist, (void*)i) == DLIST_RET_OK);
	}
	for(i = 0; i < n; i++)
	{
		assert(dlist_prepend(dlist, (void*)i) == DLIST_RET_OK);
	}

	dlist_print(dlist, print_int);

	printf("\n");
	printf("\n");

	dlist_get_by_index(dlist,10,(void**)&temp);   //²âÊÔset_by_index
	print_int((void*)temp);
	printf("\n");

	dlist_set_by_index(dlist,1,(void*)100);       //²âÊÔget_by_index
	dlist_print(dlist, print_int);

	printf("\n");
	printf("\n");

	dlist_delete(dlist,1);
	dlist_print(dlist, print_int);                //²âÊÔdlist_delete

	printf("\n");
	printf("\n");

	dlist_destroy(dlist);

	return 0;
}