#ifndef lib
#define lib

#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>

#define TREE treeavl_t *p_tree
#define PTREE treeavl_t **p_tree
#define ROOT node_t *p_root
#define SafeDelete(x)		{ if (NULL != (x)) { free_node(x);     (x) = NULL; } }

typedef struct _void_ref
{
	u_int32_t  key;
	void* p_context;
} void_ref_t;

typedef struct _node
{
	struct _node *p_child[2];

	void_ref_t ref;
    bool is_red;
} node_t;

typedef struct _treeavl
{
    node_t *data;
} treeavl_t;

bool insert(TREE, void_ref_t ref);
void delete(TREE, const u_int32_t key);
void* lookup(TREE, const u_int32_t key);

bool new(PTREE);
void destructor(PTREE);
void print(TREE);
#endif
