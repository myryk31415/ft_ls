/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 01:06:11 by padam             #+#    #+#             */
/*   Updated: 2024/08/31 07:53:14 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		return (err(), NULL);
	}
	new->name = ft_strdup(name);
	if (!new->name)
	{
		list_free(lst);
		free(new);
		return (NULL);
	}
	new->next = lst;
	return (new);
}

/**
 * @brief calls `list_directory` on each directory inode
 * @param no_checks skips `.` and `..` name check
 * @return error status
 */
int	inodes_list_directories(t_inode **inodes, int no_checks, t_flags *flags)
{
	int	error;
	int	i;

	error = 0;
	i = 0;
	while(inodes[i])
	{
		if (!inodes[i]->error && S_ISDIR(inodes[i]->st.st_mode))
			if (no_checks || (ft_strcmp(inodes[i]->name, ".")
				&& ft_strcmp(inodes[i]->name, "..")))
				if (list_directory(inodes[i]->path, flags))
					error = 1;
		free(inodes[i]->name);
		free(inodes[i]->path);
		free(inodes[i]);
		i++;
	}
	free(inodes);
	return(error);
}

/**
 * @brief gathers info fo the inodes and prints everything
 * @param path the directory containing the inodes
 * @return `0` on success, `1` on error
 */
int	print_inodes(char *path, t_inode **inodes, t_flags *flags)
{
	char	**entries;
	long	blocks;
	char	*blocks_str;

	//sort
	sort(inodes, flags);
	entries = gather_info_from_inodes(inodes, &blocks, 0, flags);
	if (!entries)
		return (inodes_free(inodes, 0), 2);
	//WHY IS IT DOUBLE THE SIZE??
	blocks_str = ft_ltoa(blocks / 2);
	if (!blocks_str)
		return (string_arr_free(entries), inodes_free(inodes, 0), 2);
	if (entries)
		print_group(path, entries, blocks_str, flags);
	free(blocks_str);
	string_arr_free(entries);
	if (!flags->R || flags-> d)
		return (inodes_free(inodes, 0), 0);
	return (inodes_list_directories(inodes, 0, flags));
}

/**
 * @brief reads all entries of the directory stream of path, also sets count accordingly
 * @attention returned list is in reverse order
 * @return linked list with all the names, `NULL` on error
 */
t_dir_tmp	*read_dir(char *path, int *count, t_flags *flags)
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

	name_lst = read_dir(path, &count, flags);
	if (!name_lst)
		return (2);
	inodes = ft_calloc(count + 1, sizeof(t_inode *));
	if (!inodes)
	{
		list_free(name_lst);
		return(err(), 2);
	}
	while (count--)
	{
		inodes[count] = populate_inode(path, name_lst->name);
		if (!inodes[count])
			return (inodes_free(inodes, count), list_free(name_lst), 2);
		tmp = name_lst;
		name_lst = name_lst->next;
		free(tmp);
	}
	return (print_inodes(path, inodes, flags));
}
