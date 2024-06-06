/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:13:26 by hladeiro          #+#    #+#             */
/*   Updated: 2024/06/07 00:24:44 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H 

#include ".minilibx-linux/mlx.h"
//#include ".minilibx-linux/mlx_int.h"
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
//library from keys
#include <X11/keysym.h>
#include "statemachine.h"
#include <unistd.h>

#define WINDOW_WIDTH    1280 
#define WINDOW_HEIGHT	720


typedef struct s_player
{
    int	x;
    int	y;
    int width;
    int height;
    void	*image;
	int	current_frameframes;
	char	dir;
}	t_player;

#endif