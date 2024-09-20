#include <stdlib.h>
#include <stdio.h>
#include <libtreeavl.h>
#include <stdbool.h>

void ins(PTREE, int key, char *val)
{
    void_ref_t v1 = {.key=key, .p_context=val};
    insert(*p_tree, v1);
}


int main(int argc, char** argv)
{
     TREE;
    bool res = new(&p_tree);
    printf("p_tree-%p\n", p_tree);
    if(false == res)
    {
        printf("error 1\n");
	    exit(1);
    }
    void_ref_t arr[] = 
    {
	{14, "e"}
	,{6, "e"}
	,{5, "e"}
	,{2, "e"}
	,{1, "e"}
	,{4, "e"}
    ,{9, "98"}
    ,{7, "98"}
    ,{8, "98"}
    ,{10, "98"}
    ,{11, "98"}
    ,{44, "98"}
    ,{22, "98"}
    ,{72, "98"}
    ,{63, "98"}
    ,{98, "98"}
    
    };
    for(int i=0; i < sizeof(arr)/sizeof(void_ref_t);i++)    {
	printf("ins %d %s\n", arr[i].key, arr[i].p_context);
	ins(&p_tree, arr[i].key, arr[i].p_context);
	print(p_tree);
	printf("\n");
    }

    exit(0);

    print(p_tree);

    char *v;
    char *msg[] = {"found %d %s\n", "not found %d\n"};

    v = lookup(p_tree, 4);
    printf(msg[!((size_t)v | (size_t)0)], 4, v);

    v = lookup(p_tree, 5);
    printf(msg[!((size_t)v | (size_t)0)], 5, v);

    v = lookup(p_tree, 99);
    printf(msg[!((size_t)v | (size_t)0)], 99, v);


    printf("delete 1,8,9,4 %p \n",p_tree);

    delete(p_tree, 1);
    //delete(p_tree, 2);
    delete(p_tree, 8);
    delete(p_tree, 9);
    delete(p_tree, 4);
    print(p_tree);

    destructor(&p_tree);
    printf("ok\n");
    return 0;
}
