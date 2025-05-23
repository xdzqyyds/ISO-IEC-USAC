/*****************************************************************************
 *                                                                           *
"This software module was originally developed by 

Fraunhofer Gesellschaft IIS 

in the course of development of the MPEG-2 AAC/MPEG-4 Audio standard ISO/IEC 13818-7, 
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
Copyright(c)1998, 1999, 2000.
 *                                                                           *
 *****************************************************************************/

/* This file has been created automatically. */
/* Any changes in this file will be lost.    */

#define D(a) {const void *dummyfilepointer; dummyfilepointer = &a;}
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "all.h"
#include "allHandles.h"
#include "nok_ltp_common.h"      /* structs */
#include "obj_descr.h"           /* structs */
#include "tf_mainStruct.h"       /* structs */
#include "resilience.h"
#include "rvlcScfConceal.h"
#include "tf_main.h"
#ifdef MY_DEBUG
#define DEGUG_CODE( code ) { code }
#else
#define DEBUG_CODE( code )
#endif
#define CONCEAL_THRESH_2 3.3
#define ENHANCED_CONCEALMENT 1
#define SQR(x) ((x)*(x))

#ifndef ABS
#define ABS(x) ( (x)>0 ? (x): -(x) ) /* should be replaced by _ABS from math.h */
#endif

int ScfRecovery( HANDLE_RESILIENCE hResilience,
                 int numOfFacs,
                 short * forwFacs,
                 int forwPos,
                 short * backwFacs,
                 int backwPos,
                 short global_gain,
                 short * outFacs,
                 short * lastFrame,
                 char enhc_con_bit,
                 Info *info )
{
  D(hResilience)
  D(numOfFacs)
  D(forwFacs)
  D(forwPos)
  D(backwFacs)
  D(backwPos)
  D(global_gain)
  D(outFacs)
  D(lastFrame)
  D(enhc_con_bit)
  D(info)
  return(0);
}

#if ENHANCED_CONCEALMENT
#endif
#if ENHANCED_CONCEALMENT
#endif
#if ENHANCED_CONCEALMENT
#endif
#undef D
