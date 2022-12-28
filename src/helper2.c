#include "../philo.h"

int	clock_started(t_philos *ph)
{
	pthread_mutex_lock(&ph->m_dead_clock);
	if (ph->death_clock)
	{
		//ft_printf("phil %d timeleft %ld\n", ph->id, ph->death_clock - get_time());
		pthread_mutex_unlock(&ph->m_dead_clock);
		return (1);
	}
	pthread_mutex_unlock(&ph->m_dead_clock);
	return (0);
}

int	update_clock(t_philos *ph)
{
	pthread_mutex_lock(&ph->m_dead_clock);
	ph->death_clock = get_time() + ph->data->time_to_die;
	// ft_printf("phil %d clock updated og set %ld\n", ph->id, ph->death_clock);
	pthread_mutex_unlock(&ph->m_dead_clock);
	return (0);
}

int	update_eating(t_philos *ph, int eat_food)
{
	pthread_mutex_lock(&ph->m_eating);
	if (eat_food)
	{
		ph->is_eating = 1;
		pthread_mutex_unlock(&ph->m_eating);
		return (0);
	}
	else
	{
		ph->eat_count--;
		if (!ph->eat_count)
		{
			ph->is_eating = 0;
			pthread_mutex_unlock(&ph->m_eating);
			pthread_mutex_lock(&ph->data->m_living);
			ph->data->philo_living--;
			ft_printf("living count %d\n", ph->data->philo_living);
			pthread_mutex_unlock(&ph->data->m_living);
			return (1);
		}
		ph->is_eating = 0;
		pthread_mutex_unlock(&ph->m_eating);
	}
	return (0);
}

int	time_ran_out(t_philos ph)
{
	pthread_mutex_lock(&ph.m_dead_clock);
	pthread_mutex_lock(&ph.m_eating);
	if (!ph.is_eating && (ph.death_clock < get_time()))
	{
		//ft_printf("time ran out\n");
		pthread_mutex_unlock(&ph.m_dead_clock);
		pthread_mutex_unlock(&ph.m_eating);
		return (1);
	}
	pthread_mutex_unlock(&ph.m_dead_clock);
	pthread_mutex_unlock(&ph.m_eating);
	return (0);
}
