/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 07:18:34 by padam             #+#    #+#             */
/*   Updated: 2024/08/13 06:52:11 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char *get_string_long(t_inode *inode, t_flags *flags)
{
	(void)inode;
	(void)flags;
	return("");
}

char	*inode_to_string(t_inode *inode, t_flags *flags)
{
	if (flags->l || flags->g)
		return (get_string_long(inode, flags));
	return(inode->name);
}

t_inode	*path_to_inode(char *path, char *name)
{
	t_inode 	*inode;

	inode = ft_calloc(1, sizeof(t_inode));
	if (!inode)
		return (err(), NULL);
	inode->name = name;
	if (stat(name, &inode->st) == -1)
	{
		err();
		free(inode->name);
		return (NULL);
	}
	inode->path = ft_path_append(path, name);
	if (!inode->path)
	{
		err();
		free(inode->name);
		return (NULL);
	}
	return (inode);
}

