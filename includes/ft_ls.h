/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:37:52 by padam             #+#    #+#             */
/*   Updated: 2024/08/13 03:03:59 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <dirent.h>
# include <sys/stat.h>
# include "../libft/includes/libft.h"

typedef struct s_flags
{
	bool a;
	bool d;
	bool f;
	bool g;
	bool l;
	bool u;
	bool r;
	bool R;
	bool t;
	bool show_foldername;
} t_flags;

typedef struct s_inode
{
	char		*path;
	char		*name;
	struct stat	st;
} t_inode;

typedef struct s_dir_tmp
{
	char 		*name;
	t_dir_tmp	*next;
} t_dir_tmp;

char	**parse_arguments(char **argv, t_flags *flags);

// info
t_inode	*path_to_inode(char *path, char *name);

// list
int		list_directory(char *path, t_flags *flags);
int		list_entity(char *path);

// print
void	print_group(char *folder_name, char **entries, t_flags *flags);

// sort
void	decide_sorting(t_inode *nodes, t_flags *flags);

// utils
void	err(void);

#endif
