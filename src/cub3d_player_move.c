/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_player_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homohame <homohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 23:37:28 by homohame          #+#    #+#             */
/*   Updated: 2025/08/12 08:51:05 by homohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_player(t_game *game)
{
	t_player	*player;
	float		move_speed;
	float		rotation_speed;
	//float		cos_angle;
	//float		sin_angle;

	player = &game->player;

	rotation_speed = 0.01;
	move_speed = 0.015;
	//cos_angle = cos(player->angle);
	//sin_angle = sin(player->angle);

	if (player->key_rarrow)
	{
		player->angle -= rotation_speed;
		printf("Turning right !\n");
		player->old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(rotation_speed) - player->dir_y * sin(rotation_speed);
		player->dir_y = player->old_dir_x * sin(rotation_speed) + player->dir_y * cos(rotation_speed);
		player->old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(rotation_speed) - player->plane_y * sin(rotation_speed);
		player->plane_y = player->old_plane_x * sin(rotation_speed) + player->plane_y * cos(rotation_speed);
	}
	if (player->key_larrow)
	{
		player->angle += rotation_speed;
		printf("Turning left !\n");
		player->old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-rotation_speed) - player->dir_y * sin(-rotation_speed);
		player->dir_y = player->old_dir_x * sin(-rotation_speed) + player->dir_y * cos(-rotation_speed);
		player->old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-rotation_speed) - player->plane_y * sin(-rotation_speed);
		player->plane_y = player->old_plane_x * sin(-rotation_speed) + player->plane_y * cos(-rotation_speed);
	}
	
	//if (player->angle > 2 * PI)
	//	player->angle = 0;
	//if (player->angle < 0)
	//	player->angle = 2 * PI;

	if (player->key_w)
	{
		printf("Moving forward !\n");
		if (game->map[(int)player->py][(int)(player->px + player->dir_x * move_speed)] != '1')
			player->px += player->dir_x * move_speed;
		if (game->map[(int)(player->py + player->dir_y * move_speed)][(int)player->px] != '1')
			player->py += player->dir_y * move_speed;
	}
	if (player->key_s)
	{
		printf("Moving backward !\n");
		if (game->map[(int)player->py][(int)(player->px - player->dir_x * move_speed)] != '1')
			player->px -= player->dir_x * move_speed;
		if (game->map[(int)(player->py - player->dir_y * move_speed)][(int)player->px] != '1')
			player->py -= player->dir_y * move_speed;
	}
	if (player->key_a)
	{
		printf("Moving left !\n");
		if (game->map[(int)player->py][(int)(player->px + player->plane_x * move_speed)] != '1')
			player->px += player->plane_x * move_speed;
		if (game->map[(int)(player->py + player->plane_y * move_speed)][(int)player->px] != '1')
			player->py += player->plane_y * move_speed;
	}
	if (player->key_d)
	{
		printf("Moving right !\n");
		if (game->map[(int)player->py][(int)(player->px - player->plane_x * move_speed)] != '1')
			player->px -= player->plane_x * move_speed;
		if (game->map[(int)(player->py - player->plane_y * move_speed)][(int)player->px] != '1')
			player->py -= player->plane_y * move_speed;
	}

}

int	key_press(int key_code, t_game *game)
{
	if (key_code == XK_w)
		game->player.key_w = 1;
	if (key_code == XK_s)
		game->player.key_s = 1;
	if (key_code == XK_a)
		game->player.key_a = 1;
	if (key_code == XK_d)
		game->player.key_d = 1;
	if (key_code == XK_Left)
		game->player.key_larrow = 1;
	if (key_code == XK_Right)
		game->player.key_rarrow = 1;
	if (key_code == XK_Escape)
		free_all(game);
	return (0);
}

int	key_release(int key_code, t_player *player)
{
	if (key_code == XK_w)
		player->key_w = 0;
	if (key_code == XK_s)
		player->key_s = 0;
	if (key_code == XK_a)
		player->key_a = 0;
	if (key_code == XK_d)
		player->key_d = 0;
		if (key_code == XK_Left)
		player->key_larrow = 0;
	if (key_code == XK_Right)
		player->key_rarrow = 0;
	return (0);
}

void	draw_player(t_game *game)
{
	int	i;
	int	size;

	size = 2;
	i = -1;
	while (++i < size)
		put_pixel(game, i + game->player.px * BLOCK , game->player.py * BLOCK , 0xFF0000);
	i = -1;
	while (++i < size)
		put_pixel(game, game->player.px * BLOCK, i + game->player.py * BLOCK, 0xFF0000);
	i = -1;
	while (++i < size)
		put_pixel(game, game->player.px * BLOCK + 2, i + game->player.py * BLOCK, 0xFF0000);
	i = -1;
	while (++i < size + 1)
		put_pixel(game, i + game->player.px * BLOCK, 2 + game->player.py * BLOCK, 0xFF0000);

		
	//while (++i < size)
	//	put_pixel(game, game->player.py * BLOCK, i + game->player.px * BLOCK, 0xFF0000);
	//i = -1;
	//while (++i < size)
	//	put_pixel(game, i + game->player.py * BLOCK, game->player.px * BLOCK, 0xFF0000);
	//i = -1;
	//while (++i < size)
	//	put_pixel(game, i + game->player.py * BLOCK, game->player.px * BLOCK + 2, 0xFF0000);
	//i = -1;
	//while (++i < size + 1)
	//	put_pixel(game, 2 + game->player.py * BLOCK, i + game->player.px * BLOCK, 0xFF0000);
}
