/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 14:17:50 by gpaeng            #+#    #+#             */
/*   Updated: 2021/07/01 14:28:28 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_mutex_init(t_philo *philo)
{
	int idx;

	idx = 0;
	while (idx < philo->philo_num)
	{
		
	}
}

int	ft_check_init(t_philo *philo)
{
	return (philo->philo_num < 2 || philo->time_to_die < 0 ||
	philo->time_to_eat < 0 || philo->time_to_sleep < 0);
}

int ft_philo_init(t_philo *philo, char *argv[], int argc)
{
	philo->philo_num = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->must_eat_num = -1; //없음
	if (argc == 6)
		philo->must_eat_num = ft_atoi(argv[5]);
	if (ft_check_init(philo))
		return (-1);
	if (ft_mutex_init(philo)))
		return (-1);
	
}