/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 02:32:13 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/04 03:32:55 by alberrod         ###   ########.fr       */
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

void	parse_commands(int argc, char **argv, t_cmd **cmd_list)
{
	int	idx;

	idx = 2;
	while (idx < argc -1)
		ft_cmdadd_back(cmd_list, ft_cmdnew(argv[idx++]));
}

void	exec_cmd(t_cmd *cmd_list, char **path, char **envp)
{
	char	*exec_path;

	while(*path != NULL)
	{
		exec_path = ft_sprintf("%s/%s", *path, cmd_list->content[0]);
		if (execve(exec_path, cmd_list->content, envp) != -1)
			break ;
		path++;
	}
	if (*path == NULL)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

// Reads from the in file. Output to the write channel
void	set_in_file(int fd_pipe, char *file1)
{
	int	fd_in;

	fd_in = open(file1, O_RDONLY);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_pipe, STDOUT_FILENO);
	close(fd_in);
	close(fd_pipe);
}

void	launch_cmd(t_cmd *cmd_list, char **path, char **envp)
{
	int pid;
	
	pid = fork();
	if (pid == 0)
		exec_cmd(cmd_list, path, envp);
	else
		wait(NULL);
}

// Reads from the read channel. Output to the output file 
void	set_out_file(int fd_pipe, char *file2)
{
	int fd_out;
	
	dup2(fd_pipe, STDIN_FILENO);
	close(fd_pipe);
	fd_out = open(file2, O_WRONLY | O_CREAT, 0644 | O_APPEND);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

int	main(int argc, char **argv, char **envp)
{
	char	*file1;
	char	*file2;
	t_cmd	*cmd_list = NULL;
	char	**path;
	int		fd_pipe[2];

	if (argc < 5)
		return (1);
	file1 = ft_strdup(argv[1]);
	file2 = ft_strdup(argv[argc - 1]);
	parse_commands(argc, argv, &cmd_list);
	path = extract_path(envp);
	if (pipe(fd_pipe) == -1)
	{
		perror("pipe");
		exit(-1);
	}
	set_in_file(fd_pipe[1], file1);
	launch_cmd(cmd_list, path, envp);
	set_out_file(fd_pipe[0], file2);
	launch_cmd(cmd_list->next, path, envp);
	return (0);
}