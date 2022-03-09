#include "../includes/fdf.h"
#include "../libraries/minilibx_mms/mlx.h"

static t_point	move_right(t_point step)
{
	step.x++;
	return (step);
}

static t_point	move_down(t_point step)
{
	step.y++;
	return (step);
}

void	draw_grid(t_info *info)
{
	t_point	step;

	step.y = 0;
	while (step.y < info->ord_count)
	{
		step.x = 0;
		while (step.x < info->abs_count)
		{
			if (step.x < info->abs_count - 1)
				fdf_bresenham(info, step, move_right(step));
			if (step.y < info->ord_count - 1)
				fdf_bresenham(info, step, move_down(step));
			step.x++;
		}
		step.y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}
