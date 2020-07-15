/*
 * Copyright (c) 2020 Brian Callahan <bcallah@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <ctype.h>
#include <err.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <term.h>
#include <unistd.h>

#include "freebee.h"
#include "version.h"

/*
 * Fisher-Yates shuffle
 */
static void
shuffle(int *a, int *b, int *c, int *d, int *e, int *f)
{
	int array[6], i, j, t;

	array[0] = *a;
	array[1] = *b;
	array[2] = *c;
	array[3] = *d;
	array[4] = *e;
	array[5] = *f;

	for (i = 5; i > 0; i--) {
		j = arc4random_uniform(i + 1);
		t = array[j];
		array[j] = array[i];
		array[i] = t;
	}

	*a = array[0];
	*b = array[1];
	*c = array[2];
	*d = array[3];
	*e = array[4];
	*f = array[5];
}

static void
show_answers(void)
{
	int printed = 7; /* Number of \n in heading */
	size_t i, j, queens;

	putp(clear_screen);

	putchar('\n');
	printf("          %c     %c\n\n", letters[0], letters[1]);
	printf("       %c     %c     %c\n\n", letters[2], letters[6], letters[3]);
	printf("          %c     %c\n\n", letters[4], letters[5]);

	for (i = 0; i < words; i++) {
		for (j = 0; wordlist[i][j] != '\n'; j++)
			putchar(wordlist[i][j]);
		putchar('\n');
		if (++printed > rows - 3) {
			while (getchar() != '\n')
				;
			putp(clear_screen);
			printed = 0;
		}
	}

	printf("\n");
	if (++printed > rows - 3) {
		while (getchar() != '\n')
			;
		putp(clear_screen);
		printed = 0;
	}
	printf("Total words:  %zu\n", words);
	if (++printed > rows - 3) {
		while (getchar() != '\n')
			;
		putp(clear_screen);
		printed = 0;
	}
	printf("Total points: %zu\n", total);
	if (++printed > rows - 3) {
		while (getchar() != '\n')
			;
		putp(clear_screen);
		printed = 0;
	}
	queens = total * 0.70;
	printf("Points for Queen Bee: %zu\n", queens);

	while (getchar() != '\n')
		;
}

static void
show_found(void)
{
	int printed = 0;
	size_t i;

	putp(clear_screen);
	for (i = 0; i < found; i++) {
		printf("%s", foundlist[i]);
		if (++printed > rows - 3) {
			while (getchar() != '\n')
				;
			putp(clear_screen);
			printed = 0;
		}
	}

	printf("\n");
	if (++printed > rows - 3) {
		while (getchar() != '\n')
			;
		putp(clear_screen);
		printed = 0;
	}
	printf("Words found: %zu\n", found);

	while (getchar() != '\n')
		;
}

static int
check(char *guess, int cont)
{
	char *g;
	int center = 0;

	for (g = guess; *g != '\n'; g++) {
		if (!isalpha(*g))
			return 0;
		if (isupper(*g))
			*g = tolower(*g);
		if (*g == letters[6])
			center = 1;
	}

	if (center == 0) {
		if (cont == 0) {
			printf("Must use center letter\n");
			while (getchar() != '\n')
				;
		}
		return 0;
	}

	if (strlen(guess) - 1 < 4) {
		if (cont == 0) {
			printf("Too short!\n");
			while (getchar() != '\n')
				;
		}
		return 0;
	}

	return 1;
}

static void
add_points(const char *guess)
{
	int one, two, three, four, five, six;
	int i = 0, j = 0;

	one = two = three = four = five = six = 0;

	if (daily == 1)
		fputs(guess, daily_save);

	if ((i = strlen(guess) - 1) < 7) {
		if (i == 4)
			i = 1;
		points += i;
		return;
	}

	i = 0;
	while (guess[i] != '\n') {
		for (j = 0; j < 7; j++) {
			if (guess[i] == letters[j]) {
				switch(j) {
				case 0:
					one = 1;
					break;
				case 1:
					two = 1;
					break;
				case 2:
					three = 1;
					break;
				case 3:
					four = 1;
					break;
				case 4:
					five = 1;
					break;
				case 5:
					six = 1;
				}
				break;
			}
		}
		++i;
	}

	if (one && two && three && four && five && six) {
		printf("Pangram!\n");
		points += (strlen(guess) - 1) + 7;
		while (getchar() != '\n')
			;
	} else {
		points += strlen(guess) - 1;
	}
}

