/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 02:32:13 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/09 21:09:26 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_cmd(t_cmd *cmd_list, char **path, char **envp)
{
	char	*exec_path;
	char	*err_mssg;

	while (*path != NULL)
	{
		exec_path = ft_sprintf("%s/%s", *path, cmd_list->content[0]);
		if (access(exec_path, X_OK) == 0)
			execve(exec_path, cmd_list->content, envp);
		path++;
	}
	if (*path == NULL)
	{
		err_mssg = ft_sprintf("Command not found: %s\n", cmd_list->content[0]);
		write(STDERR_FILENO, err_mssg, ft_strlen(err_mssg));
		// exit(EXIT_FAILURE);
		exit(1);
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
