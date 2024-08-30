/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:11:24 by padam             #+#    #+#             */
/*   Updated: 2024/08/30 00:58:31 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief prints both strings (and a newline)
 */
void	put_two_strings(char *s1, char *s2, bool newline)
{
	ft_putstr(s1);
	ft_putstr(s2);
	if (newline)
		ft_putchar('\n');
}

/**
 * @brief prints one group of files e.g. lists one folder
 * @param folder_name can be `NULL`
 * @param entries string array containing the gathered info got each inode
 * @param blocks the amount of blocks used by the group; can be `NULL`
 */
void	print_group(char *folder_name, char **entries, char *blocks, t_flags *flags)
{
	if (flags->first_entry)
		flags->first_entry = false;
	else
		ft_putstr("\n");
	if (flags->show_foldername && folder_name)
		put_two_strings(folder_name, ":", 1);
	if (flags->l)
	{
		if (blocks)
			put_two_strings("total ", blocks, 1);
		while (*entries)
			ft_putendl(*entries++);
	}
	else
	{
		if (!entries)
			return ;
		while (*entries)
			put_two_strings(*entries++, "  ", 0);
		ft_putstr("\n");
	}
}
