/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_every_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:36:36 by shebaz            #+#    #+#             */
/*   Updated: 2024/04/05 10:34:06 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void push(Stack **stackA, int data)
{
    Stack *node;

    node = malloc(sizeof(Stack));
    if (!node)
    {
        printf("Allocation Failure");
        return ;
    }
    node -> data = data;
    node -> next = *stackA;
    *stackA = node;
}

Stack *pop(Stack **stack_s) 
{
    Stack *tmp;

    tmp = *stack_s;
    Stack *courant = (*stack_s) -> next;
    tmp -> data = (*stack_s) -> data;
    *stack_s = courant;
    return (tmp);
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

void push2(Stack *node, Stack **dest)//done
{
    node->next = *dest;
    *dest = node;
}

int pos(Stack *stack,int element)//done
{
    Stack *courant;
    int i;

    courant = stack;
    i = 0;
    while (courant)
    {
        if (courant->data == element)
            return(i);
        i++;
        courant = courant-> next;
    }
    return(-1);
}

int find_max_elememt(Stack *stackB)//done
{
    int     max_element;
    Stack*  courant;

    max_element = INT_MIN;
    courant = stackB;
    while (courant)
    {
        if (courant->data > max_element)           
            max_element = courant->data;            
        courant = courant->next;
    }
    return (max_element);
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

int calcule_nbr_mouvement_stackB(Stack *stackB, int element)//it works
{
    int     movements;
    Stack*  copyB;
    int     k;
    int     size;

    copyB = stackB;
    movements = 0;
    k = find_closest_pos(stackB, element);
    if(k == 0)
        return (0);
    else if (k <= ft_lstsize(stackB) / 2)
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
        size = ft_lstsize(stackB) - 1;
        while (k != 0)
        {
            rrb(&copyB);
            movements++;
            k++;
            if (k == size)
                break;
        }
        rrb(&copyB);
        movements++;
    }
    return (movements);
}
int calcule_nbr_mouvement_stackA(Stack *stackA, Stack *stackB, int element)
{
    int     movements;
    Stack   *copyA;
    Stack   *copyB;
    int     j;
    int     size;

    movements = 0;
    copyA = copied_stack(stackA);
    copyB = copied_stack(stackB);
    j = pos(stackA, element);
    size = ft_lstsize(stackA) / 2;
    if (j == 0)
    {
        movements += calcule_nbr_mouvement_stackB(copyB,element) + 1;
        pb(&copyA, &copyB);
    }
    else if (j == 1)
    {
        sa(copyA);
        movements += calcule_nbr_mouvement_stackB(copyB,element) + 2;
        pb(&copyA, &copyB);
    }
    else if (j <= size && j > 1)
    {
        while (j != 0)
        {
            ra(&copyA);
            movements++;
            j--;
        }
        movements += calcule_nbr_mouvement_stackB(copyB,element) + 1;
        pb(&copyA,&copyB);
    }
    else if(j == ft_lstsize(stackA) - 1)
    {
        rra(&copyA);
        movements = calcule_nbr_mouvement_stackB(copyB,element) + 2;
        pb(&copyA, &copyB);
    }
    else if(j > size && j != ft_lstsize(stackA) - 1)
    {
        while(j != 0)
        {
            rra(&copyA);
            movements++;
            j = pos(copyA,element);
        }
        movements += calcule_nbr_mouvement_stackB(copyB,element) + 1;
        pb(&copyA, &copyB);
    }
    free(copyA);
    free(copyB);
    return (movements);
}

int calculate_Min_element(Stack *stackA,Stack *stackB)
{
    int Min_element;
    Stack *courant;
    int Min_count;
    int i;
    int *count;

    i = 0;
    Min_count = INT_MAX;
    courant = stackA;
    Min_element = stackA->data;
    count = malloc(ft_lstsize(stackA) * sizeof(int));
    if (!count)
        return 0;
    while (i < ft_lstsize(stackA) && courant != NULL)
    {
        count[i] = calcule_nbr_mouvement_stackA(stackA, stackB, courant->data);
        if(count[i] < Min_count)
        {
            Min_count = count[i];
            Min_element = courant->data;
        }
        i++;
        courant = courant -> next;
    }
    free(count);
    return(Min_element);
}

void sort_stackb_before(Stack** stackB, int pos)//done
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
        while(pos != ft_lstsize(*stackB) - 1)
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

void push_the_min(Stack** stackA, Stack** stackB, int element, int pos)
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
        printf("pb\n");
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
        printf("pb\n");
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
        printf("pb\n");
    }
}

int nbr_of_arguments(int argc, char **argv)//done
{
    int i;
    int count;

    i = 1;
    count = 0;
    while(i < argc)
    {
        count += ft_counter(argv[i],' ');
        i++;
    }
    return (count);
}

int check_duplicate(long *arr, int argc, char **argv)//done
{
    int i;
    int j;

    i = 0;
    j = 1;
    while (i < nbr_of_arguments(argc,argv) - 1)
    {
        if(arr[i] > INT_MAX || arr[i] < INT_MIN)
            return (0);
        j = i + 1;
        while (j < nbr_of_arguments(argc,argv))
        {
            if (arr[i] == arr[j] || arr[j] > INT_MAX || arr[j] < INT_MIN)
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

int check_type(char **tab)//done
{
	int i;
	int j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (j < ft_strlen(tab[i]))
		{
			if (tab[i][j] < 48 || tab[i][j] > 57)
            {
                if(tab[i][0] != '-' && tab[i][0] != '+')
                    return (0);
            }
			j++;
		}
		i++;
	}
	return (1);
}

long *check_arguments(int argc, char **argv)//done
{
    int i;
    int j;
	int k;
	char **tab;
	long *arr;

    i = 1;
    j = 0;
    arr = malloc(nbr_of_arguments(argc,argv));
	if(!arr)
		return 0;
    while (i < argc)
    {
        k = 0;
        if (ft_counter(argv[i],' ') == 0)
            return (0);
        tab = ft_split(argv[i], ' ');
		if (!check_type(tab))
			return (0);
        while (tab[k])
            arr[j++] = ft_atoi(tab[k++]);
		i++;
    }
    return (arr);
}
int check_ALL(int argc, char **argv)//done
{
    long *arr;

    if(argc == 1)
        exit(1);
    arr = check_arguments(argc, argv);
	if (!arr || !check_duplicate(arr, argc, argv))
	{
        printf("Error\n");
        free(arr);
		return 0;
    }
    return 1;
}


void sort_stackB(Stack **stackB)//done
{
    int position;
    int max_element;

    max_element = find_max_elememt(*stackB);
    position = pos(*stackB,max_element);
    while (position != 0)
    {
        if(position <= ft_lstsize(*stackB) / 2)
        {
            rb(stackB);
            printf("rb\n");
        }
        else if(position > ft_lstsize(*stackB) / 2)
        {
            rrb(stackB);
            printf("rrb\n");
        }
        position = pos(*stackB,max_element);
    }
}
void push_to_stackB(Stack **stackA,Stack **stackB)//done
{
    int Min_element;
    
    push2(pop(stackA), stackB);
    printf("pb\n");
    push2(pop(stackA), stackB);
    printf("pb\n");
    while (ft_lstsize(*stackA) != 0)
    {
        Min_element = calculate_Min_element(*stackA, *stackB);
        push_the_min(stackA, stackB, Min_element, pos(*stackA, Min_element));
    }
    if (!isStackSorted(*stackB,0))
        sort_stackB(stackB);    
}
void push_back_to_stackA(Stack **stackA,Stack **stackB)//done
{
    int size;

    size = ft_lstsize(*stackB);
    while (size != 0)
    {
        pa(stackA,stackB);
        printf("pa\n");
        size --;
    }
}

int Min_element(Stack *stackA)
{
    int min_element;
    
    min_element = INT_MAX;
    while (stackA)
    {
        if(stackA->data < min_element)
            min_element = stackA->data;
        stackA = stackA -> next;
    }
    return (min_element);
}

void sort_three_element(Stack **stackA)
{
    Stack *courant = *stackA;
    Stack *last = *stackA;
    while (last->next != NULL)
        last = last->next;
    Stack *tmp = (*stackA)->next;
    while(!isStackSorted(*stackA,0))
    {
        if(courant->data > last->data)
        {
            rra(stackA);
            printf("rra\n");
        }
        else if (courant -> data > tmp->data)
        {
            sa(courant);
            printf("sa\n");
        }
        else if (tmp->data > last->data)
        {
            rra(stackA);
            printf("rra\n");
        }
        courant = *stackA;
        last = *stackA;
        while (last->next != NULL)
            last = last->next;
        tmp = (*stackA)->next;
    }
}

void sort_five_element(Stack **stackA, Stack **stackB)
{    
    int i;
    int min_element;

    i = 0;
    while (i < 2)
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
        i++;
        pb(stackA, stackB);
        printf("pb\n");
    }
    sort_three_element(stackA);
}
int main(int argc, char** argv) //done
{
    Stack* stackA;
    Stack* stackB;
    long *arr;
    int size;

    stackA = NULL;
    stackB = NULL;
    if (!check_ALL(argc, argv))
        return (0);
    else
    {
        size = nbr_of_arguments(argc, argv);
        arr = check_arguments(argc, argv);
        while(size > 0)
        {
            push(&stackA, arr[size - 1]);
            size--;
        }
        free(arr);
    }
    if (isStackSorted(stackA , 0))
        return (0);
    if(ft_lstsize(stackA) == 2)
            printf("sa\n");
    else if(ft_lstsize(stackA) == 5)
    {
        sort_five_element(&stackA,&stackB);
        push_back_to_stackA(&stackA, &stackB);
    }
    else if(ft_lstsize(stackA) == 3)
        sort_three_element(&stackA);
    else
    {
        push_to_stackB(&stackA,&stackB);
        // Stack *courant;
        // courant = stackA;
        // int i = 0;
        // while(courant)
        // {
        //     printf("data %d = %d\n",i,courant->data);
        //     courant = courant -> next;
        //     i++;
        // }
        //push_back_to_stackA(&stackA,&stackB);
    }
    // Stack *courant;
    // courant = stackA;
    // int i = 0;
    // while(courant)
    // {
    //     printf("data %d = %d\n",i,courant->data);
    //     courant = courant -> next;
    //     i++;
    // }
    return 0;
}

