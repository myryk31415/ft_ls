/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:37:52 by padam             #+#    #+#             */
/*   Updated: 2024/08/10 07:36:45 by padam            ###   ########.fr       */
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

typedef struct flags
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
} t_flags;

typedef struct inode
{
	char *path;
	struct stat st;
} t_inode;

void	init_flags(t_flags *flags);
char	**parse_arguments(char **argv, t_flags *flags);
int		list_entity(char *path);

//utils
void	err(void);
#endif
