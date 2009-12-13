/*============================================================================

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

===============================================================================*/
/****************************************************************************

   Copyright (C) 2009 William Hart

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"

void fmpz_fdiv_q(fmpz_t f, const fmpz_t g, const fmpz_t h)
{
	fmpz c1 = *g;
	fmpz c2 = *h;
	
   if (fmpz_is_zero(h))
   {
      printf("Exception : divide by zero in fmpz_cdiv_q\n");
      abort();
   }

   if (!COEFF_IS_MPZ(c1)) // g is small
	{
	   if (!COEFF_IS_MPZ(c2)) // h is also small
		{
			fmpz q = c1 / c2; // compute C quotient
			fmpz r = c1 - c2*q; // compute remainder
			
         if ((c2 > 0L) && (r < 0L)) q--; // q cannot overflow as remainder implies |c2| != 1
			else if ((c2 < 0L) && (r > 0L)) q--;
         
         fmpz_set_si(f, q);
		} else // h is large and g is small
		{
			if (c1 == 0L) fmpz_set_ui(f, 0L); // g is zero
			else if (((c1 < 0L) && (fmpz_sgn(h) < 0)) || 
				      ((c1 > 0L) && (fmpz_sgn(h) > 0))) // signs are the same
				fmpz_zero(f); // quotient is positive, round down to zero
			else fmpz_set_si(f, -1L); // quotient is negative, round down to minus one        
		}
	} else // g is large
	{   
		__mpz_struct * mpz_ptr = _fmpz_promote(f);
		
		if (!COEFF_IS_MPZ(c2)) // h is small
		{
		   if (c2 > 0) // h > 0
			{
            mpz_fdiv_q_ui(mpz_ptr, COEFF_TO_PTR(c1), c2);
			   _fmpz_demote_val(f); // division by h may result in small value		
			} else
			{
            mpz_cdiv_q_ui(mpz_ptr, COEFF_TO_PTR(c1), -c2);
			   _fmpz_demote_val(f); // division by h may result in small value
				
				fmpz_neg(f, f);
			}
		} else // both are large
		{
			mpz_fdiv_q(mpz_ptr, COEFF_TO_PTR(c1), COEFF_TO_PTR(c2));
			_fmpz_demote_val(f); // division by h may result in small value		
		}	
	}
}