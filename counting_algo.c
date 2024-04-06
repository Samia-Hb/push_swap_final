// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include "push_swap.h"
// #define INT_MIN -2147483648
// #define INT_MAX 2147483647

// typedef struct stack{
//     int data;
//     int index;
//     struct stack *next;
// } Stack;

void push(Stack **stackA, int data)
{
    Stack *node = malloc(sizeof(Stack));
    if (!node)
    {
        printf("Allocation Failure");
        return;
    }
    node -> data = data;
    node -> next = *stackA;
    *stackA = node;
}

Stack *pop(Stack **stack_s) 
{
    Stack *tmp = *stack_s;
    Stack *courant = (*stack_s) -> next;
    tmp -> data = (*stack_s) -> data;
    *stack_s = courant;
    return tmp;
}

void sa(Stack *stackA)  //it works
{
    Stack *courant = stackA->next;
    int tmp = stackA->data;
    stackA->data = courant->data;
    courant->data = tmp;
}

void sb(Stack *stackB) //it works
{
    Stack *courant = stackB->next;
    int tmp = stackB->data;
    stackB->data = courant->data;
    courant->data = tmp;
}

void ss(Stack *stackA,Stack *stackB) //it works
{
    sa(stackA);
    sb(stackB);
}

int	ft_lstsize(Stack *lst) //it works
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

void pa(Stack** stackA, Stack** stackB) //it works
{
    if (ft_lstsize(*stackB) > 0)
    {
        Stack *courant = pop(stackB);
        courant->next = *stackA;
        *stackA = courant;
    }
}

void pb(Stack** stackA, Stack** stackB) //it works
{
    if (ft_lstsize(*stackA) > 0)
    {
        Stack *courant = pop(stackA);
        courant->next = *stackB;
        *stackB = courant;
    }
}

void ra(Stack** stackA) //it works
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

void rb(Stack** stackB) //it works
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

void rr(Stack** stackA,Stack** stackB) //it works
{
    ra(stackA);
    rb(stackB);
}

void rra(Stack** stackA) //it works
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

void rrb(Stack** stackB) //it works
{
    Stack *last = *stackB;
    Stack *new_end = NULL;
    while(last->next != NULL)
    {
        new_end = last;
        last = last->next;
    }
    last -> next = *stackB;
    *stackB = last;
    new_end ->next = NULL;
}

void rrr(Stack** stackA,Stack** stackB) //it works
{
    rra(stackA);
    rrb(stackB);
}

int isStackSorted(Stack *s,int element)
{
    Stack *courant = s;
    Stack *courant1 = s->next;
    if(element == 1)
    {
        while (courant1 != NULL)
        {
            if (courant->data < courant1->data)
                return 0;
            courant = courant->next;
            courant1 = courant1->next;
        }
        return 1;
    }else if(element == 0)
    {
        while (courant1 != NULL)
        {
            if (courant->data > courant1->data)
                return 0;
            courant = courant->next;
            courant1 = courant1->next;
        }
    }
    return 1;
}

// void sort_stack(Stack *stack)
// {
//     while (isStackSorted(stack) != 1)
//     {
//         Stack *courant = stack;
//         Stack *tfoo = courant->next;
//         while (courant->next != NULL && tfoo != NULL)
//         {
//             if(courant->data < tfoo->data)
//             {
//                 int tmp = courant->data;
//                 courant->data = tfoo->data;
//                 tfoo->data = tmp;
//             }
//             courant = courant->next;
//             tfoo = tfoo->next;
//         }
//     }
// }

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

Stack *copied_stack(Stack *stack_to_copy)//it works
{
    Stack *copied = NULL;
    Stack *temp = NULL;
    int i = 0;
    int size = ft_lstsize(stack_to_copy);
    while (i < size)
    {
        push(&temp, stack_to_copy -> data);
        stack_to_copy = stack_to_copy->next;
        i++;
    }
    while(temp != NULL)
    {
        push(&copied, temp->data);
        temp = temp->next;
    }
    return copied;
}

void push2(Stack *node,Stack **dest)
{
    node->next = *dest;
    *dest = node;
}

