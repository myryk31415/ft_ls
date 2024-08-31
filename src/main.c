/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:36:36 by padam             #+#    #+#             */
/*   Updated: 2024/08/31 06:48:10 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief sets all flags except `first entry` to false
*/
void init_flags(t_flags *flags)
{
	int		i;
	bool	*cast;

	cast = (bool *)flags;
	i = sizeof(t_flags);
	while (i--)
		cast[i] = false;
	flags->first_entry = true;
}

/**
 * @brief populates the inode array
 * @return error status
 */
int	get_inodes(t_inode **inodes, char **names)
{
	while (*names)
	{
		if (names[0][0] != '-' || !names[0][1])
		{
			*inodes = populate_inode(NULL, ft_strdup(*names));
			if (!*inodes)
				return (2);
			inodes++;
		}
		names ++;
	}
	return (0);
}

/**
 * @brief similar to `inodes_to_print` but seperates folders and files
 * @return error status
 */
int	list_argv(int count, char **paths, t_flags *flags)
{
	t_inode	**inodes;
	char	**entries;

	inodes = ft_calloc(count + 1, sizeof(t_inode **));
	if (!inodes)
		return(err(), 1);
	if (get_inodes(inodes, paths))
		return (free(inodes), 2);
	sort(inodes, flags);
	//print only files
	entries = gather_info_from_inodes(inodes, NULL, !flags->d, flags);
	if (entries)
		print_group(NULL, entries, NULL, flags);
	string_arr_free(entries);
	// list_directory on folders
	if (flags->d)
		return (inodes_free(inodes, 0), 0);
	return (inodes_list_directories(inodes, 1, flags));
}

/**
 * @brief main function of ft_ls
 * @return error status
*/
int main(int argc, char **argv)
{
	t_flags	flags;
	int		i;

	(void)argc;
	init_flags(&flags);
	i = parse_arguments(argv + 1, &flags);
	if (i > 1)
		flags.show_foldername = true;
	if (i)
		return (list_argv(i, ++argv, &flags));
	else
	{
		if (!flags.d)
			return (list_directory(".", &flags));
		*argv = ".";
		return (list_argv(1, argv, &flags));
	}
}
