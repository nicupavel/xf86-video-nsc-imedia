/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/nsc/nsc.h,v 1.5tsi Exp $ */
/*
 * $Workfile: nsc.h $
 * $Revision$
 * $Author$
 *
 * File Contents: This file contains the data structures Geode driver.
 *
 * Project:       Geode Xfree Frame buffer device driver.
 * 
 */

/* 
 * NSC_LIC_ALTERNATIVE_PREAMBLE
 *
 * Revision 1.0
 *
 * National Semiconductor Alternative GPL-BSD License
 *
 * National Semiconductor Corporation licenses this software 
 * ("Software"):
 *
 * National Xfree frame buffer driver
 *
 * under one of the two following licenses, depending on how the 
 * Software is received by the Licensee.
 * 
 * If this Software is received as part of the Linux Framebuffer or
 * other GPL licensed software, then the GPL license designated 
 * NSC_LIC_GPL applies to this Software; in all other circumstances 
 * then the BSD-style license designated NSC_LIC_BSD shall apply.
 *
 * END_NSC_LIC_ALTERNATIVE_PREAMBLE */

/* NSC_LIC_BSD
 *
 * National Semiconductor Corporation Open Source License for 
 *
 * National Xfree frame buffer driver
 *
 * (BSD License with Export Notice)
 *
 * Copyright (c) 1999-2001
 * National Semiconductor Corporation.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 *
 *   * Redistributions of source code must retain the above copyright 
 *     notice, this list of conditions and the following disclaimer. 
 *
 *   * Redistributions in binary form must reproduce the above 
 *     copyright notice, this list of conditions and the following 
 *     disclaimer in the documentation and/or other materials provided 
 *     with the distribution. 
 *
 *   * Neither the name of the National Semiconductor Corporation nor 
 *     the names of its contributors may be used to endorse or promote 
 *     products derived from this software without specific prior 
 *     written permission. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
 * NATIONAL SEMICONDUCTOR CORPORATION OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER 
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE,
 * INTELLECTUAL PROPERTY INFRINGEMENT, OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * EXPORT LAWS: THIS LICENSE ADDS NO RESTRICTIONS TO THE EXPORT LAWS OF 
 * YOUR JURISDICTION. It is licensee's responsibility to comply with 
 * any export regulations applicable in licensee's jurisdiction. Under 
 * CURRENT (2001) U.S. export regulations this software 
 * is eligible for export from the U.S. and can be downloaded by or 
 * otherwise exported or reexported worldwide EXCEPT to U.S. embargoed 
 * destinations which include Cuba, Iraq, Libya, North Korea, Iran, 
 * Syria, Sudan, Afghanistan and any other country to which the U.S. 
 * has embargoed goods and services. 
 *
 * END_NSC_LIC_BSD */

/* NSC_LIC_GPL
 *
 * National Semiconductor Corporation Gnu General Public License for 
 *
 * Geode Xfree frame buffer driver
 *
 * (GPL License with Export Notice)
 *
 * Copyright (c) 1999-2001
 * National Semiconductor Corporation.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version  
 *
 * In addition to the terms of the GNU General Public License, neither 
 * the name of the National Semiconductor Corporation nor the names of 
 * its contributors may be used to endorse or promote products derived 
 * from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
 * NATIONAL SEMICONDUCTOR CORPORATION OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER 
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE, 
 * INTELLECTUAL PROPERTY INFRINGEMENT, OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE. See the GNU General Public License for more details. 
 *
 * EXPORT LAWS: THIS LICENSE ADDS NO RESTRICTIONS TO THE EXPORT LAWS OF 
 * YOUR JURISDICTION. It is licensee's responsibility to comply with 
 * any export regulations applicable in licensee's jurisdiction. Under 
 * CURRENT (2001) U.S. export regulations this software 
 * is eligible for export from the U.S. and can be downloaded by or 
 * otherwise exported or reexported worldwide EXCEPT to U.S. embargoed 
 * destinations which include Cuba, Iraq, Libya, North Korea, Iran, 
 * Syria, Sudan, Afghanistan and any other country to which the U.S. 
 * has embargoed goods and services. 
 *
 * You should have received a copy of the GNU General Public License 
 * along with this file; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 
 *
 * END_NSC_LIC_GPL */

