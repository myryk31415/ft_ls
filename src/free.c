/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 03:33:53 by padam             #+#    #+#             */
/*   Updated: 2024/08/31 06:43:18 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief frees an array of inodes
 */
void	inodes_free(t_inode **inodes, int start)
{
	if (!inodes)
		return ;
	while (inodes[start])
	{
		free(inodes[start]->name);
		free(inodes[start]->path);
		free(inodes[start]);
		start++;
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
		list = list->next;
		free(tmp->name);
		free(tmp);
	}
}

/**
 * @brief frees an char double pointer
 */
void	string_arr_free(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
