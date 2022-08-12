/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:18:00 by msoler-e          #+#    #+#             */
/*   Updated: 2022/08/04 11:49:10 by msoler-e         ###   ########.fr       */
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

# define PHILO_EAT "\033[1;93mis eating 🍝\033[0;39m"
# define PHILO_SLEEP "\033[1;95mis sleeping 🌙\033[0;39m"
# define PHILO_THINK "\033[1;90mis thinking 💭\033[0;39m"
# define PHILO_TAKE_FORK "\033[1;94mhas taken a fork 🍴\033[0;39m"
# define PHILO_DIE "\033[1;91mdied 💀\033[0;39m"

/* Enum to handle errors in philosophers */
typedef enum e_philo_err
{
	END = 1,
	INV_ARGS = -1,
	TOO_MANY_PHILO = -2,
	INV_PHILO_COUNT = -3,
	INV_DIE_TIME = -4,
	INV_EAT_TIME = -5,
	INV_SLEEP_TIME = -6,
	INV_REPEAT_COUNT = -7,
	NO_MEMORY = -8,
	THREAD_FAILED = -9
}			t_philo_err;

/* Struct to store all data */
typedef struct s_philo_data
{
	int				philo_count;
	useconds_t		init_time;
	long			repeat_count;
	long long		die_time;
	long long		eat_time;
	long long		sleep_time;
	long			eat_count;
	pthread_mutex_t	eat_count_lock;
	int				died;
	pthread_mutex_t	died_lock;
}					t_philo_data;

/* Struct to handle info for every philosopher */
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

/* Prints error message with custom param given an error code */
int			philo_perror(char *param, t_philo_err err_code);

/* Prints error message and exits freeing everything */
void		*philo_exit(t_list *philos, char *param, t_philo_err err_code);

/* Personal & more precise implementation of the usleep function */
int			ft_usleep(useconds_t usec);

/* Returns current time in miliseconds */
useconds_t	philo_get_time(void);

/* Fills an array with the default info for every philosopher */
t_list		*philo_lst(t_philo_data *d);

/* Creates threads for every philosopher */
void		*philo_init(int philo_count, t_list *philos);

/* Prints current state of a philosopher if applicable */
void		philo_timestamp(t_list *philos, char *action, useconds_t t);
/* Returns length of string */
size_t		ft_strlen(const char *s);

/* Prints string with write */
int			ft_putstr_fd(char *s, int fd);

/* Returns 1 if a char is of a space form: space, tab, etc */
int			ft_isspace(char c);

/* Returns 1 if c is a number in the ASCII table */
int			ft_isdigit(int c);

/* Returns equivalent int from a string, or -1 */
long long	ft_atoi(const char *nptr);

/* Writes char to given fd */
int			ft_putchar_fd(char c, int fd);

/* Writes unsigned long number to given fd */
int			ft_putnbr_fd(long unsigned n, int fd);

/* Frees a char ** accordingly */
void		ft_free_matrix(char ***m);

/* Writes n chars sequentially */
int			ft_putnchar_fd(char c, int fd, int n);

/* Returns length of a number in a given base */
int			ft_nbrlen(long n, int base);

/* Adds a node at the end of a list */
void		ft_lstadd_back(t_list **lst, t_list *newnode);

/* Creates new node */
t_list		*ft_lstnew(void *content);

/* Returns last node of linked list */
t_list		*ft_lstlast(t_list *lst);

/* Deletes every node of linked list */
void		ft_lstclear(t_list **lst, void (*del)(void*));

/* Deletes one node in a linked list */
void		ft_lstdelone(t_list *lst, void (*del)(void*));


#endif
