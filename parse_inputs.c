/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 03:42:07 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/09 21:02:39 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**extract_path(char **envp)
{
	char	**path_env;
	char	**path_array;

	path_array = ft_calloc(1, 1);
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path_env = ft_split(*envp, '=');
			path_array = ft_split(path_env[1], ':');
			break ;
		}
		envp++;
	}
	return (path_array);
}

static void	parse_commands(int argc, char **argv, t_cmd **cmd_list)
{
	int	idx;

	idx = 2;
	while (idx < argc -1)
		ft_cmdadd_back(cmd_list, ft_cmdnew(argv[idx++]));
}

static char	*parse_file(char **str_list, int idx)
{
	char	*file;

	if (str_list[idx])
		file = ft_strdup(str_list[idx]);
	else
		file = NULL;
	return (file);
}

void	parse_input(int argc, char **argv, char *files[2], t_cmd **cmd_list)
{
	if (argc < 5)
		exit (EXIT_FAILURE);
	files[STDIN_FILENO] = parse_file(argv, 1);
	files[STDOUT_FILENO] = parse_file(argv, argc - 1);
	parse_commands(argc, argv, cmd_list);
}
