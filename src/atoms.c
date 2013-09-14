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

#include "atoms.h"
#include <sde-utils.h>

static int atoms_resolved = False;

#define A(x) Atom a##x = 0;
#include "atom_names.h"
#undef A

enum {
    #define A(x) I##x,
    #include "atom_names.h"
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
        #include "atom_names.h"
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
    #include "atom_names.h"
    #undef A
}