static void
found_word(const char *guess)
{
	size_t i;

	for (i = 0; i < found; i++) {
		if (!strcmp(guess, foundlist[i])) {
			printf("Word already found\n");
			while (getchar() != '\n')
				;
			return;
		}
	}

	(void) strlcat(foundlist[i], guess, sizeof(foundlist[i]));

	++found;

	add_points(guess);
}

static void
find_word(const char *guess, int cont)
{
	size_t i;

	for (i = 0; i < words; i++) {
		if (!strcmp(guess, wordlist[i])) {
			found_word(guess);
			return;
		}
	}

	if (cont == 0) {
		printf("Word not in list\n");
	} else {
		printf("Invalid save file, starting anew\n");
		while (getchar() != '\n')
			;
		(void) memset(foundlist, 0, sizeof(foundlist));
		points = 0;
	}

	while (getchar() != '\n')
		;
}

static void
daily_continue(void)
{
	char *word = NULL;
	char buf[PATH_MAX];
	int ch;
	size_t wordsize = 0;
	ssize_t wordlen;

	(void) snprintf(buf, sizeof(buf), "%s/daily.txt", homedir);
	if ((daily_save = fopen(buf, "r")) == NULL) {
		if ((daily_save = fopen(buf, "w+")) == NULL)
			err(1, "fopen");

		return;
	}

	printf("You appear to have a saved game. Continue? (y/n) ");
	ch = getchar();
	while (getchar() != '\n')
		;

	if (ch == 'y' || ch == 'Y') {
		while ((wordlen = getline(&word, &wordsize, daily_save)) != -1) {
			if (check(word, 1) == 0) {
				printf("Invalid save file, starting anew\n");
				while (getchar() != '\n')
					;
				(void) memset(foundlist, 0, sizeof(foundlist));
				points = 0;
				break;
			}
			find_word(word, 1);
			if (points == 0)
				break;
		}
		free(word);

		(void) fclose(daily_save);
		if ((daily_save = fopen(buf, "a+")) == NULL)
			err(1, "fopen");

		return;
	}

	(void) fclose(daily_save);
	(void) unlink(buf);

	if ((daily_save = fopen(buf, "w+")) == NULL)
		return;
}

/*
 * Main loop
 */
void
play_game(void)
{
	char guess[32];
	int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5;
	int afirst = 0, qfirst = 0;

	if (daily == 1)
		daily_continue();

	while (1) {
		putp(clear_screen);
		printf("Free Bee %s | Score: %zu | Rank: %s | https://freebee.fun/\n\n", VERSION, points, rank());
		printf("          %c     %c\n\n", letters[a], letters[b]);
		printf("       %c     %c     %c\n\n", letters[c], letters[6], letters[d]);
		printf("          %c     %c\n\n", letters[e], letters[f]);

		if (qfirst == 0 && !strcmp(rank(), "Queen Bee!")) {
			printf("You have earned the rank of Queen Bee and won the game!\n");
			printf("You may continue playing. Can you find all the words? (y/n)\n");
			while (getchar() != '\n')
				;

			qfirst = 1;
		}

		if (afirst == 0 && found == words) {
			printf("You found all the words!\n");
			while (getchar() != '\n')
				;

			afirst = 1;
		}

		printf("? to shuffle\n");
		printf("! to display found words\n");
		if (daily == 0)
			printf("& to display answers\n");
		printf("; to quit\n\n");

		printf("Enter a word: ");
		(void) fgets(guess, sizeof(guess), stdin);

		if (guess[0] == ';')
			break;

		if (guess[0] == '?') {
			shuffle(&a, &b, &c, &d, &e, &f);
			continue;
		}

		if (guess[0] == '!') {
			show_found();
			continue;
		}

		if (daily == 0 && guess[0] == '&') {
			show_answers();
			continue;
		}

		if (check(guess, 0) == 0)
			continue;

		find_word(guess, 0);
	}
}
