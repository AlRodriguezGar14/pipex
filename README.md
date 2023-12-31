## Understanding the allowed functions:

### dup2():

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
