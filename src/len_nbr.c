/*
** EPITECH PROJECT, 2023
** len_nbr
** File description:
** len_nbr
*/

#include <stdio.h>
#include "../my_hunter.h"

int len_nbr(int nb)
{
    int cnt = 1;

    if (nb == 0)
        return 1;
    while (nb >= 10){
        nb = nb / 10;
        cnt++;
    }
    return cnt;
}