#ifndef _NSC_GEODE_H_
#define _NSC_GEODE_H_

// #include "config.h"

#include "xaa.h"
#include "xf86Cursor.h"
#if !defined(STB_X)
#include "vgaHW.h"
#endif
#include "xf86int10.h"
#include "xf86xv.h"

#if defined(STB_X)
#define GFX(func) Gal_##func
#define GFX2(func) Gal2_##func
#define OPTACCEL(func) func
#else /* STB_X */
#define GFX(func) gfx_##func
#define GFX2(func) gfx2_##func

#if defined(OPT_ACCEL)
#define OPTACCEL(func) OPT##func
#else /* OPT_ACCEL */
#define OPTACCEL(func) func
#endif /* OPT_ACCEL */

#endif /* STB_X */

#define GEODEPTR(p) ((GeodePtr)((p)->driverPrivate))

#define DEFAULT_IMG_LINE_BUFS 20
#define DEFAULT_CLR_LINE_BUFS 20
/* 64x64 cursor used as 32x32 */
#define HW_CURSOR_W 64
#define HW_CURSOR_H 64

#define HW_ARGB_CURSOR_W 48
#define HW_ARGB_CURSOR_H 64

#define DebugPort(_Val) gfx_outb(0x84, (_Val));

#define DEFAULT_NUM_OF_BUF 20		/* default # of buffers */

#if defined(MYDBG)
#define DEBUGMSG(cond, drv_msg) if((cond)) xf86DrvMsg drv_msg
#else
#define DEBUGMSG(cond, drv_msg)
#endif

/* Overlay Transparency Key */
#define TRANSPARENCY_KEY 255

#if defined(EXTERN)
unsigned char DCount = 0;

#if defined(STB_X)
void
gfx_outb(unsigned short port, unsigned char data)
{
   __asm__ volatile ("outb %0,%1"::"a" (data), "d"(port));
}
#endif
#else
extern unsigned char DCount;

#if defined(STB_X)
extern void gfx_outb(unsigned short port, unsigned char data);
extern unsigned char gfx_inb(unsigned short port);
#endif
#endif

#if defined(STB_X)
#include "nsc_galproto.h"
#else
extern void gfx_write_reg32(int offset, int data);
extern void gfx_write_reg16(int offset, short data);
extern void gfx_write_reg8(int offset, char data);
extern int gfx_read_reg32(int offset);
extern short gfx_read_reg16(int offset);
extern void gfx_write_vid32(int offset, int data);
extern int gfx_read_vid32(int offset);
extern unsigned char gfx_inb(unsigned short port);
extern void gfx_outb(unsigned short port, unsigned char data);
extern unsigned short gfx_inw(unsigned short port);
extern void gfx_outw(unsigned short port, unsigned short data);
extern unsigned long gfx_ind(unsigned short port);
extern void gfx_outd(unsigned short port, unsigned long data);

/* conflict with cim ... */
#define Q_WORD QQ_WORD
#include "gfx_rtns.h"
#undef Q_WORD

#include "panel.h"

#include "cim_rtns.h"

#define CIM_CMD_BFR_SZ 0x200000L
#define CIM_CMD_BFR_MIN 0x20000L

typedef struct __CIM_DISPLAYTIMING
{
   unsigned short wPitch;
   unsigned short wBpp;

   VG_DISPLAY_MODE vgDisplayMode;
}
CIM_DISPLAYTIMING, *CIM_PDISPLAYTIMING;


typedef struct __TVPARAMS
{
   unsigned int dwFlags;
   unsigned short wWidth;
   unsigned short wHeight;
   unsigned short wStandard;
   unsigned short wType;
   unsigned short wOutput;
   unsigned short wResolution;
   Bool bState;
}
TVPARAMS, *PTVPARAMS;

