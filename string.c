/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:46:43 by msoler-e          #+#    #+#             */
/*   Updated: 2022/11/28 11:47:32 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	int	n;

	n = 0;
	if (!s)
		return (n);
	while (*s != '\0')
	{
		n++;
		s++;
	}
	return (n);
}

int	ft_putchar_fd(char c, int fd)
{
	return ((int)write(fd, &c, 1));
}

int	ft_putnbr_fd(long unsigned x, int fd)
{
	int	n;

	n = 0;
	if (x > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		n += ft_putchar_fd(x + '0', fd);
	return (n);
}

int	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		return ((int)write(fd, s, ft_strlen(s)));
	return (0);
}

int	ft_putnchar_fd(char c, int fd, int x)
{
	int	n;

	n = 0;
	while (x-- > 0)
		n += (int)write(fd, &c, 1);
	return (n);
}
