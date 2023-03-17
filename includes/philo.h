/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eminatch <eminatch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:17:50 by eminatch          #+#    #+#             */
/*   Updated: 2023/03/17 20:18:06 by eminatch         ###   ########.fr       */
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

# define NC	"\e[0m"
# define YELLOW	"\e[33m"
# define BYELLOW	"\e[1;33m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"

/* ERROR MESSAGES */

# define ERROR_MSG "Error:\n"
# define ERROR_AC "Invalid number of arguments\n"
# define ERROR_AV_DIGIT "Invalid digit\n"
# define ERROR_NO_PHILO "No philosopher sitting at the table\n"
# define ERROR_TIME "Invalid timezone\n"
# define ERROR_MUTEX "Could not initialize mutexes.\n"
# define ERROR_TH "Could not initialize threads\n"
# define ERROR_TIME_MS "Could not get time in miliseconds\n"
# define ERROR_PHILO_TABLE "Could not initialize philo_list\n"

/* MESSAGES */

# define FORK "Has taken a fork\n"
# define EAT "Is eating\n"
# define SLEEP "Is sleeping\n"
# define THINK "Is thinking\n"
# define DEATH "died\n"
# define EAT_COUNT " meals for each philosophers\n"

/* STRUCTURES */

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	bool			dead;
	int				time_to_die;
	pthread_mutex_t	*right_fork;
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
	time_t			time_of_day;
	int				time_ms;
	int				nb_meal;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	pthread_t		monitor;
	pthread_mutex_t	*time_keeper;
}				t_table;

/* MAIN */
int		main(int ac, char **av);

/* PHILO_UTILS */
void	ft_write_msg(char *s);

/* CONDITIONS */
t_philo	*fill_table(int ac, char **av, t_philo *philo);
int		ft_atoi_philo(const char *s, int *flag);
void	ft_atoi_philo_bis(const char *s, int *flag, int *j, int *nb);
bool	is_nb(char *av);
bool	is_sign(char c);
bool	is_digit(char c);
bool	ft_check_conditions(char **av);

/* TABLE */
t_philo	*ft_init_philo(t_table *table);
void	philo_list(t_philo *philo, int id);
bool	table_list(t_table *table);

/* ROUTINE */
bool	philosophers_start_routine(t_table *table);
void	philosophers_end_routine(t_table *table);
void	*philosophers_routine(void *param);
time_t	today_is_ms(int time_ms);

/* ROUTINE UTILS */
void	join_threads(t_table *table);
bool	is_dead(t_philo *philo);
void	kill_philos(t_table *table);
bool	check_meals(t_philo *philo);
void	*ft_monitoring(void *param);

/* ERRORS */
void	ft_error(char *s);
void	ft_free_philo(t_table *table);
char	**ft_free(char **str);

#endif
