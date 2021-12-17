#include "../includes/fdf.h"

static void	fdf_pixel_put(t_info *info, t_point curr)
{
	char	*dest;
	int		location;

	location = curr.y * info->img.len + curr.x * (info->img.bpp / 8);
	dest = info->img.addr + location;
	*(unsigned int *)dest = curr.color;
}

static void	grad_slope(t_info *info)
{	
	while (info->line.curr.x <= info->line.end.x)
	{
		if (!bounds_err(info, info->line.curr))
		{	
			init_color(info);
			fdf_pixel_put(info, info->line.curr);
		}
		if (info->line.diff > 0)
		{
			info->line.curr.y = info->line.curr.y + info->yi;
			info->line.diff += (2 * (info->line.delta.y - info->line.delta.x));
		}
		else
			info->line.diff = info->line.diff + 2 * info->line.delta.y;
		info->line.curr.x++;
	}
}

static void	steep_slope(t_info *info)
{
	while (info->line.curr.y <= info->line.end.y)
	{
		if (!bounds_err(info, info->line.curr))
		{	
			init_color(info);
			fdf_pixel_put(info, info->line.curr);
		}
		if (info->line.diff > 0)
		{
			info->line.curr.x = info->line.curr.x + info->xi;
			info->line.diff += (2 * (info->line.delta.x - info->line.delta.y));
		}
		else
			info->line.diff = info->line.diff + 2 * info->line.delta.x;
		info->line.curr.y++;
	}	
}

static void	reverse_line(t_info *info)
{
	t_point	tmp;

	tmp = info->line.start;
	info->line.start = info->line.end;
	info->line.end = tmp;
}

void	fdf_bresenham(t_info *info, t_point start, t_point end)
{
	init_point_info(info, &info->line.start, &start);
	init_point_info(info, &info->line.end, &end);
	if (is_grad_slope(info->line.start, info->line.end))
	{	
		if (info->line.start.x > info->line.end.x)
			reverse_line(info);
		init_line_info(info);
		grad_slope(info);
	}
	else
	{
		if (info->line.start.y > info->line.end.y)
			reverse_line(info);
		init_line_info(info);
		steep_slope(info);
	}
}
