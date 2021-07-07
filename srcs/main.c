/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:20:43 by gpaeng            #+#    #+#             */
/*   Updated: 2021/07/07 18:09:15 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_philo_eat(t_philo *philo)
{
	t_game *game;

	game = philo->game;
	pthread_mutex_lock(&(game->eating));
	ft_printf(game, "is eating", philo->id);
	pthread_mutex_unlock(&(game->eating));
	(game->eat_num)++;
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

void	*ft_p_thread(void *philo)
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
		if (game->eat_num >= game->philo_num)
			break ;
		ft_printf(game, "is sleeping", philo_copy->id); // is sleeping
		ft_printf(game, "is thinking", philo_copy->id); // is thinking 
	}
	return (NULL);
}

void	ft_end_philo(t_game *game, t_philo *philo)
{
	int	idx;

	idx = 0;
	while (idx < game->philo_num)
		pthread_join(philo[idx++].id, NULL);
	idx = 0;
	while (idx < game->philo_num)
		pthread_mutex_destroy(&(game->forks[idx++]));
	free(game->philo);
	free(game->forks);
	pthread_mutex_destroy(&(game->write));
}

int		ft_philo_start(t_game *game)
{
	int		idx;

	idx = 0;
	while (idx < game->philo_num)
	{
		if (pthread_create(&(game->philo[idx].thread_id), NULL, ft_p_thread, (void *)&(game->philo[idx])))
			return (-1);
		idx++;
	}
	ft_end_philo(game, game->philo);
	return (0);
}

int		main(int argc, char *argv[])
{
	t_game	*game;

	game = NULL;
	if (argc != 5 && argc != 6)
		return (ft_error("[Error] check argc"));
	if (ft_philo_input(game, argv, argc))
		return (ft_error("[Error] check philo init"));
	if (ft_philo_start(game))
		return (ft_error("[Error] check philo start"));
	return (0); //프로그램 정상 종료 알려준다.
}
