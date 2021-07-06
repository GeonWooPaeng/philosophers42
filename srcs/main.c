/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:20:43 by gpaeng            #+#    #+#             */
/*   Updated: 2021/07/06 16:32:45 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_philo_eats(t_philo *philo)
{
	t_game *game;

	game = philo->game;
	//fork
	pthread_mutex_lock(&(game->forks[philo->left_fork]));
	printf(""); // has taken a fork
	pthread_mutex_lock(&(game->forks[philo->right_fork]));
	printf(""); // has taken a fork
	//eat
	pthread_mutex_lock(&(game->eating));
	printf(""); //is eating
	pthread_mutex_unlock(&(game->eating));
	(game->eat_num)++;
	pthread_mutex_unlock(&(game->forks[philo->left_fork]));
	pthread_mutex_unlock(&(game->forks[philo->right_fork]));
}

void	ft_p_thread(t_philo *philo)
{
	int	idx;
	t_game	*game;
	
	idx = 0;
	game = philo->game;
	if (philo->thread_id % 2)
		usleep(15000);
	while (!(game->die))
	{
		ft_philo_eats(philo);
		if (game->eat_num >= game->philo_num)
			break ;
		printf(""); // is sleeping
		printf(" "); // is thinking 
	}
}

void	ft_end_philo(t_game *game, t_philo *philo)
{
	int	idx;

	idx = 0;
	while (idx < game->philo_num)
		pthread_join(philo[idx++].thread_id, NULL);
	idx = 0;
	while (idx < game->philo_num)
		pthread_mutex_destroy(&(game->forks[idx++]));
	pthread_mutex_destroy(&(game->sleeping));
	pthread_mutex_destroy(&(game->thinking));
}

int		ft_philo_start(t_game *game)
{
	int		idx;

	idx = 0;
	while (idx < game->philo_num)
	{
		if (pthread_create(&(game->philo[idx].thread_id), NULL, ft_p_thread, &(game->philo[idx])))
			return (0);
		idx++;
	}
	ft_end_philo(game, game->philo);
}

int		main(int argc, char *argv[])
{
	t_game	*game;

	if (argc == 5 || argc == 6)
		if (ft_philo_input(game, argv, argc))
			return (ft_error("[Error] check philo init"));
	if (ft_philo_start(game))
		return (ft_error("[Error] check philo start"));
	else
		return (ft_error("[Error] check argc"));
	return (0); //프로그램 정상 종료 알려준다.
}
