/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:20:43 by gpaeng            #+#    #+#             */
/*   Updated: 2021/07/20 17:11:29 by gpaeng           ###   ########.fr       */
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
		if (game->eat_num == game->philo_num)
			break ;
		ft_printf(game, "is sleeping", philo_copy->id); // is sleeping
		ft_sleep(game);
		ft_printf(game, "is thinking", philo_copy->id); // is thinking 
	}
	return (NULL);
}

void	ft_end_philo(t_game *game)
{
	int		idx;
	t_philo	*philo;
	
	idx = 0;
	philo = game->philo;
	while (idx < game->philo_num)
		pthread_join(philo[idx++].id, NULL);
	idx = 0;
	while (idx < game->philo_num)
		pthread_mutex_destroy(&(game->forks[idx++]));
	free(game->philo);
	free(game->forks);
	pthread_mutex_destroy(&(game->write));
}

void	ft_death_check(t_game *game, t_philo *philo)
{
	int		idx;
	int		death_check;

	death_check = 0;
	while (game->eat_num != game->philo_num)
	{
		idx = 0;
		while ((idx < game->philo_num) && (!(game->die)))
		{
			pthread_mutex_lock();
			if ()
			pthread_mutex_unlock();
		}
	}
}

int		ft_philo_start(t_game *game)
{
	int		idx;
	void 	*v_philo;
	
	idx = 0;
	game->start_time = ft_time();
	while (idx < game->philo_num)
	{	
		v_philo = (void *)&(game->philo[idx]);
		if (pthread_create(&(game->philo[idx].thread_id), NULL, ft_p_thread, v_philo))
			return (-1);
		idx++;
	}
	//사망자 check 해줘야 합니다.
	ft_death_check(game, game->philo);
	ft_end_philo(game);
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
