/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2010-2011 Freescale Semiconductor, Inc.
 * Author: Dipen Dudhat <dipen.dudhat@freescale.com>
 */

#ifndef __FSL_IFC_H
#define __FSL_IFC_H

#ifdef CONFIG_FSL_IFC
#include <config.h>
#include <part.h>
#ifdef CONFIG_ARM
#include <asm/arch/soc.h>
#else
#include <asm/ppc.h>
#endif

#define FSL_IFC_V1_1_0	0x01010000
#define FSL_IFC_V2_0_0	0x02000000

#ifdef CONFIG_SYS_FSL_IFC_LE
#define ifc_in32(a)       in_le32(a)
#define ifc_out32(a, v)   out_le32(a, v)
#define ifc_in16(a)       in_le16(a)
#define ifc_out16(a, v)   out_le16(a, v)
#elif defined(CONFIG_SYS_FSL_IFC_BE)
#define ifc_in32(a)       in_be32(a)
#define ifc_out32(a, v)   out_be32(a, v)
#define ifc_in16(a)       in_be16(a)
#define ifc_out16(a, v)   out_be16(a, v)
#else
#error Neither CONFIG_SYS_FSL_IFC_LE nor CONFIG_SYS_FSL_IFC_BE is defined
#endif

/*
 * CSPR - Chip Select Property Register
 */
#define CSPR_BA				0xFFFF0000
#define CSPR_BA_SHIFT			16
#define CSPR_PORT_SIZE			0x00000180
#define CSPR_PORT_SIZE_SHIFT		7
/* Port Size 8 bit */
#define CSPR_PORT_SIZE_8		0x00000080
/* Port Size 16 bit */
#define CSPR_PORT_SIZE_16		0x00000100
/* Port Size 32 bit */
#define CSPR_PORT_SIZE_32		0x00000180
/* Write Protect */
#define CSPR_WP				0x00000040
#define CSPR_WP_SHIFT			6
/* Machine Select */
#define CSPR_MSEL			0x00000006
#define CSPR_MSEL_SHIFT			1
/* External Transceiver Enable */
#define CSPR_TE			0x00000010
/* NOR */
#define CSPR_MSEL_NOR			0x00000000
/* NAND */
#define CSPR_MSEL_NAND			0x00000002
/* GPCM */
#define CSPR_MSEL_GPCM			0x00000004
/* Bank Valid */
#define CSPR_V				0x00000001
#define CSPR_V_SHIFT			0

/* Convert an address into the right format for the CSPR Registers */
#define CSPR_PHYS_ADDR(x)		(((uint64_t)x) & 0xffff0000)

/*
 * Address Mask Register
 */
#define IFC_AMASK_MASK			0xFFFF0000
#define IFC_AMASK_SHIFT			16
#define IFC_AMASK(n)			(IFC_AMASK_MASK << \
					(LOG2(n) - IFC_AMASK_SHIFT))

/*
 * Chip Select Option Register IFC_NAND Machine
 */
/* Enable ECC Encoder */
#define CSOR_NAND_ECC_ENC_EN		0x80000000
#define CSOR_NAND_ECC_MODE_MASK		0x30000000
/* 4 bit correction per 520 Byte sector */
#define CSOR_NAND_ECC_MODE_4		0x00000000
/* 8 bit correction per 528 Byte sector */
#define CSOR_NAND_ECC_MODE_8		0x10000000
/* Enable ECC Decoder */
#define CSOR_NAND_ECC_DEC_EN		0x04000000
/* Row Address Length */
#define CSOR_NAND_RAL_MASK		0x01800000
#define CSOR_NAND_RAL_SHIFT		20
#define CSOR_NAND_RAL_1			0x00000000
#define CSOR_NAND_RAL_2			0x00800000
#define CSOR_NAND_RAL_3			0x01000000
#define CSOR_NAND_RAL_4			0x01800000
/* Page Size 512b, 2k, 4k */
#define CSOR_NAND_PGS_MASK		0x00180000
#define CSOR_NAND_PGS_SHIFT		16
#define CSOR_NAND_PGS_512		0x00000000
#define CSOR_NAND_PGS_2K		0x00080000
#define CSOR_NAND_PGS_4K		0x00100000
#define CSOR_NAND_PGS_8K		0x00180000
/* Spare region Size */
#define CSOR_NAND_SPRZ_MASK		0x0000E000
#define CSOR_NAND_SPRZ_SHIFT		13
#define CSOR_NAND_SPRZ_16		0x00000000
#define CSOR_NAND_SPRZ_64		0x00002000
#define CSOR_NAND_SPRZ_128		0x00004000
#define CSOR_NAND_SPRZ_210		0x00006000
#define CSOR_NAND_SPRZ_218		0x00008000
#define CSOR_NAND_SPRZ_224		0x0000A000
#define CSOR_NAND_SPRZ_CSOR_EXT	0x0000C000
/* Pages Per Block */
#define CSOR_NAND_PB_MASK		0x00000700
#define CSOR_NAND_PB_SHIFT		8
#define CSOR_NAND_PB(n)		((LOG2(n) - 5) << CSOR_NAND_PB_SHIFT)
/* Time for Read Enable High to Output High Impedance */
#define CSOR_NAND_TRHZ_MASK		0x0000001C
#define CSOR_NAND_TRHZ_SHIFT		2
#define CSOR_NAND_TRHZ_20		0x00000000
#define CSOR_NAND_TRHZ_40		0x00000004
#define CSOR_NAND_TRHZ_60		0x00000008
#define CSOR_NAND_TRHZ_80		0x0000000C
#define CSOR_NAND_TRHZ_100		0x00000010
/* Buffer control disable */
#define CSOR_NAND_BCTLD			0x00000001

/*
 * Chip Select Option Register - NOR Flash Mode
 */
