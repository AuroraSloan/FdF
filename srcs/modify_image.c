#include <math.h>

void	x_rot(int *axis, double *value, double rot)
{
	int		tmp_axis;
	double	tmp_value;

	tmp_axis = *axis;
	tmp_value = *value;
	*axis = cos(rot) * tmp_axis - sin(rot) * tmp_value;
	*value = sin(rot) * tmp_axis + cos(rot) * tmp_value;
}

void	y_rot(int *axis, double *value, double rot)
{
	int		tmp_axis;
	double	tmp_value;

	tmp_axis = *axis;
	tmp_value = *value;
	*axis = cos(rot) * tmp_axis - sin(rot) * tmp_value;
	*value = -sin(rot) * tmp_axis + cos(rot) * tmp_value;
}

void	z_rot(int *x, int *y, double rot)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*x = cos(rot) * tmp_x - sin(rot) * tmp_y;
	*y = sin(rot) * tmp_x + cos(rot) * tmp_y;
}
