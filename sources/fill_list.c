/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego <ediego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 09:46:41 by ediego            #+#    #+#             */
/*   Updated: 2019/12/20 20:41:11 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_flag(int *i, const char *str, t_lst *cur)
{
	if (str[*i] == '-')
		cur->minus = 1;
	else if (str[*i] == '+')
		cur->plus = 1;
	else if (str[*i] == ' ')
		cur->space = 1;
	else if (str[*i] == '#')
		cur->sharp = 1;
	else if (str[*i] == '0' && (str[*i - 1] == '-' || str[*i - 1] == '+' ||
	str[*i - 1] == ' ' || str[*i - 1] == '#' || str[*i - 1] == '%'))
		cur->zero = 1;
}

void	fill_width(int *i, char *str, t_lst *cur, va_list args)
{
	int width;

	width = 0;
	if (str[*i] == '*')
		width = va_arg(args, int);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		width = (str[*i] - '0') + (width * 10);
		*i = *i + 1;
	}
	if ((cur->width = width) < 0)
	{
		cur->minus = 1;
		cur->width *= -1;
	}
}

void	fill_prec(int *i, char *str, t_lst *cur, va_list args)
{
	int prec;

	prec = 0;
	*i = *i + 1;
	if (str[*i] == '*')
		prec = va_arg(args, int);
	if (str[*i] == '-')
	{
		*i = *i + 1;
		cur->minus = 1;
	}
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		prec = (str[*i] - '0') + (prec * 10);
		*i = *i + 1;
	}
	cur->prec = prec;
	if (prec == 0)
		cur->isnull = 1;
	if (prec < 0)
		cur->prec = 0;
}

void	fill_size(int *i, const char *str, t_lst *cur)
{
	if (str[*i] == 'L')
		cur->size = 3;
	else if (str[*i] == 'l' && str[*i - 1] == 'l')
		cur->size = 2;
	else if (str[*i] == 'l')
		cur->size = 1;
	else if (str[*i] == 'h' && str[*i - 1] == 'h')
		cur->size = 4;
	else if (str[*i] == 'h')
		cur->size = 5;
}

void	fill_type(int *i, const char *str, t_lst *cur)
{
	if (str[*i] == 'd' || str[*i] == 'i')
		cur->type = 1;
	else if (str[*i] == 'o')
		cur->type = 2;
	else if (str[*i] == 'u')
		cur->type = 3;
	else if (str[*i] == 'x')
		cur->type = 4;
	else if (str[*i] == 'X')
		cur->type = 5;
	else if (str[*i] == 'f')
		cur->type = 6;
	else if (str[*i] == 'c')
		cur->type = 10;
	else if (str[*i] == 's')
		cur->type = 11;
	else if (str[*i] == 'p')
		cur->type = 12;
	else if (str[*i] == '%')
		cur->type = 888;
	else
		cur->type = 0;
}
