#include "../includes/fdf.h"
#include "../libraries/libft/libft.h"
#include "../libraries/minilibx_mms/mlx.h"
#include <unistd.h>
#include <fcntl.h>

static void	init_mlx_win(t_info *info)
{
	info->mlx = mlx_init();
	if (!info->mlx)
		ft_failed_exit("Connection to X-server failed", NULL);
	info->win = mlx_new_window(info->mlx, info->win_width,
			info->win_hight, "fdf");
	if (!info->win)
		exit_failed(info, "Could not create window");
	info->img.img = mlx_new_image(info->mlx, info->win_width, info->win_hight);
	if (!info->img.img)
		exit_failed(info, "Could not create image");
	info->img.addr = mlx_get_data_addr(info->img.img,
			&info->img.bpp, &info->img.len, &info->img.end);
}

static void	init_info(t_info *info)
{
	info->mlx = NULL;
	info->img.img = NULL;
	info->img.addr = NULL;
	info->win = NULL;
	info->ord = 0;
	info->ord_count = 0;
	info->abs = 0;
	info->abs_count = 0;
	info->min_elevation = 0;
	info->max_elevation = 0;
	info->win_width = WID;
	info->win_hight = HGHT;
	info->grid_zoom = DEFAULT_ZOOM;
	info->elevation_zoom = DEFAULT_ZOOM;
	info->projection = 'i';
	info->x_shift = 0;
	info->y_shift = 0;
	info->x_rot = 0;
	info->y_rot = 0;
	info->z_rot = 0;
	read_map_info(info);
	init_mlx_win(info);
	init_map(info);
}

static void	check_args(t_info *info, int argc, char **argv)
{
	int		start;
	int		fd;
	char	buf[1];
	int		ret;

	if (argc > 2)
		ft_failed_exit("Too many arguments", NULL);
	else if (argc < 2)
		ft_failed_exit("Please select which .fdf file to read", NULL);
	start = ft_strlen(argv[1]) - 4;
	if (ft_memcmp(&argv[1][start], ".fdf", 4) != 0)
		ft_failed_exit("The second argument should be a .fdf file", NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_failed_exit("Could not open .fdf file", NULL);
	ret = read(fd, buf, 1);
	close(fd);
	if (ret == -1)
		ft_failed_exit("Check .fdf file is correct type of file", NULL);
	info->filename = argv[1];
}

int	main(int argc, char **argv)
{
	t_info	info;

	check_args(&info, argc, argv);
	init_info(&info);
	draw_grid(&info);
	mlx_hook(info.win, KEY_PRESS, KEY_PRESS_MASK, &key_press, &info);
	mlx_hook(info.win, WIN_DSTRY, WIN_DSTRY_MASK, &exit_successful, &info);
	mlx_loop(info.mlx);
}