int pos(Stack *stack,int element)   
{
    Stack *courant = stack;
    int i = 0;
    while(courant)
    {
        if(courant->data == element)
            return i;
        i++;
        courant = courant-> next;
    }
    return -1;
}

// int absolu(int number)
// {
//     if(number < 0)
//         return (number * -1);
//     else
//         return number;
// }

int find_closest_pos(Stack *stackB, int element)
{
    int Close_pos = -1;
    Stack *courant = stackB;
    int min_diff = INT_MIN;
    while (courant != NULL)
    {
        if (courant->data < element && courant ->data > min_diff)
        {
            min_diff = courant->data;
            Close_pos = pos(stackB,courant->data);
        }
        courant = courant -> next;
    }
    courant = stackB;               
    if (Close_pos == -1)
    {
        int max_element = INT_MIN;
        while (courant)
        {
            if (courant->data > max_element)           
                max_element = courant->data;            
            courant = courant->next;
        }
        Close_pos = pos(stackB,max_element);
    }
    return Close_pos;
}

int calcule_nbr_mouvement_stackB(Stack *stackB, int element)    //it works
{
    int movements = 0;
    Stack *copyB = stackB;
    int k = find_closest_pos(stackB, element);
    if(k == 0)
        return 0;
    else if(k <= ft_lstsize(stackB) / 2)
    {
        while(k != 0)
        {
            rb(&copyB);
            movements++;
            k--;
        }
    }
    else if (k == ft_lstsize(stackB) - 1)
    {
        rrb(&copyB);
        return (movements + 1);
    }
    else if (k > ft_lstsize(stackB) / 2 && k != ft_lstsize(stackB) - 1)
    {
        int size = ft_lstsize(stackB) - 1;
        while (k != 0)
        {
            rrb(&copyB);
            movements++;
            k++;
            if(k == size)
                break;
        }
        rrb(&copyB);
        movements++;
    }
    return movements;
}

int calcule_nbr_mouvement_stackA(Stack *stackA, Stack *stackB, int element)
{
    int movements = 0;
    Stack *copyA = copied_stack(stackA);
    Stack *copyB = copied_stack(stackB);
    int j = pos(stackA,element);
    int size = ft_lstsize(stackA) / 2;
    if(j == 0)
    {
        movements += calcule_nbr_mouvement_stackB(copyB,element);
        pb(&copyA,&copyB);
        movements++;
    }
    else if(j == 1)
    {
        sa(copyA);
        movements += calcule_nbr_mouvement_stackB(copyB,element);
        pb(&copyA,&copyB);
        movements += 2;
    }
    else if(j <= size && j > 1)
    {
        while(j != 0)
        {
            ra(&copyA);
            movements++;
            j--;
        }
        movements += calcule_nbr_mouvement_stackB(copyB,element);
        pb(&copyA,&copyB);
        movements++;
    }else if(j == ft_lstsize(stackA) - 1)
    {
        rra(&copyA);
        movements = calcule_nbr_mouvement_stackB(copyB,element);
        pb(&copyA,&copyB);
        movements += 2;
    }else if(j > size && j != ft_lstsize(stackA) - 1)
    {
        while(j != 0)
        {
            rra(&copyA);
            movements++;
            j = pos(copyA,element);
        }
        movements += calcule_nbr_mouvement_stackB(copyB,element);
        pb(&copyA,&copyB);
        movements++;
    }
    return (movements);
}

int calculate_Min_element(Stack *stackA,Stack *stackB)
{
    int Min_element = stackA -> data;
    Stack *courant = stackA;
    int Min_count = INT_MAX;
    int i = 0;
    int *count = malloc(ft_lstsize(stackA) * sizeof(int));
    if (!count)
    {
        printf("Allocation Failed");
        return 0;
    }
    while (i < ft_lstsize(stackA) && courant != NULL)
    {
        count[i] = calcule_nbr_mouvement_stackA(stackA, stackB, courant->data);
        if(count[i] < Min_count)
        {
            Min_count = count[i];
            Min_element = courant->data;
        }
        i++;
        courant = courant ->next;
    }
    free(count);
    return(Min_element);
}

