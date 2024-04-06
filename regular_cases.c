/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regular_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:18:40 by shebaz            #+#    #+#             */
/*   Updated: 2024/04/03 12:28:55 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void the_rest_of_case(Stack **stackA,int j)
{
    if(j == 1)
    {
        sa(*stackA);
        printf("sa\n");
    }
    else
    {
        rra(stackA);
        printf("rra\n");
    }
}

void sort_three_element(Stack **stackA)//done
{
    Stack *courant;
    Stack *last;
    Stack *tmp;

    last = *stackA;
    tmp = (*stackA)->next;
    courant = *stackA;
    while (last->next != NULL)
            last = last->next;
    while (!isStackSorted(*stackA,0))
    {
        if (courant->data > last->data)
            the_rest_of_case(stackA,0);
        else if (courant -> data > tmp->data)
            the_rest_of_case(stackA,1);
        else if (tmp->data > last->data)
            the_rest_of_case(stackA,0);
        courant = *stackA;
        last = *stackA;
        while (last->next != NULL)
            last = last->next;
        tmp = (*stackA)->next;
    }
}

void sort_five_element(Stack **stackA, Stack **stackB)//done
{    
    int i;
    int min_element;

    i = 0;
    while (i++ < 2)
    {
        min_element = Min_element(*stackA);
        while (pos(*stackA, min_element) != 0)
        {
            if(pos(*stackA, min_element) <= ft_lstsize(*stackA) / 2)
            {
                ra(stackA);
                printf("ra\n");
            }
            else
            {
                rra(stackA);
                printf("rra\n");
            }
        }
        pb(stackA, stackB);
        printf("pb\n");
    }
    sort_three_element(stackA);
}