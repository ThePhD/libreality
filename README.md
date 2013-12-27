libreality
==========

The GPL is not magic.

This piece of the Furrovine Engine that supports querying file contents and extensions to get their true type. If you want more files types to be supported, just make a pull request and add it to the `reality.cpp` file.

Meant to be a replacement for the lame and annoying GPLv2 "libmagic": in fairytale land, GPL is best license. In reality, not so much.

All necessary source is included. There's a Visual Studio solution if you want, but you can easily makefile this into a lovely little shared library: it's using basic C++11 to get the job done.
