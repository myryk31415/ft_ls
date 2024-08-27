/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:36:36 by padam             #+#    #+#             */
/*   Updated: 2024/08/27 08:31:10 by padam            ###   ########.fr       */
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

int	input_list(int count, char **paths, t_flags *flags)
{
	t_inode	**inodes;
	char	**entries;

	//make list
	inodes = ft_calloc(count + 1, sizeof(t_inode **));
	if (!inodes)
		return(err(), 1);
	if (test(inodes, paths))
		return (1);
	//sort
	decide_sorting(inodes, flags);
	//print only files
	entries = inode_arr_to_string_arr(inodes, NULL, !flags->d, flags);
	if (entries)
		print_group(NULL, entries, NULL, flags);
	// list_directory on folders
	if (flags->d)
		return (0);
	return (inodes_list_directories(inodes, 1, flags));
}

/**
 * @brief main function of ft_ls
 * @return
*/
int main(int argc, char **argv)
{
	t_flags	flags;
	int		i;

	// no_args = 1;
	(void)argc;
	init_flags(&flags);
	i = parse_arguments(argv + 1, &flags);
	if (i > 1)
		flags.show_foldername = true;
	if (i)
		return (input_list(i, ++argv, &flags));
	else
	{
		if (!flags.d)
			list_directory(".", &flags);
		*argv = ".";
		return (input_list(1, argv, &flags));
	}
}
