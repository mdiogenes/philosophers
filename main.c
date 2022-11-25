/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:46:26 by msoler-e          #+#    #+#             */
/*   Updated: 2022/11/25 12:48:25 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo_data	parse(char **argv)
{
	t_philo_data	d;

	d.philo_count = ft_atoi(argv[1]);
	if (d.philo_count <= 0)
		ft_exit(NULL, argv[1], INV_PHILO);
	if (d.philo_count > 800)
		ft_exit(NULL, argv[1], MAX_PHILO);
	d.die_time = ft_atoi(argv[2]);
	if (d.die_time == -1)
		ft_exit(NULL, argv[2], INV_DIE);
	d.eat_time = ft_atoi(argv[3]);
	if (d.eat_time == -1)
		ft_exit(NULL, argv[3], INV_EAT);
	d.sleep_time = ft_atoi(argv[4]);
	if (d.sleep_time == -1)
		ft_exit(NULL, argv[4], INV_SLEEP);
	d.repeat_count = -2;
	if (argv[5])
	{
		d.repeat_count = ft_atoi(argv[5]);
		if (d.repeat_count == -1 || !d.repeat_count)
			ft_exit(NULL, argv[5], INV_REPEAT);
	}
	return (d);
}

int	main(int argc, char **argv)
{
	t_philo_data	d;
	t_list			*philos;

	if (argc != 5 && argc != 6)
	{
		ft_exit(NULL, NULL, INV_ARGS);
		printf("\nInstructions: Number of philosophers <philo_count>");
		printf("\n<die_time><eat_time><sleep_time> [<repeat_times>]");
		return (1);
	}
	d = parse(argv);
	if (d.philo_count <= 0 || d.philo_count > 800 || d.die_time == -1 || \
		d.eat_time == -1 || d.sleep_time == -1 || d.repeat_count == -1 || \
		!d.repeat_count)
		return (1);
	d.i_time = get_time();
	d.died = 0;
	d.eat_count = 0;
	pthread_mutex_init(&d.died_lock, NULL);
	pthread_mutex_init(&d.eat_count_lock, NULL);
	philos = philo_lst(&d);
	ft_lstlast(philos)->next = philos;
	philo_init(d.philo_count, philos);
	ft_exit(philos, NULL, END);
	return (0);
}
