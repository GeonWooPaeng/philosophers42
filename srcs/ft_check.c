/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:46:24 by gpaeng            #+#    #+#             */
/*   Updated: 2021/07/31 17:55:19 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_eat_check(t_game *game, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < game->philo_num && philo[i].eat_cnt > game->must_eat_num)
		i++;
	if (i == game->philo_num)
		game->eat_check = 1;
}

void	ft_death_check(t_game *game, t_philo *philo)
{
	int		i;
	int		death_check;

	death_check = 0;
	while (!game->eat_check)
	{
		i = 0;
		while ((i < game->philo_num) && (!(game->die)))
		{
			pthread_mutex_lock(&(game->eating));
			if (ft_time() - philo[i].check_d_time > game->time_to_die)
			{
				ft_printf(game, "died", i);
				death_check = 1;
			}
			pthread_mutex_unlock(&(game->eating));
			usleep(100);
			i++;
		}
		if (death_check)
			break ;
		ft_eat_check(game, game->philo);
	}
}
