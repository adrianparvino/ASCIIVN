/* This file is part of ASCIIVN.
 *
 * Copyright (C) 2017  Adrian Parvin D. Ouano
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "keyevent.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#else
#include<unistd.h>
#include<termios.h>
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#else
struct termios saved_attributes;
#endif

void
keyevent_start()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	// TODO: Support Windows
	fprintf(stderr, "Windows is not yet supported.\n");
	exit(EXIT_FAILURE);
#else
	/* Taken from https://www.gnu.org/software/libc/manual/html_node/Noncanon-Example.html */
	struct termios tattr;
	char *name;
	
	/* Make sure stdin is a terminal. */
	if (!isatty (STDIN_FILENO))
		{
			fprintf (stderr, "Not a terminal.\n");
			exit (EXIT_FAILURE);
		}
	
	/* Save the terminal attributes so we can restore them later. */
	tcgetattr (STDIN_FILENO, &saved_attributes);
	atexit (keyevent_end);
	
	/* Set the funny terminal modes. */
	tcgetattr (STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);	
#endif
}

struct keyevent
keyevent_getenvent()
{
	char c = getchar();

	return (struct keyevent) { .tag = CHAR, .character = c };
}

void
keyevent_end()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#else
	fprintf(stderr, "Windows is not yet supported.\n");
	exit(EXIT_FAILURE);
	tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
#endif
}
