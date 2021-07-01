/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:53:16 by gpaeng            #+#    #+#             */
/*   Updated: 2021/06/29 19:08:51 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *t_function(void *param)
{
	for (int i= 1; i<=5; i++)
	{
		usleep(1000 * 1000 * 2);
		printf("%s: ", (char *)param);
		printf("쓰레드 함수 실행중 %d/5\n",i);
	}
	printf("쓰레드 함수 종료\n");
	return (void *)2147483647;
}

int main()
{
	pthread_t p_thread1;
	pthread_t p_thread2;
	int thr_id1;
	int thr_id2;

	thr_id1 = pthread_create(&p_thread1, NULL, t_function, "thread1");
	thr_id2 = pthread_create(&p_thread2, NULL, t_function, "thread2");
	if (thr_id1 < 0 || thr_id2 < 0)
	{
		perror("thread create error: ");
		exit(0);
	}
	pthread_detach(p_thread1);
	pthread_detach(p_thread2);
	// pthread_join(p_thread1, 0);
	// pthread_join(p_thread2, 0);

	int s = 0;
	while (42)
	{
		printf("%d초 경과\n", s++);
		usleep(1000 * 1000);
	}
	printf("main() 종료 \n");
	return (0);

	
}