/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:36:36 by padam             #+#    #+#             */
/*   Updated: 2024/08/10 08:05:47 by padam            ###   ########.fr       */
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
}


int	separate_dirs(char **argv, t_flags *flags)
{

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
	i = parse_arguments(argv, &flags);
	if (i > 1)
		flags.show_foldername = true;
	if (i)
	{
		//make list

		//print only files

		//list_folder on folders
	}
	else
		list_folder(".", &flags);

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
