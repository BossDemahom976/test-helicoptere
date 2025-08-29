/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homohame <homohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:12:10 by homohame          #+#    #+#             */
/*   Updated: 2025/08/11 13:56:33 by homohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 900
# define HEIGHT 600
# define BLOCK 12

# define MAP 1

# define PI 3.14159265359

# include "./minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_player
{
	double	px;
	double	py;

	double	dir_x;
	double	dir_y;
	
	double	old_dir_x;
	double	old_dir_y;
	
	double	plane_x;
	double	plane_y;

	double	old_plane_x;
	double	old_plane_y;
	
	double	angle;

	int		key_w;
	int		key_s;
	int		key_a;
	int		key_d;

	int		key_larrow;
	int		key_rarrow;
}	t_player;

typedef struct s_data
{
	char	*mlx_data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_data;

typedef struct s_texture
{
	int		width;
	int		height;
	void	*ptr;
	t_data	data;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	void		*mlx_img;

	char		**map;

	t_data		data;

	t_player	player;

	t_texture	n_wall;
	t_texture	s_wall;
	t_texture	e_wall;
	t_texture	w_wall;

}	t_game;

typedef struct s_square
{
	int	x;
	int	y;
	int	size;
}	t_square;

typedef struct s_ray
{
	int			map_x;
	int			map_y;

	double		dir_x;
	double		dir_y;

	double		camera_x;

	double		s_dist_x;
	double		s_dist_y;

	double		d_dist_x;
	double		d_dist_y;

	int			step_x;
	int			step_y;

	int			line_height;

	double		perp_wall_dist;

	int			color;

	int			draw_start;
	int			draw_end;

	t_texture	*texture;
	int			tex_x;

	int			side;
}	t_ray;

//cub3d_pixel_put.c
void	put_pixel(t_game *game, int x, int y, int color);
void	draw_square(t_game *game, t_square *square, int color);
int		draw_loop(t_game *game);
void	clear_image(t_game *game);

//cub3d_pixel_put2.c
//int	touch_wall(t_game *game, t_ray *ray);
//void	draw_line(t_game *game, float ray_start, int i);
void	draw_line3d(t_game *game, t_ray *ray, int i);

//free_cub3d.c
int		close_window(t_game *game);
void	free_all(t_game *game);

//cub3d_init.c
void	init_game(t_game *game);
void	init_textures(t_game *game);

//void	init_player(t_player *player);
void	init_player(t_player *player, char **map);

//cubd3d_player_move.c
int		key_press(int key_code, t_game *game);
int		key_release(int key_code, t_player *player);
void	move_player(t_game *game);
void	draw_player(t_game *game);

#endif