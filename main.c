/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 02:32:13 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/05 15:06:21 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_cmd(t_cmd *cmd_list, char **path, char **envp)
{
	char	*exec_path;

	while (*path != NULL)
	{
		exec_path = ft_sprintf("%s/%s", *path, cmd_list->content[0]);
		if (execve(exec_path, cmd_list->content, envp) != -1)
			break ;
		path++;
	}
	if (*path == NULL)
	{
		perror("execve: command not found");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*files[2];
	t_cmd	*cmd_list;
	char	**path;
	int		fd_pipe[2];
	int		pid;

	cmd_list = NULL;
	path = extract_path(envp);
	parse_input(argc, argv, files, &cmd_list);
	create_pipes(fd_pipe);
	fork_process(&pid);
	if (pid == 0)
	{
		read_process(files[STDIN_FILENO], fd_pipe);
		exec_cmd(cmd_list, path, envp);
	}
	write_process(files[STDOUT_FILENO], fd_pipe);
	exec_cmd(cmd_list->next, path, envp);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	return (0);
}
