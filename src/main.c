/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:36:36 by padam             #+#    #+#             */
/*   Updated: 2024/08/27 05:58:48 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief sets all flags to false
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

// void	beginningsort(t_inode **inodes, t_flags *flags)
// {

// }

int	test(t_inode **inodes, char **names)
{
	while (*names)
	{
		if (names[0][0] != '-' || !names[0][1])
		{
			*inodes = path_to_inode(NULL, *names);
			if (!*inodes)
				return (1);
			inodes++;
		}
		names ++;
	}
	return (0);
}

/**
 * @brief main function of ft_ls
 * @return
*/
int main(int argc, char **argv)
{
	t_flags	flags;
	int		i;
	t_inode	**inodes;
	char	**entries;

	// no_args = 1;
	(void)argc;
	init_flags(&flags);
	i = parse_arguments(argv + 1, &flags);
	if (i > 1)
		flags.show_foldername = true;
	if (i)
	{
		//make list
		inodes = ft_calloc(i + 1, sizeof(t_inode **));
		if (!inodes)
			return(err(), 1);
		if (test(inodes, ++argv))
			return (1);
		//sort
		decide_sorting(inodes, &flags);
		//print only files
		entries = inode_arr_to_string_arr(inodes, NULL, 1, &flags);
		if (entries)
			print_group(NULL, entries, NULL, &flags);
		// list_directory on folders
		return (inodes_list_directories(inodes, 1, &flags));
	}
	else
		list_directory(".", &flags);
}
