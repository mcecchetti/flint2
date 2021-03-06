/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2010 William Hart

******************************************************************************/

#include <stdlib.h>
#include <mpir.h>
#include <mpfr.h>
#include "flint.h"
#include "mpfr_mat.h"

void
mpfr_mat_clear(mpfr_mat_t mat)
{
    if (mat->entries)
    {
        long i;
        for (i = 0; i < mat->r * mat->c; i++)
            mpfr_clear(mat->entries + i);   /* Clear all coefficients */
        flint_free(mat->entries);     /* Clean up array of entries */
        flint_free(mat->rows);        /* Clean up row array */
    }
}
