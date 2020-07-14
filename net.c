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

#include <curl/curl.h>

#include <limits.h>
#include <stdio.h>
#include <term.h>
#include <unistd.h>

#include "freebee.h"

void
today(void)
{
	CURL *curl;
	FILE *fp;
	char buf[PATH_MAX];
	int ch, i = 0;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://freebee.fun/daily/today.txt");

		/* use a GET to fetch this */
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

		(void) unlink(buf);
		(void) snprintf(buf, sizeof(buf), "%s/today.txt", homedir);
		if ((fp = fopen(buf, "w+")) == NULL)
			return;

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
 
		/* Perform the request */
		curl_easy_perform(curl);

		curl_easy_cleanup(curl);

		(void) fseek(fp, 0L, SEEK_SET);
		while ((ch = fgetc(fp)) != EOF) {
			if (i > 6)
				break;
			letters[i++] = ch;
		}

		(void) fclose(fp);

		(void) unlink(buf);
	}
}

void
yesterday(void)
{
	CURL *curl;
	FILE *fp;
	char buf[PATH_MAX];
	int ch, printed = 0;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://freebee.fun/daily/yesterday.txt");

		/* use a GET to fetch this */
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

		(void) snprintf(buf, sizeof(buf), "%s/yesterday.txt", homedir);
		if ((fp = fopen(buf, "w+")) == NULL)
			return;

		(void) unlink(buf);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
 
		/* Perform the request */
		curl_easy_perform(curl);

		curl_easy_cleanup(curl);

		(void) fseek(fp, 0L, SEEK_SET);

		putp(clear_screen);
		while ((ch = fgetc(fp)) != EOF) {
			fputc(ch, stdout);
			if (ch == '\n') {
				if (++printed > rows - 4) {
					while (getchar() != '\n')
						;
					putp(clear_screen);
					printed = 0;
				}
			}
		}

		(void) fclose(fp);
		(void) unlink(buf);

		while (getchar() != '\n')
			;
	}
}
