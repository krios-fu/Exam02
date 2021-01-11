/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:11:18 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/11 22:12:05 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

size_t ft_strlen (const char *str)
{
    size_t len;

    len = 0;

    while (str[len] != '\0')
        len++;
    
    return (len);   
}

int ft_intlen (long long num, int base)
{
    int len;
    len = 1;

    while (num >= base || num <= -base)
    {
        num /= base;
        len++;
    }
    return (len);   
}

void ft_printnum (long long num, int basel, char *base)
{
    if(num >= basel)
        ft_printnum(num/basel, basel, base);
    write(1, &base[num%basel], 1);
}

int ft_printf(const char *format, ...)
{
    va_list list;

    char *str, *s, *base;
    int w = 0, p = 0, dot = 0, spc = 0, zero = 0, neg = 0, basel = 0, len = 0, lenstr = 0;
    long num;
    va_start(list, format);

    str =(char *)format;

    while(*str != '\0')
    {
        if(*str == '%')
        {
            int w = 0, p = 0, dot = 0, spc = 0, zero = 0, neg = 0, basel = 0, len = 0, num = 0;
            str++;
            while(*str >= '0' && *str <= '9')
            {
                w = w * 10 + (*str - 48);
                str++;
            }
            if(*str == '.')
            {
                str++;
                while(*str >= '0' && *str <= '9')
                {
                     p = p * 10 + (*str - 48);
                     str++;
                }
                     dot = 1;
            }
            if(*str == 's')
            {
                s = va_arg(list, char*);
                if(!s)
                    s = "(null)";
                len += ft_strlen (s);
            }
            if(*str == 'x')
            {
                num = va_arg(list, unsigned);
                base = "0123456789abcdef";
                basel = 16;
                len = ft_intlen (num, basel);

            }
             if(*str == 'd')
            {
                num = va_arg(list, int);
                base = "0123456789";
                basel = 10;
                if (num < 0)
                {
                    num *= -1;
                    neg = 1;
                }
                len = ft_intlen (num, basel);
            }
            if(dot == 1 && p >= len && *str != 's')
                zero = p - len;
            else if (dot == 1 && *str == 's' && p < len)
                    len = p;
            else if (dot == 1 && p == 0 && (*str == 's' || num == 0))
                len = 0;
            spc = w - len - zero;

            while (spc-- > 0)
                lenstr += write(1, " ", 1);
            if(neg == 1)
                lenstr += write(1, "-", 1);
            while (zero-- > 0)
                lenstr += write(1, "0", 1);
            if(*str == 's')
                lenstr += write(1, s, len);
            else if (num > 0)
            {
                ft_printnum(num, basel, base);
                lenstr += len;
            }       
        }
        else
            lenstr += write(1, str, 1);
        str++;
    }
    va_end(list);
    return(lenstr);

}

int main()
{
    printf("----> Mio\n");
    printf("\n%d\n", ft_printf("holala%d %10.s", 12, "42\0"));
    printf("\n----> Original\n");
    printf("\n%d\n", printf("holala%d %10.s", 12, "42\0"));
    return(0);
}
