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

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freebee.h"

/*
 * The seventh letter is the center letter.
 * All valid words must have at least 1 occurance of it.
 */
void
create_anagrams(void)
{
	FILE *fp;
	char *word = NULL, *w;
	char letters[8];
	int pangram, words;
	int one, two, three, four, five, six;
	size_t i, j, wordsize = 0;
	ssize_t wordlen, special, yes;
	char wordlist[1024 * 1024];

	if ((fp = fopen("sowpods.txt", "r")) == NULL)
		err(1, "fopen");

again:
	/* Start by generated 7 random distinct letters.  */
	(void) memset(letters, 0, sizeof(letters));
	for (i = 0; i < sizeof(letters) - 1; i++) {
bad:
		letters[i] = (unsigned char) arc4random_uniform(26) + 'a';
		for (j = 0; j < i; j++) {
			if (letters[j] == letters[i])
				goto bad;
		}
	}

	/* Create anagrams.  */
	(void) memset(wordlist, 0, sizeof(wordlist));
	pangram = 0;
	words = 0;
	while ((wordlen = getline(&word, &wordsize, fp)) != -1) {
		j = 0;
		special = 0;
		yes = 0;
		one = two = three = four = five = six = 0;
		while (word[j] != '\n') {
			for (i = 0; i < 7; i++) {
				if (word[j] == letters[i]) {
					++yes;
					switch (i) {
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
					}
					break;
				}
			}
			++j;
		}
		if (special && yes == wordlen - 1) {
			++words;
			(void) strlcat(wordlist, word, sizeof(wordlist));
			if (special && one && two && three && four && five && six)
				pangram = 1;
		}
	}

	/* Not a good game, try again.  */
	if (!pangram || words < 30 || words > 100) {
		(void) fseek(fp, 0L, SEEK_SET);
		goto again;
	}

	puts(letters);
	putchar('\n');
	puts(wordlist);

	(void) fclose(fp);
}
