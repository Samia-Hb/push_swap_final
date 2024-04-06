#include "push_swap.h"

int find_min_element(Stack *stackA)
{
    Stack *courant = stackA;
    int min = INT_MAX;
    while (courant)
    {
        if (courant->data < min)
            min = courant->data;
        courant = courant->next;
    }
    return (min);
}
int find_closest_pos_v2(Stack *stackA, int element)//done
{
    int     Close_pos;
    Stack   *courant;
    int     min_diff;
    int     min_element;

    min_diff = INT_MAX;
    courant = stackA;
    Close_pos = INT_MAX;
    while (courant != NULL)
    {
        if (courant->data > element && courant -> data < min_diff)
        {
            min_diff = courant->data;
            Close_pos = pos(stackA,min_diff);
        }
        courant = courant -> next;
    }
    courant = stackA;               
    if (Close_pos == -1)
    {
        min_element = find_min_element(stackA);
        Close_pos = pos(stackA,min_element);
    }
    return (Close_pos);
}
void push_the_min_part2(Stack** stackA, Stack** stackB, int element)
{
        while (pos(*stackB,element) != 0)
        {
            if (pos(*stackB, element) <= ft_lstsize(*stackB) / 2)
            {
                if (find_closest_pos_v2(*stackA, element) <= ft_lstsize(*stackA) / 2)
                {
                    while(find_closest_pos_v2(*stackA, element) != 0)
                    {
                        rr(stackA,stackB);
                        printf("rr\n");
                        if (pos(*stackB, element) == 0)
                            break;
                    }
                }
                if(pos(*stackB, element) != 0)
                {
                    rb(stackB);
                    printf("rb\n");
                }
            }
            else if(pos(*stackB, element) > ft_lstsize(*stackB) / 2)
            {
                if(find_closest_pos_v2(*stackA, element) > ft_lstsize(*stackA) / 2)
                {
                    while (find_closest_pos_v2(*stackA, element) != 0)
                    {
                        rrr(stackA,stackB);
                        printf("rrr\n");
                        if(pos(*stackB, element) == 0)
                            break;
                    }
                }
                if(pos(*stackB, element) != 0)
                {
                    rrb(stackB);
                    printf("rrb\n");
                }
            }
        }
    sort_stackb_before(stackA, find_closest_pos(*stackA, element));
    pa(stackA, stackB);
    printf("pa\n");
}
int calculate_Min_element_v2(Stack *stackA,Stack *stackB)//done
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
    free (count);
    return (Min_element);
}
void push_back_to_stackA(Stack **stackA,Stack **stackB)
{
    int Min_element;

    while(ft_lstsize(*stackB) != 0)
    {
        Min_element = calculate_Min_element_v2(*stackB,*stackA);
        push_the_min_part2(stackA,stackB,Min_element);
    }
   
}