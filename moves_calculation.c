/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_calculation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:03:33 by shebaz            #+#    #+#             */
/*   Updated: 2024/04/03 12:10:33 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

Stack *copied_stack(Stack *stack_to_copy)//done
{
    Stack *copied;
    Stack *temp;
    int i;
    int size;

    temp = NULL;
    copied = NULL;
    i = 0;
    size = ft_lstsize(stack_to_copy);
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
    return (copied);
}

int pos(Stack *stack,int element)//done
{
    Stack *courant;
    int i;

    courant = stack;
    i = 0;
    while(courant)
    {
        if(courant->data == element)
            return(i);
        i++;
        courant = courant-> next;
    }
    return(-1);
}

int find_closest_pos(Stack *stackB, int element)//done
{
    int     Close_pos;
    Stack   *courant;
    int     min_diff;
    int     max_element;

    min_diff = INT_MIN;
    courant = stackB;
    Close_pos = -1;
    while (courant != NULL)
    {
        if (courant->data < element && courant -> data > min_diff)
        {
            min_diff = courant->data;
            Close_pos = pos(stackB,courant->data);
        }
        courant = courant -> next;
    }
    courant = stackB;               
    if (Close_pos == -1)
    {
        max_element = find_max_elememt(stackB);
        Close_pos = pos(stackB,max_element);
    }
    return (Close_pos);
}

int calcule_nbr_mouvement_stackB(Stack *stackB, int element, int k,int *movements)//done
{
    Stack*  copyB;

    copyB = stackB;
    if (k <= ft_lstsize(stackB) / 2)
    {
        while(k != 0)
        {
            rb(&copyB);
            (*movements)++;
            k--;
        }
    }
    else if(k > ft_lstsize(stackB) / 2)
    {
        while(k != 0)
        {   
            rrb(&copyB);
            (*movements)++;
            k = find_closest_pos(stackB, element);
        }
    }
    return (*movements);
}


int calcule_nbr_mouvement_stackA(Stack *stackA, Stack *stackB, int element)//done
{
    int movements;
    Stack *copyA ; 
    Stack *copyB ;

    movements = 0;
    copyA = copied_stack(stackA);
    copyB = copied_stack(stackB);
    while (pos(copyA, element) != 0)
    {
        if(pos(stackA, element) == 1)
            sa(copyA);
        else if (pos(copyA, element) <= ft_lstsize(copyA) / 2)
            ra(&copyA);
        else
            rra(&copyA);
        movements++;
    }
    movements += calcule_nbr_mouvement_stackB(copyB, element,find_closest_pos(stackB, element),&movements) + 1;
    pb(&copyA, &copyB);
    return movements;
}