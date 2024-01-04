/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_cmd_list_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 02:10:19 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/04 03:54:50 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*ft_cmdnew(void *content)
{
	t_cmd	*new_l;

	new_l = malloc(sizeof(struct s_list));
	if (!new_l)
		return (NULL);
	new_l->content = ft_split((char *)content, ' ');
	new_l->next = NULL;
	return (new_l);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*current;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	ft_cmditer(t_cmd *lst, void (*f)(char **))
{
	t_cmd	*curr;

	if (!lst)
		return ;
	while (lst)
	{
		curr = lst;
		lst = curr->next;
		f(curr->content);
	}
}

void	print_commands(char **cmd_lst)
{
	printf("cmd: ");
	while (*cmd_lst)
		printf("%s, ", *cmd_lst++);
	printf("\n");
}
