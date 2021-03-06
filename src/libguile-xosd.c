/* libguile-xosd.c --- Guile bindings for libxosd
 *
 * Copyright (C) 2004, 2005 Yann Hodique <Yann.Hodique@lifl.fr>
 * Copyright (C) 2016 Alex Kost <alezost@gmail.com>
 *
 * Created: 10 Oct 2004
 *
 * This file is part of Guile-XOSD.
 *
 * Guile-XOSD is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Guile-XOSD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Guile-XOSD.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <libguile.h>
#include <xosd.h>

static scm_t_bits xosd_tag;

#define XOSD(x) ((xosd *) SCM_SMOB_DATA(x))

inline void
error (const char *msg, SCM args)
{
  scm_error (scm_from_utf8_symbol("xosd-error"),
             NULL, msg, args, SCM_BOOL_F);
}

SCM_DEFINE_PUBLIC (scm_xosd_set_bar_length,
                   "xosd-set-bar-length!",
                   2, 0, 0,
                   (SCM osd, SCM n),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-set-bar-length!");
    SCM_ASSERT(scm_is_integer(n), n, SCM_ARG2,
               "xosd-set-bar-length!");
    xosd_set_bar_length(XOSD(osd), scm_to_int(n));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_is_onscreen,
                   "xosd-onscreen?",
                   1, 0, 0,
                   (SCM osd),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-onscreen?");
    return (xosd_is_onscreen(XOSD(osd)))?SCM_BOOL_T:SCM_BOOL_F;
}

SCM_DEFINE_PUBLIC (scm_xosd_wait_until_no_display,
                   "xosd-wait-until-no-display",
                   1, 0, 0,
                   (SCM osd),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-wait-until-nodisplay");
    xosd_wait_until_no_display(XOSD(osd));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_hide,
                   "xosd-hide",
                   1, 0, 0,
                   (SCM osd),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-hide");
    xosd_hide(XOSD(osd));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_show,
                   "xosd-show",
                   1, 0, 0,
                   (SCM osd),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-show");
    xosd_show(XOSD(osd));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_set_pos,
                   "xosd-set-pos!",
                   2, 0, 0,
                   (SCM osd, SCM pos),
                   "")
{
    int xosd_pos;
    char *pos_str;

    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-set-pos!");
    SCM_ASSERT(scm_is_symbol(pos), pos, SCM_ARG2,
               "xosd-set-pos!");

    pos_str = scm_to_locale_string(scm_symbol_to_string(pos));
    if (!strcmp("top", pos_str))
        xosd_pos = XOSD_top;
    else if (!strcmp("bottom", pos_str))
        xosd_pos = XOSD_bottom;
    else if (!strcmp("middle", pos_str))
        xosd_pos = XOSD_middle;
    else
        error("Unknown position: ~S", scm_list_1(pos));

    xosd_set_pos(XOSD(osd), xosd_pos);
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_set_align,
                   "xosd-set-align!",
                   2, 0, 0,
                   (SCM osd, SCM align),
                   "")
{
    int xosd_align;
    char *align_str;

    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-set-align!");
    SCM_ASSERT(scm_is_symbol(align), align, SCM_ARG2,
               "xosd-set-align!");

    align_str = scm_to_locale_string(scm_symbol_to_string(align));
    if (!strcmp("left", align_str))
        xosd_align = XOSD_left;
    else if (!strcmp("right", align_str))
        xosd_align = XOSD_right;
    else if (!strcmp("center", align_str))
        xosd_align = XOSD_center;
    else
        error("Unknown align: ~S", scm_list_1(align));

    xosd_set_align(XOSD(osd), xosd_align);
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_set_shadow_offset,
                   "xosd-set-shadow-offset!",
                   2, 0, 0,
                   (SCM osd, SCM n),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-set-shadow-offset!");
    SCM_ASSERT(scm_is_integer(n), n, SCM_ARG2,
               "xosd-set-shadow-offset!");
    xosd_set_shadow_offset(XOSD(osd), scm_to_int(n));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_set_outline_offset,
                   "xosd-set-outline-offset!",
                   2, 0, 0,
                   (SCM osd, SCM n),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-set-outline-offset!");
    SCM_ASSERT(scm_is_integer(n), n, SCM_ARG2,
               "xosd-set-outline-offset!");
    xosd_set_outline_offset(XOSD(osd), scm_to_int(n));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_set_horizontal_offset,
                   "xosd-set-horizontal-offset!",
                   2, 0, 0,
                   (SCM osd, SCM n),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-set-horizontal-offset!");
    SCM_ASSERT(scm_is_integer(n), n, SCM_ARG2,
               "xosd-set-horizontal-offset!");
    xosd_set_horizontal_offset(XOSD(osd), scm_to_int(n));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_set_vertical_offset,
                   "xosd-set-vertical-offset!",
                   2, 0, 0,
                   (SCM osd, SCM n),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-set-vertival-offset!");
    SCM_ASSERT(scm_is_integer(n), n, SCM_ARG2,
               "xosd-set-vertical-offset!");
    xosd_set_vertical_offset(XOSD(osd), scm_to_int(n));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_set_timeout,
                   "xosd-set-timeout!",
                   2, 0, 0,
                   (SCM osd, SCM time),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-set-timeout!");
    SCM_ASSERT(scm_is_integer(time), time, SCM_ARG2,
               "xosd-set-timeout!");
    xosd_set_timeout(XOSD(osd), scm_to_int(time));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_scroll,
                   "xosd-scroll",
                   2, 0, 0,
                   (SCM osd, SCM n),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-scroll");
    SCM_ASSERT(scm_is_integer(n), n, SCM_ARG2,
               "xosd-scroll");
    xosd_scroll(XOSD(osd), scm_to_int(n));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_set_outline_colour,
                   "xosd-set-outline-colour!",
                   2, 0, 0,
                   (SCM osd, SCM str),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-set-outline-colour!");
    SCM_ASSERT(scm_is_string(str), str, SCM_ARG2,
               "xosd-set-outline-colour!");
    xosd_set_outline_colour(XOSD(osd), scm_to_locale_string(str));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_set_shadow_colour,
                   "xosd-set-shadow-colour!",
                   2, 0, 0,
                   (SCM osd, SCM str),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-set-shadow-colour!");
    SCM_ASSERT(scm_is_string(str), str, SCM_ARG2,
               "xosd-set-shadow-colour!");
    xosd_set_shadow_colour(XOSD(osd), scm_to_locale_string(str));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_set_colour,
                   "xosd-set-colour!",
                   2, 0, 0,
                   (SCM osd, SCM str),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-set-colour!");
    SCM_ASSERT(scm_is_string(str), str, SCM_ARG2,
               "xosd-set-colour!");
    xosd_set_colour(XOSD(osd), scm_to_locale_string(str));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_set_font,
                   "xosd-set-font!",
                   2, 0, 0,
                   (SCM osd, SCM str),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-set-font!");
    SCM_ASSERT(scm_is_string(str), str, SCM_ARG2,
               "xosd-set-font!");
    xosd_set_font(XOSD(osd), scm_to_locale_string(str));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_get_colour,
                   "xosd-get-colour",
                   1, 0, 0,
                   (SCM osd),
                   "")
{
    int r, g, b;
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-get-colour");
    xosd_get_colour(XOSD(osd), &r, &g, &b);
    return scm_cons(scm_from_int(r),
                    scm_cons(scm_from_int(g),
                             scm_cons(scm_from_int(b),
                                      SCM_EOL)));
}

SCM_DEFINE_PUBLIC (scm_xosd_get_number_lines,
                   "xosd-get-number-lines",
                   1, 0, 0,
                   (SCM osd),
                   "")
{
    int lines;
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-get-number-lines");
    lines = xosd_get_number_lines(XOSD(osd));
    return scm_from_int(lines);
}

SCM_DEFINE_PUBLIC (scm_xosd_display_string,
                   "xosd-display-string",
                   3, 0, 0,
                   (SCM osd, SCM line, SCM str),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-display-string");
    SCM_ASSERT(scm_is_integer(line), line, SCM_ARG2,
               "xosd-display-string");
    SCM_ASSERT(scm_is_string(str), str, SCM_ARG3,
               "xosd-display-string");
    xosd_display(XOSD(osd), scm_to_int(line),
                 XOSD_string, scm_to_locale_string(str));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_display_percentage,
                   "xosd-display-percentage",
                   3, 0, 0,
                   (SCM osd, SCM line, SCM per),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-display-percentage");
    SCM_ASSERT(scm_is_integer(line), line, SCM_ARG2,
               "xosd-display-percentage");
    SCM_ASSERT(scm_is_integer(per), per, SCM_ARG3,
               "xosd-display-percentage");
    xosd_display(XOSD(osd), scm_to_int(line),
                 XOSD_percentage, scm_to_int(per));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_display_slider,
                   "xosd-display-slider",
                   3, 0, 0,
                   (SCM osd, SCM line, SCM per),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-display-slider");
    SCM_ASSERT(scm_is_integer(line), line, SCM_ARG2,
               "xosd-display-slider");
    SCM_ASSERT(scm_is_integer(per), per, SCM_ARG3,
               "xosd-display-slider");
    xosd_display(XOSD(osd), scm_to_int(line),
                 XOSD_slider, scm_to_int(per));
    return SCM_UNSPECIFIED;
}

SCM_DEFINE_PUBLIC (scm_xosd_create,
                   "xosd-create",
                   0, 1, 0,
                   (SCM n),
                   "")
{
    xosd *osd;
    int lines;
    if (SCM_UNBNDP(n)) {
        lines = 1;
    } else {
        SCM_ASSERT(scm_is_integer(n), n, SCM_ARG1, "xosd-create");
        lines = scm_to_int(n);
        if (lines < 1)
            error("The number of OSD lines should be more than 0",
                  SCM_BOOL_F);
    }
    osd = xosd_create(lines);
    if (!osd)
        /* Maybe DISPLAY is not set, or connection to X server failed. */
        error("Error during creating xosd object", SCM_BOOL_F);
    SCM_RETURN_NEWSMOB(xosd_tag, osd);
}

SCM_DEFINE_PUBLIC (scm_xosd_destroy,
                   "xosd-destroy",
                   1, 0, 0,
                   (SCM osd),
                   "")
{
    SCM_ASSERT(SCM_SMOB_PREDICATE(xosd_tag, osd), osd, SCM_ARG1,
               "xosd-destroy");
    xosd_destroy(XOSD(osd));
    return SCM_UNSPECIFIED;
}

static SCM
mark_xosd (SCM xosd_smob)
{
    return SCM_BOOL_F;
}

static size_t
free_xosd (SCM xosd_smob)
{
    xosd *osd = XOSD(xosd_smob);
    xosd_destroy(osd);
    return sizeof(xosd*);
}

void
init_xosd (void)
{
    xosd_tag = scm_make_smob_type("xosd", sizeof(xosd*));
    scm_set_smob_mark(xosd_tag, mark_xosd);
    scm_set_smob_free(xosd_tag, free_xosd);

#ifndef SCM_MAGIC_SNARFER
#include "libguile-xosd.x"
#endif
}

/* libguile-xosd.c ends here */
