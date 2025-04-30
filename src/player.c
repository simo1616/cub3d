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

int	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	if (keycode == KEY_ESC || keycode == KEY_Q)
		exit(0);
	return (0);
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

void	move_player(t_player *player)
{
	float speed = player->movespeed;
	float angle_speed = player->rotspeed;
	float dir_x = cosf(player->angle);
	float dir_y	= sinf(player->angle);

	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;

	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;

	if (player->key_up) // W
	{
		player->x += dir_x * speed;
		player->y += dir_y * speed;
	}
	if (player->key_down) // S
	{
		player->x -= dir_x * speed;
		player->y -= dir_y * speed;
	}
	if (player->key_left) // A
	{
		player->x += dir_y * speed;
		player->y -= dir_x * speed;
	}
	if (player->key_right) // D
	{
		player->x -= dir_y * speed;
		player->y += dir_x * speed;
	}
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
