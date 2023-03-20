/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:17:50 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/20 16:39:01 by eminatch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PHILO_H
# define PHILO_H

/* LIBS */

# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <stdbool.h>

/* COLORS */

# define CYAN		"\e[36m"
# define YELLOW		"\e[33m"
# define RED		"\e[31m"
# define GREEN		"\e[32m"
# define BLUE 		"\e[34m"
# define PINK		"\e[38;5;206m"
# define RESET 		"\e[0m"

/* ERROR MESSAGES */

# define ERROR_MSG "Error:\n"
# define ERROR_ZERO "Values must be higher than 0\n"
# define ERROR_MAX "Values out of int max range\n"
# define ERROR_AC "Invalid number of arguments\n"
# define ERROR_DIGIT "Invalid digit\n"
# define ERROR_PHILO "No philosopher sitting at the table\n"
# define ERROR_TIME "Invalid timezone\n"
# define ERROR_MUTEX "Could not initialize mutexes.\n"
# define ERROR_TH "Could not initialize threads\n"
# define ERROR_TIME_MS "Could not get time in ms\n"
# define ERROR_PHILO_TABLE "Could not initialize philo_list\n"

/* MESSAGES */

# define DEATH "died\n"
# define EAT_COUNT " meals for each philosophers\n"

/* STRUCTURES */

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	bool			dead;
	long int		last_meal;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t		th;
	struct s_philo	*prev;
	struct s_philo	*next;
	t_table			*table;

}				t_philo;			

typedef struct s_table
{
	t_philo			*start;
	t_philo			*philo;
	int				nb_philo;
	long int		time;
	int				nb_meal;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	pthread_t		monitor;
	pthread_mutex_t	time_keeper;
	pthread_mutex_t	print_keeper;
}				t_table;

/* STATUS */

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	FORK = 4,
}	t_status;

/* MAIN */
bool		check_philo_and_forks(t_table *table);
int			main(int ac, char **av);

/* CONDITIONS */
bool		check_table(int ac, char **av, t_table *table);
int			ft_atoi_philo(const char *s, int *flag);
void		ft_atoi_philo_bis(const char *s, int *flag, int *j, int *nb);
bool		check_values(t_table *table);
void		*one_philo(t_philo *philo);

/* CONDITION UTILS */
bool		is_nb(char *av);
bool		is_sign(char c);
bool		is_digit(char c);
bool		ft_check_conditions(char **av);

/* TABLE */
t_philo		*ft_init_philo(t_table *table);
void		philo_list(t_philo *philo, int id);
bool		fill_table_list(t_table *table);
bool		init_fork(t_table *table);

/* ROUTINE */
bool		philosophers_start_routine(t_table *table);
void		philosophers_end_routine(t_table *table);
void		*philosophers_routine(void *param);
void		philo_cycle(t_philo *philo);
long int	get_time(void);

/* ROUTINE UTILS */
void		join_threads(t_table *table);
bool		is_dead(t_philo *philo);
void		kill_philos(t_table *table);
bool		check_meals(t_philo *philo);
void		*ft_monitoring(void *param);

/* ERRORS */
void		ft_error(char *s);
void		ft_free_philo(t_table *table);
void		ft_print_status(t_philo *philo, char *c, char *str);
void		ft_write_msg(t_philo *philo, t_status status);

#endif
