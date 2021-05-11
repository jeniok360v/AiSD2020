#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 101


struct node
{
    char data[MAX_SIZE];
    struct node *right_child; 
    struct node *left_child;
};

int find(struct node *root, char x[])
{
    struct node *temp;
    temp = root;
    for(;;){
        if(temp == NULL){
            return 0;
        }
        if(strcmp(temp->data, x)==0){
            return 1;
        }
        if(strcmp(x, temp->data)>0){
            //printf("%s\n", )
            temp=temp->right_child;
        }
        else{
            temp=temp->left_child;
        }
    }
    printf("error!\n");
    return -1;
}

struct node* search(struct node *root, char x[])
{
    if(root==NULL || strcmp(root->data, x)==0) //if root->data is x then the element is found
        return root;
    else if(strcmp(x, root->data)>0) // x is greater, so we will search the right subtree
        return search(root->right_child, x);
    else //x is smaller than the data, so we will search the left subtree
        return search(root->left_child, x);
}


struct node* find_minimum(struct node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->left_child != NULL) 
        return find_minimum(root->left_child); 
    return root;
}

struct node* find_maximum(struct node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->right_child != NULL) 
        return find_maximum(root->right_child); 
    return root;
}

//function to create a node
struct node* new_node(char x[])
{
    struct node *p;
    p = malloc(sizeof(struct node));
    strcpy(p->data, x);
    //p->data = x;
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}

struct node* insert(struct node *root, char x[])
{
    //searching for the place to insert
    if(root==NULL)
        return new_node(x);
    else if(strcmp(x, root->data)>0) // x is greater. Should be inserted to right
        root->right_child = insert(root->right_child, x);
    else // x is smaller should be inserted to left
        root->left_child = insert(root->left_child,x);
    return root;
}

struct node* delete(struct node *root, char x[])
{
    if(root==NULL)
        return NULL;
    if (strcmp(x, root->data)>0)
        root->right_child = delete(root->right_child, x);
    else if(strcmp(x, root->data)<0)
        root->left_child = delete(root->left_child, x);
    else
    {
        //No Children
        if(root->left_child==NULL && root->right_child==NULL)
        {
            free(root);
            return NULL;
        }
        //One Child
        else if(root->left_child==NULL || root->right_child==NULL)
        {
            struct node *temp;
            if(root->left_child==NULL)
                temp = root->right_child;
            else
                temp = root->left_child;
            free(root);
            return temp;
        }
        //Two Children
        else
        {
            struct node *temp = find_minimum(root->right_child);
            strcpy(root->data, temp->data);
            root->right_child = delete(root->right_child, temp->data);
        }
    }
    return root;
}

struct node* inOrderSuccessor(struct node* root, char x[])
{
    struct node* n = search(root, x);
    if(n == NULL){
        printf("\nWTF\n");
        return NULL;
    }
    if (n->right_child != NULL)
        return find_minimum(n->right_child);
 
    struct node* succ = NULL;
 
    // Start from root and search for
    // successor down the tree
    while (root != NULL)
    {
        if (strcmp(n->data, root->data)<0)
        {
            succ = root;
            root = root->left_child;
        }
        else if (strcmp(n->data, root->data)>0)
            root = root->right_child;
        else
            break;
    }
    return succ;
}

void inorder(struct node *root)
{
    if(root!=NULL) // checking if the root is not null
    {
        inorder(root->left_child); // visiting left child
        printf(" %s ", root->data); // printing data at root
        inorder(root->right_child);// visiting right child
    }
}

void print(struct node *root){
    if(root!=NULL){
        printf("%s\n", root->data);
    }
}

int main()
{
    /*
                   20
                 /    \
                /      \
               5       30
             /   \     /\
            /     \   /  \
           1      15 25  40
                /          \
               /            \
              9             45
            /   \          /
           /     \        /
          7      12      42
    */
    struct node *root = NULL;
    root = new_node("20");
    insert(root,"5" );
    insert(root,"1" );
    insert(root,"15");
    insert(root,"9" );
    insert(root,"7" );
    insert(root,"12");
    insert(root,"30");
    insert(root,"25");
    insert(root,"40");
    insert(root,"45");
    insert(root,"42");

    printf("%i\n\n", find(root, "42"));
    print(inOrderSuccessor(root,"45"));
    print(inOrderSuccessor(root,"25"));
    print(inOrderSuccessor(root,"42"));
    print(inOrderSuccessor(root,"12"));
    printf("\n\n");
    print(find_minimum(root));
    print(find_maximum(root));

    inorder(root);
    printf("\n");

    root = delete(root, "1");
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25   40
                /           \
               /             \
              9              45
            /   \           /
           /     \         /
          7      12       42
    */

    root = delete(root, "40");
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25  45
                 /       / 
                /       /   
               9       42    
             /   \          
            /     \        
           7      12      
    */

    root = delete(root, "45");
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25  42
                 /          
                /            
               9            
             /   \          
            /     \        
           7      12      
    */
    root = delete(root, "9");
    inorder(root);
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25  42
                 /          
                /            
               12            
             /             
            /             
           7            
    */
    printf("\n");
    return 0;
}