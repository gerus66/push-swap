/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 12:14:01 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/17 12:09:50 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 10

int				get_next_line(const int fd, char **line);

size_t			ft_strlen(const char *s);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
int				ft_atoi(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_power(int nb, int power);
char			*ft_strtrim(char const *s);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strnew(size_t size);
char			*ft_itoa(int n);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strdup(const char *s1);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *hayst, const char *needl, size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			**ft_strsplit(char const *s, char c);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_memdel(void **ap);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_bzero(void *s, size_t n);
void			*ft_memalloc(size_t size);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

typedef struct	s_vector
{
	void	*cont;
	size_t	v_size;
	size_t	len;
	ssize_t	offset;
}				t_vector;

t_vector		*ft_vnew(t_vector **v, size_t v_size);
t_vector		*ft_vadd(t_vector *v, void *cont, size_t c_size);
t_vector		*ft_vresize(t_vector *v);
void			*ft_vreset(t_vector *v);
void			ft_vprint(t_vector v);

typedef struct	s_avltree
{
	int					key;
	void				*item;
	size_t				item_s;
	unsigned char		h;
	struct s_avltree	*left;
	struct s_avltree	*right;
}				t_avltree;

t_avltree		*ft_tree_newnode(int key, void const *item, size_t item_s);
t_avltree		*ft_tree_delnode(t_avltree *root, int key);
void			*ft_tree_search(t_avltree *root, int key);
void			ft_tree_putnode(void *node);
void			ft_tree_infix(t_avltree *root, void (*apply)(void *));
void			ft_tree_insert(t_avltree **r, int key, void const *item,
		size_t item_s);
void			ft_tree_balance(t_avltree **r);
void			ft_tree_print(t_avltree *tr, int digits);

#endif
