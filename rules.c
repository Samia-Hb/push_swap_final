#include "push_swap.h"

int	ft_lstsize(stack_a *lst)
{
	int		i;
	stack_a	*courant;

	i = 0;
	courant = lst;
	while (courant != NULL)
	{
		i++;
		courant = courant -> next;
	}
	return (i);
}

int	ft_lstsize1(stack_b *lst)
{
	int		i;
	stack_b	*courant;

	i = 0;
	courant = lst;
	while (courant != NULL)
	{
		i++;
		courant = courant -> next;
	}
	return (i);
}

void sa(stack_a* stack)
{
    stack_a *tmp = malloc(sizeof(stack_a));
    if(ft_lstsize(stack) > 1)
    {
        stack_a *node;
        node = top -> next;
        tmp->data = top->data;
        top->data = node->data;
        node->data = tmp->data;
    }
}

void sb(stack_b* stack1)
{
    stack_b *tmp = malloc(sizeof(stack_b));
    if (ft_lstsize1(stack1) > 1)
    {
        stack_b *node;
        node = top1 -> next;
        tmp->data = top1->data;
        top1->data = node->data;
        node->data = tmp->data;
    }
}

void ss(stack_a* stack, stack_b* stack1)
{
    sa(stack);
    sb(stack1);
}
void pa(stack_a** stack, stack_b** stack1)
{
    if (ft_lstsize1(*stack1) > 0)
    {
        stack_a* tmp = malloc(sizeof(stack_a));
        if (!tmp)
            return;
        tmp->data = top1->data;
        tmp->next = *stack;
        *stack = tmp;
        top1 = top1->next;
    }
}
void pb(stack_a** stack,stack_b** stack1)
{
    if (ft_lstsize(*stack) > 0)
    {
        stack_b *tmp = malloc(sizeof(stack_b));
        if(!tmp)
            return;
        tmp -> data = top -> data;
        tmp -> next = *stack1;
        *stack1 = tmp;
        top = top->next;
    }
}

void ra(stack_a** stack)
{
    if (*stack == NULL || (*stack)->next == NULL)
        return;
    stack_a* last = *stack;
    while (last->next != NULL)
    {
        last = last->next;
    }
    top= (*stack)-> next;
    last-> next = *stack;
    *stack = (*stack)-> next;
    top = *stack;
    last->next->next = NULL;
}
void rb(stack_b** stack1)
{
    stack_b *last = *stack1;
    stack_b *tmp = (*stack1) -> next; 
    if(!*stack1 || (*stack1)->next == NULL)
        return ;
    while(last->next != NULL)
        last = last -> next;
    last->next = (*stack1);
    (*stack1) = tmp;
    last->next->next = NULL;
}


void rra(stack_a** stack)
{
    stack_a* courant = *stack;
    stack_a* last = NULL;
    while(courant -> next != NULL){
        last = courant;
        courant = courant->next;
    }
    courant->next = (*stack);
    (*stack) = courant;
    last->next = NULL;
}

void rrb(stack_b** stack1)
{
    stack_b* courant = *stack1;
    stack_b* last = NULL;
    while(courant -> next != NULL){
        last = courant;
        courant = courant->next;
    }
    courant->next = (*stack1);
    (*stack1) = courant;
    last->next = NULL;
}


void push_A(stack_a *stack,int data)
{
    stack_a *tmp = (stack_a*)malloc(sizeof(stack_a));
    if (!tmp)
        return ;
    tmp -> data = data;
    tmp->next = stack;
    stack = tmp;
}

void push_B(stack_b *stack1,int data)
{
    stack_b *tmp = (stack_b*)malloc(sizeof(stack_b));
    if(!tmp)
        return ;
    tmp->data = data;
    tmp-> next = stack1;
    stack1 = tmp;
}



int get_pos(stack_a *stack,int data)
{
    stack_a *courant;
    int i = 0;
    courant = stack;
    while (courant->next!=NULL)
    {
        if (courant -> data = data)
            return i;
        i++;
        courant = courant->next;
    }
    return 0; //that's mean that the element is no in the stack.
}
int calcule_nbr_mvt(stack_a *stack,stack_b *stack1)
{
    int i = 0;
    int arr = malloc(sizeof(ft_lstsize(stack)));
    if(!arr)
        return 0;
    stack_b *tmp = stack1 -> next;
    push_B(stack1,stack1->data);
    push_B(stack1, tmp-> data);
    


}

