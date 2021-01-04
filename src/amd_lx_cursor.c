/*
 * $Workfile: amd_lx_cursor.c $
 * $Revision: #4 $
 * $Author: raymondd $
 *
 * File Contents: Xfree cursor implementation routines
 *                for geode HWcursor init.setting cursor color,image etc
 *                are done here.
 * Project:       Geode Xfree Frame buffer device driver.
 *
 */

/* <LIC_AMD_STD>
 * Copyright (c) 2003-2005 Advanced Micro Devices, Inc.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 *  
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 *  
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 * 
 * Neither the name of the Advanced Micro Devices, Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 * </LIC_AMD_STD>  */
/* <CTL_AMD_STD>
 * </CTL_AMD_STD>  */
/* <DOC_AMD_STD>
 * </DOC_AMD_STD>  */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "nsc.h"

#include "xf86.h"
#include "xf86_OSproc.h"
#include "xf86_ansic.h"
#include "xf86Pci.h"
#include "xf86PciInfo.h"

/* Forward declarations of the functions */
Bool LXHWCursorInit(ScreenPtr pScrn);
static void LXSetCursorColors(ScrnInfoPtr pScrni, int bg, int fg);
static void LXSetCursorPosition(ScrnInfoPtr pScrni, int x, int y);
void LXLoadCursorImage(ScrnInfoPtr pScrni, unsigned char *src);
void LXHideCursor(ScrnInfoPtr pScrni);
void LXShowCursor(ScrnInfoPtr pScrni);
static Bool LXUseHWCursor(ScreenPtr pScrn, CursorPtr pCurs);
extern void LXSetVideoPosition(int x, int y, int width, int height,
				short src_w, short src_h, short drw_w,
				short drw_h, int id, int offset,
				ScrnInfoPtr pScrni);
#ifdef ARGB_CURSOR
static Bool LXUseHWCursorARGB(ScreenPtr pScreen, CursorPtr pCurs);
static void LXLoadCursorARGB(ScrnInfoPtr pScrn, CursorPtr pCurs);
#endif

/*----------------------------------------------------------------------------
 * LXHWCursorInit.
 *
 * Description	:This function sets the cursor information by probing the
 * hardware.
 *
 * Parameters.
 *     pScrn	:Screeen pointer structure.
 *
 * Returns		:TRUE on success and FALSE on Failure
 *
 * Comments		:Geode supports the hardware_cursor,no need to enable SW
 *                    cursor.
*----------------------------------------------------------------------------
*/
Bool
LXHWCursorInit(ScreenPtr pScrn)
{
   ScrnInfoPtr pScrni = xf86Screens[pScrn->myNum];
   GeodePtr pGeode = GEODEPTR(pScrni);
   xf86CursorInfoPtr infoPtr;

   infoPtr = xf86CreateCursorInfoRec();
   if (!infoPtr)
      return FALSE;
   /* the geode structure is intiallized with the cursor infoRec */
   pGeode->CursorInfo = infoPtr;
   infoPtr->MaxWidth = 32;
   infoPtr->MaxHeight = 32;
   /* seeting up the cursor flags */
   infoPtr->Flags = HARDWARE_CURSOR_BIT_ORDER_MSBFIRST |
	 HARDWARE_CURSOR_TRUECOLOR_AT_8BPP |
	 HARDWARE_CURSOR_SOURCE_MASK_NOT_INTERLEAVED;
   /* cursor info ptr is intiallized with the values obtained from
    * * durnago calls
    */
   infoPtr->SetCursorColors = LXSetCursorColors;
   infoPtr->SetCursorPosition = LXSetCursorPosition;
   infoPtr->LoadCursorImage = LXLoadCursorImage;
   infoPtr->HideCursor = LXHideCursor;
   infoPtr->ShowCursor = LXShowCursor;
   infoPtr->UseHWCursor = LXUseHWCursor;
#ifdef ARGB_CURSOR
   infoPtr->UseHWCursorARGB = LXUseHWCursorARGB;
   infoPtr->LoadCursorARGB = LXLoadCursorARGB;
#endif

   return (xf86InitCursor(pScrn, infoPtr));
}

