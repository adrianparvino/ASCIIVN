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

#include "event.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <errno.h>
#include <string.h>

_Atomic size_t resized = 0; // Semaphore-like

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#else
#include<unistd.h>
#include<termios.h>
#include<signal.h>
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#else
struct termios saved_attributes;
#endif

void
signal_resize(int signo)
{
	++resized;
}

void
event_start()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	// TODO: Support Windows
	fprintf(stderr, "Windows is not yet supported.\n");
	exit(EXIT_FAILURE);
#else
	/* Taken from https://www.gnu.org/software/libc/manual/html_node/Noncanon-Example.html */
	struct termios tattr;
	
	/* Make sure stdin is a terminal. */
	if (!isatty (STDIN_FILENO))
		{
			fprintf (stderr, "Not a terminal.\n");
			exit (EXIT_FAILURE);
		}
	
	/* Save the terminal attributes so we can restore them later. */
	tcgetattr (STDIN_FILENO, &saved_attributes);
	atexit (event_end);
	
	/* Set the funny terminal modes. */
	tcgetattr (STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);

	struct sigaction sa;
	memset(&sa, 0, sizeof sa);
	sa.sa_handler = signal_resize;
	sa.sa_flags = 0;
	
	sigaction(SIGWINCH, &sa, NULL);
#endif
}

struct event
event_getevent()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#else
	for (;;)
		{
			errno = 0;
			int c = getchar();

			switch (c)
				{
				case -1:
					if (errno != EINTR) exit(EXIT_FAILURE);

					if (resized > 0)
						{
							--resized;
							return (struct event) { .tag = RESIZE };
						}
					break;
#endif
				case '\x1b': // ESC
					if (getchar() != '[') // CSI
						{
							continue;
						}

					switch (c = getchar())
						{
						case UP: // 'A'
						case DOWN: // 'B'
							return (struct event) { .tag = c };
						}
					break;
				case RET:
					return (struct event) { .tag = RET };
				}
			
			return (struct event) { .tag = CHAR, .character = c };
		}
}

void
event_end()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	fprintf(stderr, "Windows is not yet supported.\n");
	exit(EXIT_FAILURE);
#else
	tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
#endif
}
