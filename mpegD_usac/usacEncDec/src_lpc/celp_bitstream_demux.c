/*====================================================================*/
/*         MPEG-4 Audio (ISO/IEC 14496-3) Copyright Header            */
/*====================================================================*/
/*
This software module was originally developed by Rakesh Taori and Andy
Gerrits (Philips Research Laboratories, Eindhoven, The Netherlands) in
the course of development of the MPEG-4 Audio (ISO/IEC 14496-3). This
software module is an implementation of a part of one or more MPEG-4
Audio (ISO/IEC 14496-3) tools as specified by the MPEG-4 Audio
(ISO/IEC 14496-3). ISO/IEC gives users of the MPEG-4 Audio (ISO/IEC
14496-3) free license to this software module or modifications thereof
for use in hardware or software products claiming conformance to the
MPEG-4 Audio (ISO/IEC 14496-3). Those intending to use this software
module in hardware or software products are advised that its use may
infringe existing patents. The original developer of this software
module and his/her company, the subsequent editors and their
companies, and ISO/IEC have no liability for use of this software
module or modifications thereof in an implementation. Copyright is not
released for non MPEG-4 Audio (ISO/IEC 14496-3) conforming products.
CN1 retains full right to use the code for his/her own purpose, assign
or donate the code to a third party and to inhibit third parties from
using the code for non MPEG-4 Audio (ISO/IEC 14496-3) conforming
products.  This copyright notice must be included in all copies or
derivative works. Copyright 1996.
*/
/*====================================================================*/
/*====================================================================*/
/*                                                                    */
/*      SOURCE_FILE:    CELP_BITSTREAM_DEMUX.C                        */
/*      COMPONENT:      Bitstream to Parameter converter              */
/*                                                                    */
/*====================================================================*/
    
/*====================================================================*/
/*      I N C L U D E S                                               */
/*====================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "common_m4a.h"

#include "bitstream.h"
#include "phi_cons.h"      
#include "lpc_common.h"  /* Common LPC core Defined Constants           */
#include "celp_bitstream_demux.h"    /* Parameter to bitstream conversion routines  */
/* #include "phi_freq.h"   */
#include "pan_celp_const.h"

/*======================================================================*/
/*      G L O B A L    D A T A   D E F I N I T I O N S                  */
/*======================================================================*/
/*
static short freq[ORDER_LPC_16 + 1][36];
static int counter[ORDER_LPC_16 + 1];
static long frame_count = 1;
static long ft = 1;
*/
/*======================================================================*/
/* Function Definition: read_celp_bitstream_header                     */
/*======================================================================*/

void read_celp_bitstream_header (HANDLE_BSBITSTREAM hdrStream,                /* In: Bitstream                    */
                                 long * const ExcitationMode,           /* In: Excitation Mode              */
                                 long * const SampleRateMode,           /* In: SampleRate Mode              */
                                 long * const QuantizationMode,         /* In: Type of Quantization         */
                                 long * const FineRateControl,          /* In: Fine Rate Control switch     */
                                 long * const RPE_configuration,        /* In: Wideband configuration       */
                                 long * const Wideband_VQ,              /* In: Wideband VQ mode             */
                                 long * const MPE_Configuration,        /* In: Narrowband configuration     */
                                 long * const NumEnhLayers,             /* In: Number of Enhancement Layers */
                                 long * const BandwidthScalabilityMode, /* In: bandwidth switch             */
                                 long * const SilenceCompressionSW,     /* In: SilenceCompressionSW         */
                                 int  dec_objectVerType,
                                 long * const BWS_Configuration         /* In: BWS_configuration            */
)
{
    unsigned long temp;
    *QuantizationMode = VectorQuantizer;
    *Wideband_VQ = Optimized_VQ;
    /* -----------------------------------------------------------------*/
    /* Read Excitation mode                                          */
    /* -----------------------------------------------------------------*/
    BsGetBit(hdrStream, &temp, 1); *ExcitationMode = temp;
    
    /* -----------------------------------------------------------------*/
    /* Read Sampling Rate mode                                          */
    /* -----------------------------------------------------------------*/
    BsGetBit(hdrStream, &temp, 1); *SampleRateMode = temp;
    
    /* -----------------------------------------------------------------*/
    /* Read FineRateControl                                             */
    /* -----------------------------------------------------------------*/
    BsGetBit(hdrStream, &temp, 1); *FineRateControl = temp;
    
    /* -----------------------------------------------------------------*/
    /* Read SilenceCompressionSW                                        */
    /* -----------------------------------------------------------------*/

    if (dec_objectVerType == CelpObjectV2) 
    {
        BsGetBit(hdrStream, &temp, 1); *SilenceCompressionSW = temp;
    }

    /* -----------------------------------------------------------------*/
    /* Read Configuration                                               */
    /* -----------------------------------------------------------------*/
    if (*ExcitationMode == RegularPulseExc )
    {
        BsGetBit(hdrStream, &temp, 3); *RPE_configuration = temp;
    }
    
    if (*ExcitationMode == MultiPulseExc )
    {
        BsGetBit(hdrStream, &temp, 5); *MPE_Configuration = temp;
        BsGetBit(hdrStream, &temp, 2); *NumEnhLayers = temp;
        /* -------------------------------------------------------------*/
        /* Read Bandwidth Scalability Mode                              */
        /* -------------------------------------------------------------*/
        BsGetBit(hdrStream, &temp, 1); *BandwidthScalabilityMode = temp;
        if (*BandwidthScalabilityMode == ON)
        {
            /* ---------------------------------------------------------*/
            /* If Bandwidth Scalability Mode, read BWS_Configuration    */
            /* ---------------------------------------------------------*/
            BsGetBit(hdrStream, &temp, 2); *BWS_Configuration = temp;
        }
    }
}
/*======================================================================*/
/* Function Definition: Read_Narrowband_LSP                             */
/*======================================================================*/
void Read_NarrowBand_LSP
(
    HANDLE_BSBITSTREAM bitStream,           /* In: Bitstream                 */
    unsigned long indices[]           /* Out: indices to rfc_table[]   */
)
{
    /*==================================================================*/
    /*     Read the Parameters from the Bitstream                       */
    /*     These represent the packed LPC Indices                       */     
    /*==================================================================*/
    BsGetBit(bitStream, &indices[0], PAN_BIT_LSP22_0);
    BsGetBit(bitStream, &indices[1], PAN_BIT_LSP22_1);
    BsGetBit(bitStream, &indices[2], PAN_BIT_LSP22_2);
    BsGetBit(bitStream, &indices[3], PAN_BIT_LSP22_3);
    BsGetBit(bitStream, &indices[4], PAN_BIT_LSP22_4);
}

