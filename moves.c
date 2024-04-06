/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:37:35 by shebaz            #+#    #+#             */
/*   Updated: 2024/04/05 07:59:49 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(Stack *stackA)//it works
{
	int		tmp;
	Stack		*courant;

	courant = stackA->next;
	tmp = stackA->data;
	stackA->data = courant->data;
	courant->data = tmp;
}

void	sb(Stack *stackB)//it works
{
	int	tmp;
	Stack	*courant;

	courant = stackB->next;
	tmp = stackB->data;
	stackB->data = courant->data;
	courant->data = tmp;
}

void	pa(Stack **stackA, Stack **stackB)//it works
{
	Stack	*courant;

	if (ft_lstsize(*stackB) > 0)
	{
		courant = pop(stackB);
		courant->next = *stackA;
		*stackA = courant;
	}
}

void	pb(Stack **stackA, Stack **stackB)//it works
{
	Stack	*courant;

	if (ft_lstsize(*stackA) > 0)
	{
		courant = pop(stackA);
		courant->next = *stackB;
		*stackB = courant;
	}
}

void	ra(Stack **stackA)//it works
{
	Stack	*last;

	if (*stackA == NULL || (*stackA)->next == NULL)
		return ;
	last = *stackA;
	while (last->next != NULL)
		last = last->next;
	last->next = *stackA;
	*stackA = (*stackA)->next;
	last->next->next = NULL;
}

void	rb(Stack **stackB)//it works
{
	Stack	*last;

	if (*stackB == NULL || (*stackB)->next == NULL)
		return ;
	last = *stackB;
	while (last->next != NULL)
		last = last->next;
	last->next = *stackB;
	*stackB = (*stackB)-> next;
	last->next->next = NULL;
}

void rr(Stack** stackA,Stack** stackB)
{
    ra(stackA);
    rb(stackB);
}

void	rra(Stack **stackA)//it works
{
	Stack	*last;
	Stack	*new_end;

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

void	rrb(Stack **stackB)//it works
{
	Stack	*last;
	Stack	*new_end;

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

void rrr(Stack **stackA,Stack **stackB)
{
    rra(stackA);
    rrb(stackB);
}
