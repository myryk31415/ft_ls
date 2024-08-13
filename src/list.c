/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 01:06:11 by padam             #+#    #+#             */
/*   Updated: 2024/08/11 07:16:55 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir_tmp	*store_name(char *name, t_dir_tmp *lst)
{
	t_dir_tmp *new;

	new = ft_calloc(1, sizeof(t_dir_tmp));
	if (!new)
		return(err(), NULL);
	new->name = ft_strdup(name);
	new->next = lst;
	return (new);
}

int	list_directory(char *path, t_flags *flags)
{
	DIR 			*dir;
	struct dirent	*dirent;
	t_dir_tmp		*name_lst;
	int				i;

	i = 0;
	name_lst = NULL;
	dir = opendir(path);
	dirent = readdir(dir);
	while (dir)
	{
		i++;
		name_lst = store_name(dirent->d_name, name_lst);
		dirent = readdir(dir);
	}
	closedir(dir);
	// get all files from node

	//sort

	//print

	//if -R call list folder on all folders
	return (0);
}

// int	list_inodes(char *path)
// {
// 	// DIR *dir;
// 	struct stat st;

// 	if (stat(path, &st) == -1)
// 		err();
// 	if (S_ISDIR(st.st_mode))
// 		ft_putendl("dir");
// 	ft_printf("%u\n", st.st_ino);
// 	// dir = opendir(path);
// 	// if (!dir)
// 	// 	err();
// 	return (0);
// }
