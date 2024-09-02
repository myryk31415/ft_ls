/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:57:48 by padam             #+#    #+#             */
/*   Updated: 2024/09/03 00:28:43 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief calles `perror("ls")`
*/
void	err(void)
{
	perror("ls");
}

/**
 * @brief outputs according error message
 */
void	file_error(char *file)
{
	ft_putstr_fd("ls: cannot access '", 2);
	ft_putstr_fd(file, 2);
	perror("'");
}

/**
 * @brief outputs according error message
 */
void	dir_error(char *dir)
{
	ft_putstr_fd("ls: cannot open directory '", 2);
	ft_putstr_fd(dir, 2);
	perror("'");
}
