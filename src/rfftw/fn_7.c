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
/* Generated on Sun Nov  7 20:43:47 EST 1999 */

#include <fftw-int.h>
#include <fftw.h>

/* Generated by: ./genfft -magic-alignment-check -magic-twiddle-load-all -magic-variables 4 -magic-loopi -notwiddle 7 */

/*
 * This function contains 60 FP additions, 36 FP multiplications,
 * (or, 60 additions, 36 multiplications, 0 fused multiply/add),
 * 22 stack variables, and 28 memory accesses
 */
static const fftw_real K222520933 = FFTW_KONST(+0.222520933956314404288902564496794759466355569);
static const fftw_real K900968867 = FFTW_KONST(+0.900968867902419126236102319507445051165919162);
static const fftw_real K623489801 = FFTW_KONST(+0.623489801858733530525004884004239810632274731);
static const fftw_real K433883739 = FFTW_KONST(+0.433883739117558120475768332848358754609990728);
static const fftw_real K974927912 = FFTW_KONST(+0.974927912181823607018131682993931217232785801);
static const fftw_real K781831482 = FFTW_KONST(+0.781831482468029808708444526674057750232334519);

/*
 * Generator Id's : 
 * $Id: fn_7.c,v 1.1 2006/05/12 15:14:58 veplaini Exp $
 * $Id: fn_7.c,v 1.1 2006/05/12 15:14:58 veplaini Exp $
 * $Id: fn_7.c,v 1.1 2006/05/12 15:14:58 veplaini Exp $
 */

void fftw_no_twiddle_7(const fftw_complex *input, fftw_complex *output, int istride, int ostride)
{
     fftw_real tmp1;
     fftw_real tmp30;
     fftw_real tmp4;
     fftw_real tmp26;
     fftw_real tmp14;
     fftw_real tmp33;
     fftw_real tmp7;
     fftw_real tmp28;
     fftw_real tmp20;
     fftw_real tmp31;
     fftw_real tmp10;
     fftw_real tmp27;
     fftw_real tmp17;
     fftw_real tmp32;
     ASSERT_ALIGNED_DOUBLE;
     tmp1 = c_re(input[0]);
     tmp30 = c_im(input[0]);
     {
	  fftw_real tmp2;
	  fftw_real tmp3;
	  fftw_real tmp12;
	  fftw_real tmp13;
	  ASSERT_ALIGNED_DOUBLE;
	  tmp2 = c_re(input[istride]);
	  tmp3 = c_re(input[6 * istride]);
	  tmp4 = tmp2 + tmp3;
	  tmp26 = tmp3 - tmp2;
	  tmp12 = c_im(input[istride]);
	  tmp13 = c_im(input[6 * istride]);
	  tmp14 = tmp12 - tmp13;
	  tmp33 = tmp12 + tmp13;
     }
     {
	  fftw_real tmp5;
	  fftw_real tmp6;
	  fftw_real tmp18;
	  fftw_real tmp19;
	  ASSERT_ALIGNED_DOUBLE;
	  tmp5 = c_re(input[2 * istride]);
	  tmp6 = c_re(input[5 * istride]);
	  tmp7 = tmp5 + tmp6;
	  tmp28 = tmp6 - tmp5;
	  tmp18 = c_im(input[2 * istride]);
	  tmp19 = c_im(input[5 * istride]);
	  tmp20 = tmp18 - tmp19;
	  tmp31 = tmp18 + tmp19;
     }
     {
	  fftw_real tmp8;
	  fftw_real tmp9;
	  fftw_real tmp15;
	  fftw_real tmp16;
	  ASSERT_ALIGNED_DOUBLE;
	  tmp8 = c_re(input[3 * istride]);
	  tmp9 = c_re(input[4 * istride]);
	  tmp10 = tmp8 + tmp9;
	  tmp27 = tmp9 - tmp8;
	  tmp15 = c_im(input[3 * istride]);
	  tmp16 = c_im(input[4 * istride]);
	  tmp17 = tmp15 - tmp16;
	  tmp32 = tmp15 + tmp16;
     }
     {
	  fftw_real tmp23;
	  fftw_real tmp22;
	  fftw_real tmp35;
	  fftw_real tmp36;
	  ASSERT_ALIGNED_DOUBLE;
	  c_re(output[0]) = tmp1 + tmp4 + tmp7 + tmp10;
	  tmp23 = (K781831482 * tmp14) + (K974927912 * tmp20) + (K433883739 * tmp17);
	  tmp22 = tmp1 + (K623489801 * tmp4) - (K900968867 * tmp10) - (K222520933 * tmp7);
	  c_re(output[6 * ostride]) = tmp22 - tmp23;
	  c_re(output[ostride]) = tmp22 + tmp23;
	  {
	       fftw_real tmp25;
	       fftw_real tmp24;
	       fftw_real tmp21;
	       fftw_real tmp11;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp25 = (K433883739 * tmp14) + (K974927912 * tmp17) - (K781831482 * tmp20);
	       tmp24 = tmp1 + (K623489801 * tmp7) - (K222520933 * tmp10) - (K900968867 * tmp4);
	       c_re(output[4 * ostride]) = tmp24 - tmp25;
	       c_re(output[3 * ostride]) = tmp24 + tmp25;
	       tmp21 = (K974927912 * tmp14) - (K781831482 * tmp17) - (K433883739 * tmp20);
	       tmp11 = tmp1 + (K623489801 * tmp10) - (K900968867 * tmp7) - (K222520933 * tmp4);
	       c_re(output[5 * ostride]) = tmp11 - tmp21;
	       c_re(output[2 * ostride]) = tmp11 + tmp21;
	  }
	  c_im(output[0]) = tmp30 + tmp33 + tmp31 + tmp32;
	  tmp35 = (K781831482 * tmp26) + (K974927912 * tmp28) + (K433883739 * tmp27);
	  tmp36 = tmp30 + (K623489801 * tmp33) - (K900968867 * tmp32) - (K222520933 * tmp31);
	  c_im(output[ostride]) = tmp35 + tmp36;
	  c_im(output[6 * ostride]) = tmp36 - tmp35;
	  {
	       fftw_real tmp29;
	       fftw_real tmp34;
	       fftw_real tmp37;
	       fftw_real tmp38;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp29 = (K433883739 * tmp26) + (K974927912 * tmp27) - (K781831482 * tmp28);
	       tmp34 = tmp30 + (K623489801 * tmp31) - (K222520933 * tmp32) - (K900968867 * tmp33);
	       c_im(output[3 * ostride]) = tmp29 + tmp34;
	       c_im(output[4 * ostride]) = tmp34 - tmp29;
	       tmp37 = (K974927912 * tmp26) - (K781831482 * tmp27) - (K433883739 * tmp28);
	       tmp38 = tmp30 + (K623489801 * tmp32) - (K900968867 * tmp31) - (K222520933 * tmp33);
	       c_im(output[2 * ostride]) = tmp37 + tmp38;
	       c_im(output[5 * ostride]) = tmp38 - tmp37;
	  }
     }
}

fftw_codelet_desc fftw_no_twiddle_7_desc =
{
     "fftw_no_twiddle_7",
     (void (*)()) fftw_no_twiddle_7,
     7,
     FFTW_FORWARD,
     FFTW_NOTW,
     155,
     0,
     (const int *) 0,
};
