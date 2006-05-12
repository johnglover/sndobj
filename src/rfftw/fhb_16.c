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
/* Generated on Sun Nov  7 20:45:16 EST 1999 */

#include <fftw-int.h>
#include <fftw.h>

/* Generated by: ./genfft -magic-alignment-check -magic-twiddle-load-all -magic-variables 4 -magic-loopi -hc2hc-backward 16 */

/*
 * This function contains 298 FP additions, 134 FP multiplications,
 * (or, 244 additions, 80 multiplications, 54 fused multiply/add),
 * 49 stack variables, and 128 memory accesses
 */
static const fftw_real K1_961570560 = FFTW_KONST(+1.961570560806460898252364472268478073947867462);
static const fftw_real K390180644 = FFTW_KONST(+0.390180644032256535696569736954044481855383236);
static const fftw_real K1_111140466 = FFTW_KONST(+1.111140466039204449485661627897065748749874382);
static const fftw_real K1_662939224 = FFTW_KONST(+1.662939224605090474157576755235811513477121624);
static const fftw_real K707106781 = FFTW_KONST(+0.707106781186547524400844362104849039284835938);
static const fftw_real K382683432 = FFTW_KONST(+0.382683432365089771728459984030398866761344562);
static const fftw_real K923879532 = FFTW_KONST(+0.923879532511286756128183189396788286822416626);
static const fftw_real K765366864 = FFTW_KONST(+0.765366864730179543456919968060797733522689125);
static const fftw_real K1_847759065 = FFTW_KONST(+1.847759065022573512256366378793576573644833252);
static const fftw_real K1_414213562 = FFTW_KONST(+1.414213562373095048801688724209698078569671875);
static const fftw_real K2_000000000 = FFTW_KONST(+2.000000000000000000000000000000000000000000000);

/*
 * Generator Id's : 
 * $Id: fhb_16.c,v 1.1 2006/05/12 15:14:54 veplaini Exp $
 * $Id: fhb_16.c,v 1.1 2006/05/12 15:14:54 veplaini Exp $
 * $Id: fhb_16.c,v 1.1 2006/05/12 15:14:54 veplaini Exp $
 */

void fftw_hc2hc_backward_16(fftw_real *A, const fftw_complex *W, int iostride, int m, int dist)
{
     int i;
     fftw_real *X;
     fftw_real *Y;
     X = A;
     Y = A + (16 * iostride);
     {
	  fftw_real tmp279;
	  fftw_real tmp324;
	  fftw_real tmp312;
	  fftw_real tmp299;
	  fftw_real tmp276;
	  fftw_real tmp296;
	  fftw_real tmp309;
	  fftw_real tmp323;
	  fftw_real tmp283;
	  fftw_real tmp291;
	  fftw_real tmp286;
	  fftw_real tmp294;
	  fftw_real tmp301;
	  fftw_real tmp319;
	  fftw_real tmp327;
	  fftw_real tmp326;
	  fftw_real tmp316;
	  fftw_real tmp302;
	  ASSERT_ALIGNED_DOUBLE;
	  {
	       fftw_real tmp277;
	       fftw_real tmp278;
	       fftw_real tmp310;
	       fftw_real tmp297;
	       fftw_real tmp298;
	       fftw_real tmp311;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp277 = X[2 * iostride];
	       tmp278 = X[6 * iostride];
	       tmp310 = tmp277 - tmp278;
	       tmp297 = Y[-2 * iostride];
	       tmp298 = Y[-6 * iostride];
	       tmp311 = tmp298 + tmp297;
	       tmp279 = K2_000000000 * (tmp277 + tmp278);
	       tmp324 = K1_414213562 * (tmp310 + tmp311);
	       tmp312 = K1_414213562 * (tmp310 - tmp311);
	       tmp299 = K2_000000000 * (tmp297 - tmp298);
	  }
	  {
	       fftw_real tmp275;
	       fftw_real tmp308;
	       fftw_real tmp273;
	       fftw_real tmp306;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp274;
		    fftw_real tmp307;
		    fftw_real tmp271;
		    fftw_real tmp272;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp274 = X[4 * iostride];
		    tmp275 = K2_000000000 * tmp274;
		    tmp307 = Y[-4 * iostride];
		    tmp308 = K2_000000000 * tmp307;
		    tmp271 = X[0];
		    tmp272 = X[8 * iostride];
		    tmp273 = tmp271 + tmp272;
		    tmp306 = tmp271 - tmp272;
	       }
	       tmp276 = tmp273 + tmp275;
	       tmp296 = tmp273 - tmp275;
	       tmp309 = tmp306 - tmp308;
	       tmp323 = tmp306 + tmp308;
	  }
	  {
	       fftw_real tmp314;
	       fftw_real tmp318;
	       fftw_real tmp317;
	       fftw_real tmp315;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp281;
		    fftw_real tmp282;
		    fftw_real tmp289;
		    fftw_real tmp290;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp281 = X[iostride];
		    tmp282 = X[7 * iostride];
		    tmp283 = tmp281 + tmp282;
		    tmp314 = tmp281 - tmp282;
		    tmp289 = Y[-iostride];
		    tmp290 = Y[-7 * iostride];
		    tmp291 = tmp289 - tmp290;
		    tmp318 = tmp289 + tmp290;
	       }
	       {
		    fftw_real tmp284;
		    fftw_real tmp285;
		    fftw_real tmp292;
		    fftw_real tmp293;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp284 = X[3 * iostride];
		    tmp285 = X[5 * iostride];
		    tmp286 = tmp284 + tmp285;
		    tmp317 = tmp285 - tmp284;
		    tmp292 = Y[-3 * iostride];
		    tmp293 = Y[-5 * iostride];
		    tmp294 = tmp292 - tmp293;
		    tmp315 = tmp293 + tmp292;
	       }
	       tmp301 = tmp283 - tmp286;
	       tmp319 = tmp317 + tmp318;
	       tmp327 = tmp318 - tmp317;
	       tmp326 = tmp314 + tmp315;
	       tmp316 = tmp314 - tmp315;
	       tmp302 = tmp294 + tmp291;
	  }
	  {
	       fftw_real tmp280;
	       fftw_real tmp287;
	       fftw_real tmp288;
	       fftw_real tmp295;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp280 = tmp276 + tmp279;
	       tmp287 = K2_000000000 * (tmp283 + tmp286);
	       X[8 * iostride] = tmp280 - tmp287;
	       X[0] = tmp280 + tmp287;
	       tmp288 = tmp276 - tmp279;
	       tmp295 = K2_000000000 * (tmp291 - tmp294);
	       X[12 * iostride] = tmp288 + tmp295;
	       X[4 * iostride] = tmp288 - tmp295;
	  }
	  {
	       fftw_real tmp300;
	       fftw_real tmp303;
	       fftw_real tmp304;
	       fftw_real tmp305;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp300 = tmp296 - tmp299;
	       tmp303 = K1_414213562 * (tmp301 - tmp302);
	       X[10 * iostride] = tmp300 - tmp303;
	       X[2 * iostride] = tmp300 + tmp303;
	       tmp304 = tmp296 + tmp299;
	       tmp305 = K1_414213562 * (tmp301 + tmp302);
	       X[6 * iostride] = tmp304 - tmp305;
	       X[14 * iostride] = tmp304 + tmp305;
	  }
	  {
	       fftw_real tmp313;
	       fftw_real tmp320;
	       fftw_real tmp321;
	       fftw_real tmp322;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp313 = tmp309 + tmp312;
	       tmp320 = (K1_847759065 * tmp316) - (K765366864 * tmp319);
	       X[9 * iostride] = tmp313 - tmp320;
	       X[iostride] = tmp313 + tmp320;
	       tmp321 = tmp309 - tmp312;
	       tmp322 = (K765366864 * tmp316) + (K1_847759065 * tmp319);
	       X[5 * iostride] = tmp321 - tmp322;
	       X[13 * iostride] = tmp321 + tmp322;
	  }
	  {
	       fftw_real tmp325;
	       fftw_real tmp328;
	       fftw_real tmp329;
	       fftw_real tmp330;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp325 = tmp323 - tmp324;
	       tmp328 = (K765366864 * tmp326) - (K1_847759065 * tmp327);
	       X[11 * iostride] = tmp325 - tmp328;
	       X[3 * iostride] = tmp325 + tmp328;
	       tmp329 = tmp323 + tmp324;
	       tmp330 = (K1_847759065 * tmp326) + (K765366864 * tmp327);
	       X[7 * iostride] = tmp329 - tmp330;
	       X[15 * iostride] = tmp329 + tmp330;
	  }
     }
     X = X + dist;
     Y = Y - dist;
     for (i = 2; i < m; i = i + 2, X = X + dist, Y = Y - dist, W = W + 15) {
	  fftw_real tmp73;
	  fftw_real tmp98;
	  fftw_real tmp135;
	  fftw_real tmp160;
	  fftw_real tmp182;
	  fftw_real tmp236;
	  fftw_real tmp210;
	  fftw_real tmp248;
	  fftw_real tmp95;
	  fftw_real tmp124;
	  fftw_real tmp138;
	  fftw_real tmp164;
	  fftw_real tmp197;
	  fftw_real tmp216;
	  fftw_real tmp244;
	  fftw_real tmp252;
	  fftw_real tmp80;
	  fftw_real tmp128;
	  fftw_real tmp105;
	  fftw_real tmp161;
	  fftw_real tmp213;
	  fftw_real tmp237;
	  fftw_real tmp189;
	  fftw_real tmp249;
	  fftw_real tmp88;
	  fftw_real tmp115;
	  fftw_real tmp137;
	  fftw_real tmp163;
	  fftw_real tmp204;
	  fftw_real tmp215;
	  fftw_real tmp241;
	  fftw_real tmp251;
	  ASSERT_ALIGNED_DOUBLE;
	  {
	       fftw_real tmp69;
	       fftw_real tmp180;
	       fftw_real tmp131;
	       fftw_real tmp209;
	       fftw_real tmp72;
	       fftw_real tmp208;
	       fftw_real tmp134;
	       fftw_real tmp181;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp67;
		    fftw_real tmp68;
		    fftw_real tmp129;
		    fftw_real tmp130;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp67 = X[0];
		    tmp68 = Y[-8 * iostride];
		    tmp69 = tmp67 + tmp68;
		    tmp180 = tmp67 - tmp68;
		    tmp129 = Y[0];
		    tmp130 = X[8 * iostride];
		    tmp131 = tmp129 - tmp130;
		    tmp209 = tmp129 + tmp130;
	       }
	       {
		    fftw_real tmp70;
		    fftw_real tmp71;
		    fftw_real tmp132;
		    fftw_real tmp133;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp70 = X[4 * iostride];
		    tmp71 = Y[-12 * iostride];
		    tmp72 = tmp70 + tmp71;
		    tmp208 = tmp70 - tmp71;
		    tmp132 = Y[-4 * iostride];
		    tmp133 = X[12 * iostride];
		    tmp134 = tmp132 - tmp133;
		    tmp181 = tmp132 + tmp133;
	       }
	       tmp73 = tmp69 + tmp72;
	       tmp98 = tmp69 - tmp72;
	       tmp135 = tmp131 - tmp134;
	       tmp160 = tmp131 + tmp134;
	       tmp182 = tmp180 - tmp181;
	       tmp236 = tmp180 + tmp181;
	       tmp210 = tmp208 + tmp209;
	       tmp248 = tmp209 - tmp208;
	  }
	  {
	       fftw_real tmp91;
	       fftw_real tmp194;
	       fftw_real tmp119;
	       fftw_real tmp192;
	       fftw_real tmp94;
	       fftw_real tmp191;
	       fftw_real tmp122;
	       fftw_real tmp195;
	       fftw_real tmp116;
	       fftw_real tmp123;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp89;
		    fftw_real tmp90;
		    fftw_real tmp117;
		    fftw_real tmp118;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp89 = Y[-15 * iostride];
		    tmp90 = X[7 * iostride];
		    tmp91 = tmp89 + tmp90;
		    tmp194 = tmp89 - tmp90;
		    tmp117 = Y[-7 * iostride];
		    tmp118 = X[15 * iostride];
		    tmp119 = tmp117 - tmp118;
		    tmp192 = tmp117 + tmp118;
	       }
	       {
		    fftw_real tmp92;
		    fftw_real tmp93;
		    fftw_real tmp120;
		    fftw_real tmp121;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp92 = X[3 * iostride];
		    tmp93 = Y[-11 * iostride];
		    tmp94 = tmp92 + tmp93;
		    tmp191 = tmp92 - tmp93;
		    tmp120 = Y[-3 * iostride];
		    tmp121 = X[11 * iostride];
		    tmp122 = tmp120 - tmp121;
		    tmp195 = tmp120 + tmp121;
	       }
	       tmp95 = tmp91 + tmp94;
	       tmp116 = tmp91 - tmp94;
	       tmp123 = tmp119 - tmp122;
	       tmp124 = tmp116 + tmp123;
	       tmp138 = tmp123 - tmp116;
	       tmp164 = tmp119 + tmp122;
	       {
		    fftw_real tmp193;
		    fftw_real tmp196;
		    fftw_real tmp242;
		    fftw_real tmp243;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp193 = tmp191 - tmp192;
		    tmp196 = tmp194 - tmp195;
		    tmp197 = (K923879532 * tmp193) - (K382683432 * tmp196);
		    tmp216 = (K382683432 * tmp193) + (K923879532 * tmp196);
		    tmp242 = tmp194 + tmp195;
		    tmp243 = tmp191 + tmp192;
		    tmp244 = (K382683432 * tmp242) - (K923879532 * tmp243);
		    tmp252 = (K382683432 * tmp243) + (K923879532 * tmp242);
	       }
	  }
	  {
	       fftw_real tmp76;
	       fftw_real tmp183;
	       fftw_real tmp104;
	       fftw_real tmp184;
	       fftw_real tmp79;
	       fftw_real tmp186;
	       fftw_real tmp101;
	       fftw_real tmp187;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp74;
		    fftw_real tmp75;
		    fftw_real tmp102;
		    fftw_real tmp103;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp74 = X[2 * iostride];
		    tmp75 = Y[-10 * iostride];
		    tmp76 = tmp74 + tmp75;
		    tmp183 = tmp74 - tmp75;
		    tmp102 = Y[-2 * iostride];
		    tmp103 = X[10 * iostride];
		    tmp104 = tmp102 - tmp103;
		    tmp184 = tmp102 + tmp103;
	       }
	       {
		    fftw_real tmp77;
		    fftw_real tmp78;
		    fftw_real tmp99;
		    fftw_real tmp100;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp77 = Y[-14 * iostride];
		    tmp78 = X[6 * iostride];
		    tmp79 = tmp77 + tmp78;
		    tmp186 = tmp77 - tmp78;
		    tmp99 = Y[-6 * iostride];
		    tmp100 = X[14 * iostride];
		    tmp101 = tmp99 - tmp100;
		    tmp187 = tmp99 + tmp100;
	       }
	       tmp80 = tmp76 + tmp79;
	       tmp128 = tmp76 - tmp79;
	       tmp105 = tmp101 - tmp104;
	       tmp161 = tmp104 + tmp101;
	       {
		    fftw_real tmp211;
		    fftw_real tmp212;
		    fftw_real tmp185;
		    fftw_real tmp188;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp211 = tmp183 + tmp184;
		    tmp212 = tmp186 + tmp187;
		    tmp213 = K707106781 * (tmp211 - tmp212);
		    tmp237 = K707106781 * (tmp211 + tmp212);
		    tmp185 = tmp183 - tmp184;
		    tmp188 = tmp186 - tmp187;
		    tmp189 = K707106781 * (tmp185 + tmp188);
		    tmp249 = K707106781 * (tmp185 - tmp188);
	       }
	  }
	  {
	       fftw_real tmp84;
	       fftw_real tmp201;
	       fftw_real tmp110;
	       fftw_real tmp199;
	       fftw_real tmp87;
	       fftw_real tmp198;
	       fftw_real tmp113;
	       fftw_real tmp202;
	       fftw_real tmp107;
	       fftw_real tmp114;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp82;
		    fftw_real tmp83;
		    fftw_real tmp108;
		    fftw_real tmp109;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp82 = X[iostride];
		    tmp83 = Y[-9 * iostride];
		    tmp84 = tmp82 + tmp83;
		    tmp201 = tmp82 - tmp83;
		    tmp108 = Y[-iostride];
		    tmp109 = X[9 * iostride];
		    tmp110 = tmp108 - tmp109;
		    tmp199 = tmp108 + tmp109;
	       }
	       {
		    fftw_real tmp85;
		    fftw_real tmp86;
		    fftw_real tmp111;
		    fftw_real tmp112;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp85 = X[5 * iostride];
		    tmp86 = Y[-13 * iostride];
		    tmp87 = tmp85 + tmp86;
		    tmp198 = tmp85 - tmp86;
		    tmp111 = Y[-5 * iostride];
		    tmp112 = X[13 * iostride];
		    tmp113 = tmp111 - tmp112;
		    tmp202 = tmp111 + tmp112;
	       }
	       tmp88 = tmp84 + tmp87;
	       tmp107 = tmp84 - tmp87;
	       tmp114 = tmp110 - tmp113;
	       tmp115 = tmp107 - tmp114;
	       tmp137 = tmp107 + tmp114;
	       tmp163 = tmp110 + tmp113;
	       {
		    fftw_real tmp200;
		    fftw_real tmp203;
		    fftw_real tmp239;
		    fftw_real tmp240;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp200 = tmp198 + tmp199;
		    tmp203 = tmp201 - tmp202;
		    tmp204 = (K923879532 * tmp200) + (K382683432 * tmp203);
		    tmp215 = (K923879532 * tmp203) - (K382683432 * tmp200);
		    tmp239 = tmp201 + tmp202;
		    tmp240 = tmp199 - tmp198;
		    tmp241 = (K382683432 * tmp239) - (K923879532 * tmp240);
		    tmp251 = (K382683432 * tmp240) + (K923879532 * tmp239);
	       }
	  }
	  {
	       fftw_real tmp81;
	       fftw_real tmp96;
	       fftw_real tmp158;
	       fftw_real tmp162;
	       fftw_real tmp165;
	       fftw_real tmp166;
	       fftw_real tmp157;
	       fftw_real tmp159;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp81 = tmp73 + tmp80;
	       tmp96 = tmp88 + tmp95;
	       tmp158 = tmp81 - tmp96;
	       tmp162 = tmp160 + tmp161;
	       tmp165 = tmp163 + tmp164;
	       tmp166 = tmp162 - tmp165;
	       X[0] = tmp81 + tmp96;
	       Y[-15 * iostride] = tmp162 + tmp165;
	       tmp157 = c_re(W[7]);
	       tmp159 = c_im(W[7]);
	       X[8 * iostride] = (tmp157 * tmp158) + (tmp159 * tmp166);
	       Y[-7 * iostride] = (tmp157 * tmp166) - (tmp159 * tmp158);
	  }
	  {
	       fftw_real tmp170;
	       fftw_real tmp176;
	       fftw_real tmp174;
	       fftw_real tmp178;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp168;
		    fftw_real tmp169;
		    fftw_real tmp172;
		    fftw_real tmp173;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp168 = tmp160 - tmp161;
		    tmp169 = tmp88 - tmp95;
		    tmp170 = tmp168 - tmp169;
		    tmp176 = tmp169 + tmp168;
		    tmp172 = tmp73 - tmp80;
		    tmp173 = tmp164 - tmp163;
		    tmp174 = tmp172 - tmp173;
		    tmp178 = tmp172 + tmp173;
	       }
	       {
		    fftw_real tmp167;
		    fftw_real tmp171;
		    fftw_real tmp175;
		    fftw_real tmp177;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp167 = c_re(W[11]);
		    tmp171 = c_im(W[11]);
		    Y[-3 * iostride] = (tmp167 * tmp170) - (tmp171 * tmp174);
		    X[12 * iostride] = (tmp171 * tmp170) + (tmp167 * tmp174);
		    tmp175 = c_re(W[3]);
		    tmp177 = c_im(W[3]);
		    Y[-11 * iostride] = (tmp175 * tmp176) - (tmp177 * tmp178);
		    X[4 * iostride] = (tmp177 * tmp176) + (tmp175 * tmp178);
	       }
	  }
	  {
	       fftw_real tmp126;
	       fftw_real tmp142;
	       fftw_real tmp140;
	       fftw_real tmp144;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp106;
		    fftw_real tmp125;
		    fftw_real tmp136;
		    fftw_real tmp139;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp106 = tmp98 + tmp105;
		    tmp125 = K707106781 * (tmp115 + tmp124);
		    tmp126 = tmp106 - tmp125;
		    tmp142 = tmp106 + tmp125;
		    tmp136 = tmp128 + tmp135;
		    tmp139 = K707106781 * (tmp137 + tmp138);
		    tmp140 = tmp136 - tmp139;
		    tmp144 = tmp136 + tmp139;
	       }
	       {
		    fftw_real tmp97;
		    fftw_real tmp127;
		    fftw_real tmp141;
		    fftw_real tmp143;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp97 = c_re(W[9]);
		    tmp127 = c_im(W[9]);
		    X[10 * iostride] = (tmp97 * tmp126) + (tmp127 * tmp140);
		    Y[-5 * iostride] = (tmp97 * tmp140) - (tmp127 * tmp126);
		    tmp141 = c_re(W[1]);
		    tmp143 = c_im(W[1]);
		    X[2 * iostride] = (tmp141 * tmp142) + (tmp143 * tmp144);
		    Y[-13 * iostride] = (tmp141 * tmp144) - (tmp143 * tmp142);
	       }
	  }
	  {
	       fftw_real tmp148;
	       fftw_real tmp154;
	       fftw_real tmp152;
	       fftw_real tmp156;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp146;
		    fftw_real tmp147;
		    fftw_real tmp150;
		    fftw_real tmp151;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp146 = tmp135 - tmp128;
		    tmp147 = K707106781 * (tmp115 - tmp124);
		    tmp148 = tmp146 - tmp147;
		    tmp154 = tmp146 + tmp147;
		    tmp150 = tmp98 - tmp105;
		    tmp151 = K707106781 * (tmp138 - tmp137);
		    tmp152 = tmp150 - tmp151;
		    tmp156 = tmp150 + tmp151;
	       }
	       {
		    fftw_real tmp145;
		    fftw_real tmp149;
		    fftw_real tmp153;
		    fftw_real tmp155;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp145 = c_re(W[13]);
		    tmp149 = c_im(W[13]);
		    Y[-iostride] = (tmp145 * tmp148) - (tmp149 * tmp152);
		    X[14 * iostride] = (tmp149 * tmp148) + (tmp145 * tmp152);
		    tmp153 = c_re(W[5]);
		    tmp155 = c_im(W[5]);
		    Y[-9 * iostride] = (tmp153 * tmp154) - (tmp155 * tmp156);
		    X[6 * iostride] = (tmp155 * tmp154) + (tmp153 * tmp156);
	       }
	  }
	  {
	       fftw_real tmp206;
	       fftw_real tmp220;
	       fftw_real tmp218;
	       fftw_real tmp222;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp190;
		    fftw_real tmp205;
		    fftw_real tmp214;
		    fftw_real tmp217;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp190 = tmp182 - tmp189;
		    tmp205 = tmp197 - tmp204;
		    tmp206 = tmp190 - tmp205;
		    tmp220 = tmp190 + tmp205;
		    tmp214 = tmp210 - tmp213;
		    tmp217 = tmp215 - tmp216;
		    tmp218 = tmp214 - tmp217;
		    tmp222 = tmp214 + tmp217;
	       }
	       {
		    fftw_real tmp179;
		    fftw_real tmp207;
		    fftw_real tmp219;
		    fftw_real tmp221;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp179 = c_re(W[12]);
		    tmp207 = c_im(W[12]);
		    X[13 * iostride] = (tmp179 * tmp206) + (tmp207 * tmp218);
		    Y[-2 * iostride] = (tmp179 * tmp218) - (tmp207 * tmp206);
		    tmp219 = c_re(W[4]);
		    tmp221 = c_im(W[4]);
		    X[5 * iostride] = (tmp219 * tmp220) + (tmp221 * tmp222);
		    Y[-10 * iostride] = (tmp219 * tmp222) - (tmp221 * tmp220);
	       }
	  }
	  {
	       fftw_real tmp226;
	       fftw_real tmp232;
	       fftw_real tmp230;
	       fftw_real tmp234;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp224;
		    fftw_real tmp225;
		    fftw_real tmp228;
		    fftw_real tmp229;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp224 = tmp210 + tmp213;
		    tmp225 = tmp204 + tmp197;
		    tmp226 = tmp224 - tmp225;
		    tmp232 = tmp224 + tmp225;
		    tmp228 = tmp182 + tmp189;
		    tmp229 = tmp215 + tmp216;
		    tmp230 = tmp228 - tmp229;
		    tmp234 = tmp228 + tmp229;
	       }
	       {
		    fftw_real tmp223;
		    fftw_real tmp227;
		    fftw_real tmp231;
		    fftw_real tmp233;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp223 = c_re(W[8]);
		    tmp227 = c_im(W[8]);
		    Y[-6 * iostride] = (tmp223 * tmp226) - (tmp227 * tmp230);
		    X[9 * iostride] = (tmp227 * tmp226) + (tmp223 * tmp230);
		    tmp231 = c_re(W[0]);
		    tmp233 = c_im(W[0]);
		    Y[-14 * iostride] = (tmp231 * tmp232) - (tmp233 * tmp234);
		    X[iostride] = (tmp233 * tmp232) + (tmp231 * tmp234);
	       }
	  }
	  {
	       fftw_real tmp246;
	       fftw_real tmp256;
	       fftw_real tmp254;
	       fftw_real tmp258;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp238;
		    fftw_real tmp245;
		    fftw_real tmp250;
		    fftw_real tmp253;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp238 = tmp236 - tmp237;
		    tmp245 = tmp241 + tmp244;
		    tmp246 = tmp238 - tmp245;
		    tmp256 = tmp238 + tmp245;
		    tmp250 = tmp248 + tmp249;
		    tmp253 = tmp251 - tmp252;
		    tmp254 = tmp250 - tmp253;
		    tmp258 = tmp250 + tmp253;
	       }
	       {
		    fftw_real tmp235;
		    fftw_real tmp247;
		    fftw_real tmp255;
		    fftw_real tmp257;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp235 = c_re(W[10]);
		    tmp247 = c_im(W[10]);
		    X[11 * iostride] = (tmp235 * tmp246) + (tmp247 * tmp254);
		    Y[-4 * iostride] = (tmp235 * tmp254) - (tmp247 * tmp246);
		    tmp255 = c_re(W[2]);
		    tmp257 = c_im(W[2]);
		    X[3 * iostride] = (tmp255 * tmp256) + (tmp257 * tmp258);
		    Y[-12 * iostride] = (tmp255 * tmp258) - (tmp257 * tmp256);
	       }
	  }
	  {
	       fftw_real tmp262;
	       fftw_real tmp268;
	       fftw_real tmp266;
	       fftw_real tmp270;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp260;
		    fftw_real tmp261;
		    fftw_real tmp264;
		    fftw_real tmp265;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp260 = tmp248 - tmp249;
		    tmp261 = tmp241 - tmp244;
		    tmp262 = tmp260 + tmp261;
		    tmp268 = tmp260 - tmp261;
		    tmp264 = tmp236 + tmp237;
		    tmp265 = tmp251 + tmp252;
		    tmp266 = tmp264 - tmp265;
		    tmp270 = tmp264 + tmp265;
	       }
	       {
		    fftw_real tmp259;
		    fftw_real tmp263;
		    fftw_real tmp267;
		    fftw_real tmp269;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp259 = c_re(W[6]);
		    tmp263 = c_im(W[6]);
		    Y[-8 * iostride] = (tmp259 * tmp262) - (tmp263 * tmp266);
		    X[7 * iostride] = (tmp263 * tmp262) + (tmp259 * tmp266);
		    tmp267 = c_re(W[14]);
		    tmp269 = c_im(W[14]);
		    Y[0] = (tmp267 * tmp268) - (tmp269 * tmp270);
		    X[15 * iostride] = (tmp269 * tmp268) + (tmp267 * tmp270);
	       }
	  }
     }
     if (i == m) {
	  fftw_real tmp7;
	  fftw_real tmp51;
	  fftw_real tmp19;
	  fftw_real tmp43;
	  fftw_real tmp39;
	  fftw_real tmp47;
	  fftw_real tmp59;
	  fftw_real tmp64;
	  fftw_real tmp14;
	  fftw_real tmp56;
	  fftw_real tmp24;
	  fftw_real tmp32;
	  fftw_real tmp29;
	  fftw_real tmp33;
	  fftw_real tmp54;
	  fftw_real tmp65;
	  fftw_real tmp63;
	  fftw_real tmp66;
	  ASSERT_ALIGNED_DOUBLE;
	  {
	       fftw_real tmp3;
	       fftw_real tmp15;
	       fftw_real tmp38;
	       fftw_real tmp57;
	       fftw_real tmp6;
	       fftw_real tmp35;
	       fftw_real tmp18;
	       fftw_real tmp58;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp1;
		    fftw_real tmp2;
		    fftw_real tmp36;
		    fftw_real tmp37;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp1 = X[0];
		    tmp2 = X[7 * iostride];
		    tmp3 = tmp1 + tmp2;
		    tmp15 = tmp1 - tmp2;
		    tmp36 = Y[0];
		    tmp37 = Y[-7 * iostride];
		    tmp38 = tmp36 + tmp37;
		    tmp57 = tmp36 - tmp37;
	       }
	       {
		    fftw_real tmp4;
		    fftw_real tmp5;
		    fftw_real tmp16;
		    fftw_real tmp17;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp4 = X[4 * iostride];
		    tmp5 = X[3 * iostride];
		    tmp6 = tmp4 + tmp5;
		    tmp35 = tmp4 - tmp5;
		    tmp16 = Y[-4 * iostride];
		    tmp17 = Y[-3 * iostride];
		    tmp18 = tmp16 + tmp17;
		    tmp58 = tmp16 - tmp17;
	       }
	       tmp7 = tmp3 + tmp6;
	       tmp51 = tmp3 - tmp6;
	       tmp19 = tmp15 - tmp18;
	       tmp43 = tmp15 + tmp18;
	       tmp39 = tmp35 + tmp38;
	       tmp47 = tmp38 - tmp35;
	       tmp59 = tmp57 - tmp58;
	       tmp64 = tmp58 + tmp57;
	  }
	  {
	       fftw_real tmp10;
	       fftw_real tmp20;
	       fftw_real tmp23;
	       fftw_real tmp53;
	       fftw_real tmp13;
	       fftw_real tmp25;
	       fftw_real tmp28;
	       fftw_real tmp52;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp8;
		    fftw_real tmp9;
		    fftw_real tmp21;
		    fftw_real tmp22;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp8 = X[2 * iostride];
		    tmp9 = X[5 * iostride];
		    tmp10 = tmp8 + tmp9;
		    tmp20 = tmp8 - tmp9;
		    tmp21 = Y[-2 * iostride];
		    tmp22 = Y[-5 * iostride];
		    tmp23 = tmp21 + tmp22;
		    tmp53 = tmp21 - tmp22;
	       }
	       {
		    fftw_real tmp11;
		    fftw_real tmp12;
		    fftw_real tmp26;
		    fftw_real tmp27;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp11 = X[iostride];
		    tmp12 = X[6 * iostride];
		    tmp13 = tmp11 + tmp12;
		    tmp25 = tmp11 - tmp12;
		    tmp26 = Y[-iostride];
		    tmp27 = Y[-6 * iostride];
		    tmp28 = tmp26 + tmp27;
		    tmp52 = tmp27 - tmp26;
	       }
	       tmp14 = tmp10 + tmp13;
	       tmp56 = tmp10 - tmp13;
	       tmp24 = tmp20 - tmp23;
	       tmp32 = tmp20 + tmp23;
	       tmp29 = tmp25 - tmp28;
	       tmp33 = tmp25 + tmp28;
	       tmp54 = tmp52 - tmp53;
	       tmp65 = tmp53 + tmp52;
	  }
	  X[0] = K2_000000000 * (tmp7 + tmp14);
	  X[8 * iostride] = -(K2_000000000 * (tmp65 + tmp64));
	  tmp63 = tmp7 - tmp14;
	  tmp66 = tmp64 - tmp65;
	  X[4 * iostride] = K1_414213562 * (tmp63 - tmp66);
	  X[12 * iostride] = -(K1_414213562 * (tmp63 + tmp66));
	  {
	       fftw_real tmp61;
	       fftw_real tmp62;
	       fftw_real tmp55;
	       fftw_real tmp60;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp61 = tmp51 - tmp54;
	       tmp62 = tmp59 - tmp56;
	       X[6 * iostride] = (K765366864 * tmp61) - (K1_847759065 * tmp62);
	       X[14 * iostride] = -((K1_847759065 * tmp61) + (K765366864 * tmp62));
	       tmp55 = tmp51 + tmp54;
	       tmp60 = tmp56 + tmp59;
	       X[2 * iostride] = (K1_847759065 * tmp55) - (K765366864 * tmp60);
	       X[10 * iostride] = -((K765366864 * tmp55) + (K1_847759065 * tmp60));
	  }
	  {
	       fftw_real tmp45;
	       fftw_real tmp49;
	       fftw_real tmp48;
	       fftw_real tmp50;
	       fftw_real tmp44;
	       fftw_real tmp46;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp44 = K707106781 * (tmp32 + tmp33);
	       tmp45 = tmp43 - tmp44;
	       tmp49 = tmp43 + tmp44;
	       tmp46 = K707106781 * (tmp24 - tmp29);
	       tmp48 = tmp46 + tmp47;
	       tmp50 = tmp47 - tmp46;
	       X[3 * iostride] = (K1_662939224 * tmp45) - (K1_111140466 * tmp48);
	       X[11 * iostride] = -((K1_111140466 * tmp45) + (K1_662939224 * tmp48));
	       X[7 * iostride] = (K390180644 * tmp49) - (K1_961570560 * tmp50);
	       X[15 * iostride] = -((K1_961570560 * tmp49) + (K390180644 * tmp50));
	  }
	  {
	       fftw_real tmp31;
	       fftw_real tmp41;
	       fftw_real tmp40;
	       fftw_real tmp42;
	       fftw_real tmp30;
	       fftw_real tmp34;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp30 = K707106781 * (tmp24 + tmp29);
	       tmp31 = tmp19 + tmp30;
	       tmp41 = tmp19 - tmp30;
	       tmp34 = K707106781 * (tmp32 - tmp33);
	       tmp40 = tmp34 + tmp39;
	       tmp42 = tmp39 - tmp34;
	       X[iostride] = (K1_961570560 * tmp31) - (K390180644 * tmp40);
	       X[9 * iostride] = -((K390180644 * tmp31) + (K1_961570560 * tmp40));
	       X[5 * iostride] = (K1_111140466 * tmp41) - (K1_662939224 * tmp42);
	       X[13 * iostride] = -((K1_662939224 * tmp41) + (K1_111140466 * tmp42));
	  }
     }
}

static const int twiddle_order[] =
{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
fftw_codelet_desc fftw_hc2hc_backward_16_desc =
{
     "fftw_hc2hc_backward_16",
     (void (*)()) fftw_hc2hc_backward_16,
     16,
     FFTW_BACKWARD,
     FFTW_HC2HC,
     366,
     15,
     twiddle_order,
};
