/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 02:10:49 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/04 03:55:49 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct s_cmd
{
	char			**content;
	struct s_cmd	*next;
}	t_cmd;

// generate_cmd_list_utils.c
t_cmd	*ft_cmdnew(void *content);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void	ft_cmditer(t_cmd *lst, void (*f)(char **));
void	print_commands(char **cmd_lst);

// parse_inputs.c
char	**extract_path(char **envp);
void	parse_commands(int argc, char **argv, t_cmd **cmd_list);
char	*parse_file(char **str_list, int idx);

#endif