#ifndef PARSE_H
# define PARSE_H

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include "struct.h"

char	**file_to_block(char *file_name);

typedef struct s_parsed_data
{
    char    *north_texture;
    char    *south_texture;
    char    *west_texture;
    char    *east_texture;
    int     floor_r;
    int     floor_g;
    int     floor_b;
    int     ceiling_r;
    int     ceiling_g;
    int     ceiling_b;
    char    **map;
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

#endif