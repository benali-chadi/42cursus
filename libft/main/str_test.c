#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*ft_calloc(size_t n, size_t size)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if (!(tmp = malloc(n * size)))
		return (0);
	while (i < n)
	{
		*(tmp + i) = 0;
		i++;
	}
	return ((void *)tmp);
}

int    main(/*int ac, char **av*/)
{
        char * d1 = (char *)ft_calloc(30, 1);
        char * d2 = (char *)calloc(30, 1);
//	char *src = NULL;
//	char *dst = "ds";
//	ac--;
//	char src[] = "tesing this";
//	char dst[123] = "in";
//	char dst_1[123] = "in";
	printf("%s\n%s\n", d1, d2);
//	printf("%lu", strlcpy(dst, src, 0));

	return (0);
}
