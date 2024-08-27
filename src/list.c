/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 01:06:11 by padam             #+#    #+#             */
/*   Updated: 2024/08/27 06:12:50 by padam            ###   ########.fr       */
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
 * @brief frees the linked list
 */
void	list_free(t_dir_tmp *list)
{
	t_dir_tmp	*tmp;

	while (list)
	{
		tmp = list;
		free(list->name);
		list = list->next;
		free(tmp);
	}
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
	{
		list_free(lst);
		return(err(), NULL);
	}
	new->name = ft_strdup(name);
	new->next = lst;
	return (new);
}

int	inodes_list_directories(t_inode **inodes, int no_checks, t_flags *flags)
{
	int	error;

	error = 0;
	while(*inodes)
	{
		if (!(*inodes)->error && S_ISDIR((*inodes)->st.st_mode))
			if (no_checks || (ft_strcmp((*inodes)->name, ".")
				&& ft_strcmp((*inodes)->name, "..")))
				// list_directory((*inodes)->path, flags);
				if (list_directory((*inodes)->path, flags) == -1)
					error = 1;
		inodes++;
	}
	return(error);
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
	entries = inode_arr_to_string_arr(inodes, &blocks, 0, flags);
	//WHY IS IT DOUBLE THE SIZE??
	blocks_str = ft_ltoa(blocks / 2);
	print_group(path, entries, blocks_str, flags);
	if (!flags->R)
		return (0);
	return (inodes_list_directories(inodes, 0, flags));
}

/**
 * @brief reads all entries of the directory stream of path, also sets count accordingly
 * @attention returned list is in reverse order
 * @return linked list with all the names
 */
t_dir_tmp	*path_to_list(char *path, int *count, t_flags *flags)
{
	DIR 			*dir;
	struct dirent	*dirent;
	t_dir_tmp		*name_lst;

	*count = 0;
	name_lst = NULL;
	dir = opendir(path);
	if (!dir)
		return (file_not_found(path), NULL);
	dirent = readdir(dir);
	while (dirent)
	{
		if (flags->a || dirent->d_name[0] != '.')
		{
			(*count)++;
			name_lst = store_name(dirent->d_name, name_lst);
		}
		dirent = readdir(dir);
	}
	// gotta free name_lst as well
	if (closedir(dir) == -1)
		return (err(), NULL);
	return (name_lst);
}

/**
 * @brief gets all the inodes of a directory and lists them
 * @return `0` on success, `1` on failure
*/
int	list_directory(char *path, t_flags *flags)
{
	t_dir_tmp		*name_lst;
	t_dir_tmp		*tmp;
	int				count;
	t_inode			**inodes;

	name_lst = path_to_list(path, &count, flags);
	inodes = ft_calloc(count + 1, sizeof(t_inode *));
	if (!inodes)
		return(err(), 1);
	while (count--)
	{
		inodes[count] = path_to_inode(path, name_lst->name);
		// if (!inodes[i])
		// 	return (inodes_free(inodes + i), 1);
		tmp = name_lst;
		name_lst = name_lst->next;
		free(tmp);
	}
	return (inodes_to_print(path, inodes, flags));
}
