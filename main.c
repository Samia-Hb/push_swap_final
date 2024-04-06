/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:03:45 by shebaz            #+#    #+#             */
/*   Updated: 2024/04/04 14:52:57 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void push_back_to_stackA(Stack **stackA,Stack **stackB)//done
{
    int size;

    pa(stackA,stackB);
    printf("pa\n");
    size = ft_lstsize(*stackB);
    while (size != 0)
    {
        pa(stackA,stackB);
        printf("pa\n");
        size --;
    }
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
	if (!arr)
		return 0;
    while (i < argc)
    {
        if (ft_counter(argv[i],' ') == 0)
            return (0);
        tab = ft_split(argv[i], ' ');
		if (!check_type(tab))
			return (0);
        k = 0;
        while (tab[k])
            arr[j++] = ft_atoi(tab[k++]);
		i++;
    }
    return (arr);
}

int check_ALL(int argc, char **argv)//done
{
    long *arr;
    arr = check_arguments(argc, argv);
    if(nbr_of_arguments(argc,argv) == 1)
    {
        exit(1);
    }
	if (!arr || !check_duplicate(arr, argc, argv))
	{
        printf("Error\n");
        free(arr);
		return 0;
    }
    return 1;
}
void fill_the_stack(int argc,char **argv,Stack **stackA)//done
{
    long *arr;
    int size;

    size = nbr_of_arguments(argc, argv);
    arr = check_arguments(argc, argv);
    while(size > 0)
    {
        push(stackA, arr[size - 1]);
        size--;
    }
    free(arr);
}
int main(int argc, char** argv) //done
{
    Stack* stackA;
    Stack* stackB;

    stackA = NULL;
    stackB = NULL;
    if (!check_ALL(argc, argv))
        return (0);
    else
        fill_the_stack(argc, argv,&stackA);    
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
        push_back_to_stackA(&stackA,&stackB);
    }
    
}
