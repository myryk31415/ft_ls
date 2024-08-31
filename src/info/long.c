/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 08:00:10 by padam             #+#    #+#             */
/*   Updated: 2024/08/31 02:30:34 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief simple helper function to replace ternary operator
 * @return char value if permission is true, else `-`
 */
char	check_right(bool permission, char value)
{
	if (permission)
		return (value);
	return('-');
}

/**
 * @brief gathers access rights
 * @return string containing `d`, 'l', `r`, `w`, `x`, `-`
 */
char	*get_rights(t_inode *inode)
{
	unsigned int	perm;
	char			*modeval;

	perm = inode->st.st_mode;
	modeval = ft_calloc(11, 1);
	if (!modeval)
		return (err(), NULL);
	modeval[0] = '-';
	if (S_ISDIR(perm))
		modeval[0] = 'd';
	else if (S_ISLNK(perm))
		modeval[0] = 'l';
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

/**
 * @brief uses the uid to get the username
 * @return username as string
 */
char	*get_user(t_inode *inode)
{
	struct passwd	*passwd;

	passwd = getpwuid(inode->st.st_uid);
	if (!passwd)
		return (err(), NULL);
	return(ft_strdup(passwd->pw_name));
}

/**
 * @brief uses the gid to get the groupname
 * @return groupname as string
 */
char	*get_group(t_inode *inode)
{
	struct group	*group;

	group = getgrgid(inode->st.st_gid);
	if (!group)
		return (err(), NULL);
	return(ft_strdup(group->gr_name));
}

/**
 * @brief transforms the time into the correct format for `ls`7
 * @return the date formatted for `ls`
 */
char	*get_date_from_time(time_t *selected_time)
{
	time_t	current_time;
	char	*composed_time;
	char	*tmp_time;
	bool	recent;

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
	if (!composed_time)
		return (err(), NULL);
	ft_strlcpy(composed_time, tmp_time + 4, 7);
	ft_strlcat(composed_time, " ", 8);
	if (recent)
		ft_strlcat(composed_time, tmp_time + 11, 13);
	else
		ft_strlcat(composed_time, tmp_time + 19, 13);
	return (composed_time);
}

/**
 * @brief selects time according to flags and transforms it
 * @return the date formatted for `ls`
 */
char	*get_date(t_inode *inode, t_flags *flags)
{
	time_t	*selected_time;

	selected_time = &inode->st.st_mtime;
	if (flags->u)
		selected_time = &inode->st.st_atime;
	return (get_date_from_time(selected_time));
}
