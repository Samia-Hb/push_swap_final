#include "push_swap.h"
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

int calculate_Min_element(Stack *stackA,Stack *stackB)//done
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

void push_the_min(Stack** stackA, Stack** stackB, int element)//done
{
        while(pos(*stackA,element) != 0)
        {
            if(pos(*stackA, element) <= ft_lstsize(*stackA) / 2)
            {
                if(find_closest_pos(*stackB, element) <= ft_lstsize(*stackB) / 2)
                {
                    while (find_closest_pos(*stackB, element) != 0)
                    {
                        rr(stackA,stackB);
                        printf("rr\n");
                        if(pos(*stackA, element) == 0)
                            break;
                    }
                }
                if(pos(*stackA, element) != 0)
                {
                    ra(stackA);
                    printf("ra\n");
                }
            }
            else if(pos(*stackA, element) > ft_lstsize(*stackA) / 2)
            {
                if(find_closest_pos(*stackB, element) > ft_lstsize(*stackB) / 2)
                {
                    while (find_closest_pos(*stackB, element) != 0)
                    {
                        rrr(stackA,stackB);
                        printf("rrr\n");
                        if(pos(*stackA, element) == 0)
                            break;
                    }
                }
                if(pos(*stackA, element) != 0)
                {
                    rra(stackA);
                    printf("rra\n");
                }
            }
        }
    sort_stackb_before(stackB, find_closest_pos(*stackB, element));
    pb(stackA, stackB);
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
    int size ;
    int Min_element;

    pb(stackA, stackB);
    printf("pb\n");
    pb(stackA, stackB);
    printf("pb\n");
    size = ft_lstsize(*stackA);
    while (size != 3)
    {
        Min_element = calculate_Min_element(*stackA, *stackB);
        push_the_min(stackA, stackB, Min_element);
        printf("pb\n");
        size--;
    }
    // if (!isStackSorted(*stackB,0))
    //     sort_stackB(stackB);
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
int Min_element(Stack *stackA)//done
{
    int min_element;
    
    min_element = INT_MAX;
    while(stackA)
    {
        if(stackA->data < min_element)
            min_element = stackA->data;
        stackA = stackA -> next;
    }
    return (min_element);
}
int find_closest_pos_v2(Stack *stackA,int element)
{
    int min_diff = INT_MAX;
    int Close_pos = -1;
    Stack *courant = stackA;
    while(courant)
    {
        if(courant->data > element && courant->data > min_diff)
        {
            min_diff = courant->data;
            Close_pos = pos(stackA,min_diff);
        }
        courant = courant->next;
    }
    if(Close_pos == -1)
    {
        int Min = Min_element(stackA);
        Close_pos = pos(stackA,Min);
    }
    return (Close_pos);
}
void sort_stackA_before(Stack **stackA,int pos,int element)
{
    while(pos != 0)
    {
        if(pos <= ft_lstsize(*stackA) / 2)
        {
            ra(stackA);
            printf("ra\n");
        }
        else if(pos > ft_lstsize(*stackA) / 2)
        {
            rra(stackA);
            printf("rra\n");
        }
        pos = find_closest_pos_v2(*stackA,element);
    }
}
void push_the_min_v2(Stack **stackA,Stack **stackB,int element)
{
    while(pos(*stackB,element) != 0)
    {
        if(pos(*stackB,element) <= ft_lstsize(*stackB) / 2)
        {
            if(find_closest_pos_v2(*stackA,element) <= ft_lstsize(*stackA) / 2)
            {
                while(find_closest_pos_v2(*stackA,element) != 0)
                {
                    rr(stackA,stackB);
                    printf("rr\n");
                    if(pos(*stackB,element) == 0)
                        break;
                }
            }  
            if (pos(*stackB, element) != 0)
            {
                rb(stackB);
                printf("ra\n");
            }
        }
        else if(pos(*stackB,element) > ft_lstsize(*stackB) / 2)
        {
            if(find_closest_pos_v2(*stackA,element) > ft_lstsize(*stackA)/2)
            {
                while(find_closest_pos_v2(*stackA,element) != 0)
                {
                    rrr(stackA,stackB);
                    printf("rrr\n");
                    if(pos(*stackB,element) == 0)
                        break;
                }
                if(pos(*stackB,element) != 0)
                {
                    rrb(stackB);
                    printf("rrb\n");
                }
            }
        }
    }
    sort_stackA_before(stackA,find_closest_pos(*stackA,element),element);
    pa(stackA,stackB);
}
int calculate_Min_element_v2(Stack *stackA,Stack *stackB)
{
    int *count;
    Stack *courant;
    int Min_count;
    int i;
    count = malloc(ft_lstsize(stackB));
    if (!count)
    {
        printf("Error in V2_calculate_min");
        exit(1);
    }
    i = 0;
    Min_count = INT_MAX;
    courant = stackB;
    int Min_element = INT_MAX;
    while(i < ft_lstsize(stackB) && courant != NULL)
    {
        count[i] = calcule_nbr_mouvement_stackA(stackB, stackA, courant->data);
        if(count[i] < Min_count)
        {
            Min_count = count[i];
            Min_element = courant->data;
        }
        i++;
        courant = courant->next;
    }
    free(count);
    return(Min_element);
    ///////
}
void push_back_to_stackA_v2(Stack **stackA,Stack **stackB)
{
    int Min_element;
    while(ft_lstsize(*stackB) != 0)
    {
        Min_element = calculate_Min_element_v2(*stackA,*stackB);
        push_the_min_v2(stackA,stackB,Min_element);
    }
}
int main(int argc, char** argv)//done
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
    if (ft_lstsize(stackA) == 2)
            printf("sa\n");
    else if (ft_lstsize(stackA) == 5)
    {
        sort_five_element(&stackA,&stackB);
        push_back_to_stackA_v2(&stackA, &stackB);
    }
    else if(ft_lstsize(stackA) == 3)
        sort_three_element(&stackA);
    else
    {
        push_to_stackB(&stackA,&stackB);
        sort_stackB(&stackB);
        sort_three_element(&stackA);
        //printf("----------------\n");
        //push_back_to_stackA_v2(&stackA,&stackB);
    }
    // Stack *courant = stackA;
    // int i = 0;
    // while(courant)
    // {
    //     printf("data of stack_A %d = %d\n",i,courant->data);
    //     courant = courant -> next;
    //     i++;
    // }
    // printf("------------------\n");
    // courant = stackB;
    // i = 0;
    // while(courant)
    // {
    //     printf("data of stack_B %d = %d\n",i,courant->data);
    //     courant = courant -> next;
    //     i++;
    // }
}
                //////////////////////////

                
