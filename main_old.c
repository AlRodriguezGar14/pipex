/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 02:32:13 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/03 04:13:07 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Tu programa deberá ejecutarse de la siguiente forma:
//
//   ./pipex archivo1 comando1 comando2 archivo2
//
// Deberá utilizar 4 argumentos:
// • archivo1 y archivo2 son nombres de arhivos.
//
// • comando1 y comando2 son comandos de shell con sus respectivos parámetros. La ejecución del programa pipex deberá hacer lo mismo que el siguiente comando:
// $> < archivo1 comando1 | comando2 > archivo2
//
// Funcs allowed:
// open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid

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

int	main(int argc, char **argv, char **envp)
{
	char	*file1;
	char	*file2;
	t_cmd	*cmd_list = NULL;
	char	**path;
	int		original_stdout;
	int		original_stdin;
	int		pid;

	// Sanitize input
	if (argc < 5)
		return (1);
	// Parse files	
	file1 = ft_strdup(argv[1]);
	file2 = ft_strdup(argv[argc - 1]);
	parse_commands(argc, argv, &cmd_list);
	// Extract the path
	path = extract_path(envp);

	// Backup the original stdout/in
	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);

	// file1 is the stdin; tmp is the stdout
	int	fd_in = open(file1, O_RDONLY);
	int	fd_tmp = open("tmp.txt", O_WRONLY | O_CREAT, 0644);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_tmp, STDOUT_FILENO);
	close(fd_in);
	close(fd_tmp);
	pid = fork();
	if (pid == 0)
		exec_cmd(cmd_list, path, envp); // exec the first cmd
	else
		wait(NULL);
	// set tmp as stdin
	fd_tmp = open("tmp.txt", O_RDONLY);
	dup2(fd_tmp, STDIN_FILENO);
	close(fd_tmp);
	// set stdout to the given file
	int	fd_out = open(file2, O_WRONLY | O_CREAT, 0644);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);

	// repeat process of executing
	pid = fork();
	if (pid == 0)
		exec_cmd(cmd_list->next, path, envp);
	else
		wait(NULL);
	dup2(original_stdout, STDOUT_FILENO);
	unlink("tmp.txt");
	return (0);
}