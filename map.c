/*
 * map.c
 * 
 * Copyright 2012 Emilio López <emilio@elopez.com.ar>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdio.h>
#include <string.h>

#include "map.h"

int loadconfig(keymap *map)
{
    FILE* fp;
    ssize_t read;
    size_t alloc;
    char* line = NULL;
    char* tmp;
    unsigned int i = 0;

    fp = fopen("/etc/keybinder.conf", "r");
    if (fp == NULL)
        return -1;

    while ((read = getline(&line, &alloc, fp)) != -1) {
        /* fetch keycode*/
        tmp = strtok(line, ",");
        if (tmp == NULL)
            return -2;
        map[i].code = atoi(tmp);

        /* and command */
        tmp = strtok(NULL, ",");
        map[i].command = tmp;

        /* cleanup for next pass */
        i++;
        line = NULL;
    }

    return 0;
}
