/**
 * Copyright (c) 2013 Vadim Ushakov
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "utils.h"
#include "atoms.h"
#include <X11/Xlib.h>
#include <stdlib.h>
#include <sde-utils.h>

void * su_x11_get_xa_property(Display * display, Window xid, Atom prop, Atom type, int *nitems)
{
    Atom type_ret;
    int format_ret;
    unsigned long items_ret;
    unsigned long after_ret;

    unsigned char * prop_data = NULL;

    if (XGetWindowProperty(display, xid, prop, 0, 0x7fffffff, False,
              type, &type_ret, &format_ret, &items_ret,
              &after_ret, &prop_data) != Success)
    {
        if (prop_data)
            XFree(prop_data);
        if (nitems)
            *nitems = 0;
        return NULL;
    }

    if (nitems)
        *nitems = items_ret;
    return prop_data;
}

void * su_x11_get_utf8_property(Display * display, Window win, Atom atom)
{
    Atom type;
    int format;
    gulong nitems;
    gulong bytes_after;
    gchar *val, *retval;
    int result;
    guchar *tmp = NULL;

    type = None;
    retval = NULL;
    result = XGetWindowProperty(display, win, atom, 0, G_MAXLONG, False,
          aUTF8_STRING, &type, &format, &nitems,
          &bytes_after, &tmp);
    if (result != Success || type == None)
        return NULL;
    val = (gchar *) tmp;
    if (val) {
        if (type == aUTF8_STRING && format == 8 && nitems != 0)
            retval = g_strndup (val, nitems);
        XFree (val);
    }
    return retval;
}

