/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:14:45 by hladeiro          #+#    #+#             */
/*   Updated: 2024/06/04 13:11:59y hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void load_wall(t_data *data)
{
	int x = 0;
	int y = 0;
	while (x <= WINDOW_WIDTH && y <= WINDOW_HEIGHT)
	{
		if (x == 0 || y == 0)
			mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->wall, x, y);
		if ((x > 0 && y > 0) && (x < WINDOW_WIDTH - 16 && y < WINDOW_HEIGHT - 16))
			mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->ground, x, y);
		if (x >= WINDOW_WIDTH - 16 || y >= WINDOW_HEIGHT - 16)
			mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->wall, x, y);
		x += 16;
		if (x >= WINDOW_WIDTH && y <= WINDOW_HEIGHT)
		{
			x = 0;
			y += 16;
		}
	}
}

int load_game(t_data *data){
	static int i;
	//mlx_clear_window(data->mlx_ptr, data->window_ptr);
	if (data->m.states.c == 's')
	{
		//mlx_clear_window(data->mlx_ptr, data->window_ptr);
		data->delta += mlx_do_sync(data->mlx_ptr);
		mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->img, data->x, data->y);
		mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->img, data->x1, data->y1);
		mlx_string_put(data->mlx_ptr, data->window_ptr, WINDOW_WIDTH/ 2, WINDOW_HEIGHT / 2, 0xFFFFFF, "Press Enter To Start");
	}
	if (data->m.states.c == 'p')
	{
		if (!i)
		{
			mlx_do_sync(data->mlx_ptr);
			load_wall(data);
			mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->p_p, data->player.x, data->player.y);
			i++;
		}
		else 
		{
			data->delta += mlx_do_sync(data->mlx_ptr);
			//mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->)
			mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->ground, data->player.x, data->player.y);
			//load_wall(data);
			mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->p_p, data->player.x, data->player.y);
			data->delta = 0;
		}
			data->delta += mlx_do_sync(data->mlx_ptr);

	}

	//mlx_do_sync(data->mlx_ptr);
	//printf("%s", mlx_get_data_addr(data->player->image, data->player->x, data->player->y, 0));
	return 1;
}

int	render_next_frame(t_data *data)
{
	//we clear the window everytime we need to
	/*
	if (data->player->current_frameframes && data->frames > 10000)
	{
		data->player->current_frameframes = 0;
		mlx_destroy_image(data->mlx_ptr,data->player->image);
		data->player->image = mlx_xpm_file_to_image(data->mlx_ptr, check_data_dir(data), &x, &y);
		data->frames = 0;
	}
	 if (data->frames > 10000) {
		data->player->current_frameframes += 1;
		//mlx_destroy_image(data->mlx_ptr, data->player->image);
		mlx_destroy_image(data->mlx_ptr,data->player->image);
		data->player->image = mlx_xpm_file_to_image(data->mlx_ptr, check_data_dir(data), 
			&x, &y);
		data->frames = 0;
	}*/
	//write(1, &data->m.states.c ,1);
	if (data->x <= -1260)
		data->x = 1260;
	if (data->x1 <= -1260)
		data->x1 = 1260;
	if (data->delta >= 150)
	{
		data->x--;
		data->x1--;
		data->delta = 0;
	}
	load_game(data);
	return 1;
}


int	handle_input(int keysym, t_data *data)
{
	if (keysym == 0xff1b)
	{
		mlx_destroy_window(data->mlx_ptr, data->window_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	if (data->m.states.c == 'p')
	{
		write(1, "aqui\n", 5);
		if ((keysym == XK_d || keysym ==  XK_D))
			data->player.x+= 1;
		if ((keysym == XK_a || keysym == XK_A))
			data->player.x-= 1;
		if ((keysym == XK_s || keysym == XK_S))
			data->player.y+= 1;
		if ((keysym == XK_W || keysym == XK_w))
			data->player.y-= 1;
	}
	if (keysym == 0xff0d && data->m.states.c == 's')
	{
		//mlx_destroy_image(data->mlx_ptr, data->img);
		data->m.states.c = 'p';
		mlx_clear_window(data->mlx_ptr, data->window_ptr);
		load_game(data);
		//data->m.change(&data->m);
	}
	return (0);
}

void	create_player(t_data *d)
{
	t_player p;

	p.image = "player.xpm";
	p.x = 16;
	p.y = 32;
	p.width = 16;
	p.height = 32;
	d->player = p;
}

int	main(void)
{
	//this struct handles the screen of our library!
	t_data	data;	
	data.mlx_ptr = mlx_init();
	data.delta = 0;
	data.x = 0;
	data.y = 0;
	data.x1 = 1260;
	data.y1 = 0;
	create_player(&data);
	create_gamestate(&data);
	if (!data.mlx_ptr)
		return (1);

	//to create a window wee need the initiation of mlx, width, height
	//and the title of the screen!
	data.window_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My window");
	//we need to destroy the display since the function init allocs memory
	if (!data.window_ptr)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}


	//load the images on the current games
	data.img = mlx_xpm_file_to_image(data.mlx_ptr, data.m.states.start.img, &data.x, &data.y);
	data.x = 0;
	data.y = 0;
	data.wall = mlx_xpm_file_to_image(data.mlx_ptr, "tiles.xpm", &data.x, &data.y);
	data.ground = mlx_xpm_file_to_image(data.mlx_ptr, "groun.xpm", &data.x, &data.y);
	data.y += 16;
	data.p_p = mlx_xpm_file_to_image(data.mlx_ptr, data.player.image, &data.x, &data.y);
	data.x = 0;
	data.y = 0;
	//put the images on the current screen!v
	load_game(&data);
	//function to handle keyboard input!
	//mlx_hook(data.window_ptr, 3, KeyReleaseMask, &handle_input, &data);
	mlx_hook(data.window_ptr, 2, KeyPressMask, &handle_input, &data);
	//we pass the window, the function and the param of the function!
	mlx_loop_hook(data.mlx_ptr, render_next_frame, &data);
	//another way to deal with pressing in the keyboards
	//loop so the visual connection continue to run
	mlx_loop(data.mlx_ptr);
}


//compile:
//	cc main.c -Lminilibx-linux minilibx-linux/libmlx.a -lX11 -lXext

