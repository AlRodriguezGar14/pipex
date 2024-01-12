/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 02:32:13 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/12 20:34:03 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_cmd(t_cmd *cmd_list, char **path, char **envp)
{
	char	*exec_path;
	char	*err_mssg;

	exec_path = ft_sprintf("%s", cmd_list->content[0]);
	while (*path != NULL)
	{
		if (access(exec_path, X_OK) == 0)
			execve(exec_path, cmd_list->content, envp);
		exec_path = ft_sprintf("%s/%s", *path, cmd_list->content[0]);
		path++;
	}
	if (*path == NULL)
	{
		err_mssg = ft_sprintf("command not found: %s\n", cmd_list->content[0]);
		write(STDERR_FILENO, err_mssg, ft_strlen(err_mssg));
		exit(CMD_NOT_FOUND);
	}
}

void	mid_process(t_cmd *cmd, char **path, char **envp)
{

	int		fd_out;
	char	*error;
	char	*file = "tmp";
	int		fd[2];

	create_pipes(fd);

	close(fd[STDOUT_FILENO]);
	fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		error = ft_sprintf("no such file or directory: %s\n", file);
		write(STDERR_FILENO, error, ft_strlen(error));
		exit(NO_SUCH_FILE);
	}
	dup2(fd[STDIN_FILENO], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);

	exec_cmd(cmd, path, envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*files[2];
	t_cmd	*cmd_list;
	char	**path;
	int		fd_pipe[2];

	if (argc < 5)
		exit (2);
	cmd_list = NULL;
	path = extract_path(envp);
	parse_input(argc, argv, files, &cmd_list);
	create_pipes(fd_pipe);
	if (fork_process() == 0)
	{
		read_process(files[STDIN_FILENO], fd_pipe);
		exec_cmd(cmd_list, path, envp);
	}
	wait(NULL);
	cmd_list = cmd_list->next;
	write_process(files[STDOUT_FILENO], fd_pipe);
	exec_cmd(cmd_list, path, envp);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	exit(EXIT_SUCCESS);
}
