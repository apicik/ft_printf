/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_scp_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego <ediego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 15:41:22 by ediego            #+#    #+#             */
/*   Updated: 2019/12/21 14:55:04 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		put_lstr(char const *s, int len)
{
	if (s)
		write(1, s, len);
	return (len);
}

int		len_str(char *str)
{
	int count;

	if (str == NULL)
		return (0);
	count = 0;
	while (str[count] && str[count + 1] && str[count + 2] && str[count + 3] &&
	str[count + 4] && str[count + 5] && str[count + 6] && str[count + 7])
		count += 8;
	while (str[count])
		count++;
	return (count);
}

char	*itoa_base_16p(long long n, char *result)
{
	long long	num;
	int			ind;

	num = n;
	ind = 1;
	while ((num /= 16) >= 1)
		++ind;
	result[ind] = '\0';
	if (n == 0)
		result[0] = '\0';
	num = n;
	while (ind-- && num)
	{
		if (num % 16 < 10)
			result[ind] = num % 16 + '0';
		else
			result[ind] = num % 16 - 10 + 'a';
		num /= 16;
	}
	return (result);
}

int		print_pointer(t_lst *cur, char *num)
{
	if (cur->lenspace > 2 && !cur->minus)
		cur->lenprint += put_symb(cur->lenspace - 2, ' ');
	write(1, "0x", 2);
	if (cur->lenzero && cur->prec)
		cur->lenprint += put_symb(cur->lenzero, '0');
	if (cur->lenzero && !cur->prec)
		cur->lenprint += put_symb(cur->lenzero - 2, '0');
	if (!cur->num && !cur->isnull)
		put_symb(1, '0');
	else
		ft_putstr(num);
	if (cur->lenspace > 2 && cur->minus)
		cur->lenprint += put_symb(cur->lenspace - 2, ' ');
	return (cur->lenprint + cur->len + 2);
}

int		out_p16(t_lst *cur, va_list args)
{
	char *num;
	char *numb;
	char arr[40];

	cur->sharp = 1;
	cur->sign = 1;
	numb = arr;
	cur->num = va_arg(args, long long);
	num = itoa_base_16p(cur->num, numb);
	cur->len = len_str(num);
	if (!cur->num && !cur->isnull)
		cur->len++;
	fill_cur_xp16(cur);
	return (print_pointer(cur, num));
}
