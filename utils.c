/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:42:13 by msoler-e          #+#    #+#             */
/*   Updated: 2022/09/30 11:45:48 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_get_data(t_philo_data *d, int i)
{
	t_philo	*node;

	node = malloc(sizeof(struct s_philo));
	if (!node)
		return (ft_exit(NULL, NULL, THREAD_FAILED));
	node->id = i + 1;
	node->thread_id = 0;
	pthread_mutex_init(&node->fork_lock, NULL);
	pthread_mutex_init(&node->last_meal_lock, NULL);
	node->data = d;
	node->last_meal = 0;
	return (node);
}

t_list	*philo_lst(t_philo_data *d)
{
	int		i;
	t_list	*philos;

	i = -1;
	philos = NULL;
	while (++i < d->philo_count)
		ft_lstadd_back(&philos, ft_lstnew(philo_get_data(d, i)));
	return (philos);
}

int	ft_error(char *param, t_philo_err err_code)
{
	ft_putstr_fd("philo: ", 2);
	if (err_code == INV_ARGS)
		ft_putstr_fd("Error_number_arguments", 2);
	if (err_code == NO_MEMORY)
		ft_putstr_fd("no memory", 2);
	if (err_code == THREAD_FAILED)
		ft_putstr_fd("ERROR_create_thread", 2);
	if (err_code == INV_PHILO)
		ft_putstr_fd("ERROR_philosopher_count: ", 2);
	if (err_code == INV_DIE)
		ft_putstr_fd("ERROR_time_to_die: ", 2);
	if (err_code == INV_EAT)
		ft_putstr_fd("ERROR_time_to_eat: ", 2);
	if (err_code == INV_SLEEP)
		ft_putstr_fd("ERROR_time_to_sleep: ", 2);
	if (err_code == INV_REPEAT)
		ft_putstr_fd("ERROR_repeat_times: ", 2);
	if (err_code == MAX_PHILO)
		ft_putstr_fd("TOO_much_philosophers ", 2);
	if (param && err_code != INV_ARGS && err_code != NO_MEMORY && \
			err_code != THREAD_FAILED)
		ft_putstr_fd(param, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	timestamp(t_list *philos, char *action, useconds_t t)
{
	useconds_t	time;
	t_philo		*philo;
	int			died;
	int			eat_count;

	philo = philos->content;
	pthread_mutex_lock(&philo->data->died_lock);
	died = philo->data->died;
	pthread_mutex_lock(&philo->data->eat_count_lock);
	eat_count = philo->data->eat_count;
	time = get_time() - philo->data->i_time;
	if (philo->data->repeat_count * philo->data->philo_count != \
			eat_count && (!died || action[7] == 'd'))
	{
		printf("[\033[1;39m%06u\033[0;39m]  \033[1;96m%03d  \033[0;39m%s\n", \
				time, philo->id, action);
	}
	if (action[11] == 'e')
		philo->data->eat_count++;
	pthread_mutex_unlock(&philo->data->eat_count_lock);
	pthread_mutex_unlock(&philo->data->died_lock);
	if (philo->data->repeat_count * philo->data->philo_count != \
			eat_count && (!died || action[7] == 'd'))
		ft_usleep(t);
}

void	*ft_exit(t_list *philos, char *param, t_philo_err err_code)
{
	t_philo	*philo;
	t_list	*temp;

	temp = philos;
	if (err_code != END)
		ft_error(param, err_code);
	while (philos)
	{
		philo = philos->content;
		if (philo->id == philo->data->philo_count)
			philos->next = NULL;
		philos = philos->next;
	}
	ft_lstclear(&temp, free);
	return (NULL);
}
