#include "../includes/fdf.h"
#include "../libraries/libft/libft.h"
#include <unistd.h>
#include <stdint.h>

static void	init_min_max(t_info *info)
{	
	int	x;
	int	y;

	y = 0;
	info->min_elevation = info->map[0][0].value;
	info->max_elevation = info->map[0][0].value;
	while (y < info->ord_count)
	{
		x = 0;
		while (x < info->abs_count)
		{
			if (info->map[y][x].value < info->min_elevation)
				info->min_elevation = info->map[y][x].value;
			else if (info->map[y][x].value > info->max_elevation)
				info->max_elevation = info->map[y][x].value;
			x++;
		}
		y++;
	}
}

static int	fdf_hex_len(char *hex)
{
	int	i;

	i = 0;
	while (ft_isalnum(hex[i]))
		i++;
	return (i);
}

static uint32_t	fdf_hextol(char *hex)
{
	long	hex_l;
	int		i;
	int		len;
	uint8_t	byte;

	if (ft_memcmp("0x", hex, 2) != 0)
		return ('\0');
	hex_l = 0;
	i = 0;
	len = fdf_hex_len(hex);
	while (i < len)
	{
		if (ft_isdigit(hex[i]))
			byte = hex[i] - '0';
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			byte = hex[i] - 'a' + 10;
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			byte = hex[i] - 'A' + 10;
		hex_l = (hex_l << 4) | (byte & 0xF);
		i++;
	}
	return (hex_l);
}

static void	init_map_row(t_info *info, int fd, char *line)
{
	int	i;

	i = 0;
	info->map[info->ord] = (t_elevation *)malloc(sizeof(t_elevation)
			* info->abs_count);
	if (!(info->map[info->ord]))
		close_and_exit(info, fd, line, "Memory allocation error");
	while (line[i] && info->abs != info->abs_count)
	{
		while (ft_isspace(line[i]))
			i++;
		info->map[info->ord][info->abs].value = ft_atoi(&line[i]);
		info->map[info->ord][info->abs].color = '\0';
		if (line[i] == '-')
			i++;
		while (ft_isdigit(line[i]))
			i++;
		if (line[i] == ',')
		{
			info->map[info->ord][info->abs].color = (int)fdf_hextol(&line[++i]);
			while (ft_isalnum(line[i]) && line[i])
				i++;
		}
		info->abs++;
	}
}

void	init_map(t_info *info)
{
	t_gnl	gnl;

	gnl.line = NULL;
	gnl.fd = fdf_open_file(info, info->filename);
	gnl.ret = get_next_line(gnl.fd, &gnl.line);
	if (gnl.ret == -1)
		close_and_exit(info, gnl.fd, gnl.line, "Memory allocation error");
	info->map = (t_elevation **)malloc(sizeof(t_elevation *) * info->ord_count);
	if (!(info->map))
		close_and_exit(info, gnl.fd, gnl.line, "Memory allocation error");
	while (gnl.ret == 1)
	{
		if (gnl.line[0] == 0)
			close_and_exit(info, gnl.fd, gnl.line, "Delete blnk new lines");
		info->abs = 0;
		init_map_row(info, gnl.fd, gnl.line);
		ft_free(gnl.line);
		gnl.ret = get_next_line(gnl.fd, &gnl.line);
		if (gnl.ret == -1)
			close_and_exit(info, gnl.fd, gnl.line, "cannot read .fdf file");
		info->ord++;
	}
	ft_free(gnl.line);
	close(gnl.fd);
	init_min_max(info);
}
