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

// Sys calls (executing another program within the program)
// WARNING: execve replaces the current process with a mirror process
// that's why it should be used with fork();
// Everything after execve in the same process won't be executed
void	external_program()
{
	// Takes 3 args:
	//path to the program | command line arguments | array of env_variables or NULL
	char *args[] = {"ls", "-la", NULL};
	char *path_str = "/Users/albertorodriguez/Library/pnpm:/Users/albertorodriguez/.volta/bin:/Users/albertorodriguez/opt/anaconda3/bin:/Users/albertorodriguez/.nimble/bin:/Users/albertorodriguez/others_utility_apps/epub-translator:/Users/albertorodriguez/my_own_utility_apps/itt-to-srt:/Users/albertorodriguez/my_own_utility_apps:/Users/albertorodriguez/cli_apple_hit:/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Users/albertorodriguez/.cargo/bin:/Applications/kitty.app/Contents/MacOS:/Users/Dz/anaconda/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:/Users/Dz/.rvm/bin";

	char **path;
	char	*exec_path;
	path = ft_split(path_str, ':');

	while (*path != NULL)
	{
		exec_path = ft_sprintf("%s/%s", *path, args[0]);
		if (execve(exec_path, args, NULL) != -1)
			break ;
		path++;
	}

	// while (*(path++))
	// 	printf("path: %s\n", *path);
	
	// execve("/bin/ls", args, NULL);
}

int	main(void)
{
	// redirect_fd();
	// permissions();
	external_program();
	return (0);
}
