/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:13:26 by hladeiro          #+#    #+#             */
/*   Updated: 2024/05/31 21:45:14 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H 

#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
//library from keys
#include <X11/keysym.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT   1200 

typedef struct s_rect
{
    int	x;
    int	y;
    int width;
    int height;
    int color;
}	t_rect;


typedef struct s_data
{
    void	*mlx_ptr;
    void	*window_ptr;
    void    *texctures[5]; //trying out with images
    void    *image;
    float     y;
    float     x;
    //t_map   *map;     this will be map in the future to run our game!
}		t_data;


#endif
