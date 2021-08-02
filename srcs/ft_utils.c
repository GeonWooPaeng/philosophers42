/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 13:26:58 by gpaeng            #+#    #+#             */
/*   Updated: 2021/08/02 14:54:29 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		ft_isspace(char c)
{
	return (c == '\f' || c == '\n' || c == '\r' ||
	c == '\t' || c == '\v' || c == ' ');
}

int		ft_atoi(char *str)
{
	int result;
	int sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * sign);
}

int		ft_error(char *s)
{
	printf("%s\n", s);
	return (-1);
}

long long ft_time()
{
	struct timeval time;
	long long ms;
	
	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

void	ft_printf(t_game *game, char *str, int id)
{
	pthread_mutex_lock(&(game->write));
	if (!(game->die))
	{
		printf("%lli ", ft_time() - game->start_time); //속도
		printf("%i ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(game->write));
	return ;
}
