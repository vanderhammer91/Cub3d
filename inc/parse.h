#ifndef PARSE_H
# define PARSE_H

# include "libraries.h"
#include "raw_utils.h"

t_parsed_data	*file_to_data(char *file_name);
void			debug_print_parsed_data(t_parsed_data *data);
void			delete_parsed_data(t_parsed_data *d);

#endif
