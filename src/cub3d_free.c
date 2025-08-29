/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homohame <homohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:18:36 by homohame          #+#    #+#             */
/*   Updated: 2025/08/09 03:40:19 by homohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//void	free_split(char **split)
//{
//	int	i;

//	if (split == NULL)
//		return ;
//	i = 0;
//	while (split[i])
//	{
//		free(split[i]);
//		++i;
//	}
//	free(split);
//}

void	free_all(t_game *game)
{
	if (game->mlx_win != NULL)
		mlx_destroy_window(game->mlx, game->mlx_win);
	if (game->n_wall.ptr != NULL)
		mlx_destroy_image(game->mlx, game->n_wall.ptr);
	if (game->s_wall.ptr != NULL)
		mlx_destroy_image(game->mlx, game->s_wall.ptr);
	if (game->e_wall.ptr != NULL)
		mlx_destroy_image(game->mlx, game->e_wall.ptr);
	if (game->w_wall.ptr != NULL)
		mlx_destroy_image(game->mlx, game->w_wall.ptr);
	if (game->mlx_img != NULL)
		mlx_destroy_image(game->mlx, game->mlx_img);
	free(game->map);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

int	close_window(t_game *game)
{
	free_all(game);
	return (0);
}
