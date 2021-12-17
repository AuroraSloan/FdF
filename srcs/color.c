#include "../includes/fdf.h"

static double	fdf_percent(double start, double end, double current)
{
	double	traveled;
	double	distance;

	traveled = current - start;
	distance = end - start;
	if (distance == 0)
		return (1);
	else
		return (traveled / distance);
}

static int	fdf_interpolate(int start, int end, double percent)
{
	return ((1 - percent) * start + percent * end);
}

static t_rgb	isolate_rgb_channels(int color)
{
	t_rgb	component;

	component.red = (color >> 16) & 0xFF;
	component.green = (color >> 8) & 0xFF;
	component.blue = color & 0xFF;
	return (component);
}

int	get_point_color(t_info *info, int value)
{
	double	percent;

	percent = fdf_percent(info->min_elevation, info->max_elevation, value);
	if (percent < .2)
		return (BLACK_CURRANT);
	else if (percent < .4)
		return (DARK_CERULEAN);
	else if (percent < .6)
		return (JAVA);
	else if (percent < .8)
		return (FERN);
	else
		return (GORSE);
}

void	init_color(t_info *info)
{
	t_rgb	start_rgb;
	t_rgb	end_rgb;
	t_rgb	new_rgb;
	double	percent;

	if (info->line.start.color == info->line.end.color)
		return ;
	if (is_grad_slope(info->line.start, info->line.end))
		percent = fdf_percent(info->line.start.x, info->line.end.x,
				info->line.curr.x);
	else
		percent = fdf_percent(info->line.start.y, info->line.end.y,
				info->line.curr.y);
	start_rgb = isolate_rgb_channels(info->line.start.color);
	end_rgb = isolate_rgb_channels(info->line.end.color);
	new_rgb.red = fdf_interpolate(start_rgb.red, end_rgb.red, percent);
	new_rgb.green = fdf_interpolate(start_rgb.green, end_rgb.green, percent);
	new_rgb.blue = fdf_interpolate(start_rgb.blue, end_rgb.blue, percent);
	info->line.curr.color = ((new_rgb.red << 16) | (new_rgb.green << 8)
			| new_rgb.blue);
}
