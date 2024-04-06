/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:03:38 by shebaz            #+#    #+#             */
/*   Updated: 2024/04/04 14:13:44 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void push(Stack **stackA, int data)//done
{
    Stack *node;

    node = malloc(sizeof(Stack));
    if(!node)
    {
        printf("Allocation Failure");
        return ;
    }
    node -> data = data;
    node -> next = *stackA;
    *stackA = node;
}


Stack *pop(Stack **stack_s)//done
{
    Stack *tmp;

    tmp = *stack_s;
    Stack *courant = (*stack_s) -> next;
    tmp -> data = (*stack_s) -> data;
    *stack_s = courant;
    return (tmp);
}

int	ft_lstsize(Stack *lst) //done
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

int isStackSorted(Stack *s,int element)//done
{
    Stack *courant;
    Stack *courant1;

    courant = s;
    courant1 = s->next;
    while (courant1 != NULL)
    {
        if (element == 1 && courant->data < courant1->data)
            return (0);
        else if(element == 0 && courant->data > courant1->data)
            return (0);
        courant = courant->next;
        courant1 = courant1->next;
    }
    return 1;
}