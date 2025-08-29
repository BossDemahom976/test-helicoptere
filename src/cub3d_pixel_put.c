/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_pixel_put.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homohame <homohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:11:00 by homohame          #+#    #+#             */
/*   Updated: 2025/08/21 11:12:12 by homohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*offset;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	offset = game->data.mlx_data
		+ y * game->data.size_line
		+ x * (game->data.bpp / 8);
	*(unsigned int *)offset = color;
}

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game, x, y, 0);
			++x;
		}
		++y;
	}
}

void	draw_square(t_game *game, t_square *square, int color)
{
	int	i;

	i = -1;
	while (++i < square->size)
		put_pixel(game, i + square->x, square->y, color);
	i = -1;
	while (++i < square->size)
		put_pixel(game, square->x, i + square->y, color);
	i = -1;
	while (++i < square->size)
		put_pixel(game, square->x + square->size, i + square->y, color);
	i = -1;
	while (++i < square->size + 1)
		put_pixel(game, i + square->x, square->size + square->y, color);
}

void	draw_map(t_game *game)
{
	char		**map;
	int			x;
	int			y;
	t_square	square;

	map = game->map;
	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				square.size = BLOCK;
				square.x = x * BLOCK;
				square.y = y * BLOCK;
				draw_square(game, &square, 0xFFD700);
			}
			++x;
		}
		++y;
	}
}

int	get_texture_pixel_color(t_texture *texture, int x, int y)
{
	char	*pixel_addr;
	int		color;

	pixel_addr = texture->data.mlx_data
		+ y * texture->data.size_line
		+ (texture->width - x) * (texture->data.bpp / 8);
	color = *(unsigned int *)pixel_addr;
	return (color);
}

void	draw_line3d(t_game *game, t_ray *ray, int x)
{
	int y;
	int texY;
	double step;
	double texPos;

	step = (double)ray->texture->height / ray->line_height;
	texPos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		texY = (int)texPos;
		if (texY < 0)
			texY = 0;
		if (texY >= ray->texture->height)
			texY = ray->texture->height - 1;
		
		ray->color = get_texture_pixel_color(ray->texture, ray->tex_x, texY);
		put_pixel(game, x, y, ray->color);
		texPos += step;
		y++;
	}
}

void	draw_floor(t_game *game, int draw_end, int x, int color)
{
	int	y;

	if (draw_end < 0)
		return ;
	y = draw_end;
	while (y < HEIGHT - 1)
	{
		put_pixel(game, x, y, color);
		y++;
	}
}

void	draw_ceiling(t_game *game, int draw_end, int x, int color)
{
	int	y;

	y = 0;
	while (y < draw_end)
	{
		put_pixel(game, x, y, color);
		y++;
	}
}

int	draw_loop(t_game *game)
{
	int				i;
	int				hit;
	t_ray			ray;
	double	wall_x;

	move_player(game);
	clear_image(game);
	i = -1;
	while (++i < WIDTH)
	{
		ray.map_x = game->player.px;
		ray.map_y = game->player.py;
		ray.camera_x = - (2.0 * i / WIDTH - 1.0);
		ray.dir_x = game->player.dir_x + game->player.plane_x * ray.camera_x;
		ray.dir_y = game->player.dir_y + game->player.plane_y * ray.camera_x;
		if (ray.dir_x == 0.0) 
			ray.dir_x = 1e-30;
		else
			ray.d_dist_x = fabs(1 / ray.dir_x);
		if (ray.dir_y == 0.0)
			ray.dir_y = 1e-30;
		else
			ray.d_dist_y = fabs(1 / ray.dir_y);

		if (ray.dir_x < 0)
		{
			ray.step_x = -1;
			ray.s_dist_x = (game->player.px - ray.map_x) * ray.d_dist_x;
		}
		else
		{
			ray.step_x = 1;
			ray.s_dist_x = (ray.map_x + 1.0 - game->player.px) * ray.d_dist_x;
		}
		if (ray.dir_y < 0)
		{
			ray.step_y = -1;
			ray.s_dist_y = (game->player.py - ray.map_y) * ray.d_dist_y;
		}
		else
		{
			ray.step_y = 1;
			ray.s_dist_y = (ray.map_y + 1.0 - game->player.py) * ray.d_dist_y;
		}
		hit = 0;
		while (hit == 0)
		{
			if (ray.s_dist_x < ray.s_dist_y)
			{
				ray.s_dist_x += ray.d_dist_x;
				ray.map_x += ray.step_x;
				ray.side = 0;
			}
			else
			{
				ray.s_dist_y += ray.d_dist_y;
				ray.map_y += ray.step_y;
				ray.side = 1;
			}
			if (game->map[ray.map_y][ray.map_x] == '1') // MAP_HEIGHT - 1 -
			{
				if (ray.side == 0 && ray.dir_x > 0)
					ray.texture = &game->e_wall;
				if (ray.side == 0 && ray.dir_x < 0)
					ray.texture = &game->w_wall;
				if (ray.side == 1 && ray.dir_y > 0)
					ray.texture = &game->s_wall;
				if (ray.side == 1 && ray.dir_y < 0)
					ray.texture = &game->n_wall;
				hit = 1;
			}
		}
		if (ray.side == 0)
			ray.perp_wall_dist = (ray.map_x - game->player.px + (1 - ray.step_x) / 2) / ray.dir_x;
		else
			ray.perp_wall_dist = (ray.map_y - game->player.py + (1 - ray.step_y) / 2) / ray.dir_y;

		ray.line_height = HEIGHT / ray.perp_wall_dist;
		ray.draw_start = -ray.line_height / 2 + HEIGHT / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = ray.line_height / 2 + HEIGHT / 2;
		if (ray.draw_end >= HEIGHT)
			ray.draw_end = HEIGHT - 1;
		
		if (ray.side == 0)
			wall_x = game->player.py + ray.perp_wall_dist * ray.dir_y;
		else
			wall_x = game->player.px + ray.perp_wall_dist * ray.dir_x;
		wall_x -= floor(wall_x);

		ray.tex_x = (int)(wall_x * (double)(ray.texture->width));
		if (ray.side == 0 && ray.dir_x > 0)
			ray.tex_x = ray.texture->width - ray.tex_x - 1;
		if (ray.side == 1 && ray.dir_y < 0)
			ray.tex_x = ray.texture->width - ray.tex_x - 1;

		draw_ceiling(game, ray.draw_start, i, 0x0080FF);
		draw_line3d(game, &ray, i);
		draw_floor(game, ray.draw_end, i, 0x505050);
	}
	if (MAP)
	{
		draw_map(game);
		draw_player(game);
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->mlx_img, 0, 0);
	return (0);
}
