#include <linux/slab.h>

	
struct sNode {
    char data;
    struct sNode* next;
};

long isMatchingPair(char character1, char character2)
{
    if (character1 == '(' && character2 == ')')
        return 1;
    else if (character1 == '{' && character2 == '}')
        return 1;
    else if (character1 == '[' && character2 == ']')
        return 1;
    else
        return 0;
}

void push(struct sNode** top_ref, int new_data)
{
    // allocate node
    struct sNode* new_node
        = (struct sNode*)kmalloc(sizeof(struct sNode),GFP_KERNEL);
 
    /*if (new_node == NULL) {
        return 0; //stack OF
    }*/
 
    // put in the data
    new_node->data = new_data;
 
    // link the old list off the new node
    new_node->next = (*top_ref);
 
    // move the head to point to the new node
    (*top_ref) = new_node;
}
 
// Function to pop an item from stack
int pop(struct sNode** top_ref)
{
    char res;
    struct sNode* top;
 
    // If stack is empty then error
    if (*top_ref == NULL) {
        return -1;
    }
    else {
        top = *top_ref;
        res = top->data;
        *top_ref = top->next;
        kfree(top);
        return res;
    }
}
