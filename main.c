/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:53:16 by gpaeng            #+#    #+#             */
/*   Updated: 2021/06/29 17:09:52 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *p_function(void *data);

int main(void)
{
	pthread_t pthread;
	int thr_id;
	int status;
	char p1[] = "thread_created";
	char p2[] = "thread_main";

	thr_id = pthread_create(&pthread, NULL, p_function, (void *)p1);
	if (thr_id < 0)
	{
		perror("pthread() create error");
		exit(EXIT_FAILURE);
	}

	p_function((void *)p2);
	printf("created thread id:%lx\n", pthread);
	printf("end\n");
	return (0);
}

void *p_function(void *data)
{
	pthread_t tid;

	char* thread_name = (char *)data;
	int i = 0;
	tid = pthread_self();

	while (i < 3)
	{
		printf("thread name: %s, tid: %x\n", thread_name, (unsigned int)tid);
		i++;
		usleep(1000 * 1000);
	}
}