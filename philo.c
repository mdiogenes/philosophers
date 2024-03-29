/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:40:31 by msoler-e          #+#    #+#             */
/*   Updated: 2022/12/13 10:25:22 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_act(t_list *node, t_philo *philo, t_philo *next)
{
	pthread_mutex_lock(&philo->fork_lock);
	timestamp(node, PHILO_TAKE_FORK, 0);
	pthread_mutex_lock(&next->fork_lock);
	timestamp(node, PHILO_TAKE_FORK, 0);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_time() - philo->data->i_time;
	pthread_mutex_unlock(&philo->last_meal_lock);
	timestamp(node, PHILO_EAT, philo->data->eat_time);
	timestamp(node, PHILO_SLEEP, 0);
	pthread_mutex_unlock(&next->fork_lock);
	pthread_mutex_unlock(&philo->fork_lock);
	ft_usleep(philo->data->sleep_time);
	timestamp(node, PHILO_THINK, 0);
}

void	*start_thread(void *node)
{
	t_philo		*philo;
	t_philo		*next;
	int			i;

	i = -1;
	philo = ((struct s_list *)node)->content;
	next = ((struct s_list *)node)->next->content;
	ft_usleep(!(philo->id % 2) * 20);
	pthread_mutex_lock(&philo->data->died_lock);
	while (philo->id != next->id && !philo->data->died && \
		(philo->data->repeat_count == -2 || ++i < philo->data->repeat_count))
	{
		pthread_mutex_unlock(&philo->data->died_lock);
		philo_act(node, philo, next);
		pthread_mutex_lock(&philo->data->died_lock);
	}
	pthread_mutex_unlock(&philo->data->died_lock);
	return (NULL);
}

void	*monitor(t_list *start, t_philo *philo)
{
	long	eat_c;
	long	last_meal;

	while (1)
	{
		philo = start->content;
		pthread_mutex_lock(&philo->data->eat_count_lock);
		eat_c = philo->data->eat_count;
		pthread_mutex_unlock(&philo->data->eat_count_lock);
		pthread_mutex_lock(&philo->last_meal_lock);
		last_meal = philo->last_meal;
		pthread_mutex_unlock(&philo->last_meal_lock);
		if (get_time() - philo->data->i_time - last_meal >= \
			philo->data->die_time)
		{
			pthread_mutex_lock(&philo->data->died_lock);
			philo->data->died = 1;
			pthread_mutex_unlock(&philo->data->died_lock);
			if (eat_c != philo->data->philo_count * philo->data->repeat_count)
				timestamp(start, PHILO_DIE, 0);
			return (NULL);
		}
		start = start->next;
	}
}

void	*philo_init(int philo_count, t_list *philos)
{
	int		i;
	t_list	*start;
	t_philo	*philo;

	i = -1;
	start = philos;
	while (++i < philo_count)
	{
		philo = start->content;
		if (pthread_create(&philo->thread_id, NULL, start_thread, start))
			return (ft_exit(philos, NULL, THREAD_FAILED));
		start = start->next;
	}
	monitor(start, NULL);
	i = -1;
	while (++i < philo_count)
	{
		philo = start->content;
		pthread_join(philo->thread_id, NULL);
		start = start->next;
	}
	return (NULL);
}
