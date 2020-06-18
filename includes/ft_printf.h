/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego <ediego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 15:29:44 by ediego            #+#    #+#             */
/*   Updated: 2019/12/20 20:39:56 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct			s_lst
{
	int					minus;
	int					plus;
	int					space;
	int					sharp;
	int					zero;
	long long			num;
	unsigned long long	unum;
	int					len;
	int					len2;
	int					lenprint;
	int					lenzero;
	int					lenspace;
	int					sign;
	int					signmin;
	int					width;
	int					prec;
	int					isnull;
	int					size;
	int					type;
	char				*str;
	char				*str2;
	long double			fl;
}						t_lst;

int						ft_printf(const char *str, ...);
int						len_buf(int i, char *str);
int						chk_buf(int *i, const char *str, va_list args);
void					fill_list(int *i, char *str, t_lst *new, va_list args);
void					fill_flag(int *i, const char *str, t_lst *cur);
void					fill_width(int *i, char *str, t_lst *cur, va_list args);
void					fill_prec(int *i, char *str, t_lst *cur, va_list args);
void					fill_size(int *i, const char *str, t_lst *cur);
void					fill_type(int *i, const char *str, t_lst *cur);
int						out_list(t_lst *cur, va_list args);
int						out_chr(t_lst *cur, va_list args);
int						out_di(t_lst *cur, va_list args);
int						put_symb(int n, char sym);
int						len_num(long long num);
void					putnbrl(unsigned long long n);
int						put_c(int n, char sym);
int						out_c(t_lst *cur, va_list args);
int						out_s(t_lst *cur, va_list args);
int						out_proc(t_lst *cur);
int						len_str(char *str);
int						put_lstr(char const *s, int len);
int						out_o(t_lst *cur, va_list args);
int						output_digital(t_lst *cur);
int						out_x16(t_lst *cur, va_list args);
int						print_zero_oct(t_lst *cur);
int						print_right_x(t_lst *cur, char *num);
int						out_f(t_lst *cur, va_list args);
char					*itoa_f1(t_lst *cur, char *res);
void					real_num(t_lst *cur);
char					*itoa_f2(t_lst *cur, int len, char *numb2);
int						out_p16(t_lst *cur, va_list args);
int						out_u(t_lst *cur, va_list args);
void					find_len2(t_lst *cur);
int						print_zerodi(t_lst *cur);
void					fill_cur_xp16(t_lst *cur);
int						atoi_i(const char *s);
void					*ft_memalloc(size_t size);
void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_bzero(void *b, size_t n);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strnew(size_t size);
t_lst					*new_list(void);
size_t					ft_strlen(const char *s);
long long				atoi_ll(const char *s);

#endif