// int Min_element(Stack *stackA)//done
// {
//     int min_element;
    
//     min_element = INT_MAX;
//     while (stackA)
//     {
//         if(stackA->data < min_element)
//             min_element = stackA->data;
//         stackA = stackA -> next;
//     }
//     return (min_element);
// }
// int find_closest_pos_v2(Stack *stackA,int element)
// {
//     int min_diff = INT_MAX;
//     int Close_pos = -1;
//     Stack *courant = stackA;
//     while(courant)
//     {
//         if(courant->data > element && courant->data > min_diff)
//         {
//             min_diff = courant->data;
//             Close_pos = pos(stackA,min_diff);
//         }
//         courant = courant->next;
//     }
//     if(Close_pos == -1)
//     {
//         int min_element = min_element(stackA);
//         Close_pos = pos(stackA,min_element);
//     }
//     return Close_pos;
// }
// void sort_stackA_before(Stack **stackA,int pos)
// {
//     while(pos != 0)
//     {
//         if(pos <= ft_lstsize(stackA) / 2)
//         {
//             ra(stackA);
//             printf("ra\n");
//         }
//         else if(pos > ft_lstsize(stackA) / 2)
//         {
//             rra(stackA);
//             printf("rra\n");
//         }
//         pos = find_closest_pos_v2(*stackA,element);
//     }
// }
// void push_the_min(Stack **stackA,Stack **stackB,int element)
// {
//     while(pos(*stackB,element) != 0)
//     {
//         if(pos(*stackB,element) <= ft_lstsize(stackB) / 2)
//         {
//             if(find_closest_pos_v2(stackA,element) <= ft_lstsize(stackA) / 2)
//             {
//                 while(find_closest_pos_v2(stackA,element) != 0)
//                 {
//                     rr(stackA,stackB);
//                     printf("rr\n");
//                     if(pos(*stackB,element) == 0)
//                         break;
//                 } 
//             }  
//             if (pos(*stackB, element) != 0)
//             {
//                 rb(stackB);
//                 printf("ra\n");
//             }
//         }
//         else if(pos(*stackB,element) > ft_lstsize(stackB) / 2)
//         {
//             if(find_closest_pos_v2(stackA,element) > ft_lstsize(stackA)/2)
//             {
//                 while(find_closest_pos_v2(stackA,element) != 0)
//                 {
//                     rrr(stackA,stackB);
//                     printf("rrr\n");
//                     if(pos(*stack,element) == 0)
//                         break;
//                 }
//                 if(pos(*stackB,element) != 0)
//                 {
//                     rrb(stackB);
//                     printf("rrb\n");
//                 }
//             }
//         }
//     }
//     sort_stackA_before(stackA,find_closest_pos(*stackA,element));
//     pa(stackA,stackB);
// }
// calculate_Min_element_v2(Stack *stackA,Stack *stackB)
// {
//     int *count;
//     Stack *courant;
//     int Min_count;
//     int i;
//     count = malloc(ft_lstsize(stackB));
//     if (!count)
//     {
//         printf("Error in V2_calculate_min");
//         exit(1);
//     }
//     i = 0;
//     Min_count = INT_MAX;
//     courant = stackB;
//     Min_element = stackB -> data;
//     while (i < ft_lstsize(stackB) && courant != NULL)
//     {
//         count[i] = calcule_nbr_mouvement_stackA(stackB, stackA, courant->data);
//         if(count[i] < Min_count)
//         {
//             Min_count = count[i];
//             Min_element = courant->data;
//         }
//         i++;
//         courant = courant -> next;
//     }
//     free(count);
//     return(Min_element);

//     ///////
// }
// void push_back_to_stackA_v2(Stack **stackA,Stack **stackB)
// {
//     int Min_element;
//     while (ft_lstsize(stackB) != 0)
//     {
//         Min_element = calculate_Min_element_v2(*stackA,*stackB);
//         push_the_min(stackA,pos(stackB,Min_element));
//     }
// }