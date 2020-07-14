Free Bee
========
Free Bee is a free clone of The New York Times game Spelling Bee.

In this game, your goal is to find as many words as you can with the seven
letters you are given. Letters can be used more than once in a word. Finding
a word that uses all seven letters yields bonus points! Every game has at
least one such word, and many games have multiple. As you earn points, you
rise through the ranks of the hive, ultimately becoming the Queen Bee.

You can play the daily challenge like the original game or try your hand at a
nearly infinite number of computer-generated random challenges. Unlike the
original game, you are not restricted to only a single game per day!

The only notable difference between Free Bee and the original game is the use
 of the SOWPODS dictionary instead of the NYT dictionary. Patches welcome.

This is a very quickly made prototype for the terminal. Patches welcome.

There are plans to make this into a full-fledged desktop and web application.

Find us on the web at http://freebee.fun/

Dependencies
------------
Free Bee depends on `ncurses` for some screen handling routines and `libcurl`
for network routines. Both should be easily installable on your operating
system.

Compiling
---------
Just run `make`. Development of Free Bee is done on OpenBSD and I'm using
some OpenBSD extensions, so Linux people might need to add `libbsd` as needed.

A GNU autotools `configure` script is coming to make things even easier.

License
-------
ISC License. See LICENSE for details.
