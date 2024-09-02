/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:37:52 by padam             #+#    #+#             */
/*   Updated: 2024/09/03 01:20:56 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "../libft/includes/libft.h"

# define RECENT 15778476

typedef struct s_flags
{
	bool	a;
	bool	d;
	bool	f;
	bool	g;
	bool	l;
	bool	u;
	bool	r;
	bool	r_upper;
	bool	t;
	bool	first_entry;
	bool	show_foldername;
	int		column_width[10];
}	t_flags;

typedef struct s_inode
{
	char		*path;
	char		*name;
	struct stat	st;
	bool		error;
}	t_inode;

typedef struct s_dir_tmp
{
	char				*name;
	struct s_dir_tmp	*next;
}	t_dir_tmp;

// parser
int		parse_arguments(char **argv, t_flags *flags);

// free
void	inodes_free(t_inode **inodes, int start);
void	list_free(t_dir_tmp *list);
void	string_arr_free(char **arr);

// info
t_inode	*populate_inode(char *path, char *name);
char	**inode_to_string(t_inode *inode, t_flags *flags);
char	**gather_info_from_inodes(t_inode **inodes, long *blocks,
			int no_directories, t_flags *flags);

// long
char	*get_rights(t_inode *inode);
char	*get_user(t_inode *inode);
char	*get_group(t_inode *inode);
char	*get_date(t_inode *inode, t_flags *flags);

// list
int		inodes_list_directories(t_inode **inodes, int no_checks,
			t_flags *flags);
int		print_inodes(char *path, t_inode **inodes, t_flags *flags);
int		list_directory(char *path, t_flags *flags);

// print
void	print_group(char *folder_name, char **entries, char *blocks,
			t_flags *flags);

// sort
void	sort(t_inode **inodes, t_flags *flags);

// utils
void	err(void);
void	file_error(char *file);
void	dir_error(char *dir);

#endif