/* Enable Address shift Mode */
#define CSOR_NOR_ADM_SHFT_MODE_EN	0x80000000
/* Page Read Enable from NOR device */
#define CSOR_NOR_PGRD_EN		0x10000000
/* AVD Toggle Enable during Burst Program */
#define CSOR_NOR_AVD_TGL_PGM_EN		0x01000000
/* Address Data Multiplexing Shift */
#define CSOR_NOR_ADM_MASK		0x0003E000
#define CSOR_NOR_ADM_SHIFT_SHIFT	13
#define CSOR_NOR_ADM_SHIFT(n)	((n) << CSOR_NOR_ADM_SHIFT_SHIFT)
/* Type of the NOR device hooked */
#define CSOR_NOR_NOR_MODE_ASYNC_NOR	0x00000000
#define CSOR_NOR_NOR_MODE_AVD_NOR	0x00000020
/* Time for Read Enable High to Output High Impedance */
#define CSOR_NOR_TRHZ_MASK		0x0000001C
#define CSOR_NOR_TRHZ_SHIFT		2
#define CSOR_NOR_TRHZ_20		0x00000000
#define CSOR_NOR_TRHZ_40		0x00000004
#define CSOR_NOR_TRHZ_60		0x00000008
#define CSOR_NOR_TRHZ_80		0x0000000C
#define CSOR_NOR_TRHZ_100		0x00000010
/* Buffer control disable */
#define CSOR_NOR_BCTLD			0x00000001

/*
 * Chip Select Option Register - GPCM Mode
 */
/* GPCM Mode - Normal */
#define CSOR_GPCM_GPMODE_NORMAL		0x00000000
/* GPCM Mode - GenericASIC */
#define CSOR_GPCM_GPMODE_ASIC		0x80000000
/* Parity Mode odd/even */
#define CSOR_GPCM_PARITY_EVEN		0x40000000
/* Parity Checking enable/disable */
#define CSOR_GPCM_PAR_EN		0x20000000
/* GPCM Timeout Count */
#define CSOR_GPCM_GPTO_MASK		0x0F000000
#define CSOR_GPCM_GPTO_SHIFT		24
#define CSOR_GPCM_GPTO(n)	((LOG2(n) - 8) << CSOR_GPCM_GPTO_SHIFT)
/* GPCM External Access Termination mode for read access */
#define CSOR_GPCM_RGETA_EXT		0x00080000
/* GPCM External Access Termination mode for write access */
#define CSOR_GPCM_WGETA_EXT		0x00040000
/* Address Data Multiplexing Shift */
#define CSOR_GPCM_ADM_MASK		0x0003E000
#define CSOR_GPCM_ADM_SHIFT_SHIFT	13
#define CSOR_GPCM_ADM_SHIFT(n)	((n) << CSOR_GPCM_ADM_SHIFT_SHIFT)
/* Generic ASIC Parity error indication delay */
#define CSOR_GPCM_GAPERRD_MASK		0x00000180
#define CSOR_GPCM_GAPERRD_SHIFT		7
#define CSOR_GPCM_GAPERRD(n)	(((n) - 1) << CSOR_GPCM_GAPERRD_SHIFT)
/* Time for Read Enable High to Output High Impedance */
#define CSOR_GPCM_TRHZ_MASK		0x0000001C
#define CSOR_GPCM_TRHZ_20		0x00000000
#define CSOR_GPCM_TRHZ_40		0x00000004
#define CSOR_GPCM_TRHZ_60		0x00000008
#define CSOR_GPCM_TRHZ_80		0x0000000C
#define CSOR_GPCM_TRHZ_100		0x00000010
/* Buffer control disable */
#define CSOR_GPCM_BCTLD			0x00000001

/*
 * Flash Timing Registers (FTIM0 - FTIM2_CSn)
 */
/*
 * FTIM0 - NAND Flash Mode
 */
#define FTIM0_NAND			0x7EFF3F3F
#define FTIM0_NAND_TCCST_SHIFT	25
#define FTIM0_NAND_TCCST(n)	((n) << FTIM0_NAND_TCCST_SHIFT)
#define FTIM0_NAND_TWP_SHIFT	16
#define FTIM0_NAND_TWP(n)	((n) << FTIM0_NAND_TWP_SHIFT)
#define FTIM0_NAND_TWCHT_SHIFT	8
#define FTIM0_NAND_TWCHT(n)	((n) << FTIM0_NAND_TWCHT_SHIFT)
#define FTIM0_NAND_TWH_SHIFT	0
#define FTIM0_NAND_TWH(n)	((n) << FTIM0_NAND_TWH_SHIFT)
/*
 * FTIM1 - NAND Flash Mode
 */
#define FTIM1_NAND			0xFFFF3FFF
#define FTIM1_NAND_TADLE_SHIFT	24
#define FTIM1_NAND_TADLE(n)	((n) << FTIM1_NAND_TADLE_SHIFT)
#define FTIM1_NAND_TWBE_SHIFT	16
#define FTIM1_NAND_TWBE(n)	((n) << FTIM1_NAND_TWBE_SHIFT)
#define FTIM1_NAND_TRR_SHIFT	8
#define FTIM1_NAND_TRR(n)	((n) << FTIM1_NAND_TRR_SHIFT)
#define FTIM1_NAND_TRP_SHIFT	0
#define FTIM1_NAND_TRP(n)	((n) << FTIM1_NAND_TRP_SHIFT)
/*
 * FTIM2 - NAND Flash Mode
 */
#define FTIM2_NAND			0x1FE1F8FF
#define FTIM2_NAND_TRAD_SHIFT	21
#define FTIM2_NAND_TRAD(n)	((n) << FTIM2_NAND_TRAD_SHIFT)
#define FTIM2_NAND_TREH_SHIFT	11
#define FTIM2_NAND_TREH(n)	((n) << FTIM2_NAND_TREH_SHIFT)
#define FTIM2_NAND_TWHRE_SHIFT	0
#define FTIM2_NAND_TWHRE(n)	((n) << FTIM2_NAND_TWHRE_SHIFT)
/*
 * FTIM3 - NAND Flash Mode
 */
#define FTIM3_NAND			0xFF000000
#define FTIM3_NAND_TWW_SHIFT	24
#define FTIM3_NAND_TWW(n)	((n) << FTIM3_NAND_TWW_SHIFT)

/*
 * FTIM0 - NOR Flash Mode
 */
#define FTIM0_NOR			0xF03F3F3F
#define FTIM0_NOR_TACSE_SHIFT	28
#define FTIM0_NOR_TACSE(n)	((n) << FTIM0_NOR_TACSE_SHIFT)
#define FTIM0_NOR_TEADC_SHIFT	16
#define FTIM0_NOR_TEADC(n)	((n) << FTIM0_NOR_TEADC_SHIFT)
#define FTIM0_NOR_TAVDS_SHIFT	8
#define FTIM0_NOR_TAVDS(n)	((n) << FTIM0_NOR_TAVDS_SHIFT)
#define FTIM0_NOR_TEAHC_SHIFT	0
#define FTIM0_NOR_TEAHC(n)	((n) << FTIM0_NOR_TEAHC_SHIFT)
/*
 * FTIM1 - NOR Flash Mode
 */
#define FTIM1_NOR			0xFF003F3F
#define FTIM1_NOR_TACO_SHIFT	24
#define FTIM1_NOR_TACO(n)	((n) << FTIM1_NOR_TACO_SHIFT)
#define FTIM1_NOR_TRAD_NOR_SHIFT	8
#define FTIM1_NOR_TRAD_NOR(n)	((n) << FTIM1_NOR_TRAD_NOR_SHIFT)
#define FTIM1_NOR_TSEQRAD_NOR_SHIFT	0
#define FTIM1_NOR_TSEQRAD_NOR(n)	((n) << FTIM1_NOR_TSEQRAD_NOR_SHIFT)
/*
 * FTIM2 - NOR Flash Mode
 */
#define FTIM2_NOR			0x0F3CFCFF
#define FTIM2_NOR_TCS_SHIFT		24
#define FTIM2_NOR_TCS(n)	((n) << FTIM2_NOR_TCS_SHIFT)
#define FTIM2_NOR_TCH_SHIFT		18
#define FTIM2_NOR_TCH(n)	((n) << FTIM2_NOR_TCH_SHIFT)
#define FTIM2_NOR_TWPH_SHIFT	10
#define FTIM2_NOR_TWPH(n)	((n) << FTIM2_NOR_TWPH_SHIFT)
#define FTIM2_NOR_TWP_SHIFT		0
#define FTIM2_NOR_TWP(n)	((n) << FTIM2_NOR_TWP_SHIFT)

/*
 * FTIM0 - Normal GPCM Mode
 */
#define FTIM0_GPCM			0xF03F3F3F
#define FTIM0_GPCM_TACSE_SHIFT	28
#define FTIM0_GPCM_TACSE(n)	((n) << FTIM0_GPCM_TACSE_SHIFT)
#define FTIM0_GPCM_TEADC_SHIFT	16
#define FTIM0_GPCM_TEADC(n)	((n) << FTIM0_GPCM_TEADC_SHIFT)
#define FTIM0_GPCM_TAVDS_SHIFT	8
#define FTIM0_GPCM_TAVDS(n)	((n) << FTIM0_GPCM_TAVDS_SHIFT)
#define FTIM0_GPCM_TEAHC_SHIFT	0
#define FTIM0_GPCM_TEAHC(n)	((n) << FTIM0_GPCM_TEAHC_SHIFT)
/*
 * FTIM1 - Normal GPCM Mode
 */
#define FTIM1_GPCM			0xFF003F00
#define FTIM1_GPCM_TACO_SHIFT	24
#define FTIM1_GPCM_TACO(n)	((n) << FTIM1_GPCM_TACO_SHIFT)
#define FTIM1_GPCM_TRAD_SHIFT	8
#define FTIM1_GPCM_TRAD(n)	((n) << FTIM1_GPCM_TRAD_SHIFT)
/*
 * FTIM2 - Normal GPCM Mode
 */
#define FTIM2_GPCM			0x0F3C00FF
#define FTIM2_GPCM_TCS_SHIFT	24
#define FTIM2_GPCM_TCS(n)	((n) << FTIM2_GPCM_TCS_SHIFT)
#define FTIM2_GPCM_TCH_SHIFT	18
#define FTIM2_GPCM_TCH(n)	((n) << FTIM2_GPCM_TCH_SHIFT)
#define FTIM2_GPCM_TWP_SHIFT	0
#define FTIM2_GPCM_TWP(n)	((n) << FTIM2_GPCM_TWP_SHIFT)

/*
 * Ready Busy Status Register (RB_STAT)
 */
/* CSn is READY */
#define IFC_RB_STAT_READY_CS0		0x80000000
#define IFC_RB_STAT_READY_CS1		0x40000000
#define IFC_RB_STAT_READY_CS2		0x20000000
#define IFC_RB_STAT_READY_CS3		0x10000000

/*
 * General Control Register (GCR)
 */
#define IFC_GCR_MASK			0x8000F800
/* reset all IFC hardware */
#define IFC_GCR_SOFT_RST_ALL		0x80000000
/* Turnaroud Time of external buffer */
#define IFC_GCR_TBCTL_TRN_TIME		0x0000F800
#define IFC_GCR_TBCTL_TRN_TIME_SHIFT	11

/*
 * Common Event and Error Status Register (CM_EVTER_STAT)
 */
/* Chip select error */
#define IFC_CM_EVTER_STAT_CSER		0x80000000

/*
 * Common Event and Error Enable Register (CM_EVTER_EN)
 */
/* Chip select error checking enable */
#define IFC_CM_EVTER_EN_CSEREN		0x80000000

/*
 * Common Event and Error Interrupt Enable Register (CM_EVTER_INTR_EN)
 */
/* Chip select error interrupt enable */
#define IFC_CM_EVTER_INTR_EN_CSERIREN	0x80000000

/*
 * Common Transfer Error Attribute Register-0 (CM_ERATTR0)
 */
/* transaction type of error Read/Write */
#define IFC_CM_ERATTR0_ERTYP_READ	0x80000000
#define IFC_CM_ERATTR0_ERAID		0x0FF00000
#define IFC_CM_ERATTR0_ESRCID		0x0000FF00

/*
 * Clock Control Register (CCR)
 */
#define IFC_CCR_MASK			0x0F0F8800
/* Clock division ratio */
#define IFC_CCR_CLK_DIV_MASK		0x0F000000
#define IFC_CCR_CLK_DIV_SHIFT		24
#define IFC_CCR_CLK_DIV(n)		((n-1) << IFC_CCR_CLK_DIV_SHIFT)
/* IFC Clock Delay */
#define IFC_CCR_CLK_DLY_MASK		0x000F0000
#define IFC_CCR_CLK_DLY_SHIFT		16
#define IFC_CCR_CLK_DLY(n)		((n) << IFC_CCR_CLK_DLY_SHIFT)
/* Invert IFC clock before sending out */
#define IFC_CCR_INV_CLK_EN		0x00008000
/* Fedback IFC Clock */
#define IFC_CCR_FB_IFC_CLK_SEL		0x00000800

/*
 * Clock Status Register (CSR)
 */
/* Clk is stable */
#define IFC_CSR_CLK_STAT_STABLE		0x80000000

/*
 * IFC_NAND Machine Specific Registers
 */
/*
 * NAND Configuration Register (NCFGR)
 */
/* Auto Boot Mode */
#define IFC_NAND_NCFGR_BOOT		0x80000000
/* SRAM INIT EN */
#define IFC_NAND_SRAM_INIT_EN		0x20000000
/* Addressing Mode-ROW0+n/COL0 */
#define IFC_NAND_NCFGR_ADDR_MODE_RC0	0x00000000
/* Addressing Mode-ROW0+n/COL0+n */
#define IFC_NAND_NCFGR_ADDR_MODE_RC1	0x00400000
/* Number of loop iterations of FIR sequences for multi page operations */
#define IFC_NAND_NCFGR_NUM_LOOP_MASK	0x0000F000
#define IFC_NAND_NCFGR_NUM_LOOP_SHIFT	12
#define IFC_NAND_NCFGR_NUM_LOOP(n)	((n) << IFC_NAND_NCFGR_NUM_LOOP_SHIFT)
/* Number of wait cycles */
#define IFC_NAND_NCFGR_NUM_WAIT_MASK	0x000000FF
#define IFC_NAND_NCFGR_NUM_WAIT_SHIFT	0

/*
 * NAND Flash Command Registers (NAND_FCR0/NAND_FCR1)
 */
/* General purpose FCM flash command bytes CMD0-CMD7 */
#define IFC_NAND_FCR0_CMD0		0xFF000000
#define IFC_NAND_FCR0_CMD0_SHIFT	24
#define IFC_NAND_FCR0_CMD1		0x00FF0000
#define IFC_NAND_FCR0_CMD1_SHIFT	16
#define IFC_NAND_FCR0_CMD2		0x0000FF00
#define IFC_NAND_FCR0_CMD2_SHIFT	8
#define IFC_NAND_FCR0_CMD3		0x000000FF
#define IFC_NAND_FCR0_CMD3_SHIFT	0
#define IFC_NAND_FCR1_CMD4		0xFF000000
#define IFC_NAND_FCR1_CMD4_SHIFT	24
#define IFC_NAND_FCR1_CMD5		0x00FF0000
#define IFC_NAND_FCR1_CMD5_SHIFT	16
#define IFC_NAND_FCR1_CMD6		0x0000FF00
#define IFC_NAND_FCR1_CMD6_SHIFT	8
#define IFC_NAND_FCR1_CMD7		0x000000FF
#define IFC_NAND_FCR1_CMD7_SHIFT	0

/*
 * Flash ROW and COL Address Register (ROWn, COLn)
 */
/* Main/spare region locator */
#define IFC_NAND_COL_MS			0x80000000
/* Column Address */
#define IFC_NAND_COL_CA_MASK		0x00000FFF

/*
 * NAND Flash Byte Count Register (NAND_BC)
 */
/* Byte Count for read/Write */
#define IFC_NAND_BC			0x000001FF

/*
 * NAND Flash Instruction Registers (NAND_FIR0/NAND_FIR1/NAND_FIR2)
 */
/* NAND Machine specific opcodes OP0-OP14*/
#define IFC_NAND_FIR0_OP0		0xFC000000
#define IFC_NAND_FIR0_OP0_SHIFT		26
#define IFC_NAND_FIR0_OP1		0x03F00000
#define IFC_NAND_FIR0_OP1_SHIFT		20
#define IFC_NAND_FIR0_OP2		0x000FC000
#define IFC_NAND_FIR0_OP2_SHIFT		14
#define IFC_NAND_FIR0_OP3		0x00003F00
#define IFC_NAND_FIR0_OP3_SHIFT		8
#define IFC_NAND_FIR0_OP4		0x000000FC
#define IFC_NAND_FIR0_OP4_SHIFT		2
#define IFC_NAND_FIR1_OP5		0xFC000000
#define IFC_NAND_FIR1_OP5_SHIFT		26
#define IFC_NAND_FIR1_OP6		0x03F00000
#define IFC_NAND_FIR1_OP6_SHIFT		20
#define IFC_NAND_FIR1_OP7		0x000FC000
#define IFC_NAND_FIR1_OP7_SHIFT		14
#define IFC_NAND_FIR1_OP8		0x00003F00
#define IFC_NAND_FIR1_OP8_SHIFT		8
#define IFC_NAND_FIR1_OP9		0x000000FC
#define IFC_NAND_FIR1_OP9_SHIFT		2
#define IFC_NAND_FIR2_OP10		0xFC000000
#define IFC_NAND_FIR2_OP10_SHIFT	26
#define IFC_NAND_FIR2_OP11		0x03F00000
#define IFC_NAND_FIR2_OP11_SHIFT	20
#define IFC_NAND_FIR2_OP12		0x000FC000
#define IFC_NAND_FIR2_OP12_SHIFT	14
#define IFC_NAND_FIR2_OP13		0x00003F00
#define IFC_NAND_FIR2_OP13_SHIFT	8
#define IFC_NAND_FIR2_OP14		0x000000FC
#define IFC_NAND_FIR2_OP14_SHIFT	2

/*
 * Instruction opcodes to be programmed
 * in FIR registers- 6bits
 */
enum ifc_nand_fir_opcodes {
	IFC_FIR_OP_NOP,
	IFC_FIR_OP_CA0,
	IFC_FIR_OP_CA1,
	IFC_FIR_OP_CA2,
	IFC_FIR_OP_CA3,
	IFC_FIR_OP_RA0,
	IFC_FIR_OP_RA1,
	IFC_FIR_OP_RA2,
	IFC_FIR_OP_RA3,
	IFC_FIR_OP_CMD0,
	IFC_FIR_OP_CMD1,
	IFC_FIR_OP_CMD2,
	IFC_FIR_OP_CMD3,
	IFC_FIR_OP_CMD4,
	IFC_FIR_OP_CMD5,
	IFC_FIR_OP_CMD6,
	IFC_FIR_OP_CMD7,
	IFC_FIR_OP_CW0,
	IFC_FIR_OP_CW1,
	IFC_FIR_OP_CW2,
	IFC_FIR_OP_CW3,
	IFC_FIR_OP_CW4,
	IFC_FIR_OP_CW5,
	IFC_FIR_OP_CW6,
	IFC_FIR_OP_CW7,
	IFC_FIR_OP_WBCD,
	IFC_FIR_OP_RBCD,
	IFC_FIR_OP_BTRD,
	IFC_FIR_OP_RDSTAT,
	IFC_FIR_OP_NWAIT,
	IFC_FIR_OP_WFR,
	IFC_FIR_OP_SBRD,
	IFC_FIR_OP_UA,
	IFC_FIR_OP_RB,
};

