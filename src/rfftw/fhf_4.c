/*
 * Copyright (c) 1997-1999 Massachusetts Institute of Technology
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Sun Nov  7 20:44:43 EST 1999 */

#include <fftw-int.h>
#include <fftw.h>

/* Generated by: ./genfft -magic-alignment-check -magic-twiddle-load-all -magic-variables 4 -magic-loopi -hc2hc-forward 4 */

/*
 * This function contains 34 FP additions, 14 FP multiplications,
 * (or, 28 additions, 8 multiplications, 6 fused multiply/add),
 * 15 stack variables, and 32 memory accesses
 */
static const fftw_real K707106781 = FFTW_KONST(+0.707106781186547524400844362104849039284835938);

/*
 * Generator Id's : 
 * $Id: fhf_4.c,v 1.1 2006/05/12 15:14:48 veplaini Exp $
 * $Id: fhf_4.c,v 1.1 2006/05/12 15:14:48 veplaini Exp $
 * $Id: fhf_4.c,v 1.1 2006/05/12 15:14:48 veplaini Exp $
 */

void fftw_hc2hc_forward_4(fftw_real *A, const fftw_complex *W, int iostride, int m, int dist)
{
     int i;
     fftw_real *X;
     fftw_real *Y;
     X = A;
     Y = A + (4 * iostride);
     {
	  fftw_real tmp35;
	  fftw_real tmp36;
	  fftw_real tmp37;
	  fftw_real tmp38;
	  fftw_real tmp39;
	  fftw_real tmp40;
	  ASSERT_ALIGNED_DOUBLE;
	  tmp35 = X[0];
	  tmp36 = X[2 * iostride];
	  tmp37 = tmp35 + tmp36;
	  tmp38 = X[iostride];
	  tmp39 = X[3 * iostride];
	  tmp40 = tmp38 + tmp39;
	  X[iostride] = tmp35 - tmp36;
	  Y[-iostride] = -(tmp38 - tmp39);
	  X[2 * iostride] = tmp37 - tmp40;
	  X[0] = tmp37 + tmp40;
     }
     X = X + dist;
     Y = Y - dist;
     for (i = 2; i < m; i = i + 2, X = X + dist, Y = Y - dist, W = W + 3) {
	  fftw_real tmp7;
	  fftw_real tmp30;
	  fftw_real tmp12;
	  fftw_real tmp29;
	  fftw_real tmp18;
	  fftw_real tmp26;
	  fftw_real tmp23;
	  fftw_real tmp27;
	  ASSERT_ALIGNED_DOUBLE;
	  tmp7 = X[0];
	  tmp30 = Y[-3 * iostride];
	  {
	       fftw_real tmp9;
	       fftw_real tmp11;
	       fftw_real tmp8;
	       fftw_real tmp10;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp9 = X[2 * iostride];
	       tmp11 = Y[-iostride];
	       tmp8 = c_re(W[1]);
	       tmp10 = c_im(W[1]);
	       tmp12 = (tmp8 * tmp9) - (tmp10 * tmp11);
	       tmp29 = (tmp10 * tmp9) + (tmp8 * tmp11);
	  }
	  {
	       fftw_real tmp15;
	       fftw_real tmp17;
	       fftw_real tmp14;
	       fftw_real tmp16;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp15 = X[iostride];
	       tmp17 = Y[-2 * iostride];
	       tmp14 = c_re(W[0]);
	       tmp16 = c_im(W[0]);
	       tmp18 = (tmp14 * tmp15) - (tmp16 * tmp17);
	       tmp26 = (tmp16 * tmp15) + (tmp14 * tmp17);
	  }
	  {
	       fftw_real tmp20;
	       fftw_real tmp22;
	       fftw_real tmp19;
	       fftw_real tmp21;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp20 = X[3 * iostride];
	       tmp22 = Y[0];
	       tmp19 = c_re(W[2]);
	       tmp21 = c_im(W[2]);
	       tmp23 = (tmp19 * tmp20) - (tmp21 * tmp22);
	       tmp27 = (tmp21 * tmp20) + (tmp19 * tmp22);
	  }
	  {
	       fftw_real tmp13;
	       fftw_real tmp24;
	       fftw_real tmp33;
	       fftw_real tmp34;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp13 = tmp7 + tmp12;
	       tmp24 = tmp18 + tmp23;
	       Y[-2 * iostride] = tmp13 - tmp24;
	       X[0] = tmp13 + tmp24;
	       tmp33 = tmp18 - tmp23;
	       tmp34 = tmp30 - tmp29;
	       X[3 * iostride] = -(tmp33 + tmp34);
	       Y[-iostride] = tmp34 - tmp33;
	  }
	  {
	       fftw_real tmp31;
	       fftw_real tmp32;
	       fftw_real tmp25;
	       fftw_real tmp28;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp31 = tmp29 + tmp30;
	       tmp32 = tmp26 + tmp27;
	       X[2 * iostride] = -(tmp31 - tmp32);
	       Y[0] = tmp32 + tmp31;
	       tmp25 = tmp7 - tmp12;
	       tmp28 = tmp26 - tmp27;
	       Y[-3 * iostride] = tmp25 - tmp28;
	       X[iostride] = tmp25 + tmp28;
	  }
     }
     if (i == m) {
	  fftw_real tmp1;
	  fftw_real tmp6;
	  fftw_real tmp4;
	  fftw_real tmp5;
	  fftw_real tmp2;
	  fftw_real tmp3;
	  ASSERT_ALIGNED_DOUBLE;
	  tmp1 = X[0];
	  tmp6 = X[2 * iostride];
	  tmp2 = X[iostride];
	  tmp3 = X[3 * iostride];
	  tmp4 = K707106781 * (tmp2 - tmp3);
	  tmp5 = K707106781 * (tmp2 + tmp3);
	  X[iostride] = tmp1 - tmp4;
	  X[0] = tmp1 + tmp4;
	  Y[0] = -(tmp5 + tmp6);
	  Y[-iostride] = tmp6 - tmp5;
     }
}

static const int twiddle_order[] =
{1, 2, 3};
fftw_codelet_desc fftw_hc2hc_forward_4_desc =
{
     "fftw_hc2hc_forward_4",
     (void (*)()) fftw_hc2hc_forward_4,
     4,
     FFTW_FORWARD,
     FFTW_HC2HC,
     91,
     3,
     twiddle_order,
};