/*----------------------------------------------------------------------------
 * LXSetCursorColors.
 *
 * Description	:This function sets the cursor foreground and background
 *                    colors
 * Parameters:
 *    pScrni:	Screeen information pointer structure.
 *    	   bg:	Specifies the color value of cursor background color.
 *    	   fg:	Specifies the color value of cursor foreground color.
 *    Returns:	none.
 *
 *   Comments:	The integer color value passed by this function is
 *              converted into  * RGB  value by the gfx_set_color routines.
 *----------------------------------------------------------------------------
 */
static void
LXSetCursorColors(ScrnInfoPtr pScrni, int bg, int fg)
{
    GeodePtr pGeode = GEODEPTR(pScrni);

#ifdef ARGB_CURSOR
    /* Don't recolour cursors set with SetCursorARGB. */
    if (pGeode->cursor_argb)
       return;
#endif

   vg_set_mono_cursor_colors(bg, fg);
}

/*----------------------------------------------------------------------------
 * LXSetCursorPosition.
 *
 * Description	:This function sets the cursor co -ordinates and enable the
 *               cursor.
 *
 * Parameters:
 *    pScrni: Screeen information pointer structure.
 *    	    x: Specifies the x-cordinates of the cursor.
 *    	    y: Specifies the y co-ordinate of the cursor.
 *    Returns: none.
 *
 *----------------------------------------------------------------------------
 */
static void
LXSetCursorPosition(ScrnInfoPtr pScrni, int x, int y)
{
   static unsigned long panOffset = 0;
   GeodePtr pGeode = GEODEPTR(pScrni);
   int newX, newY;

   (*pGeode->Rotation)(x,y,pGeode->HDisplay,pGeode->VDisplay,&newX,&newY);
   (*pGeode->RBltXlat)(newX,newY,32,32,&newX,&newY);
   if (newX < -31) newX = -31;
   if (newY < -31) newY = -31;

   {  VG_PANNING_COORDINATES panning;
      vg_set_cursor_position(newX+31, newY+31, &panning); }
   vg_set_cursor_enable(1);

#ifndef AMD_V4L2_VIDEO
   if ((pGeode->OverlayON) && (pGeode->EnabledOutput & LX_OT_FP)) {
      pGeode->PrevDisplayOffset = vg_get_display_offset();
      if (pGeode->PrevDisplayOffset != panOffset) {
	 LXSetVideoPosition(pGeode->video_x, pGeode->video_y,
			     pGeode->video_w, pGeode->video_h,
			     pGeode->video_srcw, pGeode->video_srch,
			     pGeode->video_dstw, pGeode->video_dsth,
			     pGeode->video_id, pGeode->video_offset,
			     pGeode->video_scrnptr);
	 panOffset = pGeode->PrevDisplayOffset;
      }
   }
#endif
}

/*----------------------------------------------------------------------------
 * LXLoadCursorImage
 *
 * Description	:This function loads the 32x32 cursor pattern.The shape
 *               and color is set by AND and XOR masking of arrays of 32
 *               DWORD.
 * Parameters:
 *    pScrni: Screeen information pointer structure.
 *    src    : Specifies cursor data.
 * Returns   : none
 *
 *----------------------------------------------------------------------------
*/
void
LXLoadCursorImage(ScrnInfoPtr pScrni, unsigned char *src)
{
   int i, n, x, y, newX, newY;
   unsigned long andMask[32], xorMask[32];
   GeodePtr pGeode = GEODEPTR(pScrni);
   unsigned long mskb, rowb;
   unsigned char *rowp = &src[0];
   unsigned char *mskp = &src[128];

   if( src != NULL ) {
      mskb = rowb = 0;
      for( y=32; --y>=0; ) 
         andMask[y] = xorMask[y] = 0;
      for( y=0; y<32; ++y ) {
         for( x=0; x<32; ++x ) {
            if( (i=x&7) == 0 ) {
               rowb = (*rowp & *mskp);
               mskb = ~(*mskp);
               ++rowp;  ++mskp;
            }
            (*pGeode->Rotation)(x,y,32,32,&newX,&newY);
            i = 7-i;  n = 31-newX;
            andMask[newY] |= (((mskb>>i)&1)<<n);
            xorMask[newY] |= (((rowb>>i)&1)<<n);
         }
      }
   }
   else {
      for( y=32; --y>=0; ) {
         andMask[y] = ~0;
         xorMask[y] = 0;
      }
   }

#ifdef ARGB_CURSOR
    pGeode->cursor_argb = FALSE;
#endif


#if 0
   andMask[31] = 0;
   xorMask[31] = 0;
   for( y=31; --y>0; ) {
      andMask[y] &= ~0x80000001;
      xorMask[y] &= ~0x80000001;
   }
   andMask[0] = 0;
   xorMask[0] = 0;
#endif

   vg_set_mono_cursor_shape32(pGeode->CursorStartOffset,&andMask[0],&xorMask[0],31,31);
}

