/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 01:06:11 by padam             #+#    #+#             */
/*   Updated: 2024/08/10 07:36:39 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
