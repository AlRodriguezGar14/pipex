/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:00:30 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/12 20:24:08 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipes(int fd_pipe[2])
{
	if (pipe(fd_pipe) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

int	fork_process()
{
	int	pid;
	pid = fork();
	if (pid == -1)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	write_process(char *file, int *fd)
{
	int		fd_out;
	char	*error;

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
}

void	read_process(char *file, int *fd)
{
	int		fd_in;
	char	*error;

	close(fd[STDIN_FILENO]);
	if (access(file, F_OK) != 0)
	{
		error = ft_sprintf("no such file or directory: %s\n", file);
		write(STDERR_FILENO, error, ft_strlen(error));
		exit(NO_SUCH_FILE);
	}
	if (access(file, R_OK) != 0)
	{
		perror("Can't read the input file");
		exit(EXIT_FAILURE);
	}
	fd_in = open(file, O_RDONLY);
	if (fd_in == -1)
	{
		perror("Something bad happened when reading the file");
		exit(EXIT_FAILURE);
	}
	dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
}
