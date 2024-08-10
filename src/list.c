/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 01:06:11 by padam             #+#    #+#             */
/*   Updated: 2024/08/10 08:47:14 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	list_folder(char *path)
{

	(void)path;
	// get all files from node

	//sort

	//print

	//if -R call list folder on all folders
}

int	list_inodes(char *path)
{
	// DIR *dir;
	struct stat st;

	if (stat(path, &st) == -1)
		err();
	if (S_ISDIR(st.st_mode))
		ft_putendl("dir");
	ft_printf("%u\n", st.st_ino);
	// dir = opendir(path);
	// if (!dir)
	// 	err();
	return (0);
}
