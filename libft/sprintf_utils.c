/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:45:50 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/29 20:57:45 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_puthexa_str(size_t n)
{
	char	buffer[17];
	int		i;
	char	*res;

	ft_memset(buffer, '\0', sizeof(buffer));
	i = 15;
	while (n > 0)
	{
		buffer[i] = HEX[n % 16];
		n /= 16;
		i--;
	}
	res = strdup(&buffer[i + 1]);
	return (res);
}

char	*ft_putaddress_str(unsigned long p)
{
	char	*res;
	char	buffer[19];
	int		i;

	ft_memset(buffer, '\0', sizeof(buffer));
	i = 17;
	buffer[0] = '0';
	buffer[1] = 'x';
	while (p > 0)
	{
		buffer[i] = HEX[p % 16];
		p /= 16;
		i--;
	}
	res = strdup(&buffer[i + 1]);
	return (res);
}
