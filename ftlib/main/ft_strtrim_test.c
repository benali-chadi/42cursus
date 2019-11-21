#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <unistd.h>

void	*ft_calloc(size_t n, size_t size)
{
	void	*tmp;
	size_t	i;

	i = 0;
	if (!(tmp = malloc(n * size)))
		return (0);
	while (i < n)
	{
		*((char *)tmp + i) = 0;
		i++;
	}
	return (tmp);
}


int main(int ac, char **av)
{
	int size = 8539;
	int i = 0;
    int * d1 = ft_calloc(size, sizeof(int));
    int * d2 = calloc(size, sizeof(int));
	 while (d1[i])
	{
		printf("%d", d1[i]);
		i++;
	}
	i = 0;
	printf("\n");
	while (d2[i])
	{
		printf("%d", *(d2 + i));
		i++;
	}
    return (0);
}