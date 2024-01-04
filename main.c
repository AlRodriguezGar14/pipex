/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 02:32:13 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/04 06:19:30 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(t_cmd *cmd_list, char **path, char **envp)
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

// Reads from the in file. Output to the write channel
int	set_in_file(int *fd_pipe, char *file1)
{
	int	fd_in;

	fd_in = open(file1, O_RDONLY);
	if (fd_in == -1)
	{
		perror("cannot open fd in");
		exit (EXIT_FAILURE);
	}
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_pipe[0], STDOUT_FILENO);
	close(fd_in);
	close(fd_pipe[1]);
	return (0);
}

void	launch_cmd(t_cmd *cmd_list, char **path, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exec_cmd(cmd_list, path, envp);
	else
		waitpid(pid, NULL, 0);
}

// Reads from the read channel. Output to the output file 
int	set_out_file(int *fd_pipe, char *file2)
{
	int	fd_out;

	dup2(fd_pipe[1], STDIN_FILENO);
	close(fd_pipe[0]);
	fd_out = open(file2, O_WRONLY | O_CREAT, 0644);
	if (fd_out == -1)
	{
		perror("cannot open fd_out");
		exit (EXIT_FAILURE);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*file1;
	char	*file2;
	t_cmd	*cmd_list;
	char	**path;
	int		fd_pipe[2];

	if (argc < 5)
		return (1);
	file1 = parse_file(argv, 1);
	file2 = parse_file(argv, argc - 1);
	cmd_list = NULL;
	parse_commands(argc, argv, &cmd_list);
	path = extract_path(envp);
	if (pipe(fd_pipe) == -1)
	{
		perror("pipe");
		exit(1);
	}

	set_out_file(fd_pipe, file2);
	launch_cmd(cmd_list->next, path, envp);
	set_in_file(fd_pipe, file1);
	launch_cmd(cmd_list, path, envp);
	return (0);
}
