#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NULL 0

typedef struct treeNode
{
    char data[100];
    struct treeNode* left;
    struct treeNode* right;
} treeNode;

class Queue
{
    struct Node
    {
        char data[100];
        struct Node* next;
    };

    struct Node* head;
    struct Node* tail;
    int length;

public:
    Queue()
    {
        init();
    }
    void init()
    {
        head = NULL;
        tail = NULL;
        length = 0;
    }
    bool is_empty()
    {
        if(length == 0)
            return true;
        return false;
    }
    void enqueue(const char* str)
    {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        strcpy(newNode->data, str);
        newNode->next = NULL;
        if(head == NULL)
            head = newNode;
        else
            tail->next = newNode;
        tail = newNode;
        length++;
    }
    char* peek_queue()
    {
        if(head == NULL)
            return NULL;
        return head->data;
    }
    char* dequeue()
    {
        struct Node* temp = head;
        char* ret = temp->data;
        head = head->next;
        if(head == NULL)
            tail = NULL;
        free(temp);
        length--;
        return ret;
    }
    void print()
    {
        struct Node* temp = head;
        while(temp != NULL)
        {
            printf("%d ",temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
};

class BST
{
    treeNode* create_Node(const char* str)
    {
        treeNode* newNode = (treeNode*) malloc(sizeof(treeNode));
        strcpy(newNode->data, str);
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

public:
    treeNode* root;

    BST()
    {
        init();
    }

    void init()
    {
        root = NULL;
    }

    treeNode* search(const char* str)
    {
        treeNode* temp = root;
        while(temp != NULL)
        {
            if(strcmp(temp->data, str) == 0)
                return temp;
            else if(strcmp(temp->data, str) > 0)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        return NULL;
    }

    void insert(const char* str)
    {
        if(root == NULL)
        {
            treeNode* newNode = create_Node(str);
            root = newNode;
            return;
        }
        treeNode* temp = root;
        while(1)
        {
            if(strcmp(temp->data, str) > 0)
            {
                if(temp->left == NULL)
                {
                    treeNode* newNode = create_Node(str);
                    temp->left = newNode;
                    return;
                }
                else
                {
                    temp = temp->left;
                }
            }
            else
            {
                if(temp->right == NULL)
                {
                    treeNode* newNode = create_Node(str);
                    temp->right = newNode;
                    return;
                }
                else
                {
                    temp = temp->right;
                }
            }
        }
    }

    void remove(const char* str)
    {
        treeNode* temp = root;
        treeNode* par;
        // search for the item intended to delete
        while(temp!= NULL)
        {
            if(strcmp(temp->data, str) == 0)
            {
                break;
            }
            else if(strcmp(temp->data, str) > 0)
            {
                par = temp;
                temp = temp->left;
            }
            else
            {
                par = temp;
                temp = temp->right;
            }
        }
        // no need to delete if item not found
        if(temp == NULL)
        {
            return;
        }
        // case 1: leaf node
        if(temp->left == NULL && temp->right == NULL)
        {
            // corner case
            if(temp == root)
            {
                root = NULL;
                free(temp);
                return;
            }
            // general case
            if(par->left == temp)
                par->left = NULL;
            else
                par->right = NULL;
            free(temp);
            return;
        }
        // case 2: one(right) child
        else if(temp->left == NULL)
        {
            // corner case
            if(temp == root)
            {
                root = temp->right;
                free(temp);
                return;
            }
            // general case
            if(par->left == temp)
                par->left = temp->right;
            else
                par->right = temp->right;
            free(temp);
            return;
        }
        // case 2: one(left) child
        else if(temp->right == NULL)
        {
            // corner case
            if(temp == root)
            {
                root = temp->left;
                free(temp);
                return;
            }
            // general case
            if(par->left == temp)
                par->left = temp->left;
            else
                par->right = temp->left;
            free(temp);
            return;
        }
        // case 3: two children
        else
        {
            // find the next greatest item
            treeNode* ng = temp->right;
            treeNode* ngPar = temp;
            while(ng->left != NULL)
            {
                ngPar = ng;
                ng = ng->left;
            }
            // replace
            strcpy(temp->data, ng->data);

            // now delete next greatest item using either case 1 or 2:
            // case 1: leaf node
            if(ng->left == NULL && ng->right == NULL)
            {
                if(ngPar->left == ng)
                    ngPar->left = NULL;
                else
                    ngPar->right = NULL;
                free(ng);
                return;
            }
            // case 2: one(right) child
            else if(ng->left == NULL)
            {
                if(ngPar->left == ng)
                    ngPar->left = ng->right;
                else
                    ngPar->right = ng->right;
                free(ng);
                return;
            }
            // case 2: one(left) child
            else if(ng->right == NULL)
            {
                if(ngPar->left == ngPar)
                    ngPar->left = ng->left;
                else
                    ngPar->right = ng->left;
                free(ng);
                return;
            }
        }
    }

    void print_tree_rec(treeNode* t, int depth)
    {
        if(t == NULL)
            return;
        // print right sub tree
        print_tree_rec(t->right, depth+1);
        // print node
        for(int i=0; i<depth; i++)
            printf("\t");
        printf("%s---------------------------------\n", t->data);
        // print left sub tree
        print_tree_rec(t->left, depth+1);
    }

    void print_tree()
    {
        printf("Printing tree\n\n");
        print_tree_rec(root, 0);
        printf("\n");
    }

    void print_inorder_rec(treeNode* t)
    {
        if(t == NULL)
            return;
        print_inorder_rec(t->left);
        printf("%s ", t->data);
        print_inorder_rec(t->right);
    }

    void print_inorder()
    {
        printf("Printing Inorder: ");
        print_inorder_rec(root);
        printf("\n\n");
    }

    treeNode* copyBST_rec(treeNode* t)
    {
        if(t == NULL)
            return NULL;
        treeNode* newNode = create_Node(t->data);
        newNode->left = copyBST_rec(t->left);
        newNode->right = copyBST_rec(t->right);
        return newNode;
    }

    BST copyBST()
    {
        BST newBST;
        newBST.root = copyBST_rec(root);
        return newBST;
    }

    void List_items_rec(treeNode* t, Queue& q)
    {
        if(t == NULL)
            return;
        List_items_rec(t->left, q);
        q.enqueue(t->data);
        List_items_rec(t->right, q);
    }

    Queue List_items()
    {
        Queue q;
        List_items_rec(root, q);
        return q;
    }
};

BST Set_Union(BST x, BST y)
{
    BST z;
    // copy all items of x into z
    z = x.copyBST();
    // make a list of all items in y
    Queue q = y.List_items();

    while(!q.is_empty())
    {
        // take items of y one at a time
        char str[100];
        strcpy(str, q.peek_queue());
        q.dequeue();

        // if the item is not already in z, add it to z
        if(z.search(str) == NULL)
        {
            z.insert(str);
        }
    }
    return z;
}

BST Set_Intersection(BST x, BST y)
{
    BST z;
    BST New;
    New = x.copyBST();
    Queue q = y.List_items();

    while(!q.is_empty())
    {
        char str[100];
        strcpy(str, q.peek_queue());
        q.dequeue();

        if(New.search(str)!= NULL)
        {
            z.insert(str);
        }
    }

    return z;
}

BST Set_Minus(BST x, BST y)
{
    BST z;

    z = x.copyBST();

    Queue q = y.List_items();

    while(!q.is_empty())
    {

        char str[100];
        strcpy(str, q.peek_queue());
        q.dequeue();


        if(z.search(str)!= NULL)
        {
            z.remove(str);
        }
    }

    return z;
}

int main()
{
    BST t1;
    t1.insert("Bangla");
    t1.insert("Chemistry");
    t1.insert("English");
    t1.insert("Geology");
    t1.insert("History");
    t1.insert("Math");
    t1.insert("Statistics");
    printf("Set t1: \n");
    t1.print_tree();
    t1.print_inorder();

    BST t2;
    t2.insert("Accounting");
    t2.insert("Bangla");
    t2.insert("Biology");
    t2.insert("Economics");
    t2.insert("English");
    t2.insert("Physics");
    printf("Set t2: \n");
    t2.print_tree();
    t2.print_inorder();

    BST A = Set_Union(t1, t2);
    printf("Set A: Union of t1 and t2\n");
    A.print_tree();
    A.print_inorder();

    BST B = Set_Intersection(t1, t2);
    printf("Set B: Intersection of t1 and t2\n");
    B.print_tree();
    B.print_inorder();

    BST C = Set_Minus(t1, t2);
    printf("Set C: Minus of t1 and t2\n");
    C.print_tree();
    C.print_inorder();

    return 0;
}

