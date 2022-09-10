/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 05:01:40 by aboudjel          #+#    #+#             */
/*   Updated: 2022/09/10 02:10:43 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H



# include <mlx.h>
# include <mlx_int.h> 
# include <math.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stddef.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h> 
# include <limits.h>
# include "../libft/include/libft.h"

# define ERR_ARGC "ERROR: CUB3D PARAMETER SHOULD BE A FONCTIONAL .cub FILE"
# define ERR_MALL "ERROR: ONE OF THE MALLOCS HAS FAILED"
# define ERR_PATH "ERROR: INVALID PATH"
# define ERR_HALF_MAP "ERROR: THERE IS EMPTY LINE WITHIN THE MAP"
# define ERR_NO_MAP "ERROR: THERE IS NO MAP OR ITS NOT VALID"
# define ERR_MAP "ERROR: THE MAP IS NOT SURROUNDED BY WALL OR THE PLAYER IS \
OUTSIDE THE MAP"
# define ERR_MAP2 "ERROR: THE MAP CAN CONTAIN ONLY: 1, 0, N, S, W AND E"
# define ERR_POS "ERROR: TOO MANY START POSITION FOR THE PLAYER"
# define ERR_POS2 "ERROR: NO START POSITION FOR THE PLAYER"
# define ERR_COLOR "ERROR: WRONG COLOR FORMAT"
# define ERR_TWICE "ERROR: A TEXTURE CANNOT BE USED TWICE"
# define ERR_XPM "ERROR: THE TEXTURE SHOULD BE A .xpm FILE"
# define ERR_DIR "ERROR: FILE IS EMPTY OR IT'S A DIRECTORY"
# define ERR_DOUBLE "ERROR: ONE OF THE PARAMETERS APPEARS TWICE"
# define ERR_MISSING "ERROR: ONE OF THE PARAMETERS OR MORE IS MISSING"
# define ERR_BEHIND "ERROR: ONLY WHITE SPACE IS ALLOW BEHIND THE MAP"

# define BLUE 0x4400CC
# define RED 0xEE1122
# define PURPLE 0x31125A
# define YELLOW 0xF7FB4B
# define GREEN 0x388A73
# define PINK 0xF4BBCC
# define ORANGE 0xFF9738
# define WHITE 0xFFFFFF
# define BLACK 0x000000

// mlx_get_screen_size pour recuperer la taille de l'ecran
# define WIDTH 1080
# define HEIGHT 720

# define PI 3.14159265
# define TXT_SIZE 64
# define DEGREE 0.0174532925
# define SPEED 10
# define FOV 60
// RAY = FOV / WIDTH : il s'agit de l'ecart entre 2 rayons
# define RAY 0.055555556



typedef enum e_hit_side
{
	N,
	S,
	E,
	W,
}	t_hit_side;

typedef struct s_ray
{
	float			distance;
	float			x;
	float			y;
	float			x_v;
	float			y_v;
	float			x_h;
	float			y_h;
	t_hit_side		hit;
	int				num;
	float			angle;
	float			fov;
}	t_ray;

typedef enum e_parsing_types
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
}	t_parsing_types;

typedef enum e_direction
{
	NW,
	NE,
	SE,
	SW,
}	t_direction;

typedef enum e_keycode {
	UP = 119,
	DOWN = 115,
	LEFT = 97,
	RIGHT = 100,
	ESCAPE = 65307,
	LEFT_ARROW = 65361,
	RIGHT_ARROW = 65363
}				t_keycode;

typedef struct s_parsing
{
	char	**map;
	char	**e_map;
	int		bool_parsing[6];
	char	**str_parsing;
	char	**param;
	char	map_char[7];
	char	map_char2[6];
	char	white_space[7];
}	t_parsing;

typedef struct s_player
{
	float	x;
	float	y;
	float	next_x;
	float	next_Y;
	double	angle;
}	t_player;

typedef struct s_map
{
	int				hauteur;
	int				largeur;
	char			**map;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	void	*north_texture;
	void	*west_texture;
	void	*east_texture;
	void	*south_texture;
}	t_map;


typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*frame_buf;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_mlx;



typedef struct s_global
{
	char		*path;
	int			nb_of_line;
	char		**file;
	t_gc		*gc;
	t_mlx		mlx;
	t_parsing	parsing;
	t_player	player;
	t_map		map;
	float		decalage_x;
	float		decalage_y;
	int			current_input;
	int			last_input;
	int			pre_last_input;
}	t_global;

/* ******************* PARSING ******************* */

void	parsing(t_global *data, char *path);

/* ------------- 1) get param and map ------------ */

void	get_tab_malloc(t_global *data);
void	get_file(t_global *data);
void	checking_file_name(char *path);
void	ft_init_struct(t_global *data, char *path);
void	init_var(t_global *g, t_gc *gc);

/* ------------- 2) get param and map ------------- */

void	copying_line(t_global *data, char *str, int j);
void	checking_each_line(t_global *data, char *str, int i, int j);
int		size_map(t_global *data, int i);
void	get_map(t_global *data, int i);
void	get_param_and_map(t_global *data, int i, int j, int k);

/* ---------------- 3) parsing map --------------- */

void	first_map_parsing(t_global *data);
void	checking_map_line(t_global *data, int i, int j, int len_map);
void	checking_player(t_global *data, int i, int j, int is_present);
void	init_player_angle(t_global *data, char c);
void	parsing_map(t_global *data);

/* ------------ 4) are params correct ------------ */

int		is_file_xpm(t_global *data);
int		is_texture_unique(t_global *data);
unsigned int	is_color_correct(t_global *data, int to_color, int i, int count);
void	are_params_correct(t_global *data);

/* -------------------- utils -------------------- */

int		val_charset_cmp(char *to_find, char *str, int length, char *w_s);
int		before_map(t_global *data, int i);
int		charset(char c, char *str);

/* -------------------- expand_map_size -------------------- */

void	copy_to_expand(t_global *data, int i, int y, int index);
void	expand_map_size(t_global	*data);
int		malloc_new_map(t_global	*data);
int		fill_new_map(t_global *data, int size);
void	expand(t_global *data, int sizex, int sizey);

/* ******************* EXECUTION ******************* */

void	execution(t_global *data);

unsigned int	ft_get_pixel(int x, int y, void *img);
void			put_pixel_to_frame_buf(t_global *data, int x, int y, int color);
int				ft_screen(t_global *data);
float 			modulo(float value, float mod_value);

float 			conv_rad(float angle);

void	move_pos2(t_global *d, int c, int c2);
int				ft_useless(t_global *data);
void			ft_hooks(t_global *data);
void			ft_moves(t_global *data);
int				key_hook(int keycode, t_global *data);

void	ft_destroy_mlx(t_global *data);


int	my_keyrelease_func(int keycode, t_global *data);





void 			put_cercle(t_global *data, int x, int y, int color);
unsigned int	rgb_to_int(unsigned int r, unsigned int g, unsigned int b);

#endif