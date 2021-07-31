/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:20:43 by gpaeng            #+#    #+#             */
/*   Updated: 2021/07/31 17:55:02 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
