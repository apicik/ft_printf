/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_ll.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego <ediego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 21:08:23 by ediego            #+#    #+#             */
/*   Updated: 2019/12/20 14:39:18 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	atoi_ll(const char *s)
{
	int				i;
	long long		res;
	int				znak;

	i = 0;
	znak = 0;
	res = 0;
	if (s[i] == '-')
		znak = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		res = (s[i] - '0') + (res * 10);
		i++;
		if (res - znak > 9223372036854775807)
			return (znak ? 0 : -1);
	}
	return (res * (znak ? -1 : 1));
}

int			atoi_i(const char *s)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while ((s[i] >= 48 && s[i] <= 57) && s[i] != '\0')
		res = (s[i++] - '0') + (res * 10);
	return (res);
}
