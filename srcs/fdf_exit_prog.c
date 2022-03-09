#include "../includes/fdf.h"
#include "../libraries/libft/libft.h"
#include "../libraries/minilibx_mms/mlx.h"
#include <unistd.h>

static void	free_memory(t_info *info)
{
	int	i;

	i = 0;
	if (info->map)
	{
		while (i < info->ord && info->map[i])
			ft_free(info->map[i++]);
		ft_free(info->map);
	}
	if (info->img.img)
		mlx_destroy_image(info->mlx, info->img.img);
	if (info->win)
		mlx_destroy_window(info->mlx, info->win);
	if (info->mlx)
		ft_free(info->mlx);
}

void	exit_failed(t_info *info, char *error_message)
{
	free_memory(info);
	ft_failed_exit(error_message, NULL);
}

int	exit_successful(t_info *info)
{
	free_memory(info);
	exit(EXIT_SUCCESS);
}

void	close_and_exit(t_info *info, int fd, char *line, char *err_msg)
{
	close(fd);
	free_memory(info);
	ft_failed_exit(err_msg, line);
}
