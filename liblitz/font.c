/*
 * (C)opyright MMIV-MMVI Anselm R. Garbe <garbeam at gmail dot com>
 * See LICENSE file for license details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <cext.h>

#include "blitz.h"

void
blitz_loadfont(Display *dpy, BlitzFont *font, char *fontstr)
{
	char *fontname = fontstr;
	char **missing = nil, *def = "?";
	int nmissing;
	if(font->set)
		XFreeFontSet(dpy, font->set);
	if(font->xfont)
		XFreeFont(dpy, font->xfont);
	font->xfont = XLoadQueryFont(dpy, fontname);
	if (!font->xfont) {
		fontname = "fixed";
		font->xfont = XLoadQueryFont(dpy, fontname);
	}
	if (!font->xfont) {
		fprintf(stderr, "%s", "liblitz: error, cannot load 'fixed' font\n");
		exit(1);
	}
	font->set = XCreateFontSet(dpy, fontname, &missing, &nmissing, &def);

	if(missing)
		XFreeStringList(missing);
}