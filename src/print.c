/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:11:24 by padam             #+#    #+#             */
/*   Updated: 2024/08/13 06:16:19 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief prints one group of files e.g. lists one folder
 * @param entries string array containing the gathered info got each inode
*/
void	print_group(char *folder_name, char **entries, t_flags *flags)
{
	if (flags->show_foldername)
	{
		ft_putstr(folder_name);
		ft_putendl(":");
	}
	// if (flags->l || flags->g)
	// {
		while (*entries)
		{
			ft_putendl(*entries);
			entries++;
		}
	// }
	ft_putendl("");
	ft_putstr("flkdsalf\n");
}
