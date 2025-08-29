/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homohame <homohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 21:08:58 by homohame          #+#    #+#             */
/*   Updated: 2025/08/12 09:09:47 by homohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char **get_map(void)
{
	//faire parsing pour recup la map dans le fichier .cub
	char **map = malloc(sizeof(char *) * 15);
	map[0] = "        1111111111111111111111111";
	map[1] = "        1000000000110000000000001";
	map[2] = "        1011000001110000000000001";
	map[3] = "00000000100100000000000000W000001";
	map[4] = "111111111011000001110000000000001";
	map[5] = "100000000011000001110111111111111";
	map[6] = "11110111111111011100000010001    ";
	map[7] = "11110111111111011101010010001    ";
	map[8] = "11000000110101011100000010001    ";
	map[9] = "10000000000000001100000010001    ";
	map[10]= "10000000000000001101010010001    ";
	map[11]= "1100000111010101111101111000111  ";
	map[12]= "11110111 1110101 101111010001    ";
	map[13]= "11111111 1111111 111111111111    ";
	map[14] = NULL;
	return (map);
}

void	init_textures(t_game *game)
{
	game->n_wall.ptr = mlx_xpm_file_to_image(game->mlx,
			"assets/wall.xpm", &game->n_wall.width,
			&game->n_wall.height);
	game->s_wall.ptr = mlx_xpm_file_to_image(game->mlx,
			"assets/thorfinn.xpm", &game->s_wall.width,
			&game->s_wall.height);
	game->e_wall.ptr = mlx_xpm_file_to_image(game->mlx,
			"assets/matrix.xpm", &game->e_wall.width,
			&game->e_wall.height);
	game->w_wall.ptr = mlx_xpm_file_to_image(game->mlx,
			"assets/gogeta.xpm", &game->w_wall.width,
			&game->w_wall.height);
	if (game->n_wall.ptr == NULL
		|| game->s_wall.ptr == NULL
		|| game->e_wall.ptr == NULL
		|| game->w_wall.ptr == NULL)
		free_all(game); // message d'erreur
	game->n_wall.data.mlx_data = mlx_get_data_addr(game->n_wall.ptr, &game->n_wall.data.bpp,
		&game->n_wall.data.size_line, &game->n_wall.data.endian);
	game->s_wall.data.mlx_data = mlx_get_data_addr(game->s_wall.ptr, &game->s_wall.data.bpp,
			&game->s_wall.data.size_line, &game->s_wall.data.endian);
	game->e_wall.data.mlx_data = mlx_get_data_addr(game->e_wall.ptr, &game->e_wall.data.bpp,
			&game->e_wall.data.size_line, &game->e_wall.data.endian);
	game->w_wall.data.mlx_data = mlx_get_data_addr(game->w_wall.ptr, &game->w_wall.data.bpp,
			&game->w_wall.data.size_line, &game->w_wall.data.endian);
}

void	init_game(t_game *game)
{
	game->map = get_map();
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		write (2, "Error\nEchec initialisation mlx\n", 32);
		free_all(game);
	}
	game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D"); //initialisation la fenetre
	if (game->mlx_win == NULL)
		free_all(game);
	game->mlx_img = mlx_new_image(game->mlx, WIDTH, HEIGHT); //initalisation de img a la taille de la fenetre
	if (game->mlx_img == NULL)
		free_all(game);
	game->data.mlx_data = mlx_get_data_addr(game->mlx_img, &game->data.bpp,
			&game->data.size_line, &game->data.endian); //initialisation de mlx_data , on met l'addrsse de mlx_img dedans
}

void	init_posmap(t_player *player, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'W')
			{
				player->px = x;
				player->py = y;
				player->dir_x = -1;
				player->dir_y = 0;
				player->plane_x = 0;
				player->plane_y = 0.66;
				player->angle = PI / 2;
			}
			++x;
		}
		++y;
	}
}

void	init_player(t_player *player, char **map)
{
	init_posmap(player, map);
	player->key_a = 0;
	player->key_d = 0;
	player->key_s = 0;
	player->key_w = 0;
	player->key_larrow = 0;
	player->key_rarrow = 0;
}

