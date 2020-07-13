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

#include <stdio.h>

#include "freebee.h"

const char *
rank(void)
{

	if (points >= queen)
		return "Queen Bee!";
	else if (points >= forager)
		return "Forager";
	else if (points >= guard)
		return "Guard";
	else if (points >= builder)
		return "Builder";
	else if (points >= feeder)
		return "Feeder";
	else if (points >= drone)
		return "Drone";
	else if (points >= hatchling)
		return "Hatchling";
	else if (points >= larva)
		return "Larva";

	return "Egg";
}

void
set_rank(void)
{

	larva = total * 0.02;
	hatchling = total * 0.05;
	drone = total * 0.08;
	feeder = total * 0.15;
	builder = total * 0.25;
	guard = total * 0.40;
	forager = total * 0.50;
	queen = total * 0.70;
}
