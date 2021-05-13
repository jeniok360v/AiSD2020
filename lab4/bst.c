#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 101


struct bst_node
{
    char data[MAX_SIZE];
    struct bst_node *right_child; 
    struct bst_node *left_child;
};

void load_file(struct bst_node **root, char filename[]);


int bst_find(struct bst_node *root, char x[]);
struct bst_node* bst_search(struct bst_node *root, char x[]);
struct bst_node* find_minimum(struct bst_node *root);
struct bst_node* find_maximum(struct bst_node *root);
struct bst_node* bst_new_node(char x[]);
struct bst_node* bst_insert(struct bst_node *root, char x[]);
struct bst_node* bst_insert_with_convertion(struct bst_node *root, char x[]);
struct bst_node* bst_delete(struct bst_node *root, char x[]);
struct bst_node* bst_inOrderSuccessor(struct bst_node* root, char x[]);
void bst_insert_convert(char **x);
void bst_inorder(struct bst_node *root);
void print(struct bst_node *root);

int main(int argc, char *argv[])
{
    struct bst_node *root = NULL;
    load_file(&root, "sample.txt");
    bst_inorder(root);
    printf("\n");

    root = bst_delete(root, "three");
    root = bst_delete(root, "three");
    root = bst_delete(root, "three");
    root = bst_delete(root, "Three");
    bst_inorder(root);

    printf("\n");
    return 0;
}



void load_file(struct bst_node **root, char filename[]){
    FILE *fp;
    long lSize;
    char *buffer;

    fp = fopen ( filename , "rb" );
    if( !fp ) perror(filename),exit(1);

    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );

    /* allocate memory for entire content */
    buffer = calloc( 1, lSize+1 );
    if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

    /* copy the file into the buffer */
    if( 1!=fread( buffer , lSize, 1 , fp) )
      fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);
    fclose(fp);

    /* do your work here, buffer is a string contains the whole text */ 
    char *string[256];           
    char delimit[]=" ,.;:!?-()[]{}<>\'\"\n";
    int i = 0, j = 0;
                                       
    string[i]=strtok(buffer,delimit);    // 5) Make use of i to be explicit 
    while(string[i]!=NULL)                    
    {
        printf("string [%d]=%s\n",i,string[i]);
        i++;
        string[i]=strtok(NULL,delimit);
    }

    //struct bst_node *root = NULL;
    bst_insert_convert(&string[0]);
    *root = bst_new_node(string[0]);
    for (j=1;j<i;j++){
        bst_insert_with_convertion(*root, string[j]);
    }
    //bst_inorder(*root);
    free(buffer);
}

int bst_find(struct bst_node *root, char x[])
{
    struct bst_node *temp;
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

struct bst_node* bst_search(struct bst_node *root, char x[])
{
    if(root==NULL || strcmp(root->data, x)==0) //if root->data is x then the element is found
        return root;
    else if(strcmp(x, root->data)>0) // x is greater, so we will bst_search the right subtree
        return bst_search(root->right_child, x);
    else //x is smaller than the data, so we will bst_search the left subtree
        return bst_search(root->left_child, x);
}


struct bst_node* find_minimum(struct bst_node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->left_child != NULL) 
        return find_minimum(root->left_child); 
    return root;
}

struct bst_node* find_maximum(struct bst_node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->right_child != NULL) 
        return find_maximum(root->right_child); 
    return root;
}

//function to create a bst_node
struct bst_node* bst_new_node(char x[])
{
    struct bst_node *p;
    p = malloc(sizeof(struct bst_node));
    //bst_insert_convert(&x);
    strcpy(p->data, x);
    //p->data = x;
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}

struct bst_node* bst_insert(struct bst_node *root, char x[])
{
    //bst_insert_convert(&x);
    if(root==NULL)
        return bst_new_node(x);
    else if(strcmp(x, root->data)>0) // x is greater. Should be inserted to right
        root->right_child = bst_insert(root->right_child, x);
    else // x is smaller should be inserted to left
        root->left_child = bst_insert(root->left_child,x);
    return root;
}

struct bst_node* bst_insert_with_convertion(struct bst_node *root, char x[]){
    bst_insert_convert(&x);
    return bst_insert(root, x);
}

struct bst_node* bst_delete(struct bst_node *root, char x[])
{
    if(root==NULL)
        return NULL;
    if (strcmp(x, root->data)>0)
        root->right_child = bst_delete(root->right_child, x);
    else if(strcmp(x, root->data)<0)
        root->left_child = bst_delete(root->left_child, x);
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
            struct bst_node *temp;
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
            struct bst_node *temp = find_minimum(root->right_child);
            strcpy(root->data, temp->data);
            root->right_child = bst_delete(root->right_child, temp->data);
        }
    }
    return root;
}

struct bst_node* bst_inOrderSuccessor(struct bst_node* root, char x[])
{
    struct bst_node* n = bst_search(root, x);
    if(n == NULL){
        printf("\nNo such element!\n");
        return NULL;
    }
    if (n->right_child != NULL)
        return find_minimum(n->right_child);
 
    struct bst_node* succ = NULL;
 
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

void bst_insert_convert(char** temp){
    int length = (int)strlen(*temp);
    printf("strlen(%s)=%i\n", *temp, length);
    char* x = calloc(length+1, sizeof(char));
    memcpy(x, *temp, length+1);
    if(length>1){
        if(!isalpha(x[length-1])){
            x[length-1]='\0';
        }
        if(!isalpha(x[0])){
            memmove(x, x+1, strlen(x));
        }
    }
    else if(length==1){
        if(!isalpha(x[0])){
            x[0]='\0';
        }
    }
    *temp = x;
    return;
}

void bst_inorder(struct bst_node *root)
{
    if(root!=NULL) // checking if the root is not null
    {
        bst_inorder(root->left_child); // visiting left child
        printf(" %s ", root->data); // printing data at root
        bst_inorder(root->right_child);// visiting right child
    }
}

void print(struct bst_node *root){
    if(root!=NULL){
        printf("%s\n", root->data);
    }
}

