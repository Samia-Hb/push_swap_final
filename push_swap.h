/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:03:42 by shebaz            #+#    #+#             */
/*   Updated: 2024/04/05 15:22:55 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#define INT_MIN -2147483648
#define INT_MAX 2147483647
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack{
    int data;
    int index;
    struct stack *next;
} Stack;

void    sa(Stack* stackA);
void    sb(Stack* stackB);
void    ss(Stack* stackA, Stack* stackB);
void    pa(Stack** stackA, Stack** stackB);
void    pb(Stack** stackA,Stack** stackB);
void    ra(Stack** stackA);
void    rb(Stack** stackB);
void    rr(Stack** stackA,Stack** stackB);
void    rra(Stack** stackA);
void    rrb(Stack** stackB);
void    rrr(Stack **stackA,Stack **stackB);
void    push(Stack **stackA, int data);
Stack   *pop(Stack **stack_s);
int     ft_lstsize(Stack *lst);
char    **ft_split(char const *s, char c);
long    *check_arguments(int argc, char **argv);
int     check_type(char **tab);
int     check_duplicate(long *arr,int argc,char **argv);
int     nbr_of_arguments(int argc, char **argv);
int     ft_strlen(const char *str);
int     isStackSorted(Stack *s,int element);
void    push_to_stackB(Stack **stackA,Stack **stackB);
void    sort_three_element(Stack **stackA);
void    push_back_to_stackA(Stack **stackA,Stack **stackB);
void    sort_five_element(Stack **stackA, Stack **stackB);
int     pos(Stack *stack,int element);
int     calcule_nbr_mouvement_stackA(Stack *stackA, Stack *stackB, int element);
int     find_closest_pos(Stack *stackB, int element);
int     find_max_elememt(Stack *stackB);
int     Min_element(Stack *stackA);
int     ft_counter(char const *str, char c);
long	ft_atoi(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void sort_stackb_before(Stack** stackB, int pos);
void push_back_to_stackA(Stack **stackA,Stack **stackB);

#endif