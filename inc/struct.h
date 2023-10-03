/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:23:24 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/03 14:19:28 by ivanderw         ###   ########.fr       */
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
	UNSET
};

typedef struct s_bound {
    t_point 			start;
    t_point 			end;
	enum e_wall_type	direction;
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
}	t_keys;

typedef struct s_game
{ 
	void	*mlx;
	void	*mlx_win;
	void	*img;
	int		w_height;
	int		w_width;
	int		prev_x;
	int		frame;
	char	**raw;
	void	*north_texture;
	void	*east_texture;
	void	*south_texture;
	void	*west_texture;
	void	*door_texture;
	void	*gun_texture;
	void	*e_texture;
	int		door_state;
	int		true_state;
	char	*door_path;
	char	*door_frame[22];
	enum	e_wall_type	closest_wall_dir;
	int		closest_wall_index;
	float	pt_dist;
	int		close_index;
	t_bound	*closest_wall;
	int		skycolour;
	int		floorcolour;
//	int	map_height;
//	int	map_width;

	t_bound	**walls;
	int num_walls;
	t_player player;
	t_keys keys;
}	t_game;

#endif
