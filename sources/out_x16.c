/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_x16.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego <ediego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:13:59 by ediego            #+#    #+#             */
/*   Updated: 2019/12/21 00:34:10 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*itoa_base_16x(unsigned long long n, int type, char *result)
{
	unsigned long long	unum;
	int					ind;

	unum = n;
	ind = 1;
	while ((unum /= 16) >= 1)
		++ind;
	unum = n;
	result[ind] = '\0';
	while (ind--)
	{
		if (unum % 16 < 10)
			result[ind] = unum % 16 + '0';
		else if (type == 4)
			result[ind] = unum % 16 - 10 + 'a';
		else
			result[ind] = unum % 16 - 10 + 'A';
		unum /= 16;
	}
	return (result);
}

int		print_left_x(t_lst *cur, char *unum)
{
	if (cur->lenzero > 0)
		cur->lenprint += put_symb(cur->lenzero, '0');
	if (!cur->unum && cur->isnull)
		put_symb(1, ' ');
	else if (!cur->unum)
		put_symb(1, '0');
	else
	{
		if (cur->sharp && cur->type == 4)
			write(1, "0x", 2);
		else if (cur->sharp && cur->type == 5)
			write(1, "0X", 2);
		ft_putstr(unum);
	}
	if (cur->lenspace > 0)
		cur->lenprint += put_symb(cur->lenspace, ' ');
	return (cur->lenprint + cur->len);
}

int		print_right_x(t_lst *cur, char *unum)
{
	if (cur->lenspace > 0)
		cur->lenprint += put_symb(cur->lenspace, ' ');
	if (cur->lenzero > 0)
		cur->lenprint += put_symb(cur->lenzero, '0');
	if (!cur->unum && cur->isnull)
		put_symb(1, ' ');
	else if (!cur->unum)
		put_symb(1, '0');
	else
	{
		if (cur->sharp && cur->type == 4)
			write(1, "0x", 2);
		else if (cur->sharp && cur->type == 5)
			write(1, "0X", 2);
		ft_putstr(unum);
	}
	return (cur->lenprint + cur->len);
}

int		print_sharp(t_lst *cur, char *unum)
{
	if (cur->lenspace > 2 && !cur->minus)
		cur->lenprint += put_symb(cur->lenspace - 2, ' ');
	if (cur->type == 4)
		write(1, "0x", 2);
	else
		write(1, "0X", 2);
	if (cur->lenzero > 0 && cur->prec)
		cur->lenprint += put_symb(cur->lenzero, '0');
	if (cur->lenzero > 2 && !cur->prec)
		cur->lenprint += put_symb(cur->lenzero - 2, '0');
	if (!cur->unum)
		cur->lenprint += put_symb(1, '0');
	else
		ft_putstr(unum);
	if (cur->lenspace > 2 && cur->minus)
		cur->lenprint += put_symb(cur->lenspace - 2, ' ');
	return (cur->lenprint + cur->len + 2);
}

int		out_x16(t_lst *cur, va_list args)
{
	char *numb;
	char arr[40];

	numb = arr;
	if (cur->minus)
		cur->zero = 0;
	if (cur->size && cur->size != 5)
		cur->unum = va_arg(args, unsigned long long);
	else
		cur->unum = va_arg(args, unsigned long long) % 4294967296;
	if (cur->size == 4)
		cur->unum %= 256;
	if (cur->size == 5)
		cur->unum %= 65536;
	numb = itoa_base_16x(cur->unum, cur->type, numb);
	cur->len = len_str(numb);
	fill_cur_xp16(cur);
	if (cur->isnull && cur->unum == 0 && !cur->width)
		return (0);
	if ((cur->sharp && cur->unum) || (cur->sharp && cur->sign))
		return (print_sharp(cur, numb));
	if (cur->minus)
		return (print_left_x(cur, numb));
	return (print_right_x(cur, numb));
}
