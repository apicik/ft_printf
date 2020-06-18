/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_o.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego <ediego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 12:36:57 by ediego            #+#    #+#             */
/*   Updated: 2019/12/20 14:42:03 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*itoa_base_8(unsigned long long num, int sharp, char *result)
{
	unsigned long long	conv;
	int					ind;

	ind = (sharp) ? 2 : 1;
	conv = num;
	while ((conv /= 8) >= 1)
		++ind;
	result[ind] = '\0';
	if (num == 0)
		return ("0");
	if (sharp)
		result[0] = '0';
	conv = num;
	while (ind-- && conv)
	{
		result[ind] = conv % 8 + '0';
		conv /= 8;
	}
	return (result);
}

int		print_llh_oct(t_lst *cur, unsigned long long octa, char *numb)
{
	char *num;

	num = itoa_base_8(octa, cur->sharp, numb);
	cur->len = len_str(num);
	if (cur->zero && cur->width)
		cur->lenprint += put_symb(cur->width - cur->len, '0');
	if (cur->width > cur->len && !cur->zero)
		cur->lenprint += put_symb(cur->width - cur->len, ' ');
	ft_putstr(num);
	return (cur->lenprint + cur->len);
}

int		print_zero_oct(t_lst *cur)
{
	if (cur->minus)
	{
		cur->lenprint += put_symb(1, '0');
		cur->lenprint += put_symb(cur->width - 1, ' ');
	}
	else
	{
		if (cur->width)
			cur->lenprint += put_symb(cur->width - 1, ' ');
		cur->lenprint += put_symb(1, '0');
	}
	return (cur->lenprint);
}

void	fill_cur_o(t_lst *cur)
{
	cur->len = len_num(cur->num);
	if (cur->sharp && cur->zero)
	{
		if (cur->prec && cur->width > cur->prec)
			cur->lenzero = cur->width - cur->prec;
		else if (cur->width > cur->prec && cur->width > cur->len)
			cur->prec = cur->width;
	}
	if (cur->sharp && cur->prec <= cur->len && cur->num)
		cur->prec = cur->len + 1;
}

int		out_o(t_lst *cur, va_list args)
{
	unsigned long long	octa;
	char				*numb;
	char				arr[40];

	numb = arr;
	if (cur->minus)
		cur->zero = 0;
	if (cur->size)
		octa = va_arg(args, unsigned long long);
	else
		octa = va_arg(args, unsigned long long) % 4294967296;
	if (cur->size == 4)
		octa %= 256;
	if (cur->size == 5)
		octa %= 65536;
	if (cur->size == 3 || cur->size == 2 || cur->size == 1)
		return (print_llh_oct(cur, octa, numb));
	cur->num = atoi_ll(itoa_base_8(octa, 0, numb));
	fill_cur_o(cur);
	if (cur->sharp && cur->isnull && !cur->num)
		cur->lenprint = print_zero_oct(cur);
	else
		cur->lenprint = output_digital(cur);
	return (cur->lenprint);
}