int main(int argc, char **argv)
{
    int j = argc;
    while(argc != 1)
    {
        stack_a *new_node = malloc(sizeof(stack_a));
        if(!new_node)
        {
            printf("Allocation error");
            return 0;
        }
        new_node->data = atoi(argv[argc - 1]);
        new_node->next = top;
        top = new_node;
        argc--;
    }

    while(j != 1)
    {
        stack_b *node = malloc(sizeof(stack_b));
        if(!node)
            return 0;
        node -> data = atoi(argv[j - 1]);
        node -> next = top1;
        top1 = node;
        j--;
    }
    stack_a *current = top;
    stack_a *test = top;
    stack_b *test1 = top1;
    printf("The original\n");
    while(current != NULL)
    {
        printf("%d\n", current->data);
        current = current->next;
    }
    ra(&test);
    printf("-----------------------------\n");
    printf("===========>Stack A\n");  
    while (test != NULL)
    {
        printf("%d\n", test->data);
        test = test->next;
    }
    printf("===========>Stack B\n");   
    while(test1 != NULL)
    {
        printf("%d\n", test1->data);
        test1 = test1->next;
    }
    return 0;
}









        //In case i need it 
// void sort_tree_element(Stack **stackB,int *count)
// {
//     Stack *courant = *stackB;
//     Stack *last = *stackB;
//     while (last->next != NULL)
//         last = last->next;
//     Stack *tmp = (*stackB)->next;
//     while (!isStackSorted(*stackB))
//     {
//         if (courant->data < last->data)
//         {
//             rrb(stackB);
//             (*count)++;
//         }
//         else if (courant->data < tmp->data)
//         {
//             sb(courant);
//             (*count)++;
//         }
//         else if (tmp->data < last->data)
//         {
//             rrb(stackB);
//             (*count)++;
//         }
//         courant = *stackB;
//         last = *stackB;
//         while (last->next != NULL)
//             last = last->next;
//         tmp = (*stackB)->next;
//     }
// }



        //rules
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:37:35 by shebaz            #+#    #+#             */
/*   Updated: 2024/03/29 15:23:18 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(Stack *stackA)//it works
{
	int	tmp;
	Stack*	courant;
	
	courant = stackA->next;
	tmp = stackA->data;
	stackA->data = courant->data;
	courant->data = tmp;
}

void	sb(Stack *stackB)//it works
{
	int	tmp;
	Stack*	courant;
       	
	courant = stackB->next;
	tmp = stackB->data;
	stackB->data = courant->data;
	courant->data = tmp;
}

void	ss(Stack *stackA, Stack *stackB)//it works
{
	sa(stackA);
	sb(stackB);
}

void	pa(Stack** stackA, Stack** stackB)//it works
{
	Stack*	courant;
	if (ft_lstsize(*stackB) > 0)
	{
		courant = pop(stackB);
		courant->next = *stackA;
		*stackA = courant;
	}
}

void	pb(Stack** stackA, Stack** stackB)//it works
{
	Stack*	courant;
	if (ft_lstsize(*stackA) > 0)
	{
		courant = pop(stackA);
		courant->next = *stackB;
		*stackB = courant;
	}
}

void	ra(Stack** stackA)//it works
{
	Stack*	last;

	if (*stackA == NULL || (*stackA)->next == NULL)
		return ;
	last = *stackA;
	while (last->next != NULL)
		last = last->next;
	last->next = *stackA;
	*stackA = (*stackA)->next;
	last->next->next = NULL;
}

void	rb(Stack** stackB)//it works
{
	Stack* last;
	if (*stackB == NULL || (*stackB)->next == NULL)
        	return;
	last = *stackB;
	while (last->next != NULL)
		last = last->next;
	last->next = *stackB;
	*stackB = (*stackB) -> next;
	last->next->next = NULL;
}

void	rr(Stack** stackA, Stack** stackB)//it works
{
	ra(stackA);
	rb(stackB);
}

void	rra(Stack** stackA)//it works
{
	Stack*	last;
	Stack*	new_end;

	last = *stackA;
	new_end = NULL;
	while (last ->next != NULL)
	{
		new_end = last;
		last = last->next;
	}
	last -> next = *stackA;
	*stackA = last;
	new_end ->next = NULL;
}

void	rrb(Stack** stackB)//it works
{
	Stack*	last;
	Stack*	new_end;

	last = *stackB;
	new_end = NULL;
	while (last->next != NULL)
	{
		new_end = last;
		last = last->next;
	}
	last -> next = *stackB;
	*stackB = last;
	new_end ->next = NULL;
}

void	rrr(Stack** stackA, Stack** stackB)//it works
{
	rra(stackA);
	rrb(stackB);
}