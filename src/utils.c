/**
 * Copyright (c) 2013 Vadim Ushakov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <sde-utils-x11/utils.h>
#include <sde-utils-x11/atoms.h>
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

