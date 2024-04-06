#include "push_swap.h"

typedef struct stack{
    int data;
    struct stack *next;
} Stack;

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


            //moves
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
        ///end_of_moves
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
                //calculate_the_moves
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
                //utils_fumctions

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
                                            //parsing//
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
        if(arr[0] > INT_MAX || arr[0] < INT_MIN)
            printf("Error");
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
                                        //the end of parsing
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
    if(pos (*stackA,element) == 1)
    {
        sa(*stackA);
        printf("sa\n");
    }
    else if (pos(*stackA,element) > 1)
    {
        while (pos(*stackA,element) != 0)
        {
            if (pos(*stackA,element) <= ft_lstsize(*stackA) / 2)
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
    int full_size;

    full_size = ft_lstsize(*stackA);
    pb(stackA, stackB);
    printf("pb\n");
    pb(stackA, stackB);
    printf("pb\n");
    size = ft_lstsize(*stackA);
    while (size != 0 && ft_lstsize(*stackB) != full_size)
    {
        Min_element = calculate_Min_element(*stackA, *stackB);
        push_the_min(stackA, stackB, Min_element);
        printf("pb\n");
        size++;
    }
    if (!isStackSorted(*stackB,0))
        sort_stackB(stackB);
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

int Min_element(Stack *stackA)//done
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
            //regular_cases
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
    /////
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
    if(ft_lstsize(stackA) == 5)
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
    printf("data = %d\n",ft_counter("+++"));
}
            //////////////////////////
void    search(t_node **astack, t_node **bstack)
{
    t_node    *tmp;
    t_node    *atmp;
    t_node    *target;
    long    min;

    index_stack(astack);
    index_stack(bstack);
    atmp = *astack;
    tmp = *bstack;
    while (atmp)
    {
        tmp = *bstack;
        index_stack(&tmp);
        min = LONG_MIN;
        while (tmp)
        {
            if (atmp->data > tmp->data && tmp->data > min)
            {
                min = tmp->data;
                target = tmp;
            }
            tmp = tmp->next;
        }
        if (min != LONG_MIN)
            atmp->target_index = target->index;
        else
            atmp->target_index = find_max(*bstack);
        atmp = atmp->next;
    }
}

void    cost(t_node **astack)
{
    t_node    *tmp;

    tmp = *astack;
    while (tmp)
    {
        tmp->cost = target_sum(absolu(tmp->index), absolu(tmp->target_index));
        tmp = tmp->next;
    }
}

int    find_max(t_node *bstack)
{
    t_node    *tmp;
    int        max;
    t_node    *m;

    tmp = bstack;
    m = bstack;
    max = (bstack)->data;
    while (tmp)
    {
        if (tmp->data > max)
        {
            max = tmp->data;
            m = tmp;
        }
        tmp = tmp->next;
    }
    return (m->index);
}

t_node    *handle_bstack(t_node **astack, t_node **bstack)
{
    t_node    *min_cost;

    search(astack, bstack);
    cost(astack);
    min_cost = find_node_min(astack);
    return (min_cost);
}

int    is_sorted(t_node **stack)
{
    t_node    *tmp;
    int        i;

    i = 0;
    index_stack(stack);
    tmp = *stack;
    while (tmp->next)
    {
        if (tmp->data > tmp->next->data)
        {
            rotate(stack);
            printmove("ra", 1);
            i++;
        }
        else
            tmp = tmp->next;
    }
    return (i);
}         
         int    target_sum(int a, int b)
{
    int    sum;

    if ((a <= 0 && b <= 0) || (a >= 0 && b >= 0))
    {
        a = absolu(a);
        b = absolu(b);
        if (a >= b)
            sum = a;
        else
            sum = b;
    }
    if ((a > 0 && b < 0) || (a < 0 && b > 0))
        sum = absolu(a) + absolu(b);
    return (sum);
}  
c t_node    *find_node_min(t_node **stack)
{
    t_node    *tmp;
    int        min;
    t_node    *m;

    if (!*stack)
        return (NULL);
    tmp = *stack;
    m = *stack;
    min = (*stack)->cost;
    while (tmp)
    {
        if (tmp->cost < min)
        {
            min = tmp->cost;
            m = tmp;
        }
        tmp = tmp->next;
    }
    return (m);
}