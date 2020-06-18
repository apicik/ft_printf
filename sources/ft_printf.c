/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego <ediego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 22:07:33 by ediego            #+#    #+#             */
/*   Updated: 2019/12/19 19:39:59 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		len_buf(int i, char *str)
{
	int count;

	count = 0;
	while (str[i] != 'c' || str[i] != 'd' || str[i] != 's' || str[i] != 'i')
	{
		count++;
		i++;
	}
	return (count);
}

int		ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	va_start(args, str);
	while (str[++i])
	{
		if (str[i] == '%')
			ret += chk_buf(&i, str, args);
		else
		{
			write(1, &str[i], 1);
			ret += 1;
		}
		if (!str[i])
			break ;
	}
	va_end(args);
	return (ret);
}
