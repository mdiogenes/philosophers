/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:18:00 by msoler-e          #+#    #+#             */
/*   Updated: 2022/11/25 12:58:42 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <sys/param.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>

# define PHILO_EAT "\033[1;93m is eating \033[0;39m"
# define PHILO_SLEEP "\033[1;95m is sleeping \033[0;39m"
# define PHILO_THINK "\033[1;90m is thinking \033[0;39m"
# define PHILO_TAKE_FORK "\033[1;94m has taken a fork \033[0;39m"
# define PHILO_DIE "\033[1;91mdied \033[0;39m"

typedef enum e_philo_err
{
	END = 1,
	INV_ARGS = -1,
	MAX_PHILO = -2,
	INV_PHILO = -3,
	INV_DIE = -4,
	INV_EAT = -5,
	INV_SLEEP = -6,
	INV_REPEAT = -7,
	NO_MEMORY = -8,
	THREAD_FAILED = -9
}			t_philo_err;

typedef struct s_philo_data
{
	int				philo_count;
	useconds_t		i_time;
	long			repeat_count;
	long long		die_time;
	long long		eat_time;
	long long		sleep_time;
	long			eat_count;
	pthread_mutex_t	eat_count_lock;
	int				died;
	pthread_mutex_t	died_lock;
}					t_philo_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	pthread_mutex_t		fork_lock;
	useconds_t			last_meal;
	pthread_mutex_t		last_meal_lock;
	struct s_philo_data	*data;
}						t_philo;
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int			ft_error(char *param, t_philo_err err_code);
void		*ft_exit(t_list *philos, char *param, t_philo_err err_code);
int			ft_usleep(useconds_t usec);
useconds_t	get_time(void);
t_list		*philo_lst(t_philo_data *d);
void		*philo_init(int philo_count, t_list *philos);
void		timestamp(t_list *philos, char *action, useconds_t t);
size_t		ft_strlen(const char *s);
int			ft_putstr_fd(char *s, int fd);
int			ft_isspace(char c);
int			ft_isdigit(int c);
long long	ft_atoi(const char *nptr);
int			ft_putchar_fd(char c, int fd);
int			ft_putnbr_fd(long unsigned n, int fd);
void		ft_free_matrix(char ***m);
int			ft_putnchar_fd(char c, int fd, int n);
int			ft_nbrlen(long n, int base);
void		ft_lstadd_back(t_list **lst, t_list *newnode);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void*));

#endif
