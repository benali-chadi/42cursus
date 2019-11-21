#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int		strl(char const *str, char c)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	if (str[0] != c && str[0] != '\0')
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

static char 	**free_tab(char **a_str, int i)
{
	while (i--)
		free(a_str[i]);
	free(a_str);
	a_str = NULL;
	return (NULL);
}

char			**ft_split(char const *str, char c)
{
	char	**a_str;
	int		i;
	int		k;
	int		*p;
	int		words;

	if (!str)
		return (0);
	words = strl(str, c);
	i = -1;
	k = 0;
	p = &k;
	
	if (!(a_str = (char **)malloc((words + 1) * (sizeof(char *)))))
		return (0);
	while (++i < words)
	{
		if (!(a_str[i] = (char *)malloc(wordlen(str, p, c) + 1)))
			return (free_tab(a_str, i));
		give_value(a_str[i], str, p, c);
	}
	a_str[i] = 0;
	return (a_str);
}


int main(/*int ac, char **av*/)
{
	char **tab;
	int i = 0;

	tab = ft_split("lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultricies diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi.", 'z');
//    ac--;
	while (tab[i])
	{
   		printf("%s\n", tab[i]);
		i++;
	}
}