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

#include <string.h>

#include "freebee.h"

static int
pangram(const char *word)
{
	char letters[7];
	int i, j = 0;

	memset(letters, 0, sizeof(letters));
	do {
		for (i = 0; i < sizeof(letters); i++) {
			if (*word == letters[i])
				break;
		}
		if (i == sizeof(letters) + 1)
			letters[j++] = *word;
	} while (*++word);

	/* Full array means we have a pangram.  */
	if (letters[6] != '\0')
		return 1;

	return 0;
}

int
add_score(const char *word)
{
	int points;

	if ((points = strlen(word)) < 4) {
		/* Too short!  */
		return 0;
	}

	if (points == 4)
		points = 1;

	/* Pangrams must be at least 7 letters.  */
	if (points > 6) {
		if ((pangram(word)) == 1)
			points += 7;
	}

	return points;
}
