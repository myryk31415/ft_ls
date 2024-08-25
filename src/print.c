/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:11:24 by padam             #+#    #+#             */
/*   Updated: 2024/08/25 05:48:37 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief prints one group of files e.g. lists one folder
 * @param entries string array containing the gathered info got each inode
 */
void	print_group(char *folder_name, char **entries, char *blocks, t_flags *flags)
{
	if (flags->first_entry)
		flags->first_entry = false;
	else
		ft_putstr("\n");
	if (flags->show_foldername)
	{
		ft_putstr(folder_name);
		ft_putendl(":");
	}
	if (flags->l || flags->g)
	{
		ft_putstr("total ");
		ft_putendl(blocks);
		while (*entries)
			ft_putendl(*entries++);
	}
	else
	{
		while (*entries)
		{
			ft_putstr(*entries++);
			ft_putstr("   ");
		}
		ft_putendl("");
	}
}
