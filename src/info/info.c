/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 07:18:34 by padam             #+#    #+#             */
/*   Updated: 2024/08/13 19:59:57by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief writes the info from the inode into a string array, also sets flags->column_width
 * @return
*/
char	**get_string_long(t_inode *inode, t_flags *flags)
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
	return(columns);
}

int	columns_join(char ***entries, t_flags *flags)
{
	int	i;
	int		total_length;
	char	*tmp;
	int		diff;

	i = 0;
	total_length = 0;
	while (i < 10)
		total_length += flags->column_width[i++] + 1;
	while (*entries)
	{
		i = 0;
		tmp = ft_calloc(total_length, 1);
		if (!tmp)
			return (1);
		while ((*entries)[i])
		{
			diff = ft_abs_int(flags->column_width[i]) - ft_strlen((*entries)[i]);
			if (flags->column_width[i] < 0 && diff > 0)
				while (diff--)
					ft_strlcat(tmp, " ", total_length);
			ft_strlcat(tmp, (*entries)[i], total_length);
			free((*entries)[i]);
			if (flags->column_width[i] > 0 && diff > 0)
				while (diff--)
					ft_strlcat(tmp, " ", total_length);
			ft_strlcat(tmp, " ", total_length);
			i++;
		}
		free(*entries);
		*entries = (char **)tmp;
		entries++;
	}
	return (0);
}

char	**inode_arr_to_string_arr(t_inode **inodes, long *blocks, int no_directories, t_flags *flags)
{
	char	**entries;
	char	***gathered_entries;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (inodes[j])
	{
		if (!inodes[j]->error && !(no_directories && S_ISDIR(inodes[j]->st.st_mode)))
			i++;
		j++;
	}
	if (!i)
		return (NULL);
	if (flags->l)
	{
		gathered_entries = ft_calloc(i+1, sizeof(char **));
		if (!gathered_entries)
			return (err(), NULL);
	}
	else
	{
		entries = ft_calloc(i + 1, sizeof(char *));
		if (!entries)
			return (err(), NULL);
	}
	j = 0;
	i = 0;
	if (blocks)
		*blocks = 0;
	while (inodes[j])
	{
		if (!inodes[j]->error && !(no_directories && S_ISDIR(inodes[j]->st.st_mode)))
		{
			if (blocks)
				*blocks += inodes[j]->st.st_blocks;
			if (flags->l)
				gathered_entries[i] = get_string_long(inodes[j], flags);
			else
				entries[i] = ft_strdup(inodes[j]->name);
			i++;
		}
		j++;
	}
	if (flags->l)
	{
		entries = (char **)gathered_entries;
		columns_join(gathered_entries, flags);
		// while (entries[i])
			// entries[i] = ft_arrjoin(gathered_entries[i++], " ");
	}
	return (entries);
}

/**
 * @brief fills a inode struct with the info for the path
 * @return the populated stucture, `NULL` on failure
*/
t_inode	*path_to_inode(char *path, char *name)
{
	t_inode 	*inode;

	inode = ft_calloc(1, sizeof(t_inode));
	if (!inode)
		return (err(), NULL);
	inode->error = false;
	inode->name = name;
	inode->path = ft_path_append(path, name);
	if (!inode->path)
	{
		err();
		// free(inode->name);
		return (NULL);
	}
	if (lstat(inode->path, &inode->st) == -1)
	{
		file_not_found(inode->path);
		inode->error = true;
		// free(inode->name);
		// free(inode->path);
		// return (NULL);
	}
	return (inode);
}
