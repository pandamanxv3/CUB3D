/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:36:26 by aboudjel          #+#    #+#             */
/*   Updated: 2021/11/25 13:36:26 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

/* ENV LISTE CHAINEE */

typedef struct s_env
{
	char			*var;
	char			*val;
	struct s_env	*next;
}	t_env;

/* GARBAGE COLLECTOR */

typedef struct s_node
{
	void			*data;
	struct s_node	*next;
}t_gc;

int		ft_atoi(char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strlen(char *str);
int		ft_strncmp(char *str1, char *str2, size_t length);
int		ft_strcmp(char *s1, char *s2);
int		ft_memcmp(void *p1, void *p2, size_t size);

void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_bzero(void *ptr, size_t n);
void	ft_striteri(char *s, void (*f)(int, char*));
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);

void	*ft_calloc( size_t n, size_t size);
void	*ft_memcpy(void *dst, void *src, size_t size);
void	*ft_memmove(void *dest, void *src, size_t size);
void	*ft_memset(void *pointer, int value, size_t count);
void	*ft_memchr(void *src, int c, size_t size);

char	*ft_itoa(int nb);
char	*ft_strchr(char *string, int c);
char	*ft_strdup(char *src);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strmapi(char *s, char (*f)(int, char));
char	*ft_strnstr(char *big, char *little, size_t len);
char	*ft_strrchr(char *string, int c);
char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char *s, int start, size_t len);

size_t	ft_strlcat(char *dest, char *src, size_t size);
size_t	ft_strlcpy(char *dst, char *src, size_t size);

// gnl 

char	*ft_strjoingnl(char *s1, char *s2);
int		ft_checkendofline(char *buffer_save);
char	*ft_print_line(char *buffer_save);
char	*ft_get_buffer_save(char *buffer_save);
char	*ft_read(int fd, char *buffer_read);
char	*get_next_line(int fd);

// split

char	**ft_dispatchsplit(char *str, char c, t_gc *gc);
char	**ft_dispatchsplit2(char *str, char *c, t_gc *gc);
int		comparaison(char c, char *src);

// garbage collector 

void	*malloc_int(int size, char *errormsg, t_gc *mallocs);
void	*malloc_str(int size, char *errormsg, t_gc *mallocs);
void	ft_free(t_gc	*lst);
void	*ft_malloc(char *type, int size, char *msg, t_gc *lst);
void	ft_gcadd_back(t_gc *lst, t_gc *new);
void	ft_gcclear(t_gc *lst);
t_gc	*ft_gcnew(void *data, t_gc *lst);
void	ft_error(t_gc *gc, char *msg);
void	*malloc_env(char *errormsg, t_gc *mallocs);

/* 
 -init le gc avec gc = ft_gcnew(NULL, NULL);
 -puis ft_malloc(type de variable, taille, msg derror,et le gc) a chaque fois que
  besoin de malloc.
 -creer des sous categorie de malloc si besoin.
 -utiliser mallocreturn_failed pour securiser un malloc externe et ne pas
 oublier de l'ajouter ensuite en faisant ft_gcadd_back(gc, ft_gcnew(DATA,gc));
*/

#endif