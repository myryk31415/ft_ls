/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 08:00:10 by padam             #+#    #+#             */
/*   Updated: 2024/08/24 08:00:32 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	check_right(bool permission, char value)
{
	if (permission)
		return (value);
	return('-');
}

char	*get_rights(t_inode *inode)
{
	unsigned int	perm;
	char			*modeval;

	perm = inode->st.st_mode;
	modeval = ft_calloc(10, 1);
	if (!modeval)
		return (NULL);
	modeval[0] = check_right(S_ISDIR(perm), 'd');
	modeval[1] = check_right(perm & S_IRUSR, 'r');
	modeval[2] = check_right(perm & S_IWUSR, 'w');
	modeval[3] = check_right(perm & S_IXUSR, 'x');
	modeval[4] = check_right(perm & S_IRGRP, 'r');
	modeval[5] = check_right(perm & S_IWGRP, 'w');
	modeval[6] = check_right(perm & S_IXGRP, 'x');
	modeval[7] = check_right(perm & S_IROTH, 'r');
	modeval[8] = check_right(perm & S_IWOTH, 'w');
	modeval[9] = check_right(perm & S_IXOTH, 'x');
	modeval[10] = '\0';
	return (modeval);
}
