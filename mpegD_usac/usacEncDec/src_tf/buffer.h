/*****************************************************************************
 *                                                                           *
"This software module was originally developed by

Pierre Lauber (Fraunhofer Gesellschaft IIS)

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
Copyright(c)1996.
 *                                                                           *
 ****************************************************************************/

#ifndef _buffer_h_
#define _buffer_h_

enum {
  VIRTUELL               = 0,
  MAX_CW_LENGTH          = 49,
  AAC_MAX_INPUT_BUF_BITS = 12288
};

/* code table for aac bitstream elements */
#define E(BITSTREAM_ELEMENT) BITSTREAM_ELEMENT
typedef enum {
#include "er_main_elements.h"
  MAX_ELEMENTS,
#include "elements.h"
  MAX_EXTRA_ELEMENTS ,
#include "../src_usac/usac_elements.h"
  MAX_USAC_ELEMENTS
} CODE_TABLE;
#undef E

#endif /*_buffer_h_*/
