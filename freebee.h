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

#ifndef DICTIONARY
#define DICTIONARY "/usr/local/share/freebee/sowpods.txt"
#endif

extern FILE *daily_save;

extern char *term;

extern char foundlist[2000][17];
extern char homedir[PATH_MAX];
extern char letters[8];
extern char wordlist[2000][17];

extern int daily;

extern size_t found;
extern size_t points;
extern size_t total;
extern size_t words;

/* Score ranks  */
extern size_t egg;
extern size_t larva;
extern size_t hatchling;
extern size_t drone;
extern size_t feeder;
extern size_t builder;
extern size_t guard;
extern size_t forager;
extern size_t queen;

extern const char *rank(void);

extern void create_anagrams(void);
extern void create_dir(void);
extern void play_game(void);
extern void set_rank(void);
extern void today(void);
extern void yesterday(void);
