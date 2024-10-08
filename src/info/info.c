/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 07:18:34 by padam             #+#    #+#             */
/*   Updated: 2024/09/03 01:31:08 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	reset_width(t_flags *flags)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		flags->column_width[i] = 0;
		i++;
	}
}

/**
 * @brief writes the info from the inode into a string array,
 * also sets flags->column_width
*/
char	**get_info_long(t_inode *inode, t_flags *flags)
{
	char	**columns;
	int		i;
	int		len;

	i = 0;
	// TODO error
	columns = ft_calloc(10, sizeof(char *));
	columns[i++] = get_rights(inode);
	columns[i++] = ft_ultoa(inode->st.st_nlink);
	if (!flags->g)
		columns[i++] = get_user(inode);
	columns[i++] = get_group(inode);
	columns[i++] = ft_ltoa(inode->st.st_size);
	columns[i++] = get_date(inode, flags);
	columns[i++] = ft_strdup(inode->name);
	columns[i] = NULL;
	while (i--)
	{
		len = ft_strlen(columns[i]);
		if (len > flags->column_width[i])
			flags->column_width[i] = len;
	}
	// while(i < 10)
	// 	free(columns[i++]);
	return (columns);
}

/**
 * @brief takes the strings of the entry and
 * joins them with padding according to flags
 * @return joined string, `NULL` on error
 */
char	*entry_join(char **entry, int total_length, t_flags *flags)
{
	char	*tmp;
	int		diff;
	int		i;

	i = 0;
	tmp = ft_calloc(total_length, 1);
	if (!tmp)
		return (NULL);
	while (entry[i])
	{
		diff = ft_abs_int(flags->column_width[i]) - ft_strlen(entry[i]);
		if (flags->column_width[i] < 0 && diff > 0)
			while (diff--)
				ft_strlcat(tmp, " ", total_length);
		ft_strlcat(tmp, entry[i], total_length);
		if (flags->column_width[i] > 0 && diff > 0)
			while (diff--)
				ft_strlcat(tmp, " ", total_length);
		ft_strlcat(tmp, " ", total_length);
		free(entry[i]);
		i++;
	}
	free(entry);
	return (tmp);
}

/**
 * @brief takes the strings for each entry and
 * 2joins them with padding according to flags
 * @warning entries is reused for tmp, don't use it afterwards
 * @return the joined strings, `NULL` on error
 */
char	**columns_join(char ***entries, t_flags *flags)
{
	int		i;
	int		total_length;
	char	**tmp;

	tmp = (char **)entries;
	i = 0;
	total_length = 0;
	while (i < 10)
		total_length += flags->column_width[i++] + 1;
	i = 0;
	while (entries[i])
	{
		tmp[i] = entry_join(entries[i], total_length, flags);
		if (!tmp[i])
		{
			while (entries[i])
				string_arr_free(entries[i++]);
			i = 0;
			while (tmp[i])
				free(tmp[i++]);
			return (NULL);
		}
		i++;
	}
	return (tmp);
}

/**
 * @brief counts the number of inodes and allocates the pointer accordingly
 * @param blocks will be set to the total amount of blocks used by the inodes
 * @return allocated pointer, `NULL` on error
 */
char	**count_inodes(t_inode **inodes, long *blocks, int no_dirs)
{
	int		i;
	int		j;
	char	**ptr;

	if (blocks)
		*blocks = 0;
	j = 0;
	i = 0;
	while (inodes[j])
	{
		if (!inodes[j]->error && !(no_dirs && S_ISDIR(inodes[j]->st.st_mode)))
		{
			if (blocks)
				*blocks += (inodes[j]->st.st_blocks);
			i++;
		}
		j++;
	}
	if (!i)
		return (NULL);
	ptr = ft_calloc(i + 1, sizeof(char *));
	return (ptr);
}

/**
 * @brief takes the inodes and transforms the info into strings
 * @param blocks will be set to the sum of all blocks used, can be `NULL`
 * @param no_dirs if set all directories will be skipped
 * @return string array with the joined info for each inode
 */
char	**gather_info_from_inodes(t_inode **inodes, long *blocks,
			int no_dirs, t_flags *flags)
{
	char	**entries;
	char	***gathered_entries;
	int		i;

	entries = count_inodes(inodes, blocks, no_dirs);
	if (!entries)
		return (err(), NULL);
	gathered_entries = (char ***)entries;
	i = 0;
	while (*inodes)
	{
		if (!(*inodes)->error && !(no_dirs && S_ISDIR((*inodes)->st.st_mode)))
		{
			if (flags->l)
				gathered_entries[i] = get_info_long((*inodes), flags);
			else
				entries[i] = ft_strdup((*inodes)->name);
			i++;
		}
		inodes++;
	}
	if (flags->l)
		entries = columns_join(gathered_entries, flags);
	return (reset_width(flags), entries);
}

/**
 * @brief fills a inode struct with the info for the path
 * @return the populated stucture, `NULL` on error
*/
t_inode	*populate_inode(char *path, char *name)
{
	t_inode	*inode;

	inode = ft_calloc(1, sizeof(t_inode));
	if (!inode)
		return (err(), NULL);
	inode->error = false;
	inode->name = name;
	inode->path = ft_path_append(path, name);
	if (!inode->path)
	{
		err();
		free(inode->name);
		return (NULL);
	}
	if (lstat(inode->path, &inode->st) == -1)
	{
		inode->error = true;
		file_error(inode->path);
		free(inode->path);
		inode->path = NULL;
		free(inode->name);
		inode->name = NULL;
	}
	return (inode);
}