/*
 * NAND Chip Select Register (NAND_CSEL)
 */
#define IFC_NAND_CSEL			0x0C000000
#define IFC_NAND_CSEL_SHIFT		26
#define IFC_NAND_CSEL_CS0		0x00000000
#define IFC_NAND_CSEL_CS1		0x04000000
#define IFC_NAND_CSEL_CS2		0x08000000
#define IFC_NAND_CSEL_CS3		0x0C000000

/*
 * NAND Operation Sequence Start (NANDSEQ_STRT)
 */
/* NAND Flash Operation Start */
#define IFC_NAND_SEQ_STRT_FIR_STRT	0x80000000
/* Automatic Erase */
#define IFC_NAND_SEQ_STRT_AUTO_ERS	0x00800000
/* Automatic Program */
#define IFC_NAND_SEQ_STRT_AUTO_PGM	0x00100000
/* Automatic Copyback */
#define IFC_NAND_SEQ_STRT_AUTO_CPB	0x00020000
/* Automatic Read Operation */
#define IFC_NAND_SEQ_STRT_AUTO_RD	0x00004000
/* Automatic Status Read */
#define IFC_NAND_SEQ_STRT_AUTO_STAT_RD	0x00000800

/*
 * NAND Event and Error Status Register (NAND_EVTER_STAT)
 */
/* Operation Complete */
#define IFC_NAND_EVTER_STAT_OPC		0x80000000
/* Flash Timeout Error */
#define IFC_NAND_EVTER_STAT_FTOER	0x08000000
/* Write Protect Error */
#define IFC_NAND_EVTER_STAT_WPER	0x04000000
/* ECC Error */
#define IFC_NAND_EVTER_STAT_ECCER	0x02000000
/* RCW Load Done */
#define IFC_NAND_EVTER_STAT_RCW_DN	0x00008000
/* Boot Loadr Done */
#define IFC_NAND_EVTER_STAT_BOOT_DN	0x00004000
/* Bad Block Indicator search select */
#define IFC_NAND_EVTER_STAT_BBI_SRCH_SE	0x00000800

/*
 * NAND Flash Page Read Completion Event Status Register
 * (PGRDCMPL_EVT_STAT)
 */
#define PGRDCMPL_EVT_STAT_MASK		0xFFFF0000
/* Small Page 0-15 Done */
#define PGRDCMPL_EVT_STAT_SECTION_SP(n)	(1 << (31 - (n)))
/* Large Page(2K) 0-3 Done */
#define PGRDCMPL_EVT_STAT_LP_2K(n)	(0xF << (28 - (n)*4))
/* Large Page(4K) 0-1 Done */
#define PGRDCMPL_EVT_STAT_LP_4K(n)	(0xFF << (24 - (n)*8))

/*
 * NAND Event and Error Enable Register (NAND_EVTER_EN)
 */
/* Operation complete event enable */
#define IFC_NAND_EVTER_EN_OPC_EN	0x80000000
/* Page read complete event enable */
#define IFC_NAND_EVTER_EN_PGRDCMPL_EN	0x20000000
/* Flash Timeout error enable */
#define IFC_NAND_EVTER_EN_FTOER_EN	0x08000000
/* Write Protect error enable */
#define IFC_NAND_EVTER_EN_WPER_EN	0x04000000
/* ECC error logging enable */
#define IFC_NAND_EVTER_EN_ECCER_EN	0x02000000

/*
 * NAND Event and Error Interrupt Enable Register (NAND_EVTER_INTR_EN)
 */
/* Enable interrupt for operation complete */
#define IFC_NAND_EVTER_INTR_OPCIR_EN		0x80000000
/* Enable interrupt for Page read complete */
#define IFC_NAND_EVTER_INTR_PGRDCMPLIR_EN	0x20000000
/* Enable interrupt for Flash timeout error */
#define IFC_NAND_EVTER_INTR_FTOERIR_EN		0x08000000
/* Enable interrupt for Write protect error */
#define IFC_NAND_EVTER_INTR_WPERIR_EN		0x04000000
/* Enable interrupt for ECC error*/
#define IFC_NAND_EVTER_INTR_ECCERIR_EN		0x02000000

/*
 * NAND Transfer Error Attribute Register-0 (NAND_ERATTR0)
 */
#define IFC_NAND_ERATTR0_MASK		0x0C080000
/* Error on CS0-3 for NAND */
#define IFC_NAND_ERATTR0_ERCS_CS0	0x00000000
#define IFC_NAND_ERATTR0_ERCS_CS1	0x04000000
#define IFC_NAND_ERATTR0_ERCS_CS2	0x08000000
#define IFC_NAND_ERATTR0_ERCS_CS3	0x0C000000
/* Transaction type of error Read/Write */
#define IFC_NAND_ERATTR0_ERTTYPE_READ	0x00080000

/*
 * NAND Flash Status Register (NAND_FSR)
 */
/* First byte of data read from read status op */
#define IFC_NAND_NFSR_RS0		0xFF000000
/* Second byte of data read from read status op */
#define IFC_NAND_NFSR_RS1		0x00FF0000

/*
 * ECC Error Status Registers (ECCSTAT0-ECCSTAT3)
 */
