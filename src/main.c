/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:36:36 by padam             #+#    #+#             */
/*   Updated: 2024/08/25 04:08:44 by padam            ###   ########.fr       */
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
	{
		//make list

		//sort

		//print only files

		//list_directory on folders
	}
	else
		list_directory(".", &flags);

	// while (*(++argv))
	// {
	// 	if (!(argv[0][0] == '-' && argv[0][1]))
	// 	{
	// 		no_args = 0;
	// 		list_entity(*argv);
	// 	}
	// }
	// if (no_args)
	// 	list_entity(".");
}
