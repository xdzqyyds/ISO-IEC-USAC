/************************* MPEG-2 AAC Audio Decoder **************************
 *                                                                           *
"This software module was originally developed by 
AT&T, Dolby Laboratories, Fraunhofer Gesellschaft IIS in the course of 
development of the MPEG-2 AAC/MPEG-4 Audio standard ISO/IEC 13818-7, 
14496-1,2 and 3. This software module is an implementation of a part of one or more 
MPEG-2 AAC/MPEG-4 Audio tools as specified by the MPEG-2 AAC/MPEG-4 
Audio standard. ISO/IEC  gives users of the MPEG-2 AAC/MPEG-4 Audio 
standards free license to this software module or modifications thereof for use in 
hardware or software products claiming conformance to the MPEG-2 AAC/MPEG-4
Audio  standards. Those intending to use this software module in hardware or 
software products are advised that this use may infringe existing patents. 
The original developer of this software module and his/her company, the subsequent 
editors and their companies, and ISO/IEC have no liability for use of this software 
module or modifications thereof in an implementation. Copyright is not released for 
non MPEG-2 AAC/MPEG-4 Audio conforming products.The original developer
retains full right to use the code for his/her  own purpose, assign or donate the 
code to a third party and to inhibit third party from using the code for non 
MPEG-2 AAC/MPEG-4 Audio conforming products. This copyright notice must
be included in all copies or derivative works." 
Copyright(c)1996.

This software was modified by Y.B. Thomas Kim on 1997-11-06
 *                                                                           *
 ****************************************************************************/
#include <stdio.h>
#include <math.h>

#include "block.h"               /* handler, defines, enums */
#include "tf_mainHandle.h"

#include "sam_tns.h"             /* structs */

#include "common_m4a.h"
#include "sam_dec.h"

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

/* Decoder transmitted coefficients for one TNS filter */
static void
sam_tns_decode_coef( int order, int coef_res, short *coef, double *a )
{
  int i, m;
  double iqfac,  iqfac_m;
  double tmp[TNS_MAX_ORDER+1], b[TNS_MAX_ORDER+1];

  /* Inverse quantization */
  iqfac   = ((1 << (coef_res-1)) - 0.5) / (C_PI/2.0);
  iqfac_m = ((1 << (coef_res-1)) + 0.5) / (C_PI/2.0);
  for (i=0; i<order; i++)  {
    tmp[i+1] = sin((double)( coef[i] / ((coef[i] >= 0) ? iqfac : iqfac_m) ));
  }
  /* Conversion to LPC coefficients
   * Markel and Gray,  pg. 95
   */
  a[0] = 1;
  for (m=1; m<=order; m++)  {
    b[0] = a[0];
    for (i=1; i<m; i++)  {
      b[i] = a[i] + tmp[m] * a[m-i];
    }
    b[m] = tmp[m];
    for (i=0; i<=m; i++)  {
      a[i] = b[i];
    }
  }
}

/* apply the TNS filter */
static void
sam_tns_ar_filter( double *spec, int size, int inc, double *lpc, int order )
{
  /*
   *	- Simple all-pole filter of order "order" defined by
   *	  y(n) =  x(n) - a(2)*y(n-1) - ... - a(order+1)*y(n-order)
   *
   *	- The state variables of the filter are initialized to zero every time
   *
   *	- The output data is written over the input data ("in-place operation")
   *
   *	- An input vector of "size" samples is processed and the index increment
   *	  to the next data sample is given by "inc"
   */
  int i, j;
  double y, state[TNS_MAX_ORDER];

  for (i=0; i<order; i++)
    state[i] = 0;

  if (inc == -1)
    spec += size-1;

  for (i=0; i<size; i++) {
    y = *spec;
    for (j=0; j<order; j++)
      y -= lpc[j+1] * state[j];
    for (j=order-1; j>0; j--)
      state[j] = state[j-1];
    state[0] = y;
    *spec = y;
    spec += inc;
  }
}

/* TNS decoding for one channel and frame */
void
sam_tns_decode_subblock(int windowSequence, double *spec, int maxSfb, int *sfbs, sam_TNSinfo *tns_info)
{
    int f, m, start, stop, size, inc;
    int n_filt, coef_res, order, direction;
    short *coef;
    double lpc[TNS_MAX_ORDER+1];
    sam_TNSfilt *filt;

    n_filt = tns_info->n_filt;
    for (f=0; f<n_filt; f++)  {
	coef_res = tns_info->coef_res;
	filt = &tns_info->filt[f];
	order = filt->order;
	direction = filt->direction;
	coef = filt->coef;
	start = filt->start_band;
	stop = filt->stop_band;

	m = sam_tns_max_order(windowSequence);
	if (order > m) {
          CommonExit (2, "Error in tns max order: %d %d", order, sam_tns_max_order(windowSequence));
          order = m;
        }
    	if (!order)  continue;

	sam_tns_decode_coef( order, coef_res, coef, lpc );

	start = MIN(start, sam_tns_max_bands(windowSequence));
	start = MIN(start, maxSfb);
	if(start > 0) {
	start = sfbs[ start ];
	}
	stop = MIN(stop, sam_tns_max_bands(windowSequence));
	stop = MIN(stop, maxSfb);
	if(stop > 0) {
	stop = sfbs[ stop ];
	}
	if ((size = stop - start) <= 0)  continue;

	if (direction)  {
	    inc = -1;
	}  else {
	    inc =  1;
	}

	sam_tns_ar_filter( &spec[start], size, inc, lpc, order );
    }
}
