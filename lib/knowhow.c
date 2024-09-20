#ifndef knowhow_c
#define knowhow_c
#include <interface.c>
#include <public.c>
#include <protected.c>
#include <private.c>
#include <stdlib.h>
// calculate the height of the node
int height(ROOT)
{
    if(NULL == p_root)
        return 0;
   return p_root->ht;
}
 
// rotates to the p_left
node_t* rotate_left(ROOT)
{
    p("rl\n");
  node_t *y = p_root->p_right;
  node_t *T2 = y->p_left;
  y->p_left = p_root;
  p_root->p_right = T2;
  p_root->ht = Max(height(p_root->p_left), height(p_root->p_right)) + 1;
  y->ht = Max(height(y->p_left), height(y->p_right)) + 1;
  return y;
}

 
// rotates to the p_right
node_t* rotate_right(ROOT)
{
    p("rr\n");
    node_t *x = p_root->p_left;
    node_t *T2 = x->p_right;
    x->p_right = p_root;
    p_root->p_left = T2;
    p_root->ht = Max(height(p_root->p_left),
          height(p_root->p_right)) +
        1;
    x->ht = Max(height(x->p_left),
          height(x->p_right)) +
        1;
    return x;
}
 
// calculates the balance factor of a node
int balance_factor(ROOT)
{
    if(NULL == p_root)
        return 0;
    return height(p_root->p_left) - height(p_root->p_right);
}
 
// inserts a new node in the AVL tree
node_t* insert_rec(ROOT, void_ref_t data)
{
    if (p_root == NULL)
    {
        node_t* pNew = new_node();
        if (pNew == NULL)
        {
            return NULL;
        }
        pNew->ref = data;
        p("new node: %d %s\n", pNew->ref.key, pNew->ref.p_context);
        return  pNew;
    }
    
    if (data.key > p_root->ref.key)
    {
        p("ins right\n");
        // insert the new node to the p_right
        p_root->p_right = insert_rec(p_root->p_right, data);
    }
    else if (data.key < p_root->ref.key)
    {
        p("ins left\n");
        // insert the new node to the p_left
        p_root->p_left = insert_rec(p_root->p_left, data);
    }
    else
        return p_root;

    // Update the balance factor of each p_root and
  // balance the 
  p_root->ht = 1 + (Max(height(p_root->p_left), height(p_root->p_right)));
  int balanceFactor = balance_factor(p_root);

  p("balance %d\n", balanceFactor);
  if (balanceFactor > 1) {
    if (data.key < p_root->p_left->ref.key) {
      return rotate_right(p_root);
    } else if (data.key > p_root->p_left->ref.key) {
      p_root->p_left = rotate_left(p_root->p_left);
      return rotate_right(p_root);
    }
  }
  if (balanceFactor < -1) {
    if (data.key > p_root->p_right->ref.key) {
      return rotate_left(p_root);
    } else if (data.key < p_root->p_right->ref.key) {
      p_root->p_right = rotate_right(p_root->p_right);
      return rotate_left(p_root);
    }
  }
  return p_root;
}


void insert(TREE, void_ref_t data)
{
    if(NULL == p_tree)
        return;
    p_tree->data = insert_rec(p_tree->data, data);
}

node_t* node_with_min_value(ROOT) {
  node_t *current = p_root;
  while (current->p_left != NULL)
    current = current->p_left;
  return current;
}

// deletes a node from the AVL tree
node_t * delete_rec(ROOT, u_int32_t key)
{
    p("in del: %d\n", key);
    // Find the node and delete it
  if (p_root == NULL)
    return p_root;
  if (key < p_root->ref.key)
    p_root->p_left = delete_rec(p_root->p_left, key);
  else if (key > p_root->ref.key)
    p_root->p_right = delete_rec(p_root->p_right, key);
  else {
    if ((p_root->p_left == NULL) || (p_root->p_right == NULL)) 
    {
        p("del found %d\n", key);
      node_t *temp = p_root->p_left ? p_root->p_left : p_root->p_right;
      if (temp == NULL) {
        temp = p_root;
        p_root = NULL;
      } else
        *p_root = *temp;
      p("del %p\n", temp);
      free(temp);
    } else {
      node_t *temp = node_with_min_value(p_root->p_right);
      p_root->ref.key = temp->ref.key;
      p_root->p_right = delete_rec(p_root->p_right,
                   temp->ref.key);
    }
  }

  if (p_root == NULL)
    return p_root;

  // Update the balance factor of each node and
  // balance the tree
  p_root->ht = 1 + (Max(height(p_root->p_left), height(p_root->p_right)));
  int balanceFactor = balance_factor(p_root);
  if (balanceFactor > 1) {
    if (balance_factor(p_root->p_left) >= 0) {
      return rotate_right(p_root);
    } else {
      p_root->p_left = rotate_left(p_root->p_left);
      return rotate_right(p_root);
    }
  }
  if (balanceFactor < -1) {
    if (balance_factor(p_root->p_right) <= 0) {
      return rotate_left(p_root);
    } else {
      p_root->p_right = rotate_right(p_root->p_right);
      return rotate_left(p_root);
    }
  }
  return p_root;
}

void delete(TREE, u_int32_t key)
{
    if(NULL == p_tree || NULL == p_tree->data)
        return;
    p_tree->data = delete_rec(p_tree->data, key);
}

 // search a node in the AVL tree
node_t* lookup_rec(ROOT, u_int32_t key)
{
    if (p_root == NULL)
    {
        return NULL;
    }
 
    if(p_root->ref.key == key)
    {
        return p_root;
    }
 
    if(key > p_root->ref.key)
    {
        return lookup_rec(p_root->p_right, key);
    }
    else
    {
        return lookup_rec(p_root->p_left, key);
    } 
}
 
// search a node in the AVL tree
void* lookup(TREE, u_int32_t key)
{
    if (NULL == p_tree || NULL == p_tree->data)
    {
        return NULL;
    }
    node_t* res = lookup_rec(p_tree->data, key);
    return (NULL == res)?NULL:res->ref.p_context;
}
 
// inorder traversal of the tree
void inorder(ROOT)
{
    if (p_root == NULL)
    {
        return;
    }
 
    inorder(p_root->p_left);
    printf("%d - %s\n", p_root->ref.key, p_root->ref.p_context);
    inorder(p_root->p_right);
}
 
// preorder traversal of the tree
void preorder(ROOT)
{
    if (p_root == NULL)
    {
        return;
    }
 
    printf("%d - %s\n", p_root->ref.key, p_root->ref.p_context);
    preorder(p_root->p_left);
    preorder(p_root->p_right);
}
 
// postorder traversal of the tree
void postorder(ROOT)
{
    if (p_root == NULL)
    {
        return;
    }
 
    postorder(p_root->p_left);
    postorder(p_root->p_right);
    printf("%d - %s\n", p_root->ref.key, p_root->ref.p_context);
}
#endif
