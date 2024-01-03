/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 02:10:49 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/03 02:12:55 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
#  define PIPEX_H

typedef struct s_cmd
{
	char			**content;
	struct s_cmd	*next;
}	t_cmd;


t_cmd	*ft_cmdnew(void *content);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void	ft_cmditer(t_cmd *lst, void (*f)(char **));
void	print_commands(char **cmd_lst);

#endif