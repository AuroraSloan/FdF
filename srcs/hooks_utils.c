#include "../includes/fdf.h"
#include "../includes/fdf_key_macros.h"

void	modify_projection(int keycode, t_info *info)
{
	info->x_shift = 0;
	info->y_shift = 0;
	info->x_rot = 0;
	info->y_rot = 0;
	info->z_rot = 0;
	if (keycode == P)
		info->projection = 'p';
	else if (keycode == I)
		info->projection = 'i';
}

void	modify_translation(int keycode, t_info *info)
{
	if (keycode == UP)
		info->y_shift -= 10;
	else if (keycode == DWN)
		info->y_shift += 10;
	else if (keycode == LFT)
		info->x_shift -= 10;
	else if (keycode == RT)
		info->x_shift += 10;
}

void	modify_transformation(int keycode, t_info *info)
{
	if (keycode == A)
		info->z_rot -= .1;
	else if (keycode == COL)
		info->z_rot += .1;
	else if (keycode == S)
		info->x_rot += .1;
	else if (keycode == L)
		info->x_rot -= .1;
	else if (keycode == D)
		info->y_rot += .1;
	else if (keycode == K)
		info->y_rot -= .1;
}

void	modify_zoom(int keycode, t_info *info)
{
	if (keycode == F)
	{
		info->grid_zoom++;
		info->elevation_zoom++;
	}
	else if (keycode == J)
	{
		info->grid_zoom--;
		info->elevation_zoom--;
	}
	else if (keycode == PLS)
		info->elevation_zoom++;
	else if (keycode == MNS)
		info->elevation_zoom--;
	if (info->grid_zoom > 100)
		info->grid_zoom = 100;
	if (info->elevation_zoom > 100)
		info->elevation_zoom = 100;
	if (info->grid_zoom < 1)
		info->grid_zoom = 1;
	if (info->elevation_zoom < 1)
		info->elevation_zoom = 1;
}
