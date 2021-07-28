/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:20:43 by gpaeng            #+#    #+#             */
/*   Updated: 2021/07/28 16:41:47 by gpaeng           ###   ########.fr       */
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