/* Number of ECC errors on sector n (n = 0-15) */
#define IFC_NAND_ECCSTAT0_ERRCNT_SECTOR0_MASK	0x0F000000
#define IFC_NAND_ECCSTAT0_ERRCNT_SECTOR0_SHIFT	24
#define IFC_NAND_ECCSTAT0_ERRCNT_SECTOR1_MASK	0x000F0000
#define IFC_NAND_ECCSTAT0_ERRCNT_SECTOR1_SHIFT	16
#define IFC_NAND_ECCSTAT0_ERRCNT_SECTOR2_MASK	0x00000F00
#define IFC_NAND_ECCSTAT0_ERRCNT_SECTOR2_SHIFT	8
#define IFC_NAND_ECCSTAT0_ERRCNT_SECTOR3_MASK	0x0000000F
#define IFC_NAND_ECCSTAT0_ERRCNT_SECTOR3_SHIFT	0
#define IFC_NAND_ECCSTAT1_ERRCNT_SECTOR4_MASK	0x0F000000
#define IFC_NAND_ECCSTAT1_ERRCNT_SECTOR4_SHIFT	24
#define IFC_NAND_ECCSTAT1_ERRCNT_SECTOR5_MASK	0x000F0000
#define IFC_NAND_ECCSTAT1_ERRCNT_SECTOR5_SHIFT	16
#define IFC_NAND_ECCSTAT1_ERRCNT_SECTOR6_MASK	0x00000F00
#define IFC_NAND_ECCSTAT1_ERRCNT_SECTOR6_SHIFT	8
#define IFC_NAND_ECCSTAT1_ERRCNT_SECTOR7_MASK	0x0000000F
#define IFC_NAND_ECCSTAT1_ERRCNT_SECTOR7_SHIFT	0
#define IFC_NAND_ECCSTAT2_ERRCNT_SECTOR8_MASK	0x0F000000
#define IFC_NAND_ECCSTAT2_ERRCNT_SECTOR8_SHIFT	24
#define IFC_NAND_ECCSTAT2_ERRCNT_SECTOR9_MASK	0x000F0000
#define IFC_NAND_ECCSTAT2_ERRCNT_SECTOR9_SHIFT	16
#define IFC_NAND_ECCSTAT2_ERRCNT_SECTOR10_MASK	0x00000F00
#define IFC_NAND_ECCSTAT2_ERRCNT_SECTOR10_SHIFT	8
#define IFC_NAND_ECCSTAT2_ERRCNT_SECTOR11_MASK	0x0000000F
#define IFC_NAND_ECCSTAT2_ERRCNT_SECTOR11_SHIFT	0
#define IFC_NAND_ECCSTAT3_ERRCNT_SECTOR12_MASK	0x0F000000
#define IFC_NAND_ECCSTAT3_ERRCNT_SECTOR12_SHIFT	24
#define IFC_NAND_ECCSTAT3_ERRCNT_SECTOR13_MASK	0x000F0000
#define IFC_NAND_ECCSTAT3_ERRCNT_SECTOR13_SHIFT	16
#define IFC_NAND_ECCSTAT3_ERRCNT_SECTOR14_MASK	0x00000F00
#define IFC_NAND_ECCSTAT3_ERRCNT_SECTOR14_SHIFT	8
#define IFC_NAND_ECCSTAT3_ERRCNT_SECTOR15_MASK	0x0000000F
#define IFC_NAND_ECCSTAT3_ERRCNT_SECTOR15_SHIFT	0

/*
 * NAND Control Register (NANDCR)
 */
#define IFC_NAND_NCR_FTOCNT_MASK	0x1E000000
#define IFC_NAND_NCR_FTOCNT_SHIFT	25
#define IFC_NAND_NCR_FTOCNT(n)	((LOG2(n) - 8)  << IFC_NAND_NCR_FTOCNT_SHIFT)

/*
 * NAND_AUTOBOOT_TRGR
 */
/* Trigger RCW load */
#define IFC_NAND_AUTOBOOT_TRGR_RCW_LD	0x80000000
/* Trigget Auto Boot */
#define IFC_NAND_AUTOBOOT_TRGR_BOOT_LD	0x20000000

/*
 * NAND_MDR
 */
/* 1st read data byte when opcode SBRD */
#define IFC_NAND_MDR_RDATA0		0xFF000000
/* 2nd read data byte when opcode SBRD */
#define IFC_NAND_MDR_RDATA1		0x00FF0000

/*
 * NOR Machine Specific Registers
 */
/*
 * NOR Event and Error Status Register (NOR_EVTER_STAT)
 */
/* NOR Command Sequence Operation Complete */
#define IFC_NOR_EVTER_STAT_OPC_NOR	0x80000000
/* Write Protect Error */
#define IFC_NOR_EVTER_STAT_WPER		0x04000000
/* Command Sequence Timeout Error */
#define IFC_NOR_EVTER_STAT_STOER	0x01000000

/*
 * NOR Event and Error Enable Register (NOR_EVTER_EN)
 */
/* NOR Command Seq complete event enable */
#define IFC_NOR_EVTER_EN_OPCEN_NOR	0x80000000
/* Write Protect Error Checking Enable */
#define IFC_NOR_EVTER_EN_WPEREN		0x04000000
/* Timeout Error Enable */
#define IFC_NOR_EVTER_EN_STOEREN	0x01000000

/*
 * NOR Event and Error Interrupt Enable Register (NOR_EVTER_INTR_EN)
 */
/* Enable interrupt for OPC complete */
#define IFC_NOR_EVTER_INTR_OPCEN_NOR	0x80000000
/* Enable interrupt for write protect error */
#define IFC_NOR_EVTER_INTR_WPEREN	0x04000000
/* Enable interrupt for timeout error */
#define IFC_NOR_EVTER_INTR_STOEREN	0x01000000

/*
 * NOR Transfer Error Attribute Register-0 (NOR_ERATTR0)
 */
/* Source ID for error transaction */
#define IFC_NOR_ERATTR0_ERSRCID		0xFF000000
/* AXI ID for error transation */
#define IFC_NOR_ERATTR0_ERAID		0x000FF000
/* Chip select corresponds to NOR error */
#define IFC_NOR_ERATTR0_ERCS_CS0	0x00000000
#define IFC_NOR_ERATTR0_ERCS_CS1	0x00000010
#define IFC_NOR_ERATTR0_ERCS_CS2	0x00000020
#define IFC_NOR_ERATTR0_ERCS_CS3	0x00000030
/* Type of transaction read/write */
#define IFC_NOR_ERATTR0_ERTYPE_READ	0x00000001

/*
 * NOR Transfer Error Attribute Register-2 (NOR_ERATTR2)
 */
#define IFC_NOR_ERATTR2_ER_NUM_PHASE_EXP	0x000F0000
#define IFC_NOR_ERATTR2_ER_NUM_PHASE_PER	0x00000F00

/*
 * NOR Control Register (NORCR)
 */
