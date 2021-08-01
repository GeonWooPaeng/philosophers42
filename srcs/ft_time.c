/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:43:13 by gpaeng            #+#    #+#             */
/*   Updated: 2021/08/01 23:23:55 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

void	ft_sleeping(t_game *game)
{
	long long sleep_time;
	long long start_s_time;
	long long now_s_time;
	
	sleep_time = (long long)(game->time_to_sleep);
	start_s_time = ft_time();
	while (!(game->die))
	{
		if ((now_s_time - start_s_time) >= sleep_time)
			break ;
		now_s_time = ft_time();
		usleep(10);
	}
}

void	ft_eating(t_game *game)
{
	long long eat_time;
	long long start_e_time;
	long long now_e_time;

	eat_time = (long long)(game->time_to_eat);
	start_e_time = ft_time();
	while (!(game->die))
	{
		now_e_time = ft_time();
		if ((now_e_time - start_e_time) >= eat_time)
			break ;
		usleep(10);
	}
}
