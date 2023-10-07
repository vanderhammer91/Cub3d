#ifndef PARSE_H
# define PARSE_H

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include "struct.h"

t_parsed_data	*file_to_data(char *file_name);
void			delete_parsed_data(t_parsed_data *d);

//parse1.c
void			debug_print_parsed_data(t_parsed_data *data);
void			debug_print_char_array(char **arr);

//parse2.c
t_parsed_data	*new_parsed_data(void);
void			delete_parsed_data(t_parsed_data *d);
void			free_char_array(char **arr);
size_t			arr_len(char **arr);
char			**ft_realloc(char **ptr, size_t old, size_t new);

//parse3.c
t_direction_and_string	line_to_texture_data(char *line);
int						is_valid_line_texture(char *line);

//parse4.c
int						can_poke_texture_data(t_parsed_data *data, t_direction_and_string pair);
void					poke_texture_data(t_parsed_data *data, t_direction_and_string pair);

//parse5.c
int						is_valid_line_colour(char *line);
t_char_and_rgb			line_to_colour_data(char *line);
int						can_poke_colour_data(t_parsed_data *data, t_char_and_rgb rgb);
void					poke_colour_data(t_parsed_data *data, t_char_and_rgb rgb);

#endif
