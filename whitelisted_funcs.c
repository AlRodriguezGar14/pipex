#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft/libft.h"

// Redirect fd's with dup2()
void	redirect_fd()
{
	char *content_file = "Add content to the output file\n";
	char *content_stdout = "No more content to the output file\n";

	// If the file doesn't exist, it's created
	int	fd = open("output_file.txt", O_WRONLY | O_CREAT, 0644);
	int	original_stdout = dup(STDOUT_FILENO);

	// now fd (the file) is the stdout. Everything printed in the terminal is redirected to the file
	dup2(fd, STDOUT_FILENO);  
	close(fd);
	write(STDOUT_FILENO, content_file, strlen(content_file));

	// reset to the original stdout
	dup2(original_stdout, STDOUT_FILENO);

	// It's important to use write() or a write()-based function due to how printf deals with buffers
	write(STDOUT_FILENO, content_stdout, strlen(content_stdout));
}

// Check permission acesses
void	permissions()
{
	/*
	 * Options: R_OK (Read), W_OK (Write), X_OK (Exec), F_OK (if exists)
	 * Returns: 0 if success. -1 if error
	*/
	if (access("src_file.txt", F_OK) == -1)
	{
		printf("The requested file doesn't exist\n");
		return ;
	}
	if (access("src_file.txt", R_OK) == -1)
		printf("You don't have read permissions\n");
	else
		printf("You can read the file\n");
}


// This is not working because execve doesn't know which is the value of $PATH
// it currently is just printing what it's echoed.
// But, this function is very useful to explain how to redirect outputs.
//
//
// char	*get_path()
// {
// 	int		original_stdout = dup(STDOUT_FILENO);
// 	int		pipes[2];
// 	pid_t	pid;
// 	char	*path;
// 	char	buffer[4096];
// 	char	*args[] = {"echo", "$PATH", NULL};
//
// 	pipe(pipes);
// 	dup2(pipes[1], STDOUT_FILENO);
// 	pid = fork();
// 	if (pid == 0)
// 		execve("/bin/echo", args, NULL);
// 	else
// 	{
// 		wait(NULL);
// 		dup2(original_stdout, STDOUT_FILENO);
// 		close(pipes[1]);
// 		read(pipes[0], buffer, sizeof(buffer));
// 		path = ft_strdup(buffer);
// 		printf("%s", buffer);
// 	}
//
// 	return (path);
// }

char	**get_path(char **env)
{
	char	**path_env;
	char	**path_array;
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			path_env = ft_split(*env, '=');
			path_array = ft_split(path_env[1], ':');
			break ;
		}
		env++;
	}
	return (path_array);
}

// Sys calls (executing another program within the program)
// WARNING: execve replaces the current process with a mirror process
// that's why it should be used with fork();
// Everything after execve in the same process won't be executed
void	external_program(char **envp)
{
	char	**path;
	char	*exec_path;
	// Takes 3 args:
	//path to the program | command line arguments | array of env_variables or NULL
	char *args[] = {"ls", "-la", NULL};

	path = get_path(envp);
	while (*path != NULL)
	{
		exec_path = ft_sprintf("%s/%s", *path, args[0]);
		if (execve(exec_path, args, envp) != -1)
			break ;
		path++;
	}
	
	// execve("/bin/ls", args, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	// redirect_fd();
	// permissions();
	external_program(envp);

	return (0);
}
