# Understanding the allowed functions:

## dup2():

Redirects fd’s. It is useful for:

- Write in a file the content that would normally be printed in the stdout

```c
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
```

## access()

Check for permissions on a file or even if a path is accessible.

The options are:

- R_OK (read)
- W_OK (write)
- X_OK (execute)
- F_OK (exists?)

If errors, return **-1**

```c
void	permissions()
{
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
```

## fork()

Create a child process simultaneous to the parent one.
The Child process is always **0**.

```c
void	fork_processes()
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) // The child process is always 0
		printf("Child process with pid %d\n", getpid());
	else
	{
		wait(NULL); // Guarantee the child is executed first
		printf("Parent process with pid %d\n", getpid());
	}
}
```

## unlink()

Delete a file.

Returns:

- 0, sucessfully deleted
- _anything else_, error.

```c
void	deleter()
{
	if (unlink("something.txt") == 0)
		printf("sucesfully removed");
	else
		printf("ups, something went wrong deleting the file");
}
```

## pipe()

Create unidirectional data channels to just write or read (pipe) what it's written at one end.
Ideally, this communication is done with parent/child processes

pipe[0] reads
pipe[1] writes

```c
void	pipelines()
{
	int		pipefd[2];
	int		original_stdout = dup(STDOUT_FILENO);
	pid_t	pid;
	char	buffer[256];
	char	*args[] = {"echo", "Hello", "World", NULL};
	char	*hi;

	if (pipe(pipefd) == -1)
	{
		// error message to the stderr
		// strerror passes a pointer to the error
		perror("something went wrong when doing piping");
		printf("an error occurred: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("something went wrong when forking");
		printf("an error occurred: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		execve("/bin/echo", args, NULL);
	else
	{
		wait(NULL);
		dup2(original_stdout, STDOUT_FILENO);
		close(pipefd[1]);
		read(pipefd[0], buffer, sizeof(buffer)); // Reads from the stdout execve
		close(pipefd[0]);
		hi = ft_strdup(buffer);
		printf("%s", hi);
	}

}
```

## execve()

Syscalls (executing another program within our program).

WARNING: execv() replaces the current process with its mirror process; that's why at least fork() is needed.
Everything after execve() in the same process won't be executed.

Takes three arguments:
path to program | command line args (in array) form | array if env_variables or NULL

```c
void	external_program(char **envp)
{
	char	**path;
	char	*exec_path;
	char *args[] = {"ls", "-la", NULL};

	path = get_path(envp);
	while (*path != NULL)
	{
		exec_path = ft_sprintf("%s/%s", *path, args[0]);
		if (execve(exec_path, args, envp) != -1)
			break ;
		path++;
	}
}
```
