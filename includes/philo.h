/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:20:39 by gpaeng            #+#    #+#             */
/*   Updated: 2021/07/31 17:54:40 by gpaeng           ###   ########.fr       */
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
	long long		check_d_time;
	int				eat_cnt;
	t_game			*game;
	pthread_t		thread_id;
}					t_philo;

typedef struct		s_game
{
	int				philo_num; //철학자의 수(포크의 개수)
	int				time_to_die; // simu 시작 후 식사 안하면 'time_to_die' millisecond안에 죽는다
	int				time_to_eat; // 포크를 2개들고 식사하는 시간(millisecond)
	int				time_to_sleep; // 철학자가 자는 시간(millisecond)
	int				must_eat_num; // 모든 철학자가 이 횟수만큼 식사 -> simu 끝, 성립 안하면 철학자 죽었을 때만 simu 끝
	int				die;
	int				eat_check;
	long long 		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eating;
	pthread_mutex_t	write;
	t_philo			*philo;
}					t_game;

/*
**ft_utils.c
*/
int			ft_isspace(char c);
int			ft_atoi(char *str);
int			ft_error(char *s);

/*
**ft_time.c
*/
long long	ft_time();
void		ft_printf(t_game *game, char *str, int id);
void		ft_sleeping(t_game *game);
void	ft_eating(t_game *game);

/*
**ft_init.c
*/
int		ft_philo_input(t_game *game, char *argv[], int argc);
int		ft_philo_init(t_game *game);
int		ft_check_init(t_game *game);

/*
**ft_check.c
*/
void	ft_eat_check(t_game *game, t_philo *philo);
void	ft_death_check(t_game *game, t_philo *philo);

/*
**ft_philo.c
*/
void	ft_philo_eat(t_philo *philo);
void	ft_philo_do(t_philo *philo);
void	*ft_pthread(void *philo);
void	ft_end_philo(t_game *game);
int		ft_philo_start(t_game *game);

/*
**main.c
*/
int		main(int argc, char *argv[]);

#endif