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

int load_game(t_data *data){
	//mlx_clear_window(data->mlx_ptr, data->window_ptr);
	if (data->m.states.c == 's')
	{
		//mlx_clear_window(data->mlx_ptr, data->window_ptr);
		data->delta += mlx_do_sync(data->mlx_ptr);
		mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->img, data->x, data->y);
		mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->img, data->x1, data->y1);
		mlx_string_put(data->mlx_ptr, data->window_ptr, WINDOW_WIDTH/ 2, WINDOW_HEIGHT / 2, 0xFFFFFF, "Press Enter To Start");
	}
	if (data->m.states.c == 'p' && data->img)
		mlx_clear_window(data->mlx_ptr, data->window_ptr);
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
	if (keysym == 0xff0d && data->m.states.c == 's')
	{
		//mlx_destroy_image(data->mlx_ptr, data->img);
		data->m.states.c = 'p';
		load_game(data);
		//data->m.change(&data->m);
	}
	//if (keysym == XK_d || keysym ==  XK_D)
	/*{
		data->player->x+= 1;
		data->player->dir = 'd';
	}
	if (keysym == XK_a || keysym == XK_A)
	{
		data->player->x-= 1;
		data->player->dir = 'a';
	}
	if (keysym == XK_s || keysym == XK_S)
	{
		data->player->y+= 1;
		data->player->dir = 's';
	}
	if (keysym == XK_W || keysym == XK_w)
	{
		data->player->y-= 1;
		data->player->dir = 'w';
	}
	else
	{
		data->player->dir = 0;
		return (0);
	}
	*/
	return (0);
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
	//put the images on the current screen!v
	load_game(&data);
	//function to handle keyboard input!
	//mlx_hook(data.window_ptr, KeyRelease, KeyReleaseMask, &handle_input, &data);
	mlx_hook(data.window_ptr, KeyPress, KeyPressMask, &handle_input, &data);
	//we pass the window, the function and the param of the function!
	mlx_loop_hook(data.mlx_ptr, render_next_frame, &data);
	//another way to deal with pressing in the keyboards
	//loop so the visual connection continue to run
	mlx_loop(data.mlx_ptr);
}


//compile:
//	cc main.c -Lminilibx-linux minilibx-linux/libmlx.a -lX11 -lXext

