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
char	*get_string_long(t_inode *inode, t_flags *flags)
{
	char	*columns[10];
	char	*joined_string;
	int		i;
	int		len;

	i = 0;
	columns[i++] = get_rights(inode);
	// TODO error
	columns[i++] = ft_ultoa(inode->st.st_nlink);
	if (!flags->g)
		columns[i++] = get_user(inode);
	columns[i++] = get_group(inode);
	columns[i++] = ft_ltoa(inode->st.st_size);
	columns[i++] = get_date(inode, flags);
	columns[i++] = inode->name;
	columns[i] = NULL;
	while (i--)
	{
		len = ft_strlen(columns[i]);
		if (len > flags->column_width[i])
			flags->column_width[i] = len;
	}
	joined_string = ft_arrjoin(columns, " ");
	// while(i < 10)
	// 	free(columns[i++]);
	return(joined_string);
}

/**
 * @brief gets name/information depending on flag from inode
 * @return a string containing the necessary information for the entry
 */
char	*inode_to_string(t_inode *inode, t_flags *flags)
{
	if (flags->l || flags->g)
		return (get_string_long(inode, flags));
	return(inode->name);
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
	inode->name = name;
	inode->path = ft_path_append(path, name);
	if (!inode->path)
	{
		err();
		// free(inode->name);
		return (NULL);
	}
	if (stat(inode->path, &inode->st) == -1)
	{
		err();
		// free(inode->name);
		// free(inode->path);
		return (NULL);
	}
	return (inode);
}
