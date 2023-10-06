/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:23:24 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 20:32:53 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_point
{
    float x;
    float y;
} t_point;

enum e_wall_type {
	EAST,
	WEST,
	NORTH,
	SOUTH,
	DOOR,
	EXIT,
	AD,
	UNSET
};

enum e_wall_texture {
	PILLAR,
	DEFAULT
};

typedef struct s_bound {
    t_point 			start;
    t_point 			end;
	enum e_wall_type	type;
	enum e_wall_texture	texture;
	int					index;
	int					is_active;
	int					is_vert;
	int					door_state;
	int					img_state;
	struct s_bound		*next;
} 						t_bound;

typedef struct s_vector
{
	float x;
	float y;
}	t_vector;

typedef struct s_ray
{
	t_point	pos;
	double rot;
}	t_ray;


typedef struct s_player
{
	t_ray	rays[70];
	t_point	pos;
	double	rot;
	int		rb;
	int		lb;
	int		ub;
	int		db;
}			t_player;

typedef struct s_keys
{
	int U_KEY_DOWN;
	int D_KEY_DOWN;
	int L_KEY_DOWN;
	int R_KEY_DOWN;
	int	SH_KEY_DOWN;
	int	SP_KEY_DOWN;
	int	E_KEY_DOWN;
	int L_ROT_KEY_DOWN;
	int R_ROT_KEY_DOWN;
	int	ENTER_KEY_DOWN;
}	t_keys;


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
}   t_parsed_data;

typedef struct s_type_and_string
{
    enum e_wall_type    dir;
    char                *str;
}   t_type_and_string;

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

typedef struct s_line
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_line;

typedef struct s_img_handler
{
	int	sprite_y;
	int	bpp;
	int	size_line;
	int	endian;
	int	colour;
	int	alpha;
	int	*texture_data;
	int	m_off;
	int	texture_y;
}	t_img_handler;

typedef	struct s_texture_lib
{
	void	*north_texture;
	void	*east_texture;
	void	*south_texture;
	void	*west_texture;
	void	*ad_texture;
	void	*door_texture;
	void	*e_texture;
	void	*exit_msg_texture;
	void	*exit_texture;
	void	*gun_texture;
	void	*pillar_texture;
	void	*title_texture;
}	t_texture_lib;

typedef struct s_game
{ 
	void	*mlx;
	void	*mlx_win;
	void	*img;

	char	**raw;
	char	*door_path;
	char	*door_frame[22];

	int		w_height;
	int		w_width;
	int		prev_x;
	int		frame;
	int		speed;
	int		msg_width;
	int		msg_height;
	int		game_state;
	int		door_state;
	int		ad_state;
	int		true_state;
	int		splash_state;
	int		cwi;
	int		close_index;
	int		skycolour;
	int		floorcolour;
	int		gun_state;
	int		num_walls;
	float	pt_dist;
	enum	e_wall_type	closest_wall_dir;
	t_bound	*closest_wall;
	t_bound	**walls;
	t_parsed_data	*parsed_data;
	t_texture_lib	t_lib;
	t_player		player;
	t_keys			keys;
}	t_game;



#endif
