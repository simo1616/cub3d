/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:32:30 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/23 22:03:42 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ERRORS_H
# define PARSER_ERRORS_H

/* ===================== CONSTANTES ERREURS ===================== */

# define ERR_OPEN_FILE \
	"Error\nImpossible d'ouvrir le fichier: "
# define ERR_MEM_ALLOC_TEXTURE \
	"Error\nÉchec de l'allocation mémoire pour textures.\n"
# define ERR_EMPTY_TEXTURE_PATH \
	"Error\nChemin de texture vide.\n"
# define ERR_TEXTURE_ALREADY_DEFINED_NO \
	"Error\nTexture NO déjà définie.\n"
# define ERR_TEXTURE_ALREADY_DEFINED_SO \
	"Error\nTexture SO déjà définie.\n"
# define ERR_TEXTURE_ALREADY_DEFINED_WE \
	"Error\nTexture WE déjà définie.\n"
# define ERR_TEXTURE_ALREADY_DEFINED_EA \
	"Error\nTexture EA déjà définie.\n"
# define ERR_MEM_ALLOC_COLOR \
	"Error\nÉchec de l'allocation mémoire pour couleur.\n"
# define ERR_INVALID_COLOR_FORMAT \
	"Error\nInvalid color format (need exactly 3 values)\n"
# define ERR_UNKNOWN_COLOR_IDENTIFIER \
	"Error\nIdentifiant de couleur inconnu \n"
# define ERR_MAP_FIRST_LAST_LINE \
	"Error\nLigne (1ère/dernière) contient autre chose que '1'.\n"
# define ERR_MAP_START_LINE \
	"Error\nUne ligne ne commence pas par un mur '1'.\n"
# define ERR_TEXTURE_NOT_DEFINED_NO \
	"Error\nTexture NO non définie.\n"
# define ERR_TEXTURE_NOT_DEFINED_SO \
	"Error\nTexture SO non définie.\n"
# define ERR_TEXTURE_NOT_DEFINED_WE \
	"Error\nTexture WE non définie.\n"
# define ERR_TEXTURE_NOT_DEFINED_EA \
	"Error\nTexture EA non définie.\n"
# define ERR_COLOR_NOT_DEFINED_F \
	"Error\nCouleur F(Sol) non définie.\n"
# define ERR_COLOR_NOT_DEFINED_C \
	"Error\nCouleur C(Plaf.) non définie.\n"
# define ERR_MAP_NOT_DEFINED \
	"Error\nMap non définie.\n"
# define ERR_MAP_EMPTY \
	"Error\nMap vide.\n"
# define ERR_MAP_INVALID_CHAR \
	"Error\nCaractère invalide.\n"
# define ERR_MAP_TEXT_MORE_THAN_ONE \
	"Error\nIl faut exactement 1 orientation (N,S,E,W).\n"
# define ERR_MAP_MALLOC \
	"Error\nMalloc failed for visited.\n"
# define ERR_MAP_NOT_CLOSE \
	"Error\nMap non fermée (fuite détectée)\n"
# define ERR_MAP_BAD \
	"Error\nDes caractères trouvés après des lignes vides suivant la carte.\n"
# define ERR_MAP_POS \
	"Error\nPosition de la map incorrecte \
	(pas toutes les textures/couleurs lues).\n"
# define ERR_MAP_ADD \
	"Error\nDes données supp après la carte.\n"
# define ERR_NMISSING_TEXTURE_PATH \
	"Error\nMissing texture path\n"
# define ERR_NTEXTURE_FILE_MUST \
	"Error\nTexture file must end with .xpm\n"
# define ERR_NCANNOT_LOAD_TEXTURE \
	"Error\nCannot load texture\n"
# define ERR_NFORMAT_TEXTURE \
	"Error\nFormat de texture invalide.\n"
# define ERR_NFORMAT_COULEUR \
	"Error\nFormat de couleur invalide.\n"
# define ERR_NHEADER_APRES_DEBUT \
	"Error\nHeader après le début de la map.\n"
# define ERR_INIT_MLX \
	"Error\nInit mlx\n"
# define ERR_NEW_WINDOW \
	"Error\nnew_window\n"
# define ERR_NEW_IMAGE \
	"Error\nnew_image\n"
# define ERR_COULEUR_DEJA_DEFINIE \
	"Error\nCouleur déjà définie.\n"
# define ERR_LIGNE \
	"Error\nLigne : "
# define ERR_COULEUR_INVALIDE \
	"Error\nCouleur invalide: "
# define ERR_HEADER_APRES_DEBUT_MAP \
	"Error\nHeader après le début de la map.\n"
# define ERR_FILE_TEXT_INACCESSIBLE \
	"Error\nfichier de texture inaccessible: "
# define ERR_LINE_INVALID \
	"Error\nLigne non reconnue dans la configuration.\n"
# define ERR_EXTENSION_INVALID \
	"Error\nFichier invalide : extension '.cub' requise\n"

#endif
