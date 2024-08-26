/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 01:06:11 by padam             #+#    #+#             */
/*   Updated: 2024/08/25 19:28:55 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief frees an array of inodes
 */
void	inodes_free(t_inode **inodes)
{
	while (*inodes)
	{
		free(*inodes);
		inodes++;
	}
	free(inodes);
}

/**
 * @brief allocates new `t_dir_tmp` struct, adds the name and prepends it to the linked list
 * @return link to the new struct
 */
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

/**
 * @brief gathers info fo the inodes and prints everything
 * @return `0` on success, `1` on error
 */
int	inodes_to_print(char *path, t_inode **inodes, t_flags *flags)
{
	char	**entries;
	long	blocks;
	char	*blocks_str;

	//sort
	decide_sorting(inodes, flags);
	entries = inode_arr_to_string_arr(inodes, &blocks, flags);
	//WHY IS IT DOUBLE THE SIZE??
	blocks_str = ft_ltoa(blocks / 2);
	print_group(path, entries, blocks_str, flags);
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
		if (flags->a || dirent->d_name[0] != '.')
		{
			i++;
			name_lst = store_name(dirent->d_name, name_lst);
		}
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