typedef struct __DISPLAYTIMING
{
   unsigned int dwDotClock;
   unsigned short wPitch;
   unsigned short wBpp;
   unsigned short wHTotal;
   unsigned short wHActive;
   unsigned short wHSyncStart;
   unsigned short wHSyncEnd;
   unsigned short wHBlankStart;
   unsigned short wHBlankEnd;
   unsigned short wVTotal;
   unsigned short wVActive;
   unsigned short wVSyncStart;
   unsigned short wVSyncEnd;
   unsigned short wVBlankStart;
   unsigned short wVBlankEnd;
   unsigned short wPolarity;
}
DISPLAYTIMING, *PDISPLAYTIMING;

/* TV Timings */
typedef struct __TVTIMING
{
   unsigned long HorzTim;
   unsigned long HorzSync;
   unsigned long VertSync;
   unsigned long LineEnd;
   unsigned long VertDownscale;
   unsigned long HorzScaling;
   unsigned long TimCtrl1;
   unsigned long TimCtrl2;
   unsigned long Subfreq;
   unsigned long DispPos;
   unsigned long DispSize;
   unsigned long Debug;
   unsigned long DacCtrl;
   unsigned int DotClock;
}
TVTIMING, *PTVTIMING;

#endif /* STB_X */

typedef struct _VESARec
{
   xf86Int10InfoPtr pInt;
}
VESARec, *VESAPtr;

#define LX 0x20
#define LX_CRT 0x21
#define LX_TFT 0x22

/* output enable types */
#define LX_OT_CRT  0x0001
#define LX_OT_FP   0x0002
#define LX_OT_VOP  0x0004
#define LX_OT_DRGB 0x0008

#define INT10_SUPPORT 1

