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