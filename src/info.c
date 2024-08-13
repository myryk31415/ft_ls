/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 07:18:34 by padam             #+#    #+#             */
/*   Updated: 2024/08/13 03:10:47 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*inode_to_string(t_inode *inode)
{
	int i=1;while(i<4)i++;printf("%i",i);

	
}

t_inode	*path_to_inode(char *path, char *name)
{
	t_inode 	*inode;

	inode = ft_calloc(1, sizeof(t_inode));
	if (!inode)
		return(err(), NULL);
	inode->name = name;
	inode->path = ft_path_append(path, name);
	if (stat(name, &inode->st) == -1)
	{
		err();
		free(inode->name);
		return (NULL);
	}
	return (inode);
}

