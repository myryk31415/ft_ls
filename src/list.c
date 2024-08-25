/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 01:06:11 by padam             #+#    #+#             */
/*   Updated: 2024/08/25 03:44:20 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	inodes_free(t_inode **inodes)
{
	while (*inodes)
	{
		free(*inodes);
		inodes++;
	}
	free(inodes);
}

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

int	inodes_to_print(char *path, t_inode **inodes, t_flags *flags)
{
	char	**entries;
	int		i;

	i = 0;
	while (inodes[i])
		i++;
	entries = ft_calloc(i + 1, sizeof(char *));
	if (!entries)
		return (err(), 1);

	//sort
	decide_sorting(inodes, flags);
	//get info
	i = 0;
	while (inodes[i])
	{
		entries[i] = inode_to_string(inodes[i], flags);
		if (!entries[i])
		{
			while (i--)
				free(entries[i]);
			free(entries);
			return (1);
		}
		i++;
	}
	//print
	print_group(path, entries, flags);
	//if -R call list folder on all folders
	if (!flags->R)
		return (0);
	while(*inodes)
	{
		if (S_ISDIR((*inodes)->st.st_mode) && ft_strcmp((*inodes)->name, ".") && ft_strcmp((*inodes)->name,".."))
			if (list_directory((*inodes)->path, flags) == -1)
				return (-1);
		inodes++;
	}
	return(0);
}

/**
 * @brief gets all the inodes of a directory and lists them
 * @return `0` on success, `1` on failure
*/
int	list_directory(char *path, t_flags *flags)
{
	DIR 			*dir;
	struct dirent	*dirent;
	t_dir_tmp		*name_lst;
	t_dir_tmp		*tmp;
	int				i;
	t_inode			**inodes;

	i = 0;
	name_lst = NULL;
	dir = opendir(path);
	if (!dir)
		return (err(), 1);
	dirent = readdir(dir);
	while (dirent)
	{
		i++;
		name_lst = store_name(dirent->d_name, name_lst);
		dirent = readdir(dir);
	}
	// gotta free name_lst as well
	closedir(dir);
	inodes = ft_calloc(i + 1, sizeof(t_inode *));
	if (!inodes)
		return(err(), 1);
	while (i--)
	{
		inodes[i] = path_to_inode(path, name_lst->name);
		// if (!inodes[i])
		// 	return (inodes_free(inodes + i), 1);
		tmp = name_lst;
		name_lst = name_lst ->next;
		free(tmp);
	}
	if (inodes_to_print(path, inodes, flags) == -1)
		return (-1);
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
