#include <unistd.h>
#include "../includes/fdf.h"
#include "../libraries/libft/libft.h"
#include <fcntl.h>

int	fdf_open_file(t_info *info, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_failed(info, "Could not open .fdf file");
	return (fd);
}

static void	check_values(t_info *info, t_gnl gnl)
{
	int		i;
	char	*compare;

	i = 0;
	while (gnl.line[i])
	{	
		while (ft_isspace(gnl.line[i]) && gnl.line[i])
			i++;
		compare = ft_itoa(ft_atoi(&gnl.line[i]));
		if (!compare)
			close_and_exit(info, gnl.fd, gnl.line, "Memory error");
		if (ft_memcmp(compare, &gnl.line[i], ft_strlen(compare) != 0))
		{
			ft_free(compare);
			if (!ft_isdigit(gnl.line[i]))
				close_and_exit(info, gnl.fd, gnl.line, "Invalid map");
			else
				close_and_exit(info, gnl.fd, gnl.line, "Value intgr ovrflw");
		}
		i += ft_strlen(compare);
		ft_free(compare);
		while ((gnl.line[i] == ',' || ft_isalnum(gnl.line[i])) && gnl.line[i])
			i++;
	}
}

static int	count_abs(t_info *info, int fd, char *line)
{
	int	i;
	int	abs_count;

	i = 0;
	abs_count = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]) || line[i] == '-')
			i++;
		if (ft_isdigit(line[i]))
			abs_count++;
		else
			close_and_exit(info, fd, line, "Invalid map format");
		while (ft_isdigit(line[i]))
			i++;
		while ((line[i] == ',' || ft_isalnum(line[i])) && line[i])
			i++;
		while (ft_isspace(line[i]))
			i++;
		if (line[i] != '\0' && !ft_isdigit(line[i]) && line[i] != '-')
			close_and_exit(info, fd, line, "Invalid item in map");
	}
	return (abs_count);
}

void	read_map_info(t_info *info)
{
	t_gnl	gnl;

	gnl.line = NULL;
	gnl.fd = fdf_open_file(info, info->filename);
	gnl.ret = get_next_line(gnl.fd, &gnl.line);
	if (gnl.ret == -1)
		close_and_exit(info, gnl.fd, gnl.line, "Memory allocation error");
	while (gnl.ret == 1)
	{	
		check_values(info, gnl);
		info->ord_count++;
		if (info->abs_count != 0
			&& info->abs_count != count_abs(info, gnl.fd, gnl.line))
			close_and_exit(info, gnl.fd, gnl.line, "Invalid map widths");
		info->abs_count = count_abs(info, gnl.fd, gnl.line);
		ft_free(gnl.line);
		gnl.ret = get_next_line(gnl.fd, &gnl.line);
		if (gnl.ret == -1)
			close_and_exit(info, gnl.fd, gnl.line, "Memory error");
	}
	ft_free(gnl.line);
	close(gnl.fd);
}
