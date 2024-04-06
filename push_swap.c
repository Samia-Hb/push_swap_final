#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack{
    int data;
    int index;
    struct stack *next;
} Stack;

void push(Stack **stackA, int data)
{
    Stack *node = malloc(sizeof(Stack));
    if (!node)
    {
        printf("Allocation Failure");
        return;
    }
    node->data = data;
    node->next = *stackA;
    *stackA = node;
}

Stack *pop(Stack **stack_s)
{
    Stack *tmp = malloc(sizeof(Stack));
    Stack *courant = (*stack_s) -> next;
    if(!tmp)
    {
        printf("Allocation Failure");
        exit(1);
    }
    tmp -> data = (*stack_s) -> data;
    *stack_s = courant;
    return tmp;
}

void sa(Stack *stackA)
{
    Stack *courant = stackA->next;
    int tmp = stackA->data;
    stackA->data = courant->data;
    courant->data = tmp;
}

void sb(Stack *stackB)
{
    Stack *courant = stackB->next;
    int tmp = stackB->data;
    stackB->data = courant->data;
    courant->data = tmp;
}

void ss(Stack *stackA,Stack *stackB)
{
    sa(stackA);
    sb(stackB);
}

int	ft_lstsize(Stack *lst)
{
	int		i;
	Stack	*courant;

	i = 0;
	courant = lst;
	while (courant != NULL)
	{
		i++;
		courant = courant -> next;
	}
	return (i);
}

void pa(Stack** stackA, Stack** stackB)
{
    if (ft_lstsize(*stackB) > 0)
    {
        Stack *courant = pop(stackB);
        courant->next = *stackA;
        *stackA = courant;
    }
}

void pb(Stack** stackA, Stack** stackB)
{
    if (ft_lstsize(*stackA) > 0)
    {
        Stack *courant = pop(stackA);
        courant->next = *stackB;
        *stackB = courant;
    }
}

void ra(Stack** stackA)
{
    if (*stackA == NULL || (*stackA)->next == NULL)
        return;
    Stack* last = *stackA;
    while (last->next != NULL)
        last = last->next;

    last->next = *stackA;
    *stackA = (*stackA)->next;
    last->next->next = NULL;
}

void rb(Stack** stackB)
{
    if (*stackB == NULL || (*stackB)->next == NULL)
        return;
    Stack* last = *stackB;
    while (last->next != NULL)
        last = last->next;
    last->next = *stackB;
    *stackB = (*stackB) -> next;
    last->next->next = NULL;
}

void rr(Stack** stackA,Stack** stackB)
{
    ra(stackA);
    rb(stackB);
}

void rra(Stack** stackA)
{
    Stack *last = *stackA;
    Stack *new_end = NULL;
    while(last ->next != NULL)
    {
        new_end = last;
        last = last->next;
    }
    last -> next = *stackA;
    *stackA = last;
    new_end ->next = NULL;
}

void rrb(Stack** stackB)
{
    Stack *last = *stackB;
    Stack *new_end = NULL;
    while(last ->next != NULL)
    {
        new_end = last;
        last = last->next;
    }
    last -> next = *stackB;
    *stackB = last;
    new_end ->next = NULL;
}

void rrr(Stack** stackA,Stack** stackB)
{
    rra(stackA);
    rrb(stackB);
}

Stack *copied_stack(Stack *stack_to_copy)
{
    Stack *copied = NULL;
    int i = 0;
    int size = ft_lstsize(stack_to_copy);
    while (i < size)
    {
        push(&copied, stack_to_copy -> data);
        stack_to_copy = stack_to_copy->next;
        i++;
    }
    return copied;
}

int isStackSorted(Stack *s)
{
    Stack *courant = s;
    Stack *courant1 = s->next;

    while (courant1 != NULL)
    {
        if (courant->data < courant1->data)
        {
            return 0; // not sorted
        }
        courant = courant->next;
        courant1 = courant1->next;
    }
    return 1; //sorted
}

void sort_stack(Stack *stack)
{
    while (isStackSorted(stack) != 1)
    {
        Stack *courant = stack;
        Stack *tfoo = courant->next;
        while (courant->next != NULL && tfoo != NULL)
        {
            if (courant->data < tfoo->data)
            {
                int tmp = courant->data;
                courant->data = tfoo->data;
                tfoo->data = tmp;
            }
            courant = courant->next;
            tfoo = tfoo->next;
        }
    }
}

void set_index(Stack *stack)
{
    int i = ft_lstsize(stack) - 1;
    Stack *courant = stack;
    while(courant != NULL)
    {
        courant -> index = i;
        courant = courant->next;
        i--;
    }
}
void push2(Stack *node,Stack **dest)
{
    node->next = *dest;
    *dest = node;
}
// Function to calculate the number of movements required to place an element in its correct position
int calcule_nbr_mouvement(Stack *stackA, Stack *stackB, int element)
{
    int movements = 0;

    Stack *currentA = stackA;
    Stack *currentB = stackB;
    //Find the position of the element in stack B
    int targetIndex = -1;
    while (currentB != NULL) {
        if (currentB->data == element) {
            targetIndex = currentB->index;
            break;
        }
        currentB = currentB->next;
    }
    // Push elements from stack A to stack B until the element is in its correct position
    while (currentA != NULL && currentA->data != element) {
        if (currentA->index > targetIndex) {
            // Move the element to the top of stack A
            while (currentA->index > targetIndex) {
                rra(&stackA);
                movements++;
            }
        } else {
            // Move the element to the top of stack A
            while (currentA->index < targetIndex) {
                ra(&stackA);
                movements++;
            }
        }
        // Push the element to stack B
        pb(&stackA, &stackB);
        movements++;
        currentA = stackA; // Reset currentA to the top of stack A
    }
    return movements;
}

int main(int argc, char** argv)
{
    Stack* stackA = NULL;
    while(argc != 1)
    {
        push(&stackA, atoi(argv[argc - 1]));
        argc--;
    }
    Stack* helper_stack = NULL;
    Stack* stackB = NULL;
    helper_stack = copied_stack(stackA);
    sort_stack(helper_stack);
    set_index(helper_stack);
    Stack *help;
    Stack *courant= stackA;
    while(courant)
    {
        help = helper_stack;
        while(help)
        {
            if(courant -> data == help->data)
                courant -> index = help->index;
            help = help -> next;
        }
        courant = courant -> next;
    }
    courant= stackA;
    push2(pop(&courant),&stackB);
    int Min_element = courant -> data;
    int *count = malloc(ft_lstsize(courant));
    if(!count)
    {
        printf("Allocation Failed");
        return 0;
    }
    count[0] = calcule_nbr_mouvement(courant);
    int Min_count = count[0];
    i = 0;
    Stack *tmp;
    while(courant != NULL)
    {
        tmp = courant->next;
        while(tmp != NULL)
        {
            count[i] = calcule_nbr_mouvement(tmp);
            if(count[i] < Min_count)
            {
                Min_count = count[i];
                Min_element = tmp->data;
            }
            tmp = tmp -> next;
            i++;
        }
        courant= courant->next;
    }
}
              

