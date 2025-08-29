/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homohame <homohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:17:32 by homohame          #+#    #+#             */
/*   Updated: 2025/08/09 03:16:14 by homohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game		game;
	int			i;

	(void)argc;
	(void)argv;
	//if arc != 2 error
	init_game(&game);
	init_player(&game.player, game.map);
	init_textures(&game);
	
	mlx_put_image_to_window(game.mlx, game.mlx_win, game.mlx_img, 0, 0);//on met l'image avec les pixel dessine dessus dans la window

	mlx_hook(game.mlx_win, 17, 1L << 0, close_window, &game);
	mlx_hook(game.mlx_win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.mlx_win, 3, 1L << 1, key_release, &game.player);

	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

// int offset = (y * line_length + x * (bits_per_pixel / 8)); pour place un pixel au bon endroit
