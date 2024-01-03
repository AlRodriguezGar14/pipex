/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 02:32:13 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/03 02:17:28 by alberrod         ###   ########.fr       */
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
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	*file1;
	char	*file2;
	t_cmd	*cmd_list = NULL;
	int		idx;

	// Sanitize input
	if (argc < 5)
		return (1);
	// Parse files	
	file1 = ft_strdup(argv[1]);
	file2 = ft_strdup(argv[argc - 1]);
	idx = 2;
	while (idx < argc -1)
		ft_cmdadd_back(&cmd_list, ft_cmdnew(argv[idx++]));


	printf("file1: %s\n", file1);
	printf("file2: %s\n", file2);
	ft_cmditer(cmd_list, print_commands);
	
	return (0);
}