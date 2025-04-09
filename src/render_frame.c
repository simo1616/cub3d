/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:49:00 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/09 20:44:05 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

static void init_data_img(t_game *game)
{
	game->data_img.whith = 800;
	game->data_img.hight = 600;
	game->data_img.pixels = (int *)mlx_get_data_addr(game->img, &game->data_img.bpp,
									&game->data_img.size_line, &game->data_img.endian);
	game->data_img.size_line = game->data_img.size_line / 4;
	game->data_img.cur_color_plaf = (game->config.color_plafond[0] << 16) |
					(game->config.color_plafond[1] << 8)  |
					game->config.color_plafond[2];
	game->data_img.cur_color_sol = (game->config.color_sol[0] << 16) |
				(game->config.color_sol[1] << 8)  |
				game->config.color_sol[2];	
}

void render_frame(t_game *game)
{
	int x;
	int y;

	init_data_img(game);

	y = 0;
	while(y < game->data_img.hight)
	{
		x = 0;
		while(x < game->data_img.whith)
		{
			if (y < game->data_img.hight / 2)
				game->data_img.pixels[y * game->data_img.size_line + x] = game->data_img.cur_color_plaf;
			else
				game->data_img.pixels[y * game->data_img.size_line + x] = game->data_img.cur_color_sol;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

// On initialise les dimensions de l'image dans notre structure 

// static void init_data_img(t_data_img *data_img)
// { 
// 	data_img->whith = 800; // largeur de l'image (attention à l'orthographe, on attend généralement "width") 
// 	data_img->hight = 600; // hauteur de l'image (même remarque pour "height") 
// }

// void render_frame(t_game *game) 
// { 
	// int *pixels; 
	// int x, 
	// int y; 
	// int line_size; 


// 	// Initialisation des dimensions de l'image
// 	init_data_img(&game->data_img);

// 	// Récupération de l'adresse du buffer d'image
// 	pixels = (int *)mlx_get_data_addr(game->img, &game->data_img.bpp,
// 										&game->data_img.size_line, &game->data_img.endian);

// 	// Calcul du nombre de pixels par ligne (size_line est en octets, d'où la division par 4 pour un affichage 32 bits)
// 	line_size = game->data_img.size_line / 4;

// 	// Conversion des tableaux de couleur RGB contenus dans game->config en entier hexadécimal.
// 	// Par exemple, pour le plafond : R << 16 | G << 8 | B
// 	color_plafond = (game->config.color_plafond[0] << 16) |
// 					(game->config.color_plafond[1] << 8)  |
// 					game->config.color_plafond[2];
// 	color_sol = (game->config.color_sol[0] << 16) |
// 				(game->config.color_sol[1] << 8)  |
// 				game->config.color_sol[2];

// 	// Remplissage du buffer image : la moitié supérieure pour le plafond et la moitié inférieure pour le sol
// 	for (y = 0; y < game->data_img.hight; y++)
// 	{
// 		for (x = 0; x < game->data_img.whith; x++)
// 		{
// 			if (y < game->data_img.hight / 2)
// 				pixels[y * line_size + x] = color_plafond;
// 			else
// 				pixels[y * line_size + x] = color_sol;
// 		}
// 	}
// 	// Affichage de l'image dans la fenêtre
// 	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
// }