#include "parse.h"
#include "raw_utils.h"

size_t	get_line_width(char *str)
{
	size_t	width;

	width = ft_strlen(str);
	while (str[width] == ' ')
	{
		width--;
	}
	return (width);
}

size_t	get_filewidth(char *str)
{
	int		fd;
	char	*line;
	size_t	max_width;
	size_t	line_width;

	max_width = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			break ;
		}
		line_width = get_line_width(line);
		if (line_width > max_width)
		{
			max_width = line_width;
		}
	}
	return (max_width);
}

void	print_char_table(char **dat)
{
	while (*dat)
	{
		printf("line is: <%s>\n", *dat);
		dat++;
	}
	printf("done printing block\n");
}

char	**file_to_block(char *file_name)
{
	int		fd;
	char	**result;
	size_t	width;
	char	*line;
	size_t	i;

	result = malloc(sizeof (char *) * get_fileheight(file_name + 1));
	if (!result)
	{
		return (NULL);
	}
	width = get_filewidth(file_name);
	if (width == 0)
	{
		// error handle
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		// error handle
	}
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			break ;
		}
		result[i] = malloc(sizeof (char) * width + 1);
		if (result[i] == NULL)
		{
			// clean up and exit
		}
		ft_strlcpy(result[i], line, width + 1);
		memset(&result[i][ft_strlen(line) - 1], ' ', width - ft_strlen(line) + 1);
		result[i][width] = '\0';
		free(line);
		i++;
	}
	result[i] = NULL;
	print_char_table(result);
	return (result);
}
