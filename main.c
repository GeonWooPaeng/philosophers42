/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:53:16 by gpaeng            #+#    #+#             */
/*   Updated: 2021/07/01 16:44:30 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex_lock;

int g_cnt = 0;

void *t_function(void *data)
{
	int i;
	char *thread_name = (char *)data;
	pthread_mutex_lock(&mutex_lock);
	g_cnt = 0;
	
	for (i = 0; i < 3; i++)
	{
		printf("%s cnt %d\n", thread_name, g_cnt);
		g_cnt += 1;
		sleep(1);
	}
	pthread_mutex_unlock(&mutex_lock);
}

int main()
{
	pthread_t p_thread1, p_thread2;
	int status;

	pthread_mutex_init(&mutex_lock, NULL);
	pthread_create(&p_thread1, NULL, t_function, (void *)"Thread1");
	pthread_create(&p_thread2, NULL, t_function, (void *)"thread2");

	pthread_join(p_thread1, (void *)&status);
	pthread_join(p_thread2, (void *)&status); 
}