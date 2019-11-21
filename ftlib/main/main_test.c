#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "./libft/libft.h"


t_list	*ft_lstnew(void *content)
{
	t_list *t_list_1;

	if (!(t_list_1 = (t_list *)malloc(sizeof(t_list))))
		return (0);
	t_list_1->content = (char *)malloc(sizeof(char) * 2);
	t_list_1->content = content;
	t_list_1->next = NULL;
	return (t_list_1);
}

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (!alst)
		return ;
	new->next = *alst;
	*alst = new;
}

int	ft_lstsize(t_list *lst)
{
	t_list	*pt;
	int		i;

	if (!lst)
		return (0);
	i = 1;
	pt = lst;
	while (pt->next != NULL)
	{
		pt = pt->next;
		i++;
	}
	return (i);
}

void *del(void *t)
{
	free(t);
	return (t);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		(del)(lst->content);
		free(lst);
	}
}

int main()
{
	t_list *alst; 
	t_list *t_list_1;
	t_list *t_list_2;
	char	l[] = "this is a test";

	t_list_1 = ft_lstnew(l);
	alst = t_list_1;
	t_list_2 = ft_lstnew("chadi");
	ft_lstadd_front(&alst, t_list_2);
	printf("%s\n", t_list_1->content);
	printf("%d\n", ft_lstsize(alst));
	ft_lstdelone(t_list_1, (*del)(t_list_1));
	printf("%d\n", ft_lstsize(alst));
    return (0);
}