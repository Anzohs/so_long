/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamestate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:13:39 by hladeiro          #+#    #+#             */
/*   Updated: 2024/06/07 21:30:20 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	*render_m(t_machine *m)
{
	m->current.render();
	return (NULL);
}

void	create_states(t_machine *m)
{
	t_states	s;
	t_start	start;

	s.c = 's';
	start.img = "background.xpm";
	s.start = start;
	//create play(&s);
	//create start(&s);
	m->states = s;
}

void	*update_m(t_machine *m, float dt)
{
	m->current.update(&(m->current), dt);
	return (NULL);
}

void	*change_current(t_machine *m)
{
	if (m->states.c == 's')
		m->current = m->states.start.funct;
	if (m->states.c == 'p')
		m->current = m->states.play.funct;
	return (NULL);
}

void	create_gamestate(t_data *data)
{
	t_machine	m;

	create_states(&m);
	m.change = change_current;
	m.update = update_m;
	m.render = render_m;
	data->m = m;
}
