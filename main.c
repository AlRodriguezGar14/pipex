/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 02:32:13 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/29 21:03:37 by alberrod         ###   ########.fr       */
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

#include "libft/libft.h"


int	main(int argc, char **argv)
{
	int 	idx;
	char	*input_file = NULL;
	char	*output_file = NULL;
	char	**commands1;
	char	**commands2;


	idx = 0;
	while (++idx < argc)
	{
		if (idx == 1)
			input_file = argv[idx];
		else if (idx == argc - 1)
			output_file = argv[idx];
		else if (idx == 2)
		{
			commands1 = ft_split(argv[idx], ' ');
		}
		else
			commands2 = ft_split(argv[idx], ' ');
	}
	printf("input file: %s\n", input_file);
	printf("output file: %s\n", output_file);

	int pid = fork();
	if (pid == 0)
		execve(ft_sprintf("/bin/%s", commands1[0]), commands1, NULL);
	else
	{
		wait(NULL);
		execve(ft_sprintf("/bin/%s", commands2[0]), commands2, NULL);
	}
	return (0);
}