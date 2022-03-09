#include "../includes/fdf.h"
#include "../includes/fdf_key_macros.h"
#include "../libraries/minilibx_mms/mlx.h"

static void	reset_win(t_info *info)
{
	mlx_destroy_image(info->mlx, info->img.img);
	info->img.img = mlx_new_image(info->mlx, info->win_width, info->win_hight);
	if (!(info->img.img))
		exit_failed(info, "Could not create image");
	info->img.addr = mlx_get_data_addr(info->img.img,
			&info->img.bpp, &info->img.len, &info->img.end);
	draw_grid(info);
}

int	key_press(int keycode, t_info *info)
{
	if (keycode == ESC)
		exit_successful(info);
	else if (keycode == P || keycode == I)
		modify_projection(keycode, info);
	else if (keycode == UP || keycode == DWN
		|| keycode == LFT || keycode == RT)
		modify_translation(keycode, info);
	else if (keycode == A || keycode == COL || keycode == S
		|| keycode == L || keycode == D || keycode == K)
		modify_transformation(keycode, info);
	else if (keycode == F || keycode == J
		|| keycode == PLS || keycode == MNS)
		modify_zoom(keycode, info);
	reset_win(info);
	return (0);
}