void sort_stackb_before(Stack** stackB,int pos)
{
    if (pos == 0)
        return ;
    else if (pos <= ft_lstsize(*stackB) / 2)
    {
        while (pos != 0)
        {
            rb(stackB);
            printf("rb\n");
            pos--;
        }
    }
    else if (pos >= ft_lstsize(*stackB) / 2)
    {
        while (pos != ft_lstsize(*stackB) - 1)
        {
            rrb(stackB);
            printf("rrb\n");
            pos++;
        }
        if(pos == ft_lstsize(*stackB) - 1)
        {
            rrb(stackB);
            printf("rrb\n");
        }
    }
}

void push_the_min(Stack** stackA,Stack** stackB,int element,int pos)
{
    if(pos == 0)
    {
        sort_stackb_before(stackB,find_closest_pos(*stackB,element));  
        pb(stackA,stackB);
        printf("pb\n");
    }
    else if(pos == 1)
    {
        sa(*stackA);
        printf("sa\n");
        sort_stackb_before(stackB,find_closest_pos(*stackB,element));
        pb(stackA,stackB);
    }
    else if(pos <= ft_lstsize(*stackA) / 2 && pos > 1)
    {
        while(pos != 0)
        {
            ra(stackA);
            printf("ra\n");
            pos--;
        }
        sort_stackb_before(stackB,find_closest_pos(*stackB,element));
        pb(stackA,stackB);
    }
    else if (pos > ft_lstsize(*stackA) / 2)
    {
        while(pos != ft_lstsize(*stackA) - 1)
        {
            rra(stackA);
            printf("rra\n");
            pos++;
        }
        if(pos == ft_lstsize(*stackA) - 1)
        {
            rra(stackA);
            printf("rra\n");
            return;
        }
        sort_stackb_before(stackB,find_closest_pos(*stackB,element));
        pb(stackA,stackB);
    }
   
}
int isStackSorted_V2(Stack *stack)
{
    Stack *courant = stack;
    Stack *courant1 = stack->next;

    while (courant1 != NULL)
    {
        if (courant->data > courant1->data)
        {
            return 0;
        }
        courant = courant->next;
        courant1 = courant1->next;
    }
    return 1;
}
check_arguments(int argc,char **argv)
{
    int i = 0;
    char **numbersft_split(argv[1],' ');
}
int main(int argc, char** argv)
{
    check_arguments(argc,argv);
    Stack* stackA = NULL;
    Stack* stackB = NULL;
    if(argc == 1)
        return 0;
    while (argc != 1)
    {
        push(&stackA, atoi(argv[argc - 1]));
        argc--;
    }
    if(isStackSorted(stackA , 0))
        return 0;
    Stack *courant = stackA;
    int full_size = ft_lstsize(stackA);
    push2(pop(&stackA), &stackB);
    push2 (pop(&stackA), &stackB);
    int size = ft_lstsize(stackA);
    while (size != 0 && ft_lstsize(stackB) != full_size) // Continue until stackA is empty
    {
        int Min_element = calculate_Min_element(stackA, stackB);
        push_the_min(&stackA, &stackB, Min_element, pos(stackA, Min_element));
        size++;
    }
    if (!isStackSorted(stackB,0))
    {
        int max_element = 0;
        courant = stackB;
        while (courant)
        {
            if(courant->data > max_element)
                max_element = courant->data;
            courant = courant->next;
        }
        int position = pos(stackB,max_element);
        while(position != 0)
        {
            if(position <= ft_lstsize(stackB) / 2)
            {
                rb(&stackB);
                printf("ra\n");
            }
            else if(position > ft_lstsize(stackB) / 2)
            {
                rrb(&stackB);
                printf("rrb\n");
            }
            position = pos(stackB,max_element);
        }
    }
    courant = stackB;
    push2 (pop(&stackB), &stackA);
    printf("pa\n");
    size = ft_lstsize(stackB);
    while (size != 0)
    {
        pa(&stackA,&stackB);
        printf("pa\n");
        size --;
    }
    // printf("=================>final_stack_A\n");
    // courant = stackA;
    // printf("-------------------------\n");
    // while(courant)
    // {
    //     printf("final_data = %d\n",courant->data);
    //     courant = courant->next;
    // }
    return 0;
}