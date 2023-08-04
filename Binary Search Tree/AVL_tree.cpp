#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NULL 0

typedef struct treeNode
{
    //int data;
    char data[100];
    struct treeNode* left;
    struct treeNode* right;
    int h;
} treeNode;

int max(int a, int b)
{
    return (a > b)? a : b;
}

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
        //newNode->data = value;
        strcpy(newNode->data, str);
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->h = 0;
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

    int height(treeNode* t)
    {
        return (t == NULL)? -1 : t->h;
    }

    int get_balance(treeNode* t)
    {
        return (t == NULL)? 0 : height(t->left) - height(t->right);
    }

    treeNode* search_rec(treeNode* t, const char* key)
    {
        if(t == NULL)
            return NULL;
        if(strcmp(t->data, key) == 0)
        {
            return t;
        }
        else if(strcmp(t->data, key) > 0)
        {
            return search_rec(t->left, key);
        }
        else
        {
            return search_rec(t->right, key);
        }
    }

    treeNode* search(const char* key)
    {
        return search_rec(root, key);
    }

    treeNode* left_rotate(treeNode *t)
    {
        treeNode* going_up = t->right;
        treeNode* re_adjust = going_up->left;

        // Perform rotation
        going_up->left = t;
        t->right = re_adjust;

        // Update heights
        t->h = 1 + max(height(t->left), height(t->right));
        going_up->h = 1 + max(height(going_up->left), height(going_up->right));

        // Return new root
        return going_up;
    }

    treeNode* right_rotate(treeNode *t)
    {
        treeNode* going_up = t->left;
        treeNode* re_adjust = going_up->right;

        // Perform rotation
        going_up->right = t;
        t->left = re_adjust;

        // Update heights
        t->h = 1 + max(height(t->left), height(t->right));
        going_up->h = 1 + max(height(going_up->left), height(going_up->right));

        // Return new root
        return going_up;
    }

    treeNode* insert_rec(treeNode* t, const char* value)
    {
        if(t == NULL)
        {
            return create_Node(value);
        }
        if(strcmp(t->data, value) > 0)
        {
            t->left = insert_rec(t->left, value);
        }
        else
        {
            t->right = insert_rec(t->right, value);
        }

        t->h = 1 + max(height(t->left), height(t->right));

        // If this node becomes unbalanced, then there are 4 cases
        if(get_balance(t) > 1)
        {
            // Left Left Case; z = t, y = t->left, x = t->left->left
            if(strcmp(t->left->data, value) > 0)
            {
                // right of y becomes left of z, z becomes right of y
                // pointer of y returned and returned to ex-parent of z
                return right_rotate(t);
            }
            // Left Right Case; z = t, y = t->left, x = t->left->right
            else
            {
                // left of x becomes right of y, y becomes left of x
                // x becomes left of z
                t->left = left_rotate(t->left);
                // right of x becomes left of z, z becomes right of x
                // pointer of x returned and returned to ex-parent of z
                return right_rotate(t);
            }
        }
        if(get_balance(t) < -1)
        {
            // Right Right Case; z = t, y = t->right, x = t->right->right
            if(strcmp(t->right->data, value) < 0)
            {
                // left of y becomes right of z, z becomes left of y
                // pointer of y returned and returned to ex-parent of z
                return left_rotate(t);
            }
            // Right Left Case; z = t, y = t->right, x = t->right->left
            else
            {
                // right of x becomes left of y, y becomes right of x
                // x becomes right of z
                t->right = right_rotate(t->right);
                // left of x becomes right of z, z becomes left of x
                // pointer of x returned and returned to ex-parent of z
                return left_rotate(t);
            }
        }
        // Else return unchanged
        return t;
    }

    void insert(const char* value)
    {
        root = insert_rec(root, value);
    }

    treeNode* remove_rec(treeNode* t, const char* value)
    {
        if(t == NULL)
            return NULL;

        if(strcmp(t->data, value) > 0)
        {
            t->left = remove_rec(t->left, value);
        }
        else if(strcmp(t->data, value) < 0)
        {
            t->right = remove_rec(t->right, value);
        }
        else
        {
            if(t->left == NULL || t->right == NULL)
            {
                treeNode* temp = (t->left != NULL) ? t->left : t->right;
                if(temp == NULL)
                {
                    temp = t;
                    t = NULL;
                }
                else
                {
                    // t->data = temp->data;
                    strcpy(t->data, temp->data);
                    t->left = temp->left;
                    t->right = temp->right;
                    t->h = temp->h;
                }
                free(temp);
            }
            else
            {
                treeNode* temp = t->right;
                while(temp->left != NULL)
                    temp = temp->left;

                // t->data = temp->data;
                strcpy(t->data, temp->data);
                t->right = remove_rec(t->right, temp->data);
            }
        }

        if(t == NULL)
            return NULL;

        t->h = 1 + max(height(t->left), height(t->right));

        // If this node becomes unbalanced, then there are 4 cases
        if(get_balance(t) > 1)
        {
            // Left Left Case; z = t, y = t->left, x = t->left->left
            if(get_balance(t->left) >= 0)
            {
                // right of y becomes left of z, z becomes right of y
                // pointer of y returned and returned to ex-parent of z
                return right_rotate(t);
            }
            // Left Right Case; z = t, y = t->left, x = t->left->right
            else
            {
                // left of x becomes right of y, y becomes left of x
                // x becomes left of z
                t->left = left_rotate(t->left);
                // right of x becomes left of z, z becomes right of x
                // pointer of x returned and returned to ex-parent of z
                return right_rotate(t);
            }
        }
        if(get_balance(t) < -1)
        {
            // Right Right Case; z = t, y = t->right, x = t->right->right
            if(get_balance(t->right) <= 0)
            {
                // left of y becomes right of z, z becomes left of y
                // pointer of y returned and returned to ex-parent of z
                return left_rotate(t);
            }
            // Right Left Case; z = t, y = t->right, x = t->right->left
            else
            {
                // right of x becomes left of y, y becomes right of x
                // x becomes right of z
                t->right = right_rotate(t->right);
                // left of x becomes right of z, z becomes left of x
                // pointer of x returned and returned to ex-parent of z
                return left_rotate(t);
            }
        }
        // Else return unchanged
        return t;
    }

    void remove(const char* value)
    {
        root = remove_rec(root, value);
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
        printf("%s (h=%d)---------------------------------\n", t->data, t->h);
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
    // write your code here

    return z;
}

BST Set_Minus(BST x, BST y)
{
    BST z;
    // write your code here

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

//    BST B = Set_Intersection(t1, t2);
//    printf("Set B: Intersection of t1 and t2\n");
//    B.print_tree();
//    B.print_inorder();
//
//    BST C = Set_Minus(t1, t2);
//    printf("Set C: Minus of t1 and t2\n");
//    C.print_tree();
//    C.print_inorder();

    return 0;
}

