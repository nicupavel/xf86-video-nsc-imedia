 /*
  * 
  * <LIC_AMD_STD>
  * Copyright (C) <years> Advanced Micro Devices, Inc.  All Rights Reserved.
  * </LIC_AMD_STD>
  * 
  * <CTL_AMD_STD>
  * </CTL_AMD_STD>
  * 
  * <DOC_AMD_STD>
  * This file contains routines used in Redcloud initialization.
  * </DOC_AMD_STD>
  * 
  */

/*-----------------------------------------------------------------------------
 * gfx_get_core_freq
 *
 * Returns the core clock frequency of a GX3.
 *-----------------------------------------------------------------------------
 */
#if GFX_INIT_DYNAMIC
unsigned long gu3_get_core_freq(void)
#else
unsigned long gfx_get_core_freq(void)
#endif
{
	unsigned long value;

	/* CPU SPEED IS REPORTED BY A VSM IN VSA II */
	/* Virtual Register Class = 0x12 (Sysinfo)  */
	/* CPU Speed Register     = 0x01            */

	OUTW (0xAC1C, 0xFC53);
	OUTW (0xAC1C, 0x1201);

	value = (unsigned long)(INW (0xAC1E));

	return (value);
}

/*-----------------------------------------------------------------------------
 * gfx_get_cpu_register_base
 * 
 * This routine returns the base address for display controller registers.  
 *-----------------------------------------------------------------------------
 */
#if GFX_INIT_DYNAMIC
unsigned long gu3_get_cpu_register_base(void)
#else
unsigned long gfx_get_cpu_register_base(void)
#endif
{
	return gfx_pci_config_read (0x80000918);
}

/*-----------------------------------------------------------------------------
 * gfx_get_graphics_register_base
 * 
 * This routine returns the base address for the graphics acceleration.  
 *-----------------------------------------------------------------------------
 */
#if GFX_INIT_DYNAMIC
unsigned long gu3_get_graphics_register_base(void)
#else
unsigned long gfx_get_graphics_register_base(void)
#endif
{
	return gfx_pci_config_read (0x80000914);
}

/*-----------------------------------------------------------------------------
 * gfx_get_frame_buffer_base
 * 
 * This routine returns the base address for graphics memory.  
 *-----------------------------------------------------------------------------
 */
#if GFX_INIT_DYNAMIC
unsigned long gu3_get_frame_buffer_base(void)
#else
unsigned long gfx_get_frame_buffer_base(void)
#endif
{
	return gfx_pci_config_read (0x80000910);
}

/*-----------------------------------------------------------------------------
 * gfx_get_frame_buffer_size
 * 
 * This routine returns the total size of graphics memory, in bytes.
 *-----------------------------------------------------------------------------
 */
#if GFX_INIT_DYNAMIC
unsigned long gu3_get_frame_buffer_size(void)
#else
unsigned long gfx_get_frame_buffer_size(void)
#endif
{
	unsigned long value;

	/* FRAME BUFFER SIZE IS REPORTED BY A VSM IN VSA II */
	/* Virtual Register Class     = 0x02                */
	/* VG_MEM_SIZE (1MB units)    = 0x00                */

	OUTW (0xAC1C, 0xFC53);
	OUTW (0xAC1C, 0x0200);

	value = (unsigned long)(INW (0xAC1E)) & 0xFEl;

    /* LIMIT FRAME BUFFER SIZE TO 16MB TO MATCH LEGACY */

    if ((value << 20) > 0x1000000)
        return 0x1000000;

	return (value << 20);
}

/*-----------------------------------------------------------------------------
 * gfx_get_vid_register_base
 * 
 * This routine returns the base address for the video hardware.  
 *-----------------------------------------------------------------------------
 */
#if GFX_INIT_DYNAMIC
unsigned long gu3_get_vid_register_base(void)
#else
unsigned long gfx_get_vid_register_base(void)
#endif
{
	return gfx_pci_config_read (0x8000091C);
}



/* END OF FILE */
