/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 08:00:10 by padam             #+#    #+#             */
/*   Updated: 2024/08/25 05:39:39 by padam            ###   ########.fr       */
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

char	*get_user(t_inode *inode)
{
	struct passwd	*passwd;

	passwd = getpwuid(inode->st.st_uid);
	if (!passwd)
		return (err(), NULL);
	return(ft_strdup(passwd->pw_name));
}

char	*get_group(t_inode *inode)
{
	struct group	*group;

	group = getgrgid(inode->st.st_gid);
	if (!group)
		return (err(), NULL);
	return(ft_strdup(group->gr_name));
}

char	*get_date(t_inode *inode, t_flags *flags)
{
	time_t	current_time;
	time_t	*selected_time;
	char	*tmp_time;
	char	*composed_time;
	bool	recent;

	selected_time = &inode->st.st_mtime;
	if (flags->u)
		selected_time = &inode->st.st_atime;
	current_time = time(NULL);
	if (current_time == -1)
		return (err(), NULL);
	recent = true;
	if (current_time - *selected_time > RECENT)
		recent = false;
	tmp_time = ctime(selected_time);
	if (!tmp_time)
		return(err(), NULL);
	composed_time = ft_calloc(13, 1);
	ft_strlcpy(composed_time, tmp_time + 4, 7);
	ft_strlcat(composed_time, " ", 8);
	if (recent)
		ft_strlcat(composed_time, tmp_time + 11, 13);
	else
		ft_strlcat(composed_time, tmp_time + 19, 13);
	return (composed_time);
}
