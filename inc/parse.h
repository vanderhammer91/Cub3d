#ifndef PARSE_H
# define PARSE_H

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include "struct.h"


typedef struct s_parsed_data
{
    char    			*north_texture;
    char    			*south_texture;
    char    			*west_texture;
    char    			*east_texture;
    int     			floor_r;
    int     			floor_g;
    int     			floor_b;
    int     			ceiling_r;
    int     			ceiling_g;
    int     			ceiling_b;
    char    			**map;
	int					starting_x;
	int					starting_y;
	enum e_wall_type	starting_dir;
}   t_parsed_data;

typedef struct s_direction_and_string
{
    enum e_wall_type    dir;
    char                *str;
}   t_direction_and_string;

typedef struct s_char_and_rgb
{
    char    c;
    int     r;
    int     g;
    int     b;
}   t_char_and_rgb;

typedef struct s_coord
{
    int x;
    int y;
}   t_coord;

t_parsed_data	*file_to_data(char *file_name);
void			debug_print_parsed_data(t_parsed_data *data);
void			delete_parsed_data(t_parsed_data *d);

#endif
