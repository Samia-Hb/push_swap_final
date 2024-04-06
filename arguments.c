#include "push_swap.h"

int	ft_counter(char const *str, char c)
{
	int	i;
	int	word_counter;

	i = 0;
	word_counter = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			word_counter++;
			while (str[i + 1] == c)
			{
				i++;
			}
		}
		i++;
	}
	if (str[0] != c && str[ft_strlen(str) - 1] != c)
		word_counter++;
	if (str[0] == c && str[ft_strlen(str) - 1] == c)
		word_counter--;
	return (word_counter);
}

        //
int nbr_of_arguments(int argc, char **argv)
{
    int i = 1;
    int count = 0;
    while (i < argc)
    {
        count += ft_counter(argv[i],' ');
        i++;
    }
    return count;
}
int check_duplicate(int *arr)
{
    int i;
    int j;

    i = 0;
    while (arr[i])
    {
        j = i + 1;
        while (arr[j])
        {
            if (arr[i] == arr[j])
                return 0;
            j++;
        }
        i++;
    }
    return 1;
}

int check_type(char **tab)
{
	int i;
	int j;

	i = 0;
	while(tab[i])
	{
		j = 0;
		while (j < ft_strlen(tab[i]))
		{
			if (tab[i][j] < 48 || tab[i][j] > 57 )
				return 0;
			j++;
		}
		i++;
	}
	return 1;
}

i *check_arguments(int argc, char **argv)
{
    int i = 1;
    int j = 0;
	int k;
	char **tab;
	int *arr;

    arr = malloc(nbr_of_arguments(argc,argv));
	if(!arr)
		return 0;
    while (i < argc)
    {
        tab = ft_split(argv[i], ' ');
        k = 0;
		if(!check_type(tab))
			return 0;
        while (tab[k])
        {
            arr[j] = atoi(tab[k]);
            j++;
            k++;
        }
		i++;
    }
	if(!check_duplicate(arr))
		return 0;
    return arr;
}
int main(int argc, char** argv)
{
    Stack* stackA = NULL;
	int *arr;
	int size = nbr_of_arguments(argc,argv);
	if (!check_arguments(argc,argv))
	{
		printf("Error\n");
		return 0;
	}else
	{
		arr = check_arguments(argc,argv);
		while(size > 0)
    	{
        	push(&stackA, arr[size - 1]);
        	size--;
    	}
	}
	Stack *courant = stackA;
	while (courant)
	{
		printf("data = %d\n",courant->data);
		courant = courant -> next;
	}
    return 0;
}