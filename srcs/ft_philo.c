/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:45:10 by gpaeng            #+#    #+#             */
/*   Updated: 2021/07/31 17:45:46 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_philo_eat(t_philo *philo)
{
	t_game *game;

	game = philo->game;
	pthread_mutex_lock(&(game->eating));
	ft_printf(game, "is eating", philo->id);
	philo->check_d_time = ft_time();
	pthread_mutex_unlock(&(game->eating));
	(philo->eat_cnt)++;
	ft_eating(game);
}

void	ft_philo_do(t_philo *philo)
{
	t_game *game;

	game = philo->game;
	//fork
	pthread_mutex_lock(&(game->forks[philo->left_fork]));
	ft_printf(game, "has taken a fork", philo->id);
	pthread_mutex_lock(&(game->forks[philo->right_fork]));
	ft_printf(game, "has taken a fork", philo->id);
	//eat
	ft_philo_eat(philo);
	pthread_mutex_unlock(&(game->forks[philo->right_fork]));
	pthread_mutex_unlock(&(game->forks[philo->left_fork]));
}

void	*ft_pthread(void *philo)
{
	t_game	*game;
	t_philo *philo_copy;

	philo_copy = (t_philo *)philo;
	game = philo_copy->game;
	if ((philo_copy->id) % 2)
		usleep(15000);
	while (!(game->die))
	{
		ft_philo_do(philo_copy);
		if (game->eat_check)
			break ;
		ft_printf(game, "is sleeping", philo_copy->id);
		ft_sleeping(game);
		ft_printf(game, "is thinking", philo_copy->id);
	}
	return (0);
}

void	ft_end_philo(t_game *game)
{
	int		i;
	t_philo	*philo;
	
	i = 0;
	philo = game->philo;
	while (i < game->philo_num)
		pthread_join(philo[i++].id, NULL);
	i = 0;
	while (i < game->philo_num)
		pthread_mutex_destroy(&(game->forks[i++]));
	free(game->philo);
	free(game->forks);
	pthread_mutex_destroy(&(game->write));
}

int		ft_philo_start(t_game *game)
{
	int		i;
	void 	*v_philo;
	
	i = 0;
	game->start_time = ft_time();
	while (i < game->philo_num)
	{	
		(game->philo[i]).check_d_time = ft_time();
		v_philo = (void *)&(game->philo[i]);
		if (pthread_create(&(game->philo[i].thread_id), NULL, ft_pthread, v_philo))
			return (-1);
		i++;
	}
	ft_death_check(game, game->philo);
	ft_end_philo(game);
	return (0);
}
