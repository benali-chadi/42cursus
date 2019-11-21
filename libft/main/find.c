#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libft/libft.h"

static int		strl(char const *str, char c)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	if (str[0] != c)
		words++;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			if (str[i + 1] != c && str[i + 1] != '\0')
				words++;
		i++;
	}
	return (words);
}

static int		wordlen(char const *str, int *p, char c)
{
	int i;
	int w;

	w = 0;
	i = *p;
	while (str[i] == c)
	{
		i++;
		*p += 1;
	}
	while (str[i] != '\0')
	{
		if (str[i] == c)
			break ;
		w++;
		i++;
	}
	return (w);
}

static void		give_value(char *a_str, char const *str, int *p, int c)
{
	int j;

	j = -1;
	while (str[*p] != '\0')
	{
		if (str[*p] == c)
			break ;
		a_str[++j] = str[*p];
		*p += 1;
	}
	a_str[++j] = '\0';
}

char			**ft_split(char const *str, char c)
{
	char	**a_str;
	int		i;
	int		k;
	int		*p;

	if (!str)
		return (0);
	i = -1;
	k = 0;
	p = &k;
	if (!(a_str = (char **)malloc(strl(str, c) * sizeof(char *) + 2)))
		return (0);
	while (++i < strl(str, c))
	{
		if (!(a_str[i] = (char *)malloc((wordlen(str, p, c)) + 1)))
			return (0);
		give_value(a_str[i], str, p, c);
	}
	*(a_str + i) = 0;
	return (a_str);
}

int main(/* int ac, char **av*/)
{
	char    **tabstr;
	int i;

	i = 0;
	tabstr = ft_split("lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse", ' ');
	while (tabstr[i])
	{
		printf("%s\n", tabstr[i]);
		i++;
	}
//	printf("%s\n%s\n", dest, dest_1);
	return (0);
}