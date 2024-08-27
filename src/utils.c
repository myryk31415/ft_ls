/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:57:48 by padam             #+#    #+#             */
/*   Updated: 2024/08/27 06:06:13 by padam            ###   ########.fr       */
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

void	file_not_found(char *file)
{
	ft_putstr_fd("ls: cannot access '", 2);
	ft_putstr_fd(file, 2);
	perror("'");
}
