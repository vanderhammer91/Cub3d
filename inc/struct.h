/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:23:24 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/09 21:20:30 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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

typedef struct s_keys
{
	int	u_key_down;
	int	d_key_down;
	int	l_key_down;
	int	r_key_down;
	int	sh_key_down;
	int	sp_key_down;
	int	e_key_down;
	int	l_rot_key_down;
	int	r_rot_key_down;
	int	enter_key_down;
}	t_keys;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_bound
{
	t_point				start;
	t_point				end;
	enum e_wall_type	type;
	enum e_wall_texture	texture;
	int					index;
	int					is_active;
	int					is_vert;
	int					door_state;
	int					img_state;
	struct s_bound		*next;
}	t_bound;

typedef struct s_ray
{
	t_point	pos;
	double	rot;
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

typedef struct s_bvertices
{
	int	s_x;
	int	s_y;
	int	e_x;
	int	e_y;
}	t_bvertices;

typedef struct s_parsed_data
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceiling_r;
	int		ceiling_g;
	int		ceiling_b;
	char	**map;
}	t_parsed_data;

typedef struct s_type_and_string
{
	enum e_wall_type	dir;
	char				*str;
}	t_type_and_string;

typedef struct s_char_and_rgb
{
	char	c;
	int		r;
	int		g;
	int		b;
}	t_char_and_rgb;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

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

typedef struct s_cast_handler
{
	double	radians;
	float	x1;
	float	y1;
	float	x2;
	float	y2;
	float	x3;
	float	y3;
	float	x4;
	float	y4;
	float	denominator;
	float	t;
	float	u;
}	t_cast_handler;

typedef struct s_cast
{
	t_ray	this_ray;
	t_point	closest;
	t_point	second_closest;
	t_bound	*closest_wall;
	t_bound	*second_closest_wall;
	float	pt_dist;
	float	second_pt_dist;
	float	max_dist;
	float	second_max_dist;
	double	ray_angle;
	int		has_collided;
	int		i;
	int		j;
}	t_cast;

typedef struct s_projection
{
	int		y;
	int		start_y;
	float	ty;
	float	ty_step;
	float	tx;
	int		x_offset;
	int		y_offset;
	int		cw;
	int		pixel_colour;
	int		img_state;
	int		alpha;
	t_point	start;
	t_point	end;
}	t_projection;

typedef struct s_param
{
	float	raylength;
	int		i;
	int		ray_x;
	int		ray_y;	
}	t_param;

typedef struct s_texture_lib
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
	void				*mlx;
	void				*mlx_win;
	void				*img;
	char				**raw;
	int					w_height;
	int					w_width;
	int					map_height;
	int					map_width;
	int					prev_x;
	int					frame;
	int					speed;
	int					msg_width;
	int					msg_height;
	int					game_state;
	int					door_state;
	int					ad_state;
	int					true_state;
	int					splash_state;
	int					cwi;
	int					close_index;
	int					skycolour;
	int					floorcolour;
	int					gun_state;
	int					num_walls;
	float				pt_dist;
	enum e_wall_type	closest_wall_dir;
	t_bound				*closest_wall;
	t_bound				**walls;
	t_parsed_data		*parsed_data;
	t_texture_lib		t_lib;
	t_player			player;
	t_keys				keys;
}	t_game;

#endif