#define IFC_NORCR_MASK			0x0F0F0000
/* No. of Address/Data Phase */
#define IFC_NORCR_NUM_PHASE_MASK	0x0F000000
#define IFC_NORCR_NUM_PHASE_SHIFT	24
#define IFC_NORCR_NUM_PHASE(n)	((n-1) << IFC_NORCR_NUM_PHASE_SHIFT)
/* Sequence Timeout Count */
#define IFC_NORCR_STOCNT_MASK		0x000F0000
#define IFC_NORCR_STOCNT_SHIFT		16
#define IFC_NORCR_STOCNT(n)	((LOG2(n) - 8) << IFC_NORCR_STOCNT_SHIFT)

/*
 * GPCM Machine specific registers
 */
/*
 * GPCM Event and Error Status Register (GPCM_EVTER_STAT)
 */
/* Timeout error */
#define IFC_GPCM_EVTER_STAT_TOER	0x04000000
/* Parity error */
#define IFC_GPCM_EVTER_STAT_PER		0x01000000

/*
 * GPCM Event and Error Enable Register (GPCM_EVTER_EN)
 */
/* Timeout error enable */
#define IFC_GPCM_EVTER_EN_TOER_EN	0x04000000
/* Parity error enable */
#define IFC_GPCM_EVTER_EN_PER_EN	0x01000000

/*
 * GPCM Event and Error Interrupt Enable Register (GPCM_EVTER_INTR_EN)
 */
/* Enable Interrupt for timeout error */
#define IFC_GPCM_EEIER_TOERIR_EN	0x04000000
/* Enable Interrupt for Parity error */
#define IFC_GPCM_EEIER_PERIR_EN		0x01000000

/*
 * GPCM Transfer Error Attribute Register-0 (GPCM_ERATTR0)
 */
/* Source ID for error transaction */
#define IFC_GPCM_ERATTR0_ERSRCID	0xFF000000
/* AXI ID for error transaction */
#define IFC_GPCM_ERATTR0_ERAID		0x000FF000
/* Chip select corresponds to GPCM error */
#define IFC_GPCM_ERATTR0_ERCS_CS0	0x00000000
#define IFC_GPCM_ERATTR0_ERCS_CS1	0x00000040
#define IFC_GPCM_ERATTR0_ERCS_CS2	0x00000080
#define IFC_GPCM_ERATTR0_ERCS_CS3	0x000000C0
/* Type of transaction read/Write */
#define IFC_GPCM_ERATTR0_ERTYPE_READ	0x00000001

/*
 * GPCM Transfer Error Attribute Register-2 (GPCM_ERATTR2)
 */
/* On which beat of address/data parity error is observed */
#define IFC_GPCM_ERATTR2_PERR_BEAT		0x00000C00
/* Parity Error on byte */
#define IFC_GPCM_ERATTR2_PERR_BYTE		0x000000F0
/* Parity Error reported in addr or data phase */
#define IFC_GPCM_ERATTR2_PERR_DATA_PHASE	0x00000001

/*
 * GPCM Status Register (GPCM_STAT)
 */
#define IFC_GPCM_STAT_BSY		0x80000000  /* GPCM is busy */

#ifndef __ASSEMBLY__
#include <asm/io.h>

extern void print_ifc_regs(void);
extern void init_early_memctl_regs(void);
void init_final_memctl_regs(void);

#define IFC_RREGS_4KOFFSET	(4*1024)
#define IFC_RREGS_64KOFFSET	(64*1024)

#define IFC_FCM_BASE_ADDR \
	((struct fsl_ifc_fcm *)CFG_SYS_IFC_ADDR)

#define get_ifc_cspr_ext(i)	\
		ifc_in32(&(IFC_FCM_BASE_ADDR)->cspr_cs[i].cspr_ext)
#define get_ifc_cspr(i)		\
		ifc_in32(&(IFC_FCM_BASE_ADDR)->cspr_cs[i].cspr)
#define get_ifc_csor_ext(i)	\
		ifc_in32(&(IFC_FCM_BASE_ADDR)->csor_cs[i].csor_ext)
#define get_ifc_csor(i)		\
		ifc_in32(&(IFC_FCM_BASE_ADDR)->csor_cs[i].csor)
#define get_ifc_amask(i)	\
		ifc_in32(&(IFC_FCM_BASE_ADDR)->amask_cs[i].amask)
#define get_ifc_ftim(i, j)	\
		ifc_in32(&(IFC_FCM_BASE_ADDR)->ftim_cs[i].ftim[j])
#define set_ifc_cspr_ext(i, v)	\
		ifc_out32(&(IFC_FCM_BASE_ADDR)->cspr_cs[i].cspr_ext, v)
#define set_ifc_cspr(i, v)	\
		ifc_out32(&(IFC_FCM_BASE_ADDR)->cspr_cs[i].cspr, v)
#define set_ifc_csor_ext(i, v)	\
		ifc_out32(&(IFC_FCM_BASE_ADDR)->csor_cs[i].csor_ext, v)
#define set_ifc_csor(i, v)	\
		ifc_out32(&(IFC_FCM_BASE_ADDR)->csor_cs[i].csor, v)
#define set_ifc_amask(i, v)	\
		ifc_out32(&(IFC_FCM_BASE_ADDR)->amask_cs[i].amask, v)
#define set_ifc_ftim(i, j, v)	\
		ifc_out32(&(IFC_FCM_BASE_ADDR)->ftim_cs[i].ftim[j], v)

enum ifc_chip_sel {
	IFC_CS0,
	IFC_CS1,
	IFC_CS2,
	IFC_CS3,
	IFC_CS4,
	IFC_CS5,
	IFC_CS6,
	IFC_CS7,
};

enum ifc_ftims {
	IFC_FTIM0,
	IFC_FTIM1,
	IFC_FTIM2,
	IFC_FTIM3,
};

/*
 * IFC Controller NAND Machine registers
 */