typedef struct
{
   /* Private struct for the server */
   unsigned long cpu_version;		/* [7:0] Type:1=GXLV,2=SC1400 */
   unsigned long cpu_revision;
   unsigned long vid_version;		/* [7:0] Type:1=CS5530,2=SC1400 */
   INIT_BASE_ADDRESSES InitBaseAddress;

   EntityInfoPtr pEnt;
   ScreenBlockHandlerProcPtr BlockHandler;	/* needed for video */
   int DetectedChipSet;
   int Chipset;

   int cimFd;
   unsigned long CmdBfrOffset;
   unsigned long CmdBfrSize;
   unsigned int EnabledOutput;
   unsigned long FBTop;

   unsigned long FBLinearAddr;
   unsigned char *FBBase;
   unsigned long FBAvail;
   unsigned long FBOffset;
   unsigned long FBSize;
   unsigned int cpu_reg_size;
   unsigned int gp_reg_size;
   unsigned int vid_reg_size;

   unsigned int vg_reg_size;
   unsigned int vip_reg_size;

   int Pitch;
   int AccelPitch;                /* accel pitch (may be ShadowPitch) */

   Bool HWCursor;
#ifdef ARGB_CURSOR
   Bool cursor_argb;
#endif
   Bool NoAccel;
   Bool CustomMode;
   unsigned long VideoKey;

   Bool TVSupport;
   int tv_encoder;
   int tv_bus_fmt;
   int tv_flags;
   int tv_601_fmt;
   int tv_601_flags;
   int tv_conversion;
   int tv_vsync_shift;
   int tv_vsync_shift_count;
   int tv_vsync_select;
   int tvox, tvoy;

   int FPBiosResX, FPBiosResY;
   int FPGeomDstSet, FPGeomDstX, FPGeomDstY;
   int FPGeomActSet, FPGeomActX, FPGeomActY;

#if defined(STB_X)
   GAL_TVPARAMS TvParam;
#else
   TVPARAMS TvParam;
#endif					/* STB_X */

   int TVOx, TVOy, TVOw, TVOh;
   Bool TV_Overscan_On;

   Bool Panel;

   /* Flatpanel support from Bios */
   int FPBX;				/* xres */
   int FPBY;				/* yres */
   int FPBB;				/* bpp */
   int FPBF;				/* freq */

   int Rotate;
   void (*Rotation)(int x,int y,int w,int h,int *newX,int *newY);
   void (*RBltXlat)(int x,int y,int w,int h,int *newX,int *newY);


   Bool ShadowFB;
   unsigned char *ShadowPtr;
   int ShadowSize;
   int ShadowPitch;
   int ShadowInFBMem;

   int orig_virtX;  /* original */
   int orig_virtY;

   int HDisplay;    /* rotated */
   int VDisplay;

   void (*PointerMoved) (int index, int x, int y);
   /* CloseScreen function.        */
   CloseScreenProcPtr CloseScreen;

   Bool Compression;
   VG_COMPRESSION_DATA CBData;

   unsigned int CBOffset;
   unsigned int CBPitch;
   unsigned int CBSize;
   unsigned long CursorStartOffset;
   unsigned int CursorSize;
   xf86CursorInfoPtr CursorInfo;
   int CursorXHot;
   int CursorYHot;
   unsigned long OffscreenStartOffset;
   unsigned int OffscreenSize;

	/***Image Write structures ***/

   /* offset in video memory for ImageWrite Buffers */
   unsigned char **AccelImageWriteBuffers;
   unsigned char **AccelImageWriteBufferOffsets;
   int NoOfImgBuffers;
   unsigned char **AccelColorExpandBuffers;
   int NoOfColorExpandLines;

   FBAreaPtr CompressionArea;
   FBAreaPtr AccelImgArea;
/*****************************************/
/* Saved Console State */
#if defined(STB_X)
   GAL_VGAMODEDATA FBgfxVgaRegs;
   GAL_DISPLAYTIMING FBgfxdisplaytiming;
   GAL_TVTIMING FBgfxtvtiming;
#else
   gfx_vga_struct FBgfxVgaRegs;
   DISPLAYTIMING FBgfxdisplaytiming;
   TVTIMING FBtvtiming;
#endif					/* STB_X */

   CIM_DISPLAYTIMING FBcimdisplaytiming;

   int FBVGAActive;
   unsigned int FBTVActive;
   unsigned int FBTVEnabled;
   unsigned long FBDisplayOffset;
   unsigned long PrevDisplayOffset;

   VESAPtr vesa;

   /* compression */
   int FBCompressionEnable;

   VG_COMPRESSION_DATA FBCBData;
   VG_CURSOR_DATA FBCursor;

   unsigned long FBCompressionOffset;
   unsigned short FBCompressionPitch;
   unsigned short FBCompressionSize;

   /* Save the Cursor offset of the FB */
   unsigned long FBCursorOffset;
   unsigned char FBBIOSMode;

/*****************************************/

   XAAInfoRecPtr AccelInfoRec;

   DGAModePtr DGAModes;
   int numDGAModes;
   Bool DGAactive;
   int DGAViewportStatus;
/*****************************************/
   int video_x;
   int video_y;
   short video_w;
   short video_h;
   short video_srcw;
   short video_srch;
   short video_dstw;
   short video_dsth;
   int video_id;
   int video_offset;
   ScrnInfoPtr video_scrnptr;
   BOOL OverlayON;

   int videoKey;
   XF86VideoAdaptorPtr adaptor;
   int OverlaySkewX;
   int OverlaySkewY;
   int VideoZoomMax;
}
GeodeRec, *GeodePtr;

/* option flags are self-explanatory */
typedef enum
{
   OPTION_SW_CURSOR,
   OPTION_HW_CURSOR,
   OPTION_NOCOMPRESSION,
   OPTION_NOACCEL,
   OPTION_TV_SUPPORT,
   OPTION_TV_OUTPUT,
   OPTION_TV_OVERSCAN,
   OPTION_TV_ENCODER,
   OPTION_TV_BUS_FMT,
   OPTION_TV_FLAGS,
   OPTION_TV_601_FLAGS,
   OPTION_TV_VSYNC_SELECT,
   OPTION_TV_CONVERSION,
   OPTION_SHADOW_FB,
   OPTION_ROTATE,
   OPTION_FLATPANEL,
   OPTION_FLATPANEL_INFO,
   OPTION_FLATPANEL_IN_BIOS,
   OPTION_COLOR_KEY,
   OPTION_OSM,
   OPTION_OSM_IMG_BUFS,
   OPTION_OSM_CLR_BUFS,
   OPTION_DONT_PROGRAM,
   OPTION_CRTENABLE,
   OPTION_CUSTOM_MODE,
   OPTION_FP_DEST_GEOM,
   OPTION_FP_ACTIVE_GEOM
}
GeodeOpts;

#endif /* _NSC_GEODE_H_ */
