/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 08:55:14 by padam             #+#    #+#             */
/*   Updated: 2024/09/03 01:23:33 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief prints the error messages for the flags
*/
void	short_flag_error(char flag)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd("invalid option -- '", 2);
	ft_putchar_fd(flag, 2);
	ft_putendl_fd("'", 2);
}

/**
 * @brief Handles any long flags (--flag)
 * @param arg the string containing the flag
 * @param flags structure containing the flags
 * @return `0` on success, `1` on failure
*/
int	long_flag(char *arg, t_flags *flags)
{
	(void)flags;
	if (!*arg)
		return (0);
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd("unrecognized option '--", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("'", 2);
	return (1);
}

/**
 * @brief Handles any short flags (-flags)
 * @return `0` on success, `1` on failure
*/
int	short_flag(char *arg, t_flags *flags)
{
	while (*arg)
	{
		if (*arg == 'a')
			flags->a = true;
		else if (*arg == 'd')
			flags->d = true;
		else if (*arg == 'f')
		{
			flags->f = true;
			flags->a = true;
			flags->t = false;
			flags->u = false;
			flags->g = false;
			flags->l = false;
		}
		else if (*arg == 'g')
		{
			flags->g = true;
			flags->l = true;
		}
		else if (*arg == 'l')
			flags->l = true;
		else if (*arg == 'u')
			flags->u = true;
		else if (*arg == 'r')
			flags->r = true;
		else if (*arg == 'R')
		{
			flags->r_upper = true;
			flags->show_foldername = true;
		}
		else if (*arg == 't')
			flags->t = true;
		else
			return (short_flag_error(*arg), 1);
		arg++;
	}
	return (0);
}

/**
 * @brief set all flags acording to input
 * @attention exits if incorrect flags
 * @return amount of non-flag arguments
*/
int	parse_arguments(char **argv, t_flags *flags)
{
	int		i;
	bool	error;

	i = 0;
	error = 0;
	if (!argv)
		return (-1);
	while (argv[0] && !error)
	{
		if (argv[0][0] == '-')
		{
			if (!argv[0][1])
				i++;
			else if (argv[0][1] == '-')
				error = long_flag(argv[0] + 2, flags);
			else
				error = short_flag(argv[0] + 1, flags);
		}
		else
			i++;
		argv++;
	}
	if (error)
		exit(2);
	return (i);
}
