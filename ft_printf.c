#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int ft_putchar(char c)
{
    int len= 0;    len += write(1, &c, 1);
    return len;
}
int ft_putstr(char *str)
{
    int len = 0;
    int i= 0;
    if(!str)
    {
        write(1, "(null)", 6);
        return(6);
    }
    while(str[i])
    {
        len += ft_putchar(str[i]);
        i++;
    }
    return len;
}
int ft_putnbr(long long nbr)
{
    int len = 0;

    if(nbr == -2147483648)
    {
        len += write(1,"-2147483648", 11);
        return len;
    }
    if(nbr > 9)
    {
        len += ft_putnbr(nbr / 10);
        len += ft_putnbr(nbr % 10);
    }
    else if ( nbr < 0)
    {
        len += ft_putchar('-');
        nbr = -nbr;
    }
    else 
        len += ft_putchar(nbr + 48);
    return len;
}
int ft_len(unsigned long n)
{
    int len = 0;
    if(n == 0)
        return(1);
    while(n!= 0)
    {
        len++;
        n/=16;
    }
    return len;
}
int ft_puthex(unsigned long nbr ,char c)
{
    int len = ft_len(nbr); 
    if( nbr >= 16)
    {
        ft_puthex(nbr / 16, c);
        ft_puthex(nbr % 16, c);
    }
    else if (nbr <= 9)
        ft_putchar(nbr + 48);
    else if( nbr >9  && nbr < 16 && (c == 'x' || c == 'X'))
            ft_putchar(nbr - 10 + 'a');
    return len;
}
int checker(va_list arg, char f)
{
    int len = 0;
    if(f == 'c')
        len += ft_putchar(va_arg(arg, int));
    else if (f == 's')
        len += ft_putstr(va_arg(arg, char *));
    else if (f == 'i' || f == 'd')
        len += ft_putnbr(va_arg(arg, int));
    else if (f == 'X' || f == 'x')
        len += ft_puthex(va_arg(arg , unsigned long), f);
    else if(f == '%')
        len +=ft_putchar('%');
    return len;
}
int ft_printf(const char *str, ...)
{
    int len= 0;
    int i = 0;
    va_list arg;
    va_start(arg, str);
    while(str[i])
    {
        if(str[i] == '%')
        {
            len += checker(arg, str[i + 1]);
            i++;
        }
        else
            write(1, &str[i], 1);
        i++;
    }
    return len;
}
