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

#include <sde-utils-x11/atoms.h>
#include <sde-utils.h>

static int atoms_resolved = False;

#define A(x) Atom a##x = 0;
#include <sde-utils-x11/atom_names.h>
#undef A

enum {
    #define A(x) I##x,
    #include <sde-utils-x11/atom_names.h>
    #undef A
    N_ATOMS
};

void su_x11_resolve_well_known_atoms(Display * display)
{
    if (atoms_resolved)
        return;

    atoms_resolved = True;

    static const char * atom_names[ N_ATOMS ] = {
        #define A(x) #x,
        #include <sde-utils-x11/atom_names.h>
        #undef A
    };

    Atom atoms[ N_ATOMS ];

#ifndef DEBUG
    if( !  XInternAtoms(display, (char**)atom_names,
            N_ATOMS, False, atoms ) )
    {
        su_log_error("Error: unable to return Atoms");
        return;
    }
#else
    int i;
    for (i = 0; i < N_ATOMS; i++) {
        su_log_debug("Registering atom %s\n", atom_names[i]);
        if( !  XInternAtoms(display, ((char**)atom_names) + i,
               1, False, atoms + i) )
        {
            su_log_error("Error: unable to return Atoms");
            return;
        }
    }
#endif

    #define A(x) a##x = atoms[ I##x ];
    #include <sde-utils-x11/atom_names.h>
    #undef A
}

