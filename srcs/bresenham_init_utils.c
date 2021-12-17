#include "../includes/fdf.h"
#include <math.h>

void	fdf_iso_conv(int *x, int *y, int z)
{
	int	px;
	int	py;

	px = *x;
	py = *y;
	*x = (px - py) * cos(TAN_30_DEGREES);
	*y = (px + py + 1) * sin(TAN_30_DEGREES) - z;
}

void	init_point_info(t_info *info, t_point *dest, t_point *src)
{
	dest->value = info->map[src->y][src->x].value;
	if (!info->map[src->y][src->x].color)
		dest->color = get_point_color(info, dest->value);
	else
		dest->color = info->map[src->y][src->x].color;
	dest->value *= info->elevation_zoom;
	src->x *= info->grid_zoom;
	src->y *= info->grid_zoom;
	src->x -= ((info->abs_count - 1) * info->grid_zoom) / 2;
	src->y -= ((info->ord_count - 1) * info->grid_zoom) / 2;
	x_rot(&src->y, &dest->value, info->x_rot);
	y_rot(&src->x, &dest->value, info->y_rot);
	z_rot(&src->x, &src->y, info->z_rot);
	if (info->projection == 'i')
		fdf_iso_conv(&src->x, &src->y, dest->value);
	dest->x = src->x + (info->win_width / 2) + info->x_shift;
	dest->y = src->y + (info->win_hight / 2) + info->y_shift;
}

void	init_line_info(t_info *info)
{
	info->line.delta.x = info->line.end.x - info->line.start.x;
	info->line.delta.y = info->line.end.y - info->line.start.y;
	info->line.curr = info->line.start;
	if (is_grad_slope(info->line.start, info->line.end))
	{
		info->line.diff = 2 * info->line.delta.y - info->line.delta.x;
		info->yi = 1;
		if (info->line.delta.y < 0)
		{
			info->yi = -1;
			info->line.delta.y = -info->line.delta.y;
		}
	}
	else
	{
		info->line.diff = 2 * info->line.delta.x - info->line.delta.y;
		info->xi = 1;
		if (info->line.delta.x < 0)
		{
			info->xi = -1;
			info->line.delta.x = -info->line.delta.x;
		}
	}
}
