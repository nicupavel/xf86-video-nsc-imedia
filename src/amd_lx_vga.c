/*
 * $Workfile: amd_lx_vga.c $
 * $Revision: #3 $
 * $Author: raymondd $
 *
 * This file contains routines to set modes using the VGA registers.  
 * Since this file is for the first generation graphics unit, it interfaces
 * to SoftVGA registers.  It works for both VSA1 and VSA2.
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


/* VGA STRUCTURE */

int gu3_get_vga_active(void);

int
gu3_get_vga_active(void)
{
   int data = READ_REG32(DC3_GENERAL_CFG);

   if (data & DC3_GCFG_VGAE)
      return 1;
   return 0;
}

/* END OF FILE */