/*----------------------------------------------------------------------------
 * LXHideCursor
 *
 * Description	:This function will disable the cursor.
 *
 * Parameters:
 *    pScrni: Handles to the Screeen information pointer structure.
 *
 *    Returns: none.
 *
 *   Comments:	gfx_set_cursor enable function is hardcoded to disable
 *		the cursor.
 *----------------------------------------------------------------------------
 */
void
LXHideCursor(ScrnInfoPtr pScrni)
{
   vg_set_cursor_enable(0);
}

/*----------------------------------------------------------------------------
 * LXShowCursor
 *
 * Description	:This function will enable  the cursor.
 *
 * Parameters:
 *	pScrni		:Handles to the Screeen information pointer structure.
 *
 * Returns      :none
 *
 * Comments		:gfx_set_cursor enable function is hardcoded to enable the
 * 											cursor
 *----------------------------------------------------------------------------
*/
void
LXShowCursor(ScrnInfoPtr pScrni)
{
   vg_set_cursor_enable(1);
}

/*----------------------------------------------------------------------------
 * LXUseHwCursor.
 *
 * Description	:This function will sets the hardware cursor flag in
 *                 pscreen  structure.
 *
 * Parameters.
 *	pScreen		:Handles to the Screeen pointer structure.
 *
 * Returns		:none
 *
 * Comments		:none
 *
 *----------------------------------------------------------------------------
*/
static Bool
LXUseHWCursor(ScreenPtr pScrn, CursorPtr pCurs)
{
   ScrnInfoPtr pScrni = XF86SCRNINFO(pScrn);
 
   if (pScrni->currentMode->Flags & V_DBLSCAN)
      return FALSE;
   return TRUE;
}

#ifdef ARGB_CURSOR
#include "cursorstr.h"

/* Determine if hardware cursor is in use. */
static Bool LXUseHWCursorARGB (ScreenPtr pScrn, CursorPtr pCurs)
{
   ScrnInfoPtr pScrni = xf86Screens[pScrn->myNum];
   GeodePtr pGeode = GEODEPTR(pScrni);

   if (LXUseHWCursor(pScrn, pCurs) &&
      pCurs->bits->height <= HW_ARGB_CURSOR_H &&
      pCurs->bits->width <= HW_ARGB_CURSOR_W)
      return TRUE;
   return FALSE;
}

static void LXLoadCursorARGB (ScrnInfoPtr pScrni, CursorPtr pCurs)
{
   GeodePtr pGeode = GEODEPTR(pScrni);

   int           x, y, w, h, newX,newY, newW, newH;
   CARD32        *image = pCurs->bits->argb;
   CARD32        rotated_image[HW_ARGB_CURSOR_W * HW_ARGB_CURSOR_H];

   if (!image)
      return; /* XXX can't happen */

   w = pCurs->bits->width;
   h = pCurs->bits->height;

   switch( pGeode->Rotate ) 
   {
   case 1:
   case 3:
      newW=h;
      newH=w;
      break;
   case 2:
   default:
      newW=w;
      newH=h;
   }

   if (newW > HW_ARGB_CURSOR_W)
       newW = HW_ARGB_CURSOR_W;
   if (newH > HW_ARGB_CURSOR_H)
       newH = HW_ARGB_CURSOR_H;

   for (y=0;y<h;y++)
     for (x=0;x<w;x++) {
        (*pGeode->Rotation)(x,y,w,h,&newX,&newY);
        rotated_image [newY*newW+newX] = image[y*w+x];
     }

   vg_set_color_cursor_shape (pGeode->CursorStartOffset,
                              (unsigned char*)rotated_image,
                              newW, newH, newW * 4 /*pitch*/, 31/*x_hot*/, 31/*y_hotspot*/);

   pGeode->cursor_argb = TRUE;
}

#endif

/* End of File */