/*======================================================================*/
/* Function Definition: Read_Narrowband_LSP                             */
/*======================================================================*/
void Read_BandScalable_LSP
(
    HANDLE_BSBITSTREAM bitStream,           /* In: Bitstream                  */
    unsigned long indices[]           /* Out: indices                   */
)
{
    /*==================================================================*/
    /*     Read the Parameters from the Bitstream                       */
    /*     These represent the packed LPC Indices                       */     
    /*==================================================================*/
    BsGetBit(bitStream, &indices[0], 4);
    BsGetBit(bitStream, &indices[1], 7);
    BsGetBit(bitStream, &indices[2], 4);
    BsGetBit(bitStream, &indices[3], 6);
    BsGetBit(bitStream, &indices[4], 7);
    BsGetBit(bitStream, &indices[5], 4);
}

/*======================================================================*/
/* Function Definition: Read_Wideband_LSP                               */
/*======================================================================*/
void Read_Wideband_LSP
(
    HANDLE_BSBITSTREAM bitStream,           /* In: Bitstream                  */
    unsigned long indices[]           /* Out: indices                   */
)
{
    BsGetBit(bitStream, &indices[0], PAN_BIT_LSP_WL_0);
    BsGetBit(bitStream, &indices[1], PAN_BIT_LSP_WL_1);
    BsGetBit(bitStream, &indices[2], PAN_BIT_LSP_WL_2);
    BsGetBit(bitStream, &indices[3], PAN_BIT_LSP_WL_3);
    BsGetBit(bitStream, &indices[4], PAN_BIT_LSP_WL_4);
    BsGetBit(bitStream, &indices[5], PAN_BIT_LSP_WU_0);
    BsGetBit(bitStream, &indices[6], PAN_BIT_LSP_WU_1);
    BsGetBit(bitStream, &indices[7], PAN_BIT_LSP_WU_2);
    BsGetBit(bitStream, &indices[8], PAN_BIT_LSP_WU_3);
    BsGetBit(bitStream, &indices[9], PAN_BIT_LSP_WU_4);
}


