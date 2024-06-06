/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statemachine.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:49:38 by hladeiro          #+#    #+#             */
/*   Updated: 2024/06/06 23:07:57 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATEMACHINE_H
# define STATEMACHINE_H

typedef struct s_fun
{
	void	*(*update)(struct s_fun *, float);
	void	*(*render)();
	void	*(*enter)();
	void	*(*exit)();
}		t_fun;

typedef struct s_play
{
	void	*(*init)();
	t_fun	funct;
	//add the struct of the player
}		t_play;

typedef struct s_start
{
	void	*(*init)();
	void	*img;
	t_fun	funct;
	//add the image of the screen
	/* data */
}		t_start;

typedef struct s_states
{
	t_start	start;
	t_play	play;
	char	c;
}		t_states;

typedef struct s_machine
{
	t_states	states;
	void		*(*render)(struct s_machine *);
	void		*(*change)(struct s_machine *);
	void		*(*update)(struct s_machine *, float);
	t_fun		current;
}				t_machine;

typedef struct s_data
{
    void	*mlx_ptr;
    void	*window_ptr;
	void	*img;
	void	*img2;
	int	x;
	int	y;
	int	x1;
	int	y1;
	int	delta;
	t_machine	m;
    //t_map   *map;     this will be map in the future to run our game!
}		t_data;

void	create_gamestate(t_data *data);
void	create_states(t_machine *m);
void	*update_m(t_machine *m, float dt);
void	*change_current(t_machine *m);
void	*render_m(t_machine *m);


#endif
