#include "cub3d.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = -PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

static void	rotate_player(t_player *player)
{
	if (player->left_rotate)
		player->angle -= ROT_SPEED;
	if (player->right_rotate)
		player->angle += ROT_SPEED;
	if (player->angle < 0)
		player->angle += 2 * PI;
	else if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
}

static void	translate_player(t_player *player, t_game *game)
{
	float	new_x;
	float	new_y;
	float	dir;
	if (player->key_up || player->key_down)
	{
		if (player->key_up)
			dir = 1.0f;
		else
			dir = -1.0f;
		new_x = player->x + cosf(player->angle) * MOVE_SPEED * dir;
		new_y = player->y + sinf(player->angle) * MOVE_SPEED * dir;
		if (!is_wall(new_x, player->y, game))
			player->x = new_x;
		if (!is_wall(player->x, new_y, game))
			player->y = new_y;
	}
}

static void	strafe_player(t_player *player, t_game *game)
{
	float	new_x;
	float	new_y;
	float	dir;

	if (player->key_left || player->key_right)
	{
		if (player->key_right)
			dir = 1.0f;
		else
			dir = -1.0f;
		new_x = player->x + cosf(player->angle + dir * PI / 2) * MOVE_SPEED;
		new_y = player->y + sinf(player->angle + dir * PI / 2) * MOVE_SPEED;
		if (!is_wall(new_x, player->y, game))
			player->x = new_x;
		if (!is_wall(player->x, new_y, game))
			player->y = new_y;
	}
}


void	move_player(t_player *player, t_game *game)
{
	rotate_player(player);
	translate_player(player, game);
	strafe_player(player, game);
}
