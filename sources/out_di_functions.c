/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_di_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego <ediego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 10:43:00 by ediego            #+#    #+#             */
/*   Updated: 2019/12/20 14:38:16 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		put_symb(int n, char sym)
{
	int c;

	c = 0;
	while (++c <= n)
	{
		ft_putchar(sym);
		if (c == n)
			break ;
	}
	return (c);
}

int		len_num(long long num)
{
	int c;

	c = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= 10;
		c++;
	}
	return (c);
}

void	putnbrl(unsigned long long n)
{
	int		ind;
	char	symba[21];

	ind = 0;
	if (n == 0)
		ft_putchar('0');
	while (n != 0)
	{
		symba[ind++] = '0' + (n % 10);
		n = n / 10;
	}
	while (ind > 0)
		ft_putchar(symba[(ind--) - 1]);
}

int		print_zerodi(t_lst *cur)
{
	if (cur->width)
		cur->lenspace++;
	if (cur->plus && cur->minus)
		cur->lenprint += put_symb(1, '+');
	if (cur->lenspace)
		cur->lenprint += put_symb(cur->lenspace, ' ');
	if (cur->plus && !cur->minus)
		cur->lenprint += put_symb(1, '+');
	return (cur->lenprint);
}
