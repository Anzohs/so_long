/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:14:45 by hladeiro          #+#    #+#             */
/*   Updated: 2024/05/31 21:46:56 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	render_next_frame(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->image, data->x, data->y);
}


int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->window_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	if (keysym == XK_d || keysym ==  XK_D)
		data->x+= 1;
	if (keysym == XK_a || keysym == XK_A)
		data->x-= 1;
	if (keysym == XK_s || keysym == XK_S)
		data->y+= 1;
	if (keysym == XK_W || keysym == XK_w)
		data->y-= 1;
	return (0);
}

int	main(void)
{
	//this struct handles the screen of our library!
	t_data	data;	
	int	c = 32;
	data.x = 200;
	data.y = 200;
	data.mlx_ptr = mlx_init();
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


	//load the images on the current game
	data.image = mlx_xpm_file_to_image(data.mlx_ptr, "img.xpm", &c, &c);
	//put the images on the current screen!
	mlx_put_image_to_window(data.mlx_ptr, data.window_ptr, data.image, 200, 200);
	//function to handle keyboard input!
	mlx_hook(data.window_ptr, KeyRelease, KeyReleaseMask, &handle_input, &data);
	mlx_hook(data.window_ptr, KeyPress, KeyPressMask, &handle_input, &data);
	//we pass the window, the function and the param of the function!
	mlx_loop_hook(data.mlx_ptr, render_next_frame, &data);
	//another way to deal with pressing in the keyboards
	//loop so the visual connection continue to run
	mlx_loop(data.mlx_ptr);
}


//compile:
//	cc main.c -Lminilibx-linux minilibx-linux/libmlx.a -lX11 -lXext

