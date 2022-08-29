/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 05:01:40 by aboudjel          #+#    #+#             */
/*   Updated: 2022/08/29 07:06:54 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

typedef enum e_parsing_types
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
}	t_parsing_types;

static char	*param[] = { //passe pas a la norme faudrait init a la main
	"NO", "SO", "WE", "EA", "F", "C", NULL
};

static char	map_char[] = {//passe pas a la norme faudrait init a la main
	'0', '1', 'N', 'S', 'E', 'W', '\0'
};

static char	map_char2[] = {//passe pas a la norme faudrait init a la main
	'0', 'N', 'S', 'E', 'W', '\0'
};

static const char	white_space[] = {//passe pas a la norme faudrait init a la main
	' ', '\t', '\v', '\f', '\r', '\n', '\0'
};

typedef struct s_parsing //jme sers de ca pour parser et je navigue dans ces 2 tab avec le enum plus haut
{
	int		bool_parsing[6]; //savoir si on a rencontrer chaque element
	char	**str_parsing; //stocker les texture/couleur trouver apres NO,SO,WE,EA,F,C
}	t_parsing;

typedef struct s_map //une fois que tout est clean jmet la map les couleur et les xpm dedans
{
	char	**map;
	int		*floor_color;
	int		*ceiling_color;
	char	*wall_path[4];
}	t_map;

typedef struct s_global
{
	char		*path; //le path du file rentre en parametre
	int			nb_of_line; //nb de ligne du file
	char		**file; //le contenu du file
	t_gc		*gc; // la garbage collector (trouvable dans la libft)
	int			xp_position; //position x du joueur au depart, a mettre peut etre dans une struct dedie au mouvement/exec
	int			yp_position; //position x du joueur au depart, a mettre peut etre dans une struct dedie au mouvement/exec
	t_parsing	parsing; //struct qui sert durant le parsing
	t_map		map; //struct des donnes parsee de la map
}	t_global;

/* ******************* PARSING ******************* */

void	parsing(t_global *general, char *path);

/* ------------- 1) get param and map ------------ */

void	get_tab_malloc(t_global *general);
void	get_file(t_global *general);
void	checking_file_name(char *path);
void	ft_init_struct(t_global *g, char *path);

/* ------------- 2) get param and map ------------- */

void	copying_line(t_global *general, char *str, int j);
void	checking_each_line(t_global *general, char *str, int i, int j);
int		size_map(t_global *general, int i);
void	get_map(t_global *general, int i);
void	get_param_and_map(t_global *general, int i, int j, int k);

/* ---------------- 3) parsing map --------------- */

void	first_map_parsing(t_global *general);
void	checking_map_line(t_global *g, int i, int j, int len_map);
void	checking_player(t_global *general, int i, int j, int is_present);
void	parsing_map(t_global *g);

/* ------------ 4) are params correct ------------ */

int		is_file_xpm(t_global *general);
int		is_texture_unique(t_global *general);
int		*is_color_correct(t_global *g, int to_color);
void	are_params_correct(t_global *general);

/* -------------------- utils -------------------- */

int		val_charset_cmp(char *to_find, char *str, int length);
int		before_map(t_global *general, int i);
int		charset(char c, char *str);

/* ******************* EXECUTION ******************* */

void	execution(t_global *general);

#endif