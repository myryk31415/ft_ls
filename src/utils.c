/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:57:48 by padam             #+#    #+#             */
/*   Updated: 2024/08/28 05:52:57 by padam            ###   ########.fr       */
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
void	file_not_found(char *file)
{
	ft_putstr_fd("ls: cannot access '", 2);
	ft_putstr_fd(file, 2);
	perror("'");
}
