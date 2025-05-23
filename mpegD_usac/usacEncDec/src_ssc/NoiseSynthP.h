/***********************************************************************
MPEG-4 Audio RM Module
Parametric based codec - SSC (SinuSoidal Coding) bit stream Encoder

This software was originally developed by:
* Arno Peters, Philips CE - ASA-labs Eindhoven <arno.peters@philips.com>
* Jan Dasselaar, Philips CE - ASA-labs Eindhoven <jan.dasselaar@philips.com>
* Werner Oomen, Philips CE - ASA-labs Eindhoven <werner.oomen@philips.com>

And edited by:
*

in the course of development of the MPEG-4 Audio standard ISO-14496-1, 2 and 3. 
This software module is an implementation of a part of one or more MPEG-4 Audio
tools as specified by the MPEG-4 Audio standard. ISO/IEC gives users of the 
MPEG-4 Audio standards free licence to this software module or modifications 
thereof for use in hardware or software products claiming conformance to the 
MPEG-4 Audio standards. Those intending to use this software module in hardware
or software products are advised that this use may infringe existing patents.
The original developers of this software of this module and their company, 
the subsequent editors and their companies, and ISO/EIC have no liability for 
use of this software module or modifications thereof in an implementation. 
Copyright is not released for non MPEG-4 Audio conforming products. The 
original developer retains full right to use this code for his/her own purpose,
assign or donate the code to a third party and to inhibit third party from
using the code for non MPEG-4 Audio conforming products. This copyright notice
must be included in all copies of derivative works.

Copyright � 2001.

Source file: NoiseSynthP.h

Required libraries: <none>

Authors:
AP: Arno Peters,   Philips CE - ASA-labs Eindhoven <arno.peters@philips.com>
JD: Jan Dasselaar, Philips CE - ASA-labs Eindhoven <jan.dasselaar@philips.com>
WO: Werner Oomen,  Philips CE - ASA-labs Eindhoven <werner.oomen@philips.com>

Changes:
06-Sep-2001 JD  Initial version
25 Jul 2002 TM  m8540 improved noise coding + 8 sf/frame
15-Jul-2003 RJ  RM3a: Added time/pitch scaling, command line based
************************************************************************/

/******************************************************************************
 *
 *   Module              : Noise synthesiser
 *
 *   Description         : Generates Noise Components
 *
 *   Tools               : Microsoft Visual C++ 6.0
 *
 *   Target Platform     : ANSI-C
 *
 *   Naming Conventions  : All function names are prefixed by SSC_NOISESYNTH_
 *
 *   Build options       : If the SSC_NOISE_SYNTH_FAST symbol is defined a 
 *                         fast replacement for the random number generator 
 *                         will be used. This generator produces different
 *                         numbers however.
 *
 *
 ******************************************************************************/

/*============================================================================*/
/*       INCLUDES                                                             */
/*============================================================================*/

#include "PlatformTypes.h"
#include "SSC_System.h"
#include "SSC_SigProc_Types.h"

/*============================================================================*/
/*       TYPE DEFINITIONS                                                     */
/*============================================================================*/

typedef struct _SSC_NOISESYNTH
{
    UInt           FilterLength;
    UInt32         RandomSeed;
    SSC_SAMPLE_INT FilterState[SSC_N_MAX_FILTER_COEFFICIENTS+1];
    SSC_SAMPLE_INT* pBuffer;
    SSC_SAMPLE_INT* envGain;
} SSC_NOISESYNTH;
