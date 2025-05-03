#include "cub3d.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = -PI / 2;
	player->movespeed = MOVE_SPEED;
	player->rotspeed = ROT_SPEED;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;

	player->left_rotate = false;
	player->right_rotate = false;
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

static void	rotate_player(t_player *player)
{
	float	angle_speed;

	angle_speed = player->rotspeed;

	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle < 0)
		player->angle += 2 * PI;
	else if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
}

static void	translate_player(t_player *player, t_game *game)
{
	float	speed;
	float	new_x;
	float	new_y;
	float	dir;

	speed = player->movespeed;
	if (player->key_up || player->key_down)
	{
		if (player->key_up)
			dir = 1.0f;
		else
			dir = -1.0f;
		new_x = player->x + cosf(player->angle) * speed * dir;
		new_y = player->y + sinf(player->angle) * speed * dir;
		if (!is_wall(new_x, player->y, game))
			player->x = new_x;
		if (!is_wall(player->x, new_y, game))
			player->y = new_y;
	}
}

static void	strafe_player(t_player *player, t_game *game)
{
	float	speed;
	float	new_x;
	float	new_y;
	float	dir;

	speed = player->movespeed;
	if (player->key_left || player->key_right)
	{
		if (player->key_right)
			dir = 1.0f;
		else
			dir = -1.0f;
		new_x = player->x + cosf(player->angle + dir * PI / 2) * speed;
		new_y = player->y + sinf(player->angle + dir * PI / 2) * speed;
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


/* 	if (player->key_up)
		printf("W\n");
	if (player->key_down)
		printf("S\n");
	if (player->key_left)
		printf("A\n");
	if (player->key_right)
		printf("D\n");
 */

/* 	if (player->x < 0)
		player->x = 0;
	if (player->x > WIDTH - 20)
		player->x = WIDTH - 20;
	if (player->y < 0)
		player->y = 0;
	if (player->y > HEIGHT - 20)
		player->y = HEIGHT - 20; */
