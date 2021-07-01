/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:20:43 by gpaeng            #+#    #+#             */
/*   Updated: 2021/07/01 17:55:09 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
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
