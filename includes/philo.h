/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:20:39 by gpaeng            #+#    #+#             */
/*   Updated: 2021/07/07 11:36:11 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct		s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	struct s_game	*game;
}					t_philo;

typedef struct		s_game
{
	int				philo_num; //철학자의 수(포크의 개수)
	int				time_to_die; // simu 시작 후 식사 안하면 'time_to_die' millisecond안에 죽는다
	int				time_to_eat; // 포크를 2개들고 식사하는 시간(millisecond)
	int				time_to_sleep; // 철학자가 자는 시간(millisecond)
	int				must_eat_num; // 모든 철학자가 이 횟수만큼 식사 -> simu 끝, 성립 안하면 철학자 죽었을 때만 simu 끝
	int				eat_num;
	int				die;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eating;
	pthread_mutex_t	sleeping;
	pthread_mutex_t	thinking;
	t_philo			*philo;
}					t_game;

#endif