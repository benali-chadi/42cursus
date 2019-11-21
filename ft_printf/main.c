#include "ft_printf.h"
#include <stdio.h>

int main()
{
    printf("%*.**\n",5,4,2);
    ft_printf("%*.**\n",5,4,2);
}