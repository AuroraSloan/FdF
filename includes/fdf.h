#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# define WID 1000
# define HGHT 1000
# define TAN_30_DEGREES .577
# define DEFAULT_ZOOM 10

# define BLACK_CURRANT 0x533A71 /*CYBER_GRAPE*/
# define DARK_CERULEAN 0x6184D8 /*GLAUCOUS*/
# define JAVA 0x50C5B7 /*MEDIUM_TURQUOISE*/
# define FERN 0xCEC5B /*INCHWORM*/
# define GORSE 0xF0F465 /*ICTERINE*/


/*# define BLACK_CURRANT 0x440154
# define DARK_CERULEAN 0x00589
# define JAVA 0x21918C
# define FERN 0x5DC86D
# define GORSE 0xFDE725*/

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define WIN_DSTRY 17
# define KEY_PRESS_MASK 1
# define KEY_RELEASE_MASK 2
# define WIN_DSTRY_MASK 131072

# include <stdbool.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		end;
}				t_img;

typedef struct s_point
{
	int		x;
	int		y;
	double	value;
	int		color;
}				t_point;

typedef struct s_elevation
{
	double	value;
	int		color;
}				t_elevation;

typedef struct s_gnl
{
	char	*line;
	int		fd;
	int		ret;
}				t_gnl;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

typedef struct s_line
{
	t_point	start;
	t_point	curr;
	t_point	end;
	t_point	delta;
	int		diff;	
}				t_line;

typedef struct s_info
{
	int			win_width;
	int			win_hight;
	void		*mlx;
	void		*win;
	char		*filename;
	t_elevation	**map;
	int			ord;
	int			ord_count;	
	int			abs;
	int			abs_count;
	t_img		img;
	t_line		line;
	int			grid_zoom;
	int			elevation_zoom;
	int			x_shift;
	int			y_shift;
	int			yi;
	int			xi;
	int			min_elevation;
	int			max_elevation;
	char		projection;
	double		x_rot;
	double		y_rot;
	double		z_rot;
}					t_info;

int		key_press(int keycode, t_info *info);
void	exit_failed(t_info *info, char *error_message);
int		exit_successful(t_info *info);
void	draw_grid(t_info *info);
void	read_map_info(t_info *info);
void	close_and_exit(t_info *info, int fd, char *line, char *err_msg);
int		fdf_open_file(t_info *info, char *filename);
void	init_map(t_info *info);
void	fdf_bresenham(t_info *info, t_point start, t_point end);
int		fdf_abs(int num);
bool	bounds_err(t_info *info, t_point curr);
void	init_line_info(t_info *info);
void	init_point_info(t_info *info, t_point *dest, t_point *src);
int		fdf_min(int a, int b);
int		fdf_max(int a, int b);
void	init_color(t_info *info);
bool	is_grad_slope(t_point start, t_point end);
int		main(int argc, char **argv);
void	fdf_iso_conv(int *x, int *y, int z);
int		get_point_color(t_info *info, int value);
void	x_rot(int *axis, double *value, double rot);
void	y_rot(int *axis, double *value, double rot);
void	z_rot(int *x, int *y, double rot);
void	modify_projection(int keycode, t_info *info);
void	modify_translation(int keycode, t_info *info);
void	modify_transformation(int keycode, t_info *info);
void	modify_zoom(int keycode, t_info *info);

#endif
