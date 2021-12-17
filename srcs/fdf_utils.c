#include "../includes/fdf.h"

int	fdf_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

bool	is_grad_slope(t_point start, t_point end)
{
	return (fdf_abs(end.y - start.y) < fdf_abs(end.x - start.x));
}

int	fdf_max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

int	fdf_min(int a, int b)
{
	if (b < a)
		return (b);
	return (a);
}

bool	bounds_err(t_info *info, t_point curr)
{
	return (curr.y < 0 || curr.x < 0
		|| curr.y > info->win_hight - 1 || curr.x > info->win_width - 1);
}
