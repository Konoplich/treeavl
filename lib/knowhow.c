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
    node_t* p_right_child = p_root->p_right;
    p_root->p_right = p_right_child->p_left;
    p_right_child->p_left = p_root;
 
    // update the heights of the nodes
    p_root->ht = height(p_root);
    p_right_child->ht = height(p_right_child);
 
    // return the new node after rotation
    return p_right_child;
}
 
// rotates to the p_right
node_t* rotate_right(ROOT)
{
    node_t* p_left_child = p_root->p_left;
    p_root->p_left = p_left_child->p_right;
    p_left_child->p_right = p_root;
 
    // update the heights of the nodes
    p_root->ht = height(p_root);
    p_left_child->ht = height(p_left_child);
 
    // return the new node after rotation
    return p_left_child;
}
 
// calculates the balance factor of a node
int balance_factor(ROOT)
{
    if(NULL == p_root)
        return 0;
    return height(p_root->p_left) - height(p_root->p_right);
}
 

// inserts a new node in the AVL tree
node_t* insert_rec1(ROOT, void_ref_t data)
{
    if (p_root == NULL)
    {
        node_t* pNew = new_node();
        pNew->ref = data;
        p("new node: %d %s\n", pNew->ref.key, pNew->ref.p_context);
        if (pNew == NULL)
        {
            return NULL;
        }
        return  pNew;
    }
    else if (data.key > p_root->ref.key)
    {
        p("\n");
        // insert the new node to the p_right
        p_root->p_right = insert_rec1(p_root->p_right, data);
 
        // tree is unbalanced, then rotate it
        if (balance_factor(p_root) == -2)
        {
            if (data.key > p_root->p_right->ref.key)
            {                
                p_root = rotate_left(p_root);
                p("rotete left\n");
            }
            else
            {
                p_root->p_right = rotate_right(p_root->p_right);
                p_root = rotate_left(p_root);
                p("rotate right,left\n");
            }
        }
    }
    else 
    {
        p("\n");
        // insert the new node to the p_left
        p_root->p_left = insert_rec1(p_root->p_left, data);
 
        // tree is unbalanced, then rotate it
        if (balance_factor(p_root) == 2)
        {
            if (data.key < p_root->p_left->ref.key)
            {
                p_root = rotate_right(p_root);
            }
            else
            {
                p_root->p_left = rotate_left(p_root->p_left);
                p_root = rotate_right(p_root);
            }
        }
    }
    // update the heights of the nodes
    p_root->ht = height(p_root);
    return p_root;
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
    else if (data.key > p_root->ref.key)
    {
        p("\n");
        // insert the new node to the p_right
        p_root->p_right = insert_rec(p_root->p_right, data);
    }
    else if (data.key < p_root->ref.key)
    {
        p("\n");
        // insert the new node to the p_left
        p_root->p_left = insert_rec(p_root->p_left, data);
    }
    else
        return p_root;

    // Update the balance factor of each p_root and
  // balance the 
  p_root->ht = 1 + (Max(height(p_root->p_left), height(p_root->p_right)));
  int balanceFactor = balance_factor(p_root);
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

// deletes a node from the AVL tree
node_t * delete_rec(ROOT, u_int32_t x)
{
    node_t * temp = NULL;
 
    if (p_root == NULL)
    {
        return NULL;
    } 
 
    if (x > p_root->ref.key)
    {
        p_root->p_right = delete_rec(p_root->p_right, x);
        if (balance_factor(p_root) == 2)
        {
            if (balance_factor(p_root->p_left) >= 0)
            {
                p_root = rotate_right(p_root);
            }
            else
            {
                p_root->p_left = rotate_left(p_root->p_left);
                p_root = rotate_right(p_root);
            }
        }
    }
    else if (x < p_root->ref.key)
    {
        p_root->p_left = delete_rec(p_root->p_left, x);
        if (balance_factor(p_root) == -2)
        {
            if (balance_factor(p_root->p_right) <= 0)
            {
                p_root = rotate_left(p_root);
            }
            else
            {
                p_root->p_right = rotate_right(p_root->p_right);
                p_root = rotate_left(p_root);
            }
        }
    }
    else
    {
        if (p_root->p_right != NULL)
        { 
            temp = p_root->p_right;
            while (temp->p_left != NULL)
                temp = temp->p_left;
 
            p_root->ref = temp->ref;
            p_root->p_right = delete_rec(p_root->p_right, temp->ref.key);
            if (balance_factor(p_root) == 2)
            {
                if (balance_factor(p_root->p_left) >= 0)
                {
                    p_root = rotate_right(p_root);
                }
                else
                {
                    p_root->p_left = rotate_left(p_root->p_left);
                    p_root = rotate_right(p_root);
                }
            }
        }
        else
        {
            return (p_root->p_left);
        }
    }
    p_root->ht = height(p_root);
    return (p_root);
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
