/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 02:10:49 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/03 02:47:44 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
#  define PIPEX_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "libft/libft.h"
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