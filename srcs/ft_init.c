/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 14:17:50 by gpaeng            #+#    #+#             */
/*   Updated: 2021/07/01 17:14:41 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_mutex_init(t_game *game)
{
	int idx;

	idx = 0;
	while (idx < game->philo_num)
	{
		if (pthread_mutex_init(&(game->forks[idx]), NULL))
			return (-1);
	}
	return (0);
}

int	ft_check_init(t_game *game)
{
	return (game->philo_num < 2 || game->time_to_die < 0 ||
	game->time_to_eat < 0 || game->time_to_sleep < 0);
}

int ft_philo_init(t_game *game, char *argv[], int argc)
{
	game->philo_num = ft_atoi(argv[1]);
	game->time_to_die = ft_atoi(argv[2]);
	game->time_to_eat = ft_atoi(argv[3]);
	game->time_to_sleep = ft_atoi(argv[4]);
	game->must_eat_num = -1; //없음
	if (argc == 6)
		game->must_eat_num = ft_atoi(argv[5]);
	if (ft_check_init(game))
		return (-1);
	if (ft_mutex_init(game))
		return (-1);
	
}