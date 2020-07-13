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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freebee.h"
#include "version.h"

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
show_found(void)
{
	size_t i;

	system("clear");
	for (i = 0; i < found; i++)
		printf("%s", foundlist[i]);

	printf("\nPress Enter to return\n");
	(void) getchar();
}

static int
check(const char *guess)
{
	const char *g;
	int center = 0;

	for (g = guess; *g != '\n'; g++) {
		if (!isalpha(*g))
			return 0;
		if (*g == letters[6])
			center = 1;
	}

	if (center == 0) {
		printf("Must use special letter\n");
		(void) getchar();
		return 0;
	}

	if (strlen(guess) - 1 < 4) {
		printf("Too short!\n");
		(void) getchar();
		return 0;
	}

	return 1;
}

static void
add_points(const char *guess)
{
	int one, two, three, four, five, six, special;
	int i = 0, j = 0;

	one = two = three = four = five = six = special = 0;

	if ((i = strlen(guess) - 1) < 7) {
		if (i == 4)
			i = 1;
		points += i;
		return;
	}

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
					break;
				case 6:
					special = 1;
					break;
				}
				break;
			}
			++i;
		}
	}
	if (special && one && two && three && four && five && six)
		points += (strlen(guess) - 1) + 7;
	else
		points += strlen(guess) - 1;
}

static void
found_word(const char *guess)
{
	size_t i;

	for (i = 0; i < found; i++) {
		if (!strcmp(guess, foundlist[i])) {
			printf("Word already found\n");
			(void) getchar();
			return;
		}
	}

	(void) strlcat(foundlist[i], guess, sizeof(foundlist[i]));

	++found;

	add_points(guess);
}

static void
find_word(const char *guess)
{
	size_t i;

	for (i = 0; i < words; i++) {
		if (!strcmp(guess, wordlist[i])) {
			found_word(guess);
			return;
		}
	}

	printf("Word not in list\n");

	(void) getchar();
}

void
play_game(void)
{
	char guess[32];
	int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5;

	while (1) {
		system("clear");
		printf("Free Bee %s | Score: %zu\n\n", VERSION, points);
		printf("          %c     %c\n\n", letters[a], letters[b]);
		printf("       %c     %c     %c\n\n", letters[c], letters[6], letters[d]);
		printf("          %c     %c\n\n", letters[e], letters[f]);

		if (found == words) {
			printf("You found all the words!\n");
			(void) getchar();
			break;
		}

		printf("? to shuffle\n");
		printf("! to display found words\n");
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

		if (check(guess) == 0)
			continue;

		find_word(guess);
	}
}