/*======================================================================*/
/* Function Definition: Read_Wideband_LSP_V2                            */
/*======================================================================*/
void Read_Wideband_LSP_V2
(
    HANDLE_BSBITSTREAM bitStream,            /* In: Bitstream                  */
    unsigned long indices[],           /* Out: indices                   */
    unsigned long ep_class
)
{
    unsigned long dummy;

    switch (ep_class)
    {
        case 0:
            /* read class 1 */
            /* lpc0: all */
            BsGetBit(bitStream, &indices[0], 5);
            /* lpc1: 0-1 */
            BsGetBit(bitStream, &indices[1], 2);
            /* lpc2: 0-4, 6 */
            BsGetBit(bitStream, &dummy, 1);
            indices[2] |= (dummy<<6);
            BsGetBit(bitStream, &dummy, 5);
            indices[2] |= dummy;
            /* lpc4 */
            BsGetBit(bitStream, &indices[4], 1);
            /* lpc5: 0 */
            BsGetBit(bitStream, &indices[5], 1);
            break;
        case 1:
            /* read class 2 */
            /* lpc1: 2-3 */
            BsGetBit(bitStream, &dummy, 2);
            indices[1] |= (dummy<<2);
            /* lpc2: 5 */
            BsGetBit(bitStream, &dummy, 1);
            indices[2] |= (dummy<<5);
            /* lpc5: 1 */
            BsGetBit(bitStream, &dummy, 1);
            indices[5] |= (dummy<<1);
            /* lpc6: 0-1 */
            BsGetBit(bitStream, &indices[6], 2);
            break;

        case 2:
            /* read class 3 */
            /* lpc1: 4 */
            BsGetBit(bitStream, &dummy, 1);
            indices[1] |= (dummy<<4);
            /* lpc3: 1, 6 */
            BsGetBit(bitStream, &dummy, 1);
            indices[3] |= (dummy<<6);
            BsGetBit(bitStream, &dummy, 1);
            indices[3] |= (dummy<<1);
            /* lpc5: 2 */
            BsGetBit(bitStream, &dummy, 1);
            indices[5] |= (dummy<<2);
            /* lpc6: 3 */
            BsGetBit(bitStream, &dummy, 1);
            indices[6] |= (dummy<<3);
            /* lpc7: 0-1, 4, 6 */
            BsGetBit(bitStream, &dummy, 1);
            indices[7] |= (dummy<<6);
            BsGetBit(bitStream, &dummy, 1);
            indices[7] |= (dummy<<4);
            BsGetBit(bitStream, &dummy, 2);
            indices[7] |= dummy;
            /* lpc9 */
            BsGetBit(bitStream, &indices[9], 1);
            break;

        case 3:
            /* read class 4 */
            /* lpc3: 0, 2-4 */
            BsGetBit(bitStream, &dummy, 3);
            indices[3] |= (dummy<<2);
            BsGetBit(bitStream, &dummy, 1);
            indices[3] |= dummy;
            /* lpc5: 3 */
            BsGetBit(bitStream, &dummy, 1);
            indices[5] |= (dummy<<3);
            /* lpc6: 2 */
            BsGetBit(bitStream, &dummy, 1);
            indices[6] |= (dummy<<2);
            /* lpc7: 2-3, 5 */
            BsGetBit(bitStream, &dummy, 1);
            indices[7] |= (dummy<<5);
            BsGetBit(bitStream, &dummy, 2);
            indices[7] |= (dummy<<2);
            /* lpc8: 1-4 */
            BsGetBit(bitStream, &dummy, 4);
            indices[8] = (dummy<<1);
            break;

        case 4:
            /* read class 5 */
            /* lpc3: 5 */
            BsGetBit(bitStream, &dummy, 1);
            indices[3] |= (dummy<<5);
            /* lpc8: 0 */
            BsGetBit(bitStream, &dummy, 1);
            indices[8] |= dummy;
            break;

        default : 
            fprintf(stderr, "Wrong Class in Read_Wideband_LSP_V2\n");
            CommonExit(1,"celp error");
    }
}



/*======================================================================*/
/* Function Definition: Read_Narrowband_LSP_V2                            */
/*======================================================================*/
void Read_Narrowband_LSP_V2
(
    HANDLE_BSBITSTREAM bitStream,            /* In: Bitstream                  */
    unsigned long indices[],           /* Out: indices                   */
    unsigned long ep_class
)
{
    unsigned long dummy;

    switch (ep_class)
    {
        case 0:
            /* read class 1 */
            break;
        case 1:
            /* read class 2 */
            /* lpc0: 0-1*/
            BsGetBit(bitStream, &indices[0], 2);
            /* lpc1: 0 */
            BsGetBit(bitStream, &indices[1], 1);
            break;

        case 2:
            /* read class 3 */
            /* lpc2: 0, 6 */
            BsGetBit(bitStream, &dummy, 1);
            indices[2] |= (dummy<<6);
            BsGetBit(bitStream, &dummy, 1);
            indices[2] |= dummy;
            /* lpc4 */
            BsGetBit(bitStream, &indices[4], 1);

            break;

        case 3:
            /* read class 4 */
            /* lpc0: 2-3 */
            BsGetBit(bitStream, &dummy, 2);
            indices[0] |= (dummy<<2);
            /* lpc1: 1-2 */
            BsGetBit(bitStream, &dummy, 2);
            indices[1] |= (dummy<<1);
            /* lpc2: 1-5 */
            BsGetBit(bitStream, &dummy, 5);
            indices[2] |= (dummy<<1);

            break;

        case 4:
            /* read class 5 */
            /* lpc1: 3 */
            BsGetBit(bitStream, &dummy, 1);
            indices[1] |= (dummy<<3);
            /* lpc3: all */
            BsGetBit(bitStream, &indices[3], 6);
            break;

        default : 
            fprintf(stderr, "Wrong Class in Read_Narrowband_LSP_V2\n");
            CommonExit(1,"celp error");
    }
}
/*======================================================================*/
/*      H I S T O R Y                                                   */
/*======================================================================*/
/* 07-06-96  R. Taori & A.Gerrits    Initial Version                    */
/* 18-09-96  R. Taori & A.Gerrits    MPEG bitstream used                */
/* 21-05-99  T. Mlasko               Version 2 stuff added              */
