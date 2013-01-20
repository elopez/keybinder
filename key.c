/*
 * key.c
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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <linux/input.h>
#include <linux/ioctl.h>

#include "map.h"

keymap map[255] = {0};

int main (int argc, char **argv)
{
    struct input_event ev;
    int fd, rd, value, size = sizeof(struct input_event);
    int mapelements, i;
    char name[256] = "Unknown";
    char *device = NULL;

    /* Check parameters */
    if (argv[1] == NULL) {
        printf("Usage: %s /dev/input/eventX\n", argv[0]);
        return 0;
    }

    if (getuid() != 0)
        printf("You are not root! This may not work...\n");

    if (argc > 1)
        device = argv[1];

    /* Open device */
    if ((fd = open (device, O_RDONLY)) == -1)
        printf("%s is not a vaild device.\n", device);

    /* Print Device Name */
    ioctl(fd, EVIOCGNAME(sizeof(name)), name);
    printf("Reading key input from %s (%s)\n", device, name);

    /* load config */
    if(loadconfig(&map) != 0) {
        printf("Error loading config file!\n");
        return 0;
    }

    mapelements = (sizeof(map)/sizeof(keymap));
    printf("Loaded config items\n");

    while (1) {
        rd = read (fd, &ev, size);

        /* Only read the key press event */
        if (ev.value == 1 && ev.type == EV_KEY) {
            printf ("Keycode %d pressed\n", ev.code);

            /* Look for a suitable command to execute */
            for (i = 0; i < mapelements; i++) {
                if (ev.code == map[i].code)
                    system(map[i].command);
            }
        }
    }

    return 0;
}
