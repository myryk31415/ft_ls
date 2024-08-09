/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 08:55:14 by padam             #+#    #+#             */
/*   Updated: 2024/08/09 00:36:26 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
/**
 * @brief Handles any long flags (--flag)
 * @param arg the string containing the flag
 * @param flags structure containing the flags
 * @return 0 on success, 1 on failure
*/
int	long_flag(char *arg, t_flags *flags)
{
	//TODO'
	(void)flags;
	ft_putendl(arg);
	return (0);
}

/**
 * @brief Handles any short flags (-flags)
 * @param arg the string containing the flags
 * @param flags structure containing the flags
 * @return 0 on success, 1 on failure
*/
int	short_flag(char *arg, t_flags *flags)
{
	(void)flags;
	while (*arg)
	{

	}
	ft_putendl(arg);
	return (0);
}

/**
 * @brief set all flags acording to input
 * @param argv the arguments
 * @param flags structure containing the flags
 * @return the amount of non-flag arguments
*/
int	set_flags(char **argv, t_flags *flags)
{
	int i;

	i = 0;
	if (!argv)
		return (-1);
	while (argv[0])
	{
		if (argv[0][0] == '-')
		{
			if (!argv[0][1])
				write(1, "a\n", 2);
			else if (argv[0][1] == '-')
				long_flag(argv[0] + 2, flags);
			else
				short_flag(argv[0] + 1, flags);
		}
		else
			i++;
		argv++;
	}
	return i;
}

/**
 * @brief parses arguments lol
 * @param argv arguments array
 * @param flags structure containing the flags
 * @return returns a list of args
*/
char	**parse_arguments(char **argv, t_flags *flags)
{
	int i;

	i = set_flags(argv, flags);
	(void)i;
	return argv;
}
