/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:20:43 by gpaeng            #+#    #+#             */
/*   Updated: 2021/07/05 17:33:16 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void	ft_philo_eats(t_philo *philo)
{
	t_game *game;

	
}

// void	p_thread()
// {
	// if (짝수 부분)
		// usleep();
	// while (죽지 않을 때까지)
		// {
			// 철학자 먹는다
			// if (다 먹으면)
				// 끝
		// }
// }

int		ft_philo_start(t_game *game)
{
	int		idx;

	idx = 0;
	while (idx < game->philo_num)
	{
		if (pthread_create(&(game->philos[idx].thread_id), NULL, p_thread, &(game->philos[idx])))
			return (0);
		idx++;
	}
}

int		main(int argc, char *argv[])
{
	t_game	philo_info;

	if (argc == 5 || argc == 6)
		if (ft_philo_init(&philo_info, argv, argc))
			return (ft_error("[Error] check philo init"));
	if (ft_philo_start())
		return (ft_error("[Error] check philo start"));
	else
		return (ft_error("[Error] check argc"));
	return (0); //프로그램 정상 종료 알려준다.
}