struct fsl_ifc_nand {
	u32 ncfgr;
	u32 res1[0x4];
	u32 nand_fcr0;
	u32 nand_fcr1;
	u32 res2[0x8];
	u32 row0;
	u32 res3;
	u32 col0;
	u32 res4;
	u32 row1;
	u32 res5;
	u32 col1;
	u32 res6;
	u32 row2;
	u32 res7;
	u32 col2;
	u32 res8;
	u32 row3;
	u32 res9;
	u32 col3;
	u32 res10[0x24];
	u32 nand_fbcr;
	u32 res11;
	u32 nand_fir0;
	u32 nand_fir1;
	u32 nand_fir2;
	u32 res12[0x10];
	u32 nand_csel;
	u32 res13;
	u32 nandseq_strt;
	u32 res14;
	u32 nand_evter_stat;
	u32 res15;
	u32 pgrdcmpl_evt_stat;
	u32 res16[0x2];
	u32 nand_evter_en;
	u32 res17[0x2];
	u32 nand_evter_intr_en;
	u32 nand_vol_addr_stat;
	u32 res18;
	u32 nand_erattr0;
	u32 nand_erattr1;
	u32 res19[0x10];
	u32 nand_fsr;
	u32 res20[0x1];
	u32 nand_eccstat[8];
	u32 res21[0x1c];
	u32 nanndcr;
	u32 res22[0x2];
	u32 nand_autoboot_trgr;
	u32 res23;
	u32 nand_mdr;
	u32 res24[0x1c];
	u32 nand_dll_lowcfg0;
	u32 nand_dll_lowcfg1;
	u32 res25;
	u32 nand_dll_lowstat;
	u32 res26[0x3C];
};

/*
 * IFC controller NOR Machine registers
 */
struct fsl_ifc_nor {
	u32 nor_evter_stat;
	u32 res1[0x2];
	u32 nor_evter_en;
	u32 res2[0x2];
	u32 nor_evter_intr_en;
	u32 res3[0x2];
	u32 nor_erattr0;
	u32 nor_erattr1;
	u32 nor_erattr2;
	u32 res4[0x4];
	u32 norcr;
	u32 res5[0xEF];
};

/*
 * IFC controller GPCM Machine registers
 */
struct fsl_ifc_gpcm {
	u32 gpcm_evter_stat;
	u32 res1[0x2];
	u32 gpcm_evter_en;
	u32 res2[0x2];
	u32 gpcm_evter_intr_en;
	u32 res3[0x2];
	u32 gpcm_erattr0;
	u32 gpcm_erattr1;
	u32 gpcm_erattr2;
	u32 gpcm_stat;
};

#ifdef CONFIG_SYS_FSL_IFC_BANK_COUNT
#if (CONFIG_SYS_FSL_IFC_BANK_COUNT <= 8)
#define IFC_CSPR_REG_LEN	148
#define IFC_AMASK_REG_LEN	144
#define IFC_CSOR_REG_LEN	144
#define IFC_FTIM_REG_LEN	576

#define IFC_CSPR_USED_LEN	sizeof(struct fsl_ifc_cspr) * \
					CONFIG_SYS_FSL_IFC_BANK_COUNT
#define IFC_AMASK_USED_LEN	sizeof(struct fsl_ifc_amask) * \
					CONFIG_SYS_FSL_IFC_BANK_COUNT
#define IFC_CSOR_USED_LEN	sizeof(struct fsl_ifc_csor) * \
					CONFIG_SYS_FSL_IFC_BANK_COUNT
#define IFC_FTIM_USED_LEN	sizeof(struct fsl_ifc_ftim) * \
					CONFIG_SYS_FSL_IFC_BANK_COUNT
#else
#error IFC BANK count not vaild
#endif
#else
#error IFC BANK count not defined
#endif

struct fsl_ifc_cspr {
	u32 cspr_ext;
	u32 cspr;
	u32 res;
};

struct fsl_ifc_amask {
	u32 amask;
	u32 res[0x2];
};

struct fsl_ifc_csor {
	u32 csor;
	u32 csor_ext;
	u32 res;
};

struct fsl_ifc_ftim {
	u32 ftim[4];
	u32 res[0x8];
};

/*
 * IFC Controller Global Registers
 * FCM - Flash control machine
 */

struct fsl_ifc_fcm {
	u32 ifc_rev;
	u32 res1[0x2];
	struct fsl_ifc_cspr cspr_cs[CONFIG_SYS_FSL_IFC_BANK_COUNT];
	u8 res2[IFC_CSPR_REG_LEN - IFC_CSPR_USED_LEN];
	struct fsl_ifc_amask amask_cs[CONFIG_SYS_FSL_IFC_BANK_COUNT];
	u8 res3[IFC_AMASK_REG_LEN - IFC_AMASK_USED_LEN];
	struct fsl_ifc_csor csor_cs[CONFIG_SYS_FSL_IFC_BANK_COUNT];
	u8 res4[IFC_CSOR_REG_LEN - IFC_CSOR_USED_LEN];
	struct fsl_ifc_ftim ftim_cs[CONFIG_SYS_FSL_IFC_BANK_COUNT];
	u8 res5[IFC_FTIM_REG_LEN - IFC_FTIM_USED_LEN];
	u32 rb_stat;
	u32 rb_map;
	u32 wp_map;
	u32 ifc_gcr;
	u32 res7[0x2];
	u32 cm_evter_stat;
	u32 res8[0x2];
	u32 cm_evter_en;
	u32 res9[0x2];
	u32 cm_evter_intr_en;
	u32 res10[0x2];
	u32 cm_erattr0;
	u32 cm_erattr1;
	u32 res11[0x2];
	u32 ifc_ccr;
	u32 ifc_csr;
	u32 ddr_ccr_low;
};

struct fsl_ifc_runtime {
	struct fsl_ifc_nand ifc_nand;
	struct fsl_ifc_nor ifc_nor;
	struct fsl_ifc_gpcm ifc_gpcm;
};

struct fsl_ifc {
	struct fsl_ifc_fcm *gregs;
	struct fsl_ifc_runtime *rregs;
};

struct ifc_regs {
	const char *name;
	u32 pr;
	u32 pr_ext;
	u32 amask;
	u32 or;
	u32 ftim[4];
	u32 or_ext;
	u32 pr_final;
	u32 amask_final;
};

struct ifc_regs_info {
	struct ifc_regs *regs;
	u32 cs_size;
};

#ifdef CONFIG_SYS_FSL_ERRATUM_IFC_A002769
#undef CSPR_MSEL_NOR
#define CSPR_MSEL_NOR	CSPR_MSEL_GPCM
#endif
#endif /* CONFIG_FSL_IFC */

#endif /* __ASSEMBLY__ */
#endif /* __FSL_IFC_H */
