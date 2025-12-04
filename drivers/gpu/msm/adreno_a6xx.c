// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2017-2021, The Linux Foundation. All rights reserved.
 */

#include <linux/firmware.h>
#include <linux/of.h>
#include <linux/of_fdt.h>
#include <soc/qcom/subsystem_restart.h>
#include <linux/clk/qcom.h>

#include "adreno.h"
#include "adreno_a6xx.h"
#include "adreno_llc.h"
#include "adreno_pm4types.h"
#include "adreno_trace.h"
#include "kgsl_trace.h"

#ifdef _A6XX_REG_H
#undef _A6XX_REG_H
#endif
#ifndef _A6XX_REG_H
#define _A6XX_REG_H

/* A6XX interrupt bits */
#define A6XX_INT_RBBM_GPU_IDLE          0
#define A6XX_INT_CP_AHB_ERROR           1
#define A6XX_INT_ATB_ASYNCFIFO_OVERFLOW 6
#define A6XX_INT_RBBM_GPC_ERROR         7
#define A6XX_INT_CP_SW                  8
#define A6XX_INT_CP_HW_ERROR            9
#define A6XX_INT_CP_CCU_FLUSH_DEPTH_TS  10
#define A6XX_INT_CP_CCU_FLUSH_COLOR_TS  11
#define A6XX_INT_CP_CCU_RESOLVE_TS      12
#define A6XX_INT_CP_IB2                 13
#define A6XX_INT_CP_IB1                 14
#define A6XX_INT_CP_RB                  15
#define A6XX_INT_CP_RB_DONE_TS          17
#define A6XX_INT_CP_WT_DONE_TS          18
#define A6XX_INT_CP_CACHE_FLUSH_TS      20
#define A6XX_INT_RBBM_ATB_BUS_OVERFLOW  22
#define A6XX_INT_RBBM_HANG_DETECT       23
#define A6XX_INT_UCHE_OOB_ACCESS        24
#define A6XX_INT_UCHE_TRAP_INTR         25
#define A6XX_INT_DEBBUS_INTR_0          26
#define A6XX_INT_DEBBUS_INTR_1          27
#define A6XX_INT_TSB_WRITE_ERROR	28
#define A6XX_INT_ISDB_CPU_IRQ           30
#define A6XX_INT_ISDB_UNDER_DEBUG       31

/* CP Interrupt bits */
#define A6XX_CP_OPCODE_ERROR                    0
#define A6XX_CP_UCODE_ERROR                     1
#define A6XX_CP_HW_FAULT_ERROR                  2
#define A6XX_CP_REGISTER_PROTECTION_ERROR       4
#define A6XX_CP_AHB_ERROR                       5
#define A6XX_CP_VSD_PARITY_ERROR                6
#define A6XX_CP_ILLEGAL_INSTR_ERROR             7

/* CP registers */
#define A6XX_CP_RB_BASE                  0x800
#define A6XX_CP_RB_BASE_HI               0x801
#define A6XX_CP_RB_CNTL                  0x802
#define A6XX_CP_RB_RPTR_ADDR_LO          0x804
#define A6XX_CP_RB_RPTR_ADDR_HI          0x805
#define A6XX_CP_RB_RPTR                  0x806
#define A6XX_CP_RB_WPTR                  0x807
#define A6XX_CP_SQE_CNTL                 0x808
#define A6XX_CP_CP2GMU_STATUS            0x812
#define A6XX_CP_HW_FAULT                 0x821
#define A6XX_CP_INTERRUPT_STATUS         0x823
#define A6XX_CP_PROTECT_STATUS           0x824
#define A6XX_CP_STATUS_1                 0x825
#define A6XX_CP_SQE_INSTR_BASE_LO        0x830
#define A6XX_CP_SQE_INSTR_BASE_HI        0x831
#define A6XX_CP_MISC_CNTL                0x840
#define A6XX_CP_APRIV_CNTL               0X844
#define A6XX_CP_ROQ_THRESHOLDS_1         0x8C1
#define A6XX_CP_ROQ_THRESHOLDS_2         0x8C2
#define A6XX_CP_MEM_POOL_SIZE            0x8C3
#define A6XX_CP_CHICKEN_DBG              0x841
#define A6XX_CP_ADDR_MODE_CNTL           0x842
#define A6XX_CP_DBG_ECO_CNTL             0x843
#define A6XX_CP_PROTECT_CNTL             0x84F
#define A6XX_CP_PROTECT_REG              0x850
#define A6XX_CP_CONTEXT_SWITCH_CNTL      0x8A0
#define A6XX_CP_CONTEXT_SWITCH_SMMU_INFO_LO   0x8A1
#define A6XX_CP_CONTEXT_SWITCH_SMMU_INFO_HI   0x8A2
#define A6XX_CP_CONTEXT_SWITCH_PRIV_NON_SECURE_RESTORE_ADDR_LO   0x8A3
#define A6XX_CP_CONTEXT_SWITCH_PRIV_NON_SECURE_RESTORE_ADDR_HI   0x8A4
#define A6XX_CP_CONTEXT_SWITCH_PRIV_SECURE_RESTORE_ADDR_LO   0x8A5
#define A6XX_CP_CONTEXT_SWITCH_PRIV_SECURE_RESTORE_ADDR_HI   0x8A6
#define A6XX_CP_CONTEXT_SWITCH_NON_PRIV_RESTORE_ADDR_LO   0x8A7
#define A6XX_CP_CONTEXT_SWITCH_NON_PRIV_RESTORE_ADDR_HI   0x8A8
#define A6XX_CP_CONTEXT_SWITCH_LEVEL_STATUS 0x8AB
#define A6XX_CP_PERFCTR_CP_SEL_0         0x8D0
#define A6XX_CP_PERFCTR_CP_SEL_1         0x8D1
#define A6XX_CP_PERFCTR_CP_SEL_2         0x8D2
#define A6XX_CP_PERFCTR_CP_SEL_3         0x8D3
#define A6XX_CP_PERFCTR_CP_SEL_4         0x8D4
#define A6XX_CP_PERFCTR_CP_SEL_5         0x8D5
#define A6XX_CP_PERFCTR_CP_SEL_6         0x8D6
#define A6XX_CP_PERFCTR_CP_SEL_7         0x8D7
#define A6XX_CP_PERFCTR_CP_SEL_8         0x8D8
#define A6XX_CP_PERFCTR_CP_SEL_9         0x8D9
#define A6XX_CP_PERFCTR_CP_SEL_10        0x8DA
#define A6XX_CP_PERFCTR_CP_SEL_11        0x8DB
#define A6XX_CP_PERFCTR_CP_SEL_12        0x8DC
#define A6XX_CP_PERFCTR_CP_SEL_13        0x8DD
#define A6XX_CP_CRASH_SCRIPT_BASE_LO     0x900
#define A6XX_CP_CRASH_SCRIPT_BASE_HI     0x901
#define A6XX_CP_CRASH_DUMP_CNTL          0x902
#define A6XX_CP_CRASH_DUMP_STATUS        0x903
#define A6XX_CP_SQE_STAT_ADDR            0x908
#define A6XX_CP_SQE_STAT_DATA            0x909
#define A6XX_CP_DRAW_STATE_ADDR          0x90A
#define A6XX_CP_DRAW_STATE_DATA          0x90B
#define A6XX_CP_ROQ_DBG_ADDR             0x90C
#define A6XX_CP_ROQ_DBG_DATA             0x90D
#define A6XX_CP_MEM_POOL_DBG_ADDR        0x90E
#define A6XX_CP_MEM_POOL_DBG_DATA        0x90F
#define A6XX_CP_SQE_UCODE_DBG_ADDR       0x910
#define A6XX_CP_SQE_UCODE_DBG_DATA       0x911
#define A6XX_CP_IB1_BASE                 0x928
#define A6XX_CP_IB1_BASE_HI              0x929
#define A6XX_CP_IB1_REM_SIZE             0x92A
#define A6XX_CP_IB2_BASE                 0x92B
#define A6XX_CP_IB2_BASE_HI              0x92C
#define A6XX_CP_IB2_REM_SIZE             0x92D
#define A6XX_CP_ALWAYS_ON_COUNTER_LO     0x980
#define A6XX_CP_ALWAYS_ON_COUNTER_HI     0x981
#define A6XX_CP_AHB_CNTL                 0x98D
#define A6XX_CP_APERTURE_CNTL_HOST       0xA00
#define A6XX_CP_APERTURE_CNTL_CD         0xA03
#define A6XX_VSC_ADDR_MODE_CNTL          0xC01

/* RBBM registers */
#define A6XX_RBBM_INT_0_STATUS                   0x201
#define A6XX_RBBM_STATUS                         0x210
#define A6XX_RBBM_STATUS3                        0x213
#define A6XX_RBBM_VBIF_GX_RESET_STATUS           0x215
#define A6XX_RBBM_PERFCTR_CP_0_LO                0x400
#define A6XX_RBBM_PERFCTR_CP_0_HI                0x401
#define A6XX_RBBM_PERFCTR_CP_1_LO                0x402
#define A6XX_RBBM_PERFCTR_CP_1_HI                0x403
#define A6XX_RBBM_PERFCTR_CP_2_LO                0x404
#define A6XX_RBBM_PERFCTR_CP_2_HI                0x405
#define A6XX_RBBM_PERFCTR_CP_3_LO                0x406
#define A6XX_RBBM_PERFCTR_CP_3_HI                0x407
#define A6XX_RBBM_PERFCTR_CP_4_LO                0x408
#define A6XX_RBBM_PERFCTR_CP_4_HI                0x409
#define A6XX_RBBM_PERFCTR_CP_5_LO                0x40a
#define A6XX_RBBM_PERFCTR_CP_5_HI                0x40b
#define A6XX_RBBM_PERFCTR_CP_6_LO                0x40c
#define A6XX_RBBM_PERFCTR_CP_6_HI                0x40d
#define A6XX_RBBM_PERFCTR_CP_7_LO                0x40e
#define A6XX_RBBM_PERFCTR_CP_7_HI                0x40f
#define A6XX_RBBM_PERFCTR_CP_8_LO                0x410
#define A6XX_RBBM_PERFCTR_CP_8_HI                0x411
#define A6XX_RBBM_PERFCTR_CP_9_LO                0x412
#define A6XX_RBBM_PERFCTR_CP_9_HI                0x413
#define A6XX_RBBM_PERFCTR_CP_10_LO               0x414
#define A6XX_RBBM_PERFCTR_CP_10_HI               0x415
#define A6XX_RBBM_PERFCTR_CP_11_LO               0x416
#define A6XX_RBBM_PERFCTR_CP_11_HI               0x417
#define A6XX_RBBM_PERFCTR_CP_12_LO               0x418
#define A6XX_RBBM_PERFCTR_CP_12_HI               0x419
#define A6XX_RBBM_PERFCTR_CP_13_LO               0x41a
#define A6XX_RBBM_PERFCTR_CP_13_HI               0x41b
#define A6XX_RBBM_PERFCTR_RBBM_0_LO              0x41c
#define A6XX_RBBM_PERFCTR_RBBM_0_HI              0x41d
#define A6XX_RBBM_PERFCTR_RBBM_1_LO              0x41e
#define A6XX_RBBM_PERFCTR_RBBM_1_HI              0x41f
#define A6XX_RBBM_PERFCTR_RBBM_2_LO              0x420
#define A6XX_RBBM_PERFCTR_RBBM_2_HI              0x421
#define A6XX_RBBM_PERFCTR_RBBM_3_LO              0x422
#define A6XX_RBBM_PERFCTR_RBBM_3_HI              0x423
#define A6XX_RBBM_PERFCTR_PC_0_LO                0x424
#define A6XX_RBBM_PERFCTR_PC_0_HI                0x425
#define A6XX_RBBM_PERFCTR_PC_1_LO                0x426
#define A6XX_RBBM_PERFCTR_PC_1_HI                0x427
#define A6XX_RBBM_PERFCTR_PC_2_LO                0x428
#define A6XX_RBBM_PERFCTR_PC_2_HI                0x429
#define A6XX_RBBM_PERFCTR_PC_3_LO                0x42a
#define A6XX_RBBM_PERFCTR_PC_3_HI                0x42b
#define A6XX_RBBM_PERFCTR_PC_4_LO                0x42c
#define A6XX_RBBM_PERFCTR_PC_4_HI                0x42d
#define A6XX_RBBM_PERFCTR_PC_5_LO                0x42e
#define A6XX_RBBM_PERFCTR_PC_5_HI                0x42f
#define A6XX_RBBM_PERFCTR_PC_6_LO                0x430
#define A6XX_RBBM_PERFCTR_PC_6_HI                0x431
#define A6XX_RBBM_PERFCTR_PC_7_LO                0x432
#define A6XX_RBBM_PERFCTR_PC_7_HI                0x433
#define A6XX_RBBM_PERFCTR_VFD_0_LO               0x434
#define A6XX_RBBM_PERFCTR_VFD_0_HI               0x435
#define A6XX_RBBM_PERFCTR_VFD_1_LO               0x436
#define A6XX_RBBM_PERFCTR_VFD_1_HI               0x437
#define A6XX_RBBM_PERFCTR_VFD_2_LO               0x438
#define A6XX_RBBM_PERFCTR_VFD_2_HI               0x439
#define A6XX_RBBM_PERFCTR_VFD_3_LO               0x43a
#define A6XX_RBBM_PERFCTR_VFD_3_HI               0x43b
#define A6XX_RBBM_PERFCTR_VFD_4_LO               0x43c
#define A6XX_RBBM_PERFCTR_VFD_4_HI               0x43d
#define A6XX_RBBM_PERFCTR_VFD_5_LO               0x43e
#define A6XX_RBBM_PERFCTR_VFD_5_HI               0x43f
#define A6XX_RBBM_PERFCTR_VFD_6_LO               0x440
#define A6XX_RBBM_PERFCTR_VFD_6_HI               0x441
#define A6XX_RBBM_PERFCTR_VFD_7_LO               0x442
#define A6XX_RBBM_PERFCTR_VFD_7_HI               0x443
#define A6XX_RBBM_PERFCTR_HLSQ_0_LO              0x444
#define A6XX_RBBM_PERFCTR_HLSQ_0_HI              0x445
#define A6XX_RBBM_PERFCTR_HLSQ_1_LO              0x446
#define A6XX_RBBM_PERFCTR_HLSQ_1_HI              0x447
#define A6XX_RBBM_PERFCTR_HLSQ_2_LO              0x448
#define A6XX_RBBM_PERFCTR_HLSQ_2_HI              0x449
#define A6XX_RBBM_PERFCTR_HLSQ_3_LO              0x44a
#define A6XX_RBBM_PERFCTR_HLSQ_3_HI              0x44b
#define A6XX_RBBM_PERFCTR_HLSQ_4_LO              0x44c
#define A6XX_RBBM_PERFCTR_HLSQ_4_HI              0x44d
#define A6XX_RBBM_PERFCTR_HLSQ_5_LO              0x44e
#define A6XX_RBBM_PERFCTR_HLSQ_5_HI              0x44f
#define A6XX_RBBM_PERFCTR_VPC_0_LO               0x450
#define A6XX_RBBM_PERFCTR_VPC_0_HI               0x451
#define A6XX_RBBM_PERFCTR_VPC_1_LO               0x452
#define A6XX_RBBM_PERFCTR_VPC_1_HI               0x453
#define A6XX_RBBM_PERFCTR_VPC_2_LO               0x454
#define A6XX_RBBM_PERFCTR_VPC_2_HI               0x455
#define A6XX_RBBM_PERFCTR_VPC_3_LO               0x456
#define A6XX_RBBM_PERFCTR_VPC_3_HI               0x457
#define A6XX_RBBM_PERFCTR_VPC_4_LO               0x458
#define A6XX_RBBM_PERFCTR_VPC_4_HI               0x459
#define A6XX_RBBM_PERFCTR_VPC_5_LO               0x45a
#define A6XX_RBBM_PERFCTR_VPC_5_HI               0x45b
#define A6XX_RBBM_PERFCTR_CCU_0_LO               0x45c
#define A6XX_RBBM_PERFCTR_CCU_0_HI               0x45d
#define A6XX_RBBM_PERFCTR_CCU_1_LO               0x45e
#define A6XX_RBBM_PERFCTR_CCU_1_HI               0x45f
#define A6XX_RBBM_PERFCTR_CCU_2_LO               0x460
#define A6XX_RBBM_PERFCTR_CCU_2_HI               0x461
#define A6XX_RBBM_PERFCTR_CCU_3_LO               0x462
#define A6XX_RBBM_PERFCTR_CCU_3_HI               0x463
#define A6XX_RBBM_PERFCTR_CCU_4_LO               0x464
#define A6XX_RBBM_PERFCTR_CCU_4_HI               0x465
#define A6XX_RBBM_PERFCTR_TSE_0_LO               0x466
#define A6XX_RBBM_PERFCTR_TSE_0_HI               0x467
#define A6XX_RBBM_PERFCTR_TSE_1_LO               0x468
#define A6XX_RBBM_PERFCTR_TSE_1_HI               0x469
#define A6XX_RBBM_PERFCTR_TSE_2_LO               0x46a
#define A6XX_RBBM_PERFCTR_CCU_4_HI               0x465
#define A6XX_RBBM_PERFCTR_TSE_0_LO               0x466
#define A6XX_RBBM_PERFCTR_TSE_0_HI               0x467
#define A6XX_RBBM_PERFCTR_TSE_1_LO               0x468
#define A6XX_RBBM_PERFCTR_TSE_1_HI               0x469
#define A6XX_RBBM_PERFCTR_TSE_2_LO               0x46a
#define A6XX_RBBM_PERFCTR_TSE_2_HI               0x46b
#define A6XX_RBBM_PERFCTR_TSE_3_LO               0x46c
#define A6XX_RBBM_PERFCTR_TSE_3_HI               0x46d
#define A6XX_RBBM_PERFCTR_RAS_0_LO               0x46e
#define A6XX_RBBM_PERFCTR_RAS_0_HI               0x46f
#define A6XX_RBBM_PERFCTR_RAS_1_LO               0x470
#define A6XX_RBBM_PERFCTR_RAS_1_HI               0x471
#define A6XX_RBBM_PERFCTR_RAS_2_LO               0x472
#define A6XX_RBBM_PERFCTR_RAS_2_HI               0x473
#define A6XX_RBBM_PERFCTR_RAS_3_LO               0x474
#define A6XX_RBBM_PERFCTR_RAS_3_HI               0x475
#define A6XX_RBBM_PERFCTR_UCHE_0_LO              0x476
#define A6XX_RBBM_PERFCTR_UCHE_0_HI              0x477
#define A6XX_RBBM_PERFCTR_UCHE_1_LO              0x478
#define A6XX_RBBM_PERFCTR_UCHE_1_HI              0x479
#define A6XX_RBBM_PERFCTR_UCHE_2_LO              0x47a
#define A6XX_RBBM_PERFCTR_UCHE_2_HI              0x47b
#define A6XX_RBBM_PERFCTR_UCHE_3_LO              0x47c
#define A6XX_RBBM_PERFCTR_UCHE_3_HI              0x47d
#define A6XX_RBBM_PERFCTR_UCHE_4_LO              0x47e
#define A6XX_RBBM_PERFCTR_UCHE_4_HI              0x47f
#define A6XX_RBBM_PERFCTR_UCHE_5_LO              0x480
#define A6XX_RBBM_PERFCTR_UCHE_5_HI              0x481
#define A6XX_RBBM_PERFCTR_UCHE_6_LO              0x482
#define A6XX_RBBM_PERFCTR_UCHE_6_HI              0x483
#define A6XX_RBBM_PERFCTR_UCHE_7_LO              0x484
#define A6XX_RBBM_PERFCTR_UCHE_7_HI              0x485
#define A6XX_RBBM_PERFCTR_UCHE_8_LO              0x486
#define A6XX_RBBM_PERFCTR_UCHE_8_HI              0x487
#define A6XX_RBBM_PERFCTR_UCHE_9_LO              0x488
#define A6XX_RBBM_PERFCTR_UCHE_9_HI              0x489
#define A6XX_RBBM_PERFCTR_UCHE_10_LO             0x48a
#define A6XX_RBBM_PERFCTR_UCHE_10_HI             0x48b
#define A6XX_RBBM_PERFCTR_UCHE_11_LO             0x48c
#define A6XX_RBBM_PERFCTR_UCHE_11_HI             0x48d
#define A6XX_RBBM_PERFCTR_TP_0_LO                0x48e
#define A6XX_RBBM_PERFCTR_TP_0_HI                0x48f
#define A6XX_RBBM_PERFCTR_TP_1_LO                0x490
#define A6XX_RBBM_PERFCTR_TP_1_HI                0x491
#define A6XX_RBBM_PERFCTR_TP_2_LO                0x492
#define A6XX_RBBM_PERFCTR_TP_2_HI                0x493
#define A6XX_RBBM_PERFCTR_TP_3_LO                0x494
#define A6XX_RBBM_PERFCTR_TP_3_HI                0x495
#define A6XX_RBBM_PERFCTR_TP_4_LO                0x496
#define A6XX_RBBM_PERFCTR_TP_4_HI                0x497
#define A6XX_RBBM_PERFCTR_TP_5_LO                0x498
#define A6XX_RBBM_PERFCTR_TP_5_HI                0x499
#define A6XX_RBBM_PERFCTR_TP_6_LO                0x49a
#define A6XX_RBBM_PERFCTR_TP_6_HI                0x49b
#define A6XX_RBBM_PERFCTR_TP_7_LO                0x49c
#define A6XX_RBBM_PERFCTR_TP_7_HI                0x49d
#define A6XX_RBBM_PERFCTR_TP_8_LO                0x49e
#define A6XX_RBBM_PERFCTR_TP_8_HI                0x49f
#define A6XX_RBBM_PERFCTR_TP_9_LO                0x4a0
#define A6XX_RBBM_PERFCTR_TP_9_HI                0x4a1
#define A6XX_RBBM_PERFCTR_TP_10_LO               0x4a2
#define A6XX_RBBM_PERFCTR_TP_10_HI               0x4a3
#define A6XX_RBBM_PERFCTR_TP_11_LO               0x4a4
#define A6XX_RBBM_PERFCTR_TP_11_HI               0x4a5
#define A6XX_RBBM_PERFCTR_SP_0_LO                0x4a6
#define A6XX_RBBM_PERFCTR_SP_0_HI                0x4a7
#define A6XX_RBBM_PERFCTR_SP_1_LO                0x4a8
#define A6XX_RBBM_PERFCTR_SP_1_HI                0x4a9
#define A6XX_RBBM_PERFCTR_SP_2_LO                0x4aa
#define A6XX_RBBM_PERFCTR_SP_2_HI                0x4ab
#define A6XX_RBBM_PERFCTR_SP_3_LO                0x4ac
#define A6XX_RBBM_PERFCTR_SP_3_HI                0x4ad
#define A6XX_RBBM_PERFCTR_SP_4_LO                0x4ae
#define A6XX_RBBM_PERFCTR_SP_4_HI                0x4af
#define A6XX_RBBM_PERFCTR_SP_5_LO                0x4b0
#define A6XX_RBBM_PERFCTR_SP_5_HI                0x4b1
#define A6XX_RBBM_PERFCTR_SP_6_LO                0x4b2
#define A6XX_RBBM_PERFCTR_SP_6_HI                0x4b3
#define A6XX_RBBM_PERFCTR_SP_7_LO                0x4b4
#define A6XX_RBBM_PERFCTR_SP_7_HI                0x4b5
#define A6XX_RBBM_PERFCTR_SP_8_LO                0x4b6
#define A6XX_RBBM_PERFCTR_SP_8_HI                0x4b7
#define A6XX_RBBM_PERFCTR_SP_9_LO                0x4b8
#define A6XX_RBBM_PERFCTR_SP_9_HI                0x4b9
#define A6XX_RBBM_PERFCTR_SP_10_LO               0x4ba
#define A6XX_RBBM_PERFCTR_SP_10_HI               0x4bb
#define A6XX_RBBM_PERFCTR_SP_11_LO               0x4bc
#define A6XX_RBBM_PERFCTR_SP_11_HI               0x4bd
#define A6XX_RBBM_PERFCTR_SP_12_LO               0x4be
#define A6XX_RBBM_PERFCTR_SP_12_HI               0x4bf
#define A6XX_RBBM_PERFCTR_SP_13_LO               0x4c0
#define A6XX_RBBM_PERFCTR_SP_13_HI               0x4c1
#define A6XX_RBBM_PERFCTR_SP_14_LO               0x4c2
#define A6XX_RBBM_PERFCTR_SP_14_HI               0x4c3
#define A6XX_RBBM_PERFCTR_SP_15_LO               0x4c4
#define A6XX_RBBM_PERFCTR_SP_15_HI               0x4c5
#define A6XX_RBBM_PERFCTR_SP_16_LO               0x4c6
#define A6XX_RBBM_PERFCTR_SP_16_HI               0x4c7
#define A6XX_RBBM_PERFCTR_SP_17_LO               0x4c8
#define A6XX_RBBM_PERFCTR_SP_17_HI               0x4c9
#define A6XX_RBBM_PERFCTR_SP_18_LO               0x4ca
#define A6XX_RBBM_PERFCTR_SP_18_HI               0x4cb
#define A6XX_RBBM_PERFCTR_SP_19_LO               0x4cc
#define A6XX_RBBM_PERFCTR_SP_19_HI               0x4cd
#define A6XX_RBBM_PERFCTR_SP_20_LO               0x4ce
#define A6XX_RBBM_PERFCTR_SP_20_HI               0x4cf
#define A6XX_RBBM_PERFCTR_SP_21_LO               0x4d0
#define A6XX_RBBM_PERFCTR_SP_21_HI               0x4d1
#define A6XX_RBBM_PERFCTR_SP_22_LO               0x4d2
#define A6XX_RBBM_PERFCTR_SP_22_HI               0x4d3
#define A6XX_RBBM_PERFCTR_SP_23_LO               0x4d4
#define A6XX_RBBM_PERFCTR_SP_23_HI               0x4d5
#define A6XX_RBBM_PERFCTR_RB_0_LO                0x4d6
#define A6XX_RBBM_PERFCTR_RB_0_HI                0x4d7
#define A6XX_RBBM_PERFCTR_RB_1_LO                0x4d8
#define A6XX_RBBM_PERFCTR_RB_1_HI                0x4d9
#define A6XX_RBBM_PERFCTR_RB_2_LO                0x4da
#define A6XX_RBBM_PERFCTR_RB_2_HI                0x4db
#define A6XX_RBBM_PERFCTR_RB_3_LO                0x4dc
#define A6XX_RBBM_PERFCTR_RB_3_HI                0x4dd
#define A6XX_RBBM_PERFCTR_RB_4_LO                0x4de
#define A6XX_RBBM_PERFCTR_RB_4_HI                0x4df
#define A6XX_RBBM_PERFCTR_RB_5_LO                0x4e0
#define A6XX_RBBM_PERFCTR_RB_5_HI                0x4e1
#define A6XX_RBBM_PERFCTR_RB_6_LO                0x4e2
#define A6XX_RBBM_PERFCTR_RB_6_HI                0x4e3
#define A6XX_RBBM_PERFCTR_RB_7_LO                0x4e4
#define A6XX_RBBM_PERFCTR_RB_7_HI                0x4e5
#define A6XX_RBBM_PERFCTR_VSC_0_LO               0x4e6
#define A6XX_RBBM_PERFCTR_VSC_0_HI               0x4e7
#define A6XX_RBBM_PERFCTR_VSC_1_LO               0x4e8
#define A6XX_RBBM_PERFCTR_VSC_1_HI               0x4e9
#define A6XX_RBBM_PERFCTR_LRZ_0_LO               0x4ea
#define A6XX_RBBM_PERFCTR_LRZ_0_HI               0x4eb
#define A6XX_RBBM_PERFCTR_LRZ_1_LO               0x4ec
#define A6XX_RBBM_PERFCTR_LRZ_1_HI               0x4ed
#define A6XX_RBBM_PERFCTR_LRZ_2_LO               0x4ee
#define A6XX_RBBM_PERFCTR_LRZ_2_HI               0x4ef
#define A6XX_RBBM_PERFCTR_LRZ_3_LO               0x4f0
#define A6XX_RBBM_PERFCTR_LRZ_3_HI               0x4f1
#define A6XX_RBBM_PERFCTR_CMP_0_LO               0x4f2
#define A6XX_RBBM_PERFCTR_CMP_0_HI               0x4f3
#define A6XX_RBBM_PERFCTR_CMP_1_LO               0x4f4
#define A6XX_RBBM_PERFCTR_CMP_1_HI               0x4f5
#define A6XX_RBBM_PERFCTR_CMP_2_LO               0x4f6
#define A6XX_RBBM_PERFCTR_CMP_2_HI               0x4f7
#define A6XX_RBBM_PERFCTR_CMP_3_LO               0x4f8
#define A6XX_RBBM_PERFCTR_CMP_3_HI               0x4f9
#define A6XX_RBBM_PERFCTR_CNTL                   0x500
#define A6XX_RBBM_PERFCTR_LOAD_CMD0              0x501
#define A6XX_RBBM_PERFCTR_LOAD_CMD1              0x502
#define A6XX_RBBM_PERFCTR_LOAD_CMD2              0x503
#define A6XX_RBBM_PERFCTR_LOAD_CMD3              0x504
#define A6XX_RBBM_PERFCTR_LOAD_VALUE_LO          0x505
#define A6XX_RBBM_PERFCTR_LOAD_VALUE_HI          0x506
#define A6XX_RBBM_PERFCTR_RBBM_SEL_0             0x507
#define A6XX_RBBM_PERFCTR_RBBM_SEL_1             0x508
#define A6XX_RBBM_PERFCTR_RBBM_SEL_2             0x509
#define A6XX_RBBM_PERFCTR_RBBM_SEL_3             0x50A
#define A6XX_RBBM_PERFCTR_GPU_BUSY_MASKED        0x50B
#define A6XX_RBBM_PERFCTR_SRAM_INIT_CMD          0x50e
#define A6XX_RBBM_PERFCTR_SRAM_INIT_STATUS       0x50f
#define A6XX_RBBM_PERFCTR_MHUB_0_LO              0x512
#define A6XX_RBBM_PERFCTR_MHUB_0_HI              0x513
#define A6XX_RBBM_PERFCTR_MHUB_1_LO              0x514
#define A6XX_RBBM_PERFCTR_MHUB_1_HI              0x515
#define A6XX_RBBM_PERFCTR_MHUB_2_LO              0x516
#define A6XX_RBBM_PERFCTR_MHUB_2_HI              0x517
#define A6XX_RBBM_PERFCTR_MHUB_3_LO              0x518
#define A6XX_RBBM_PERFCTR_MHUB_3_HI              0x519
#define A6XX_RBBM_PERFCTR_FCHE_0_LO              0x51A
#define A6XX_RBBM_PERFCTR_FCHE_0_HI              0x51B
#define A6XX_RBBM_PERFCTR_FCHE_1_LO              0x51C
#define A6XX_RBBM_PERFCTR_FCHE_1_HI              0x51D
#define A6XX_RBBM_PERFCTR_FCHE_2_LO              0x51E
#define A6XX_RBBM_PERFCTR_FCHE_2_HI              0x51F
#define A6XX_RBBM_PERFCTR_FCHE_3_LO              0x520
#define A6XX_RBBM_PERFCTR_FCHE_3_HI              0x521
#define A6XX_RBBM_PERFCTR_GLC_0_LO               0x522
#define A6XX_RBBM_PERFCTR_GLC_0_HI               0x523
#define A6XX_RBBM_PERFCTR_GLC_1_LO               0x524
#define A6XX_RBBM_PERFCTR_GLC_1_HI               0x525
#define A6XX_RBBM_PERFCTR_GLC_2_LO               0x526
#define A6XX_RBBM_PERFCTR_GLC_2_HI               0x527
#define A6XX_RBBM_PERFCTR_GLC_3_LO               0x528
#define A6XX_RBBM_PERFCTR_GLC_3_HI               0x529
#define A6XX_RBBM_PERFCTR_GLC_4_LO               0x52A
#define A6XX_RBBM_PERFCTR_GLC_4_HI               0x52B
#define A6XX_RBBM_PERFCTR_GLC_5_LO               0x52C
#define A6XX_RBBM_PERFCTR_GLC_5_HI               0x52D
#define A6XX_RBBM_PERFCTR_GLC_6_LO               0x52E
#define A6XX_RBBM_PERFCTR_GLC_6_HI               0x52F
#define A6XX_RBBM_PERFCTR_GLC_7_LO               0x530
#define A6XX_RBBM_PERFCTR_GLC_7_HI               0x531

#define A6XX_RBBM_ISDB_CNT                       0x533
#define A6XX_RBBM_NC_MODE_CNTL                   0X534

#define A6XX_RBBM_SECVID_TRUST_CNTL              0xF400
#define A6XX_RBBM_SECVID_TSB_TRUSTED_BASE_LO     0xF800
#define A6XX_RBBM_SECVID_TSB_TRUSTED_BASE_HI     0xF801
#define A6XX_RBBM_SECVID_TSB_TRUSTED_SIZE        0xF802
#define A6XX_RBBM_SECVID_TSB_CNTL                0xF803
#define A6XX_RBBM_SECVID_TSB_ADDR_MODE_CNTL      0xF810

#define A6XX_RBBM_VBIF_CLIENT_QOS_CNTL   0x00010
#define A6XX_RBBM_GBIF_CLIENT_QOS_CNTL   0x00011
#define A6XX_RBBM_GBIF_HALT              0x00016
#define A6XX_RBBM_GBIF_HALT_ACK          0x00017
#define A6XX_RBBM_GPR0_CNTL              0x00018
#define A6XX_RBBM_INTERFACE_HANG_INT_CNTL 0x0001f
#define A6XX_RBBM_INT_CLEAR_CMD          0x00037
#define A6XX_RBBM_INT_0_MASK             0x00038
#define A6XX_RBBM_INT_2_MASK             0x0003A
#define A6XX_RBBM_SP_HYST_CNT            0x00042
#define A6XX_RBBM_SW_RESET_CMD           0x00043
#define A6XX_RBBM_RAC_THRESHOLD_CNT      0x00044
#define A6XX_RBBM_BLOCK_SW_RESET_CMD     0x00045
#define A6XX_RBBM_BLOCK_SW_RESET_CMD2    0x00046
#define A6XX_RBBM_BLOCK_GX_RETENTION_CNTL 0x00050
#define A6XX_RBBM_CLOCK_CNTL             0x000ae
#define A6XX_RBBM_CLOCK_CNTL_SP0         0x000b0
#define A6XX_RBBM_CLOCK_CNTL_SP1         0x000b1
#define A6XX_RBBM_CLOCK_CNTL_SP2         0x000b2
#define A6XX_RBBM_CLOCK_CNTL_SP3         0x000b3
#define A6XX_RBBM_CLOCK_CNTL2_SP0        0x000b4
#define A6XX_RBBM_CLOCK_CNTL2_SP1        0x000b5
#define A6XX_RBBM_CLOCK_CNTL2_SP2        0x000b6
#define A6XX_RBBM_CLOCK_CNTL2_SP3        0x000b7
#define A6XX_RBBM_CLOCK_DELAY_SP0        0x000b8
#define A6XX_RBBM_CLOCK_DELAY_SP1        0x000b9
#define A6XX_RBBM_CLOCK_DELAY_SP2        0x000ba
#define A6XX_RBBM_CLOCK_DELAY_SP3        0x000bb
#define A6XX_RBBM_CLOCK_HYST_SP0         0x000bc
#define A6XX_RBBM_CLOCK_HYST_SP1         0x000bd
#define A6XX_RBBM_CLOCK_HYST_SP2         0x000be
#define A6XX_RBBM_CLOCK_HYST_SP3         0x000bf
#define A6XX_RBBM_CLOCK_CNTL_TP0         0x000c0
#define A6XX_RBBM_CLOCK_CNTL_TP1         0x000c1
#define A6XX_RBBM_CLOCK_CNTL_TP2         0x000c2
#define A6XX_RBBM_CLOCK_CNTL_TP3         0x000c3
#define A6XX_RBBM_CLOCK_CNTL2_TP0        0x000c4
#define A6XX_RBBM_CLOCK_CNTL2_TP1        0x000c5
#define A6XX_RBBM_CLOCK_CNTL2_TP2        0x000c6
#define A6XX_RBBM_CLOCK_CNTL2_TP3        0x000c7
#define A6XX_RBBM_CLOCK_CNTL3_TP0        0x000c8
#define A6XX_RBBM_CLOCK_CNTL3_TP1        0x000c9
#define A6XX_RBBM_CLOCK_CNTL3_TP2        0x000ca
#define A6XX_RBBM_CLOCK_CNTL3_TP3        0x000cb
#define A6XX_RBBM_CLOCK_CNTL4_TP0        0x000cc
#define A6XX_RBBM_CLOCK_CNTL4_TP1        0x000cd
#define A6XX_RBBM_CLOCK_CNTL4_TP2        0x000ce
#define A6XX_RBBM_CLOCK_CNTL4_TP3        0x000cf
#define A6XX_RBBM_CLOCK_DELAY_TP0        0x000d0
#define A6XX_RBBM_CLOCK_DELAY_TP1        0x000d1
#define A6XX_RBBM_CLOCK_DELAY_TP2        0x000d2
#define A6XX_RBBM_CLOCK_DELAY_TP3        0x000d3
#define A6XX_RBBM_CLOCK_DELAY2_TP0       0x000d4
#define A6XX_RBBM_CLOCK_DELAY2_TP1       0x000d5
#define A6XX_RBBM_CLOCK_DELAY2_TP2       0x000d6
#define A6XX_RBBM_CLOCK_DELAY2_TP3       0x000d7
#define A6XX_RBBM_CLOCK_DELAY3_TP0       0x000d8
#define A6XX_RBBM_CLOCK_DELAY3_TP1       0x000d9
#define A6XX_RBBM_CLOCK_DELAY3_TP2       0x000da
#define A6XX_RBBM_CLOCK_DELAY3_TP3       0x000db
#define A6XX_RBBM_CLOCK_DELAY4_TP0       0x000dc
#define A6XX_RBBM_CLOCK_DELAY4_TP1       0x000dd
#define A6XX_RBBM_CLOCK_DELAY4_TP2       0x000de
#define A6XX_RBBM_CLOCK_DELAY4_TP3       0x000df
#define A6XX_RBBM_CLOCK_HYST_TP0         0x000e0
#define A6XX_RBBM_CLOCK_HYST_TP1         0x000e1
#define A6XX_RBBM_CLOCK_HYST_TP2         0x000e2
#define A6XX_RBBM_CLOCK_HYST_TP3         0x000e3
#define A6XX_RBBM_CLOCK_HYST2_TP0        0x000e4
#define A6XX_RBBM_CLOCK_HYST2_TP1        0x000e5
#define A6XX_RBBM_CLOCK_HYST2_TP2        0x000e6
#define A6XX_RBBM_CLOCK_HYST2_TP3        0x000e7
#define A6XX_RBBM_CLOCK_HYST3_TP0        0x000e8
#define A6XX_RBBM_CLOCK_HYST3_TP1        0x000e9
#define A6XX_RBBM_CLOCK_HYST3_TP2        0x000ea
#define A6XX_RBBM_CLOCK_HYST3_TP3        0x000eb
#define A6XX_RBBM_CLOCK_HYST4_TP0        0x000ec
#define A6XX_RBBM_CLOCK_HYST4_TP1        0x000ed
#define A6XX_RBBM_CLOCK_HYST4_TP2        0x000ee
#define A6XX_RBBM_CLOCK_HYST4_TP3        0x000ef
#define A6XX_RBBM_CLOCK_CNTL_RB0         0x000f0
#define A6XX_RBBM_CLOCK_CNTL_RB1         0x000f1
#define A6XX_RBBM_CLOCK_CNTL_RB2         0x000f2
#define A6XX_RBBM_CLOCK_CNTL_RB3         0x000f3
#define A6XX_RBBM_CLOCK_CNTL2_RB0        0x000f4
#define A6XX_RBBM_CLOCK_CNTL2_RB1        0x000f5
#define A6XX_RBBM_CLOCK_CNTL2_RB2        0x000f6
#define A6XX_RBBM_CLOCK_CNTL2_RB3        0x000f7
#define A6XX_RBBM_CLOCK_CNTL_CCU0        0x000f8
#define A6XX_RBBM_CLOCK_CNTL_CCU1        0x000f9
#define A6XX_RBBM_CLOCK_CNTL_CCU2        0x000fa
#define A6XX_RBBM_CLOCK_CNTL_CCU3        0x000fb
#define A6XX_RBBM_CLOCK_HYST_RB_CCU0     0x00100
#define A6XX_RBBM_CLOCK_HYST_RB_CCU1     0x00101
#define A6XX_RBBM_CLOCK_HYST_RB_CCU2     0x00102
#define A6XX_RBBM_CLOCK_HYST_RB_CCU3     0x00103
#define A6XX_RBBM_CLOCK_CNTL_RAC         0x00104
#define A6XX_RBBM_CLOCK_CNTL2_RAC        0x00105
#define A6XX_RBBM_CLOCK_DELAY_RAC        0x00106
#define A6XX_RBBM_CLOCK_HYST_RAC         0x00107
#define A6XX_RBBM_CLOCK_CNTL_TSE_RAS_RBBM 0x00108
#define A6XX_RBBM_CLOCK_DELAY_TSE_RAS_RBBM 0x00109
#define A6XX_RBBM_CLOCK_HYST_TSE_RAS_RBBM 0x0010a
#define A6XX_RBBM_CLOCK_CNTL_UCHE        0x0010b
#define A6XX_RBBM_CLOCK_CNTL2_UCHE       0x0010c
#define A6XX_RBBM_CLOCK_CNTL3_UCHE       0x0010d
#define A6XX_RBBM_CLOCK_CNTL4_UCHE       0x0010e
#define A6XX_RBBM_CLOCK_DELAY_UCHE       0x0010f
#define A6XX_RBBM_CLOCK_HYST_UCHE        0x00110
#define A6XX_RBBM_CLOCK_MODE_VFD         0x00111
#define A6XX_RBBM_CLOCK_DELAY_VFD        0x00112
#define A6XX_RBBM_CLOCK_HYST_VFD         0x00113
#define A6XX_RBBM_CLOCK_MODE_GPC         0x00114
#define A6XX_RBBM_CLOCK_DELAY_GPC        0x00115
#define A6XX_RBBM_CLOCK_HYST_GPC         0x00116
#define A6XX_RBBM_CLOCK_DELAY_HLSQ_2	 0x00117
#define A6XX_RBBM_CLOCK_CNTL_GMU_GX      0x00118
#define A6XX_RBBM_CLOCK_DELAY_GMU_GX     0x00119
#define A6XX_RBBM_CLOCK_CNTL_TEX_FCHE    0x00120
#define A6XX_RBBM_CLOCK_DELAY_TEX_FCHE   0x00121
#define A6XX_RBBM_CLOCK_HYST_TEX_FCHE    0x00122
#define A6XX_RBBM_CLOCK_HYST_GMU_GX      0x0011a
#define A6XX_RBBM_CLOCK_MODE_HLSQ	 0x0011b
#define A6XX_RBBM_CLOCK_DELAY_HLSQ       0x0011c
#define A6XX_RBBM_CLOCK_HYST_HLSQ        0x0011d
#define A6XX_RBBM_CLOCK_CNTL_FCHE        0x00123
#define A6XX_RBBM_CLOCK_DELAY_FCHE       0x00124
#define A6XX_RBBM_CLOCK_HYST_FCHE        0x00125
#define A6XX_RBBM_CLOCK_CNTL_GLC         0x0012B
#define A6XX_RBBM_CLOCK_DELAY_GLC        0x00129
#define A6XX_RBBM_CLOCK_HYST_GLC         0x0012A
#define A6XX_RBBM_CLOCK_CNTL_MHUB        0x00126
#define A6XX_RBBM_CLOCK_DELAY_MHUB       0x00127
#define A6XX_RBBM_CLOCK_HYST_MHUB        0x00128

/* DBGC_CFG registers */
#define A6XX_DBGC_CFG_DBGBUS_SEL_A                  0x600
#define A6XX_DBGC_CFG_DBGBUS_SEL_B                  0x601
#define A6XX_DBGC_CFG_DBGBUS_SEL_C                  0x602
#define A6XX_DBGC_CFG_DBGBUS_SEL_D                  0x603
#define A6XX_DBGC_CFG_DBGBUS_SEL_PING_INDEX_SHIFT   0x0
#define A6XX_DBGC_CFG_DBGBUS_SEL_PING_BLK_SEL_SHIFT 0x8
#define A6XX_DBGC_CFG_DBGBUS_CNTLT                  0x604
#define A6XX_DBGC_CFG_DBGBUS_CNTLT_TRACEEN_SHIFT    0x0
#define A6XX_DBGC_CFG_DBGBUS_CNTLT_GRANU_SHIFT      0xC
#define A6XX_DBGC_CFG_DBGBUS_CNTLT_SEGT_SHIFT       0x1C
#define A6XX_DBGC_CFG_DBGBUS_CNTLM                  0x605
#define A6XX_DBGC_CFG_DBGBUS_CTLTM_ENABLE_SHIFT     0x18
#define A6XX_DBGC_CFG_DBGBUS_OPL                    0x606
#define A6XX_DBGC_CFG_DBGBUS_OPE                    0x607
#define A6XX_DBGC_CFG_DBGBUS_IVTL_0                 0x608
#define A6XX_DBGC_CFG_DBGBUS_IVTL_1                 0x609
#define A6XX_DBGC_CFG_DBGBUS_IVTL_2                 0x60a
#define A6XX_DBGC_CFG_DBGBUS_IVTL_3                 0x60b
#define A6XX_DBGC_CFG_DBGBUS_MASKL_0                0x60c
#define A6XX_DBGC_CFG_DBGBUS_MASKL_1                0x60d
#define A6XX_DBGC_CFG_DBGBUS_MASKL_2                0x60e
#define A6XX_DBGC_CFG_DBGBUS_MASKL_3                0x60f
#define A6XX_DBGC_CFG_DBGBUS_BYTEL_0                0x610
#define A6XX_DBGC_CFG_DBGBUS_BYTEL_1                0x611
#define A6XX_DBGC_CFG_DBGBUS_BYTEL0_SHIFT           0x0
#define A6XX_DBGC_CFG_DBGBUS_BYTEL1_SHIFT           0x4
#define A6XX_DBGC_CFG_DBGBUS_BYTEL2_SHIFT           0x8
#define A6XX_DBGC_CFG_DBGBUS_BYTEL3_SHIFT           0xC
#define A6XX_DBGC_CFG_DBGBUS_BYTEL4_SHIFT           0x10
#define A6XX_DBGC_CFG_DBGBUS_BYTEL5_SHIFT           0x14
#define A6XX_DBGC_CFG_DBGBUS_BYTEL6_SHIFT           0x18
#define A6XX_DBGC_CFG_DBGBUS_BYTEL7_SHIFT           0x1C
#define A6XX_DBGC_CFG_DBGBUS_BYTEL8_SHIFT           0x0
#define A6XX_DBGC_CFG_DBGBUS_BYTEL9_SHIFT           0x4
#define A6XX_DBGC_CFG_DBGBUS_BYTEL10_SHIFT          0x8
#define A6XX_DBGC_CFG_DBGBUS_BYTEL11_SHIFT          0xC
#define A6XX_DBGC_CFG_DBGBUS_BYTEL12_SHIFT          0x10
#define A6XX_DBGC_CFG_DBGBUS_BYTEL13_SHIFT          0x14
#define A6XX_DBGC_CFG_DBGBUS_BYTEL14_SHIFT          0x18
#define A6XX_DBGC_CFG_DBGBUS_BYTEL15_SHIFT          0x1C
#define A6XX_DBGC_CFG_DBGBUS_IVTE_0                 0x612
#define A6XX_DBGC_CFG_DBGBUS_IVTE_1                 0x613
#define A6XX_DBGC_CFG_DBGBUS_IVTE_2                 0x614
#define A6XX_DBGC_CFG_DBGBUS_IVTE_3                 0x615
#define A6XX_DBGC_CFG_DBGBUS_MASKE_0                0x616
#define A6XX_DBGC_CFG_DBGBUS_MASKE_1                0x617
#define A6XX_DBGC_CFG_DBGBUS_MASKE_2                0x618
#define A6XX_DBGC_CFG_DBGBUS_MASKE_3                0x619
#define A6XX_DBGC_CFG_DBGBUS_NIBBLEE                0x61a
#define A6XX_DBGC_CFG_DBGBUS_PTRC0                  0x61b
#define A6XX_DBGC_CFG_DBGBUS_PTRC1                  0x61c
#define A6XX_DBGC_CFG_DBGBUS_LOADREG                0x61d
#define A6XX_DBGC_CFG_DBGBUS_IDX                    0x61e
#define A6XX_DBGC_CFG_DBGBUS_CLRC                   0x61f
#define A6XX_DBGC_CFG_DBGBUS_LOADIVT                0x620
#define A6XX_DBGC_VBIF_DBG_CNTL                     0x621
#define A6XX_DBGC_DBG_LO_HI_GPIO                    0x622
#define A6XX_DBGC_EXT_TRACE_BUS_CNTL                0x623
#define A6XX_DBGC_READ_AHB_THROUGH_DBG              0x624
#define A6XX_DBGC_CFG_DBGBUS_TRACE_BUF1             0x62f
#define A6XX_DBGC_CFG_DBGBUS_TRACE_BUF2             0x630
#define A6XX_DBGC_EVT_CFG                           0x640
#define A6XX_DBGC_EVT_INTF_SEL_0                    0x641
#define A6XX_DBGC_EVT_INTF_SEL_1                    0x642
#define A6XX_DBGC_PERF_ATB_CFG                      0x643
#define A6XX_DBGC_PERF_ATB_COUNTER_SEL_0            0x644
#define A6XX_DBGC_PERF_ATB_COUNTER_SEL_1            0x645
#define A6XX_DBGC_PERF_ATB_COUNTER_SEL_2            0x646
#define A6XX_DBGC_PERF_ATB_COUNTER_SEL_3            0x647
#define A6XX_DBGC_PERF_ATB_TRIG_INTF_SEL_0          0x648
#define A6XX_DBGC_PERF_ATB_TRIG_INTF_SEL_1          0x649
#define A6XX_DBGC_PERF_ATB_DRAIN_CMD                0x64a
#define A6XX_DBGC_ECO_CNTL                          0x650
#define A6XX_DBGC_AHB_DBG_CNTL                      0x651

/* VSC registers */
#define A6XX_VSC_PERFCTR_VSC_SEL_0          0xCD8
#define A6XX_VSC_PERFCTR_VSC_SEL_1          0xCD9

/* GRAS registers */
#define A6XX_GRAS_ADDR_MODE_CNTL            0x8601
#define A6XX_GRAS_PERFCTR_TSE_SEL_0         0x8610
#define A6XX_GRAS_PERFCTR_TSE_SEL_1         0x8611
#define A6XX_GRAS_PERFCTR_TSE_SEL_2         0x8612
#define A6XX_GRAS_PERFCTR_TSE_SEL_3         0x8613
#define A6XX_GRAS_PERFCTR_RAS_SEL_0         0x8614
#define A6XX_GRAS_PERFCTR_RAS_SEL_1         0x8615
#define A6XX_GRAS_PERFCTR_RAS_SEL_2         0x8616
#define A6XX_GRAS_PERFCTR_RAS_SEL_3         0x8617
#define A6XX_GRAS_PERFCTR_LRZ_SEL_0         0x8618
#define A6XX_GRAS_PERFCTR_LRZ_SEL_1         0x8619
#define A6XX_GRAS_PERFCTR_LRZ_SEL_2         0x861A
#define A6XX_GRAS_PERFCTR_LRZ_SEL_3         0x861B

/* RB registers */
#define A6XX_RB_ADDR_MODE_CNTL              0x8E05
#define A6XX_RB_NC_MODE_CNTL                0x8E08
#define A6XX_RB_PERFCTR_RB_SEL_0            0x8E10
#define A6XX_RB_PERFCTR_RB_SEL_1            0x8E11
#define A6XX_RB_PERFCTR_RB_SEL_2            0x8E12
#define A6XX_RB_PERFCTR_RB_SEL_3            0x8E13
#define A6XX_RB_PERFCTR_RB_SEL_4            0x8E14
#define A6XX_RB_PERFCTR_RB_SEL_5            0x8E15
#define A6XX_RB_PERFCTR_RB_SEL_6            0x8E16
#define A6XX_RB_PERFCTR_RB_SEL_7            0x8E17
#define A6XX_RB_PERFCTR_CCU_SEL_0           0x8E18
#define A6XX_RB_PERFCTR_CCU_SEL_1           0x8E19
#define A6XX_RB_PERFCTR_CCU_SEL_2           0x8E1A
#define A6XX_RB_PERFCTR_CCU_SEL_3           0x8E1B
#define A6XX_RB_PERFCTR_CCU_SEL_4           0x8E1C
#define A6XX_RB_PERFCTR_CMP_SEL_0           0x8E2C
#define A6XX_RB_PERFCTR_CMP_SEL_1           0x8E2D
#define A6XX_RB_PERFCTR_CMP_SEL_2           0x8E2E
#define A6XX_RB_PERFCTR_CMP_SEL_3           0x8E2F
#define A6XX_RB_RB_SUB_BLOCK_SEL_CNTL_HOST  0x8E3B
#define A6XX_RB_RB_SUB_BLOCK_SEL_CNTL_CD    0x8E3D
#define A6XX_RB_CONTEXT_SWITCH_GMEM_SAVE_RESTORE 0x8E50
#define A6XX_RB_PERFCTR_GLC_SEL_0            0x8E90
#define A6XX_RB_PERFCTR_GLC_SEL_1            0x8E91
#define A6XX_RB_PERFCTR_GLC_SEL_2            0x8E92
#define A6XX_RB_PERFCTR_GLC_SEL_3            0x8E93
#define A6XX_RB_PERFCTR_GLC_SEL_4            0x8E94
#define A6XX_RB_PERFCTR_GLC_SEL_5            0x8E95
#define A6XX_RB_PERFCTR_GLC_SEL_6            0x8E96
#define A6XX_RB_PERFCTR_GLC_SEL_7            0x8E97
#define A6XX_RB_PERFCTR_MHUB_SEL_0           0x8EA0
#define A6XX_RB_PERFCTR_MHUB_SEL_1           0x8EA1
#define A6XX_RB_PERFCTR_MHUB_SEL_2           0x8EA2
#define A6XX_RB_PERFCTR_MHUB_SEL_3           0x8EA3
#define A6XX_RB_PERFCTR_FCHE_SEL_0           0x8EB0
#define A6XX_RB_PERFCTR_FCHE_SEL_1           0x8EB1
#define A6XX_RB_PERFCTR_FCHE_SEL_2           0x8EB2
#define A6XX_RB_PERFCTR_FCHE_SEL_3           0x8EB3

/* PC registers */
#define A6XX_PC_DBG_ECO_CNTL                0x9E00
#define A6XX_PC_ADDR_MODE_CNTL              0x9E01
#define A6XX_PC_PERFCTR_PC_SEL_0            0x9E34
#define A6XX_PC_PERFCTR_PC_SEL_1            0x9E35
#define A6XX_PC_PERFCTR_PC_SEL_2            0x9E36
#define A6XX_PC_PERFCTR_PC_SEL_3            0x9E37
#define A6XX_PC_PERFCTR_PC_SEL_4            0x9E38
#define A6XX_PC_PERFCTR_PC_SEL_5            0x9E39
#define A6XX_PC_PERFCTR_PC_SEL_6            0x9E3A
#define A6XX_PC_PERFCTR_PC_SEL_7            0x9E3B

/* HLSQ registers */
#define A6XX_HLSQ_ADDR_MODE_CNTL            0xBE05
#define A6XX_HLSQ_PERFCTR_HLSQ_SEL_0        0xBE10
#define A6XX_HLSQ_PERFCTR_HLSQ_SEL_1        0xBE11
#define A6XX_HLSQ_PERFCTR_HLSQ_SEL_2        0xBE12
#define A6XX_HLSQ_PERFCTR_HLSQ_SEL_3        0xBE13
#define A6XX_HLSQ_PERFCTR_HLSQ_SEL_4        0xBE14
#define A6XX_HLSQ_PERFCTR_HLSQ_SEL_5        0xBE15
#define A6XX_HLSQ_DBG_AHB_READ_APERTURE     0xC800
#define A6XX_HLSQ_DBG_READ_SEL              0xD000

/* VFD registers */
#define A6XX_VFD_ADDR_MODE_CNTL             0xA601
#define A6XX_VFD_PERFCTR_VFD_SEL_0          0xA610
#define A6XX_VFD_PERFCTR_VFD_SEL_1          0xA611
#define A6XX_VFD_PERFCTR_VFD_SEL_2          0xA612
#define A6XX_VFD_PERFCTR_VFD_SEL_3          0xA613
#define A6XX_VFD_PERFCTR_VFD_SEL_4          0xA614
#define A6XX_VFD_PERFCTR_VFD_SEL_5          0xA615
#define A6XX_VFD_PERFCTR_VFD_SEL_6          0xA616
#define A6XX_VFD_PERFCTR_VFD_SEL_7          0xA617

/* VPC registers */
#define A6XX_VPC_ADDR_MODE_CNTL             0x9601
#define A6XX_VPC_PERFCTR_VPC_SEL_0          0x9604
#define A6XX_VPC_PERFCTR_VPC_SEL_1          0x9605
#define A6XX_VPC_PERFCTR_VPC_SEL_2          0x9606
#define A6XX_VPC_PERFCTR_VPC_SEL_3          0x9607
#define A6XX_VPC_PERFCTR_VPC_SEL_4          0x9608
#define A6XX_VPC_PERFCTR_VPC_SEL_5          0x9609

/* UCHE registers */
#define A6XX_UCHE_ADDR_MODE_CNTL            0xE00
#define A6XX_UCHE_MODE_CNTL                 0xE01
#define A6XX_UCHE_WRITE_RANGE_MAX_LO        0xE05
#define A6XX_UCHE_WRITE_RANGE_MAX_HI        0xE06
#define A6XX_UCHE_WRITE_THRU_BASE_LO        0xE07
#define A6XX_UCHE_WRITE_THRU_BASE_HI        0xE08
#define A6XX_UCHE_TRAP_BASE_LO              0xE09
#define A6XX_UCHE_TRAP_BASE_HI              0xE0A
#define A6XX_UCHE_GMEM_RANGE_MIN_LO         0xE0B
#define A6XX_UCHE_GMEM_RANGE_MIN_HI         0xE0C
#define A6XX_UCHE_GMEM_RANGE_MAX_LO         0xE0D
#define A6XX_UCHE_GMEM_RANGE_MAX_HI         0xE0E
#define A6XX_UCHE_CACHE_WAYS                0xE17
#define A6XX_UCHE_FILTER_CNTL               0xE18
#define A6XX_UCHE_CLIENT_PF                 0xE19
#define A6XX_UCHE_CLIENT_PF_CLIENT_ID_MASK  0x7
#define A6XX_UCHE_PERFCTR_UCHE_SEL_0        0xE1C
#define A6XX_UCHE_PERFCTR_UCHE_SEL_1        0xE1D
#define A6XX_UCHE_PERFCTR_UCHE_SEL_2        0xE1E
#define A6XX_UCHE_PERFCTR_UCHE_SEL_3        0xE1F
#define A6XX_UCHE_PERFCTR_UCHE_SEL_4        0xE20
#define A6XX_UCHE_PERFCTR_UCHE_SEL_5        0xE21
#define A6XX_UCHE_PERFCTR_UCHE_SEL_6        0xE22
#define A6XX_UCHE_PERFCTR_UCHE_SEL_7        0xE23
#define A6XX_UCHE_PERFCTR_UCHE_SEL_8        0xE24
#define A6XX_UCHE_PERFCTR_UCHE_SEL_9        0xE25
#define A6XX_UCHE_PERFCTR_UCHE_SEL_10       0xE26
#define A6XX_UCHE_PERFCTR_UCHE_SEL_11       0xE27
#define A6XX_UCHE_GBIF_GX_CONFIG            0xE3A

/* SP registers */
#define A6XX_SP_ADDR_MODE_CNTL              0xAE01
#define A6XX_SP_NC_MODE_CNTL                0xAE02
#define A6XX_SP_PERFCTR_SP_SEL_0            0xAE10
#define A6XX_SP_PERFCTR_SP_SEL_1            0xAE11
#define A6XX_SP_PERFCTR_SP_SEL_2            0xAE12
#define A6XX_SP_PERFCTR_SP_SEL_3            0xAE13
#define A6XX_SP_PERFCTR_SP_SEL_4            0xAE14
#define A6XX_SP_PERFCTR_SP_SEL_5            0xAE15
#define A6XX_SP_PERFCTR_SP_SEL_6            0xAE16
#define A6XX_SP_PERFCTR_SP_SEL_7            0xAE17
#define A6XX_SP_PERFCTR_SP_SEL_8            0xAE18
#define A6XX_SP_PERFCTR_SP_SEL_9            0xAE19
#define A6XX_SP_PERFCTR_SP_SEL_10           0xAE1A
#define A6XX_SP_PERFCTR_SP_SEL_11           0xAE1B
#define A6XX_SP_PERFCTR_SP_SEL_12           0xAE1C
#define A6XX_SP_PERFCTR_SP_SEL_13           0xAE1D
#define A6XX_SP_PERFCTR_SP_SEL_14           0xAE1E
#define A6XX_SP_PERFCTR_SP_SEL_15           0xAE1F
#define A6XX_SP_PERFCTR_SP_SEL_16           0xAE20
#define A6XX_SP_PERFCTR_SP_SEL_17           0xAE21
#define A6XX_SP_PERFCTR_SP_SEL_18           0xAE22
#define A6XX_SP_PERFCTR_SP_SEL_19           0xAE23
#define A6XX_SP_PERFCTR_SP_SEL_20           0xAE24
#define A6XX_SP_PERFCTR_SP_SEL_21           0xAE25
#define A6XX_SP_PERFCTR_SP_SEL_22           0xAE26
#define A6XX_SP_PERFCTR_SP_SEL_23           0xAE27

/* TP registers */
#define A6XX_TPL1_ADDR_MODE_CNTL            0xB601
#define A6XX_TPL1_NC_MODE_CNTL              0xB604
#define A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_0   0xB608
#define A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_1   0xB609
#define A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_2   0xB60A
#define A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_3   0xB60B
#define A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_4   0xB60C
#define A6XX_TPL1_PERFCTR_TP_SEL_0          0xB610
#define A6XX_TPL1_PERFCTR_TP_SEL_1          0xB611
#define A6XX_TPL1_PERFCTR_TP_SEL_2          0xB612
#define A6XX_TPL1_PERFCTR_TP_SEL_3          0xB613
#define A6XX_TPL1_PERFCTR_TP_SEL_4          0xB614
#define A6XX_TPL1_PERFCTR_TP_SEL_5          0xB615
#define A6XX_TPL1_PERFCTR_TP_SEL_6          0xB616
#define A6XX_TPL1_PERFCTR_TP_SEL_7          0xB617
#define A6XX_TPL1_PERFCTR_TP_SEL_8          0xB618
#define A6XX_TPL1_PERFCTR_TP_SEL_9          0xB619
#define A6XX_TPL1_PERFCTR_TP_SEL_10         0xB61A
#define A6XX_TPL1_PERFCTR_TP_SEL_11         0xB61B

/* VBIF registers */
#define A6XX_VBIF_VERSION                       0x3000
#define A6XX_VBIF_CLKON                         0x3001
#define A6XX_VBIF_CLKON_FORCE_ON_TESTBUS_MASK   0x1
#define A6XX_VBIF_CLKON_FORCE_ON_TESTBUS_SHIFT  0x1
#define A6XX_VBIF_GATE_OFF_WRREQ_EN             0x302A
#define A6XX_VBIF_XIN_HALT_CTRL0                0x3080
#define A6XX_VBIF_XIN_HALT_CTRL0_MASK           0xF
#define A6XX_VBIF_XIN_HALT_CTRL1                0x3081
#define A6XX_VBIF_TEST_BUS_OUT_CTRL             0x3084
#define A6XX_VBIF_TEST_BUS_OUT_CTRL_EN_MASK     0x1
#define A6XX_VBIF_TEST_BUS_OUT_CTRL_EN_SHIFT    0x0
#define A6XX_VBIF_TEST_BUS1_CTRL0               0x3085
#define A6XX_VBIF_TEST_BUS1_CTRL1               0x3086
#define A6XX_VBIF_TEST_BUS1_CTRL1_DATA_SEL_MASK 0xF
#define A6XX_VBIF_TEST_BUS1_CTRL1_DATA_SEL_SHIFT 0x0
#define A6XX_VBIF_TEST_BUS2_CTRL0               0x3087
#define A6XX_VBIF_TEST_BUS2_CTRL1               0x3088
#define A6XX_VBIF_TEST_BUS2_CTRL1_DATA_SEL_MASK 0x1FF
#define A6XX_VBIF_TEST_BUS2_CTRL1_DATA_SEL_SHIFT 0x0
#define A6XX_VBIF_TEST_BUS_OUT                  0x308C
#define A6XX_VBIF_PERF_CNT_SEL0                 0x30d0
#define A6XX_VBIF_PERF_CNT_SEL1                 0x30d1
#define A6XX_VBIF_PERF_CNT_SEL2                 0x30d2
#define A6XX_VBIF_PERF_CNT_SEL3                 0x30d3
#define A6XX_VBIF_PERF_CNT_LOW0                 0x30d8
#define A6XX_VBIF_PERF_CNT_LOW1                 0x30d9
#define A6XX_VBIF_PERF_CNT_LOW2                 0x30da
#define A6XX_VBIF_PERF_CNT_LOW3                 0x30db
#define A6XX_VBIF_PERF_CNT_HIGH0                0x30e0
#define A6XX_VBIF_PERF_CNT_HIGH1                0x30e1
#define A6XX_VBIF_PERF_CNT_HIGH2                0x30e2
#define A6XX_VBIF_PERF_CNT_HIGH3                0x30e3
#define A6XX_VBIF_PERF_PWR_CNT_EN0              0x3100
#define A6XX_VBIF_PERF_PWR_CNT_EN1              0x3101
#define A6XX_VBIF_PERF_PWR_CNT_EN2              0x3102
#define A6XX_VBIF_PERF_PWR_CNT_LOW0             0x3110
#define A6XX_VBIF_PERF_PWR_CNT_LOW1             0x3111
#define A6XX_VBIF_PERF_PWR_CNT_LOW2             0x3112
#define A6XX_VBIF_PERF_PWR_CNT_HIGH0            0x3118
#define A6XX_VBIF_PERF_PWR_CNT_HIGH1            0x3119
#define A6XX_VBIF_PERF_PWR_CNT_HIGH2            0x311a

/* GBIF countables */
#define GBIF_AXI0_READ_DATA_TOTAL_BEATS    34
#define GBIF_AXI1_READ_DATA_TOTAL_BEATS    35
#define GBIF_AXI0_WRITE_DATA_TOTAL_BEATS   46
#define GBIF_AXI1_WRITE_DATA_TOTAL_BEATS   47

/* GBIF registers */
#define A6XX_GBIF_SCACHE_CNTL1            0x3c02
#define A6XX_GBIF_QSB_SIDE0               0x3c03
#define A6XX_GBIF_QSB_SIDE1               0x3c04
#define A6XX_GBIF_QSB_SIDE2               0x3c05
#define A6XX_GBIF_QSB_SIDE3               0x3c06
#define A6XX_GBIF_HALT                    0x3c45
#define A6XX_GBIF_HALT_ACK                0x3c46

#define A6XX_GBIF_CLIENT_HALT_MASK        BIT(0)
#define A6XX_GBIF_ARB_HALT_MASK           BIT(1)
#define A6XX_GBIF_GX_HALT_MASK            BIT(0)

#define A6XX_GBIF_PERF_PWR_CNT_EN         0x3cc0
#define A6XX_GBIF_PERF_CNT_SEL            0x3cc2
#define A6XX_GBIF_PERF_PWR_CNT_SEL        0x3cc3
#define A6XX_GBIF_PERF_CNT_LOW0           0x3cc4
#define A6XX_GBIF_PERF_CNT_LOW1           0x3cc5
#define A6XX_GBIF_PERF_CNT_LOW2           0x3cc6
#define A6XX_GBIF_PERF_CNT_LOW3           0x3cc7
#define A6XX_GBIF_PERF_CNT_HIGH0          0x3cc8
#define A6XX_GBIF_PERF_CNT_HIGH1          0x3cc9
#define A6XX_GBIF_PERF_CNT_HIGH2          0x3cca
#define A6XX_GBIF_PERF_CNT_HIGH3          0x3ccb
#define A6XX_GBIF_PWR_CNT_LOW0            0x3ccc
#define A6XX_GBIF_PWR_CNT_LOW1            0x3ccd
#define A6XX_GBIF_PWR_CNT_LOW2            0x3cce
#define A6XX_GBIF_PWR_CNT_HIGH0           0x3ccf
#define A6XX_GBIF_PWR_CNT_HIGH1           0x3cd0
#define A6XX_GBIF_PWR_CNT_HIGH2           0x3cd1


/* CX_DBGC_CFG registers */
#define A6XX_CX_DBGC_CFG_DBGBUS_SEL_A                   0x18400
#define A6XX_CX_DBGC_CFG_DBGBUS_SEL_B                   0x18401
#define A6XX_CX_DBGC_CFG_DBGBUS_SEL_C                   0x18402
#define A6XX_CX_DBGC_CFG_DBGBUS_SEL_D                   0x18403
#define A6XX_CX_DBGC_CFG_DBGBUS_SEL_PING_INDEX_SHIFT    0x0
#define A6XX_CX_DBGC_CFG_DBGBUS_SEL_PING_BLK_SEL_SHIFT  0x8
#define A6XX_CX_DBGC_CFG_DBGBUS_CNTLT                   0x18404
#define A6XX_CX_DBGC_CFG_DBGBUS_CNTLT_TRACEEN_SHIFT     0x0
#define A6XX_CX_DBGC_CFG_DBGBUS_CNTLT_GRANU_SHIFT       0xC
#define A6XX_CX_DBGC_CFG_DBGBUS_CNTLT_SEGT_SHIFT        0x1C
#define A6XX_CX_DBGC_CFG_DBGBUS_CNTLM                   0x18405
#define A6XX_CX_DBGC_CFG_DBGBUS_CNTLM_ENABLE_SHIFT      0x18
#define A6XX_CX_DBGC_CFG_DBGBUS_OPL                     0x18406
#define A6XX_CX_DBGC_CFG_DBGBUS_OPE                     0x18407
#define A6XX_CX_DBGC_CFG_DBGBUS_IVTL_0                  0x18408
#define A6XX_CX_DBGC_CFG_DBGBUS_IVTL_1                  0x18409
#define A6XX_CX_DBGC_CFG_DBGBUS_IVTL_2                  0x1840A
#define A6XX_CX_DBGC_CFG_DBGBUS_IVTL_3                  0x1840B
#define A6XX_CX_DBGC_CFG_DBGBUS_MASKL_0                 0x1840C
#define A6XX_CX_DBGC_CFG_DBGBUS_MASKL_1                 0x1840D
#define A6XX_CX_DBGC_CFG_DBGBUS_MASKL_2                 0x1840E
#define A6XX_CX_DBGC_CFG_DBGBUS_MASKL_3                 0x1840F
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL_0                 0x18410
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL_1                 0x18411
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL0_SHIFT            0x0
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL1_SHIFT            0x4
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL2_SHIFT            0x8
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL3_SHIFT            0xC
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL4_SHIFT            0x10
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL5_SHIFT            0x14
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL6_SHIFT            0x18
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL7_SHIFT            0x1C
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL8_SHIFT            0x0
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL9_SHIFT            0x4
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL10_SHIFT           0x8
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL11_SHIFT           0xC
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL12_SHIFT           0x10
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL13_SHIFT           0x14
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL14_SHIFT           0x18
#define A6XX_CX_DBGC_CFG_DBGBUS_BYTEL15_SHIFT           0x1C
#define A6XX_CX_DBGC_CFG_DBGBUS_IVTE_0                  0x18412
#define A6XX_CX_DBGC_CFG_DBGBUS_IVTE_1                  0x18413
#define A6XX_CX_DBGC_CFG_DBGBUS_IVTE_2                  0x18414
#define A6XX_CX_DBGC_CFG_DBGBUS_IVTE_3                  0x18415
#define A6XX_CX_DBGC_CFG_DBGBUS_MASKE_0                 0x18416
#define A6XX_CX_DBGC_CFG_DBGBUS_MASKE_1                 0x18417
#define A6XX_CX_DBGC_CFG_DBGBUS_MASKE_2                 0x18418
#define A6XX_CX_DBGC_CFG_DBGBUS_MASKE_3                 0x18419
#define A6XX_CX_DBGC_CFG_DBGBUS_NIBBLEE                 0x1841A
#define A6XX_CX_DBGC_CFG_DBGBUS_PTRC0                   0x1841B
#define A6XX_CX_DBGC_CFG_DBGBUS_PTRC1                   0x1841C
#define A6XX_CX_DBGC_CFG_DBGBUS_LOADREG                 0x1841D
#define A6XX_CX_DBGC_CFG_DBGBUS_IDX                     0x1841E
#define A6XX_CX_DBGC_CFG_DBGBUS_CLRC                    0x1841F
#define A6XX_CX_DBGC_CFG_DBGBUS_LOADIVT                 0x18420
#define A6XX_CX_DBGC_VBIF_DBG_CNTL                      0x18421
#define A6XX_CX_DBGC_DBG_LO_HI_GPIO                     0x18422
#define A6XX_CX_DBGC_EXT_TRACE_BUS_CNTL                 0x18423
#define A6XX_CX_DBGC_READ_AHB_THROUGH_DBG               0x18424
#define A6XX_CX_DBGC_CFG_DBGBUS_TRACE_BUF1              0x1842F
#define A6XX_CX_DBGC_CFG_DBGBUS_TRACE_BUF2              0x18430
#define A6XX_CX_DBGC_EVT_CFG                            0x18440
#define A6XX_CX_DBGC_EVT_INTF_SEL_0                     0x18441
#define A6XX_CX_DBGC_EVT_INTF_SEL_1                     0x18442
#define A6XX_CX_DBGC_PERF_ATB_CFG                       0x18443
#define A6XX_CX_DBGC_PERF_ATB_COUNTER_SEL_0             0x18444
#define A6XX_CX_DBGC_PERF_ATB_COUNTER_SEL_1             0x18445
#define A6XX_CX_DBGC_PERF_ATB_COUNTER_SEL_2             0x18446
#define A6XX_CX_DBGC_PERF_ATB_COUNTER_SEL_3             0x18447
#define A6XX_CX_DBGC_PERF_ATB_TRIG_INTF_SEL_0           0x18448
#define A6XX_CX_DBGC_PERF_ATB_TRIG_INTF_SEL_1           0x18449
#define A6XX_CX_DBGC_PERF_ATB_DRAIN_CMD                 0x1844A
#define A6XX_CX_DBGC_ECO_CNTL                           0x18450
#define A6XX_CX_DBGC_AHB_DBG_CNTL                       0x18451

/* GMU control registers */
#define A6XX_GPU_GMU_GX_SPTPRAC_CLOCK_CONTROL   0x1A880
#define A6XX_GMU_GX_SPTPRAC_POWER_CONTROL	0x1A881
#define A6XX_GMU_CM3_ITCM_START			0x1B400
#define A6XX_GMU_CM3_DTCM_START			0x1C400
#define A6XX_GMU_NMI_CONTROL_STATUS		0x1CBF0
#define A6XX_GMU_BOOT_SLUMBER_OPTION		0x1CBF8
#define A6XX_GMU_GX_VOTE_IDX			0x1CBF9
#define A6XX_GMU_MX_VOTE_IDX			0x1CBFA
#define A6XX_GMU_DCVS_ACK_OPTION		0x1CBFC
#define A6XX_GMU_DCVS_PERF_SETTING		0x1CBFD
#define A6XX_GMU_DCVS_BW_SETTING		0x1CBFE
#define A6XX_GMU_DCVS_RETURN			0x1CBFF
#define A6XX_GMU_ICACHE_CONFIG			0x1F400
#define A6XX_GMU_DCACHE_CONFIG			0x1F401
#define A6XX_GMU_SYS_BUS_CONFIG			0x1F40F
#define A6XX_GMU_CM3_SYSRESET			0x1F800
#define A6XX_GMU_CM3_BOOT_CONFIG		0x1F801
#define A6XX_GMU_CX_GMU_WFI_CONFIG		0x1F802
#define A6XX_GMU_CX_GMU_WDOG_CTRL		0x1F813
#define A6XX_GMU_CM3_FW_BUSY			0x1F81A
#define A6XX_GMU_CM3_FW_INIT_RESULT		0x1F81C
#define A6XX_GMU_CM3_CFG			0x1F82D
#define A6XX_GMU_CX_GMU_POWER_COUNTER_ENABLE	0x1F840
#define A6XX_GMU_CX_GMU_POWER_COUNTER_SELECT_0	0x1F841
#define A6XX_GMU_CX_GMU_POWER_COUNTER_SELECT_1	0x1F842
#define A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_0_L	0x1F844
#define A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_0_H	0x1F845
#define A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_1_L	0x1F846
#define A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_1_H	0x1F847
#define A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_2_L	0x1F848
#define A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_2_H	0x1F849
#define A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_3_L	0x1F84A
#define A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_3_H	0x1F84B
#define A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_4_L	0x1F84C
#define A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_4_H	0x1F84D
#define A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_5_L	0x1F84E
#define A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_5_H	0x1F84F
#define A6XX_GMU_CX_GMU_ALWAYS_ON_COUNTER_L	0x1F888
#define A6XX_GMU_CX_GMU_ALWAYS_ON_COUNTER_H	0x1F889
#define A6XX_GMU_PWR_COL_INTER_FRAME_CTRL	0x1F8C0
#define A6XX_GMU_PWR_COL_INTER_FRAME_HYST	0x1F8C1
#define A6XX_GMU_PWR_COL_SPTPRAC_HYST		0x1F8C2
#define A6XX_GMU_SPTPRAC_PWR_CLK_STATUS		0x1F8D0
#define A6XX_GMU_GPU_NAP_CTRL			0x1F8E4
#define A6XX_GMU_RPMH_CTRL			0x1F8E8
#define A6XX_GMU_RPMH_HYST_CTRL			0x1F8E9
#define A6XX_GPU_GMU_CX_GMU_RPMH_POWER_STATE    0x1F8EC
#define A6XX_GPU_GMU_CX_GMU_PWR_COL_CP_MSG      0x1F900
#define A6XX_GPU_GMU_CX_GMU_PWR_COL_CP_RESP     0x1F901
#define A6XX_GMU_BOOT_KMD_LM_HANDSHAKE		0x1F9F0
#define A6XX_GMU_LLM_GLM_SLEEP_CTRL		0x1F957
#define A6XX_GMU_LLM_GLM_SLEEP_STATUS		0x1F958

/* HFI registers*/
#define A6XX_GMU_ALWAYS_ON_COUNTER_L		0x1F888
#define A6XX_GMU_ALWAYS_ON_COUNTER_H		0x1F889
#define A6XX_GMU_GMU_PWR_COL_KEEPALIVE		0x1F8C3
#define A6XX_GMU_HFI_CTRL_STATUS		0x1F980
#define A6XX_GMU_HFI_VERSION_INFO		0x1F981
#define A6XX_GMU_HFI_SFR_ADDR			0x1F982
#define A6XX_GMU_HFI_MMAP_ADDR			0x1F983
#define A6XX_GMU_HFI_QTBL_INFO			0x1F984
#define A6XX_GMU_HFI_QTBL_ADDR			0x1F985
#define A6XX_GMU_HFI_CTRL_INIT			0x1F986
#define A6XX_GMU_GMU2HOST_INTR_SET		0x1F990
#define A6XX_GMU_GMU2HOST_INTR_CLR		0x1F991
#define A6XX_GMU_GMU2HOST_INTR_INFO		0x1F992
#define A6XX_GMU_GMU2HOST_INTR_MASK		0x1F993
#define A6XX_GMU_HOST2GMU_INTR_SET		0x1F994
#define A6XX_GMU_HOST2GMU_INTR_CLR		0x1F995
#define A6XX_GMU_HOST2GMU_INTR_RAW_INFO		0x1F996
#define A6XX_GMU_HOST2GMU_INTR_EN_0		0x1F997
#define A6XX_GMU_HOST2GMU_INTR_EN_1		0x1F998
#define A6XX_GMU_HOST2GMU_INTR_EN_2		0x1F999
#define A6XX_GMU_HOST2GMU_INTR_EN_3		0x1F99A
#define A6XX_GMU_HOST2GMU_INTR_INFO_0		0x1F99B
#define A6XX_GMU_HOST2GMU_INTR_INFO_1		0x1F99C
#define A6XX_GMU_HOST2GMU_INTR_INFO_2		0x1F99D
#define A6XX_GMU_HOST2GMU_INTR_INFO_3		0x1F99E
#define A6XX_GMU_GENERAL_0			0x1F9C5
#define A6XX_GMU_GENERAL_1			0x1F9C6
#define A6XX_GMU_GENERAL_6			0x1F9CB
#define A6XX_GMU_GENERAL_7			0x1F9CC

/* ISENSE registers */
#define A6XX_GMU_ISENSE_CTRL			0x1F95D
#define A6XX_GPU_GMU_CX_GMU_ISENSE_CTRL		0x1f95d
#define A6XX_GPU_CS_ENABLE_REG			0x23120

/* LM registers */
#define A6XX_GPU_GMU_CX_GMU_PWR_THRESHOLD       0x1F94D

/* FAL10 veto register */
#define A6XX_GPU_GMU_CX_GMU_CX_FAL_INTF         0x1F8F0

#define A6XX_GMU_AO_INTERRUPT_EN		0x23B03
#define A6XX_GMU_AO_HOST_INTERRUPT_CLR		0x23B04
#define A6XX_GMU_AO_HOST_INTERRUPT_STATUS	0x23B05
#define A6XX_GMU_AO_HOST_INTERRUPT_MASK		0x23B06
#define A6XX_GPU_GMU_AO_GMU_CGC_MODE_CNTL       0x23B09
#define A6XX_GPU_GMU_AO_GMU_CGC_DELAY_CNTL      0x23B0A
#define A6XX_GPU_GMU_AO_GMU_CGC_HYST_CNTL       0x23B0B
#define A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS	0x23B0C
#define A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS2	0x23B0D
#define A6XX_GPU_GMU_AO_GPU_CX_BUSY_MASK	0x23B0E
#define A6XX_GMU_AO_AHB_FENCE_CTRL		0x23B10
#define A6XX_GMU_AHB_FENCE_STATUS		0x23B13
#define A6XX_GMU_AHB_FENCE_STATUS_CLR           0x23B14
#define A6XX_GMU_RBBM_INT_UNMASKED_STATUS	0x23B15
#define A6XX_GMU_AO_SPARE_CNTL			0x23B16

/* RGMU GLM registers */
#define A6XX_GMU_AO_RGMU_GLM_SLEEP_CTRL		0x23B80
#define A6XX_GMU_AO_RGMU_GLM_SLEEP_STATUS	0x23B81
#define A6XX_GMU_AO_RGMU_GLM_HW_CRC_DISABLE	0x23B82

/* GMU RSC control registers */
#define A6XX_GMU_RSCC_CONTROL_REQ		0x23B07
#define A6XX_GMU_RSCC_CONTROL_ACK		0x23B08

/* FENCE control registers */
#define A6XX_GMU_AHB_FENCE_RANGE_0		0x23B11
#define A6XX_GMU_AHB_FENCE_RANGE_1		0x23B12

/* GPUCC registers */
#define A6XX_GPU_CC_GX_GDSCR                   0x24403
#define A6XX_GPU_CC_GX_DOMAIN_MISC		0x24542
#define A6XX_GPU_CC_CX_GDSCR                   0x2441B

/* GPU RSC sequencer registers */
#define A6XX_GPU_RSCC_RSC_STATUS0_DRV0			0x00004
#define A6XX_RSCC_PDC_SEQ_START_ADDR			0x00008
#define A6XX_RSCC_PDC_MATCH_VALUE_LO			0x00009
#define A6XX_RSCC_PDC_MATCH_VALUE_HI			0x0000A
#define A6XX_RSCC_PDC_SLAVE_ID_DRV0			0x0000B
#define A6XX_RSCC_HIDDEN_TCS_CMD0_ADDR			0x0000D
#define A6XX_RSCC_HIDDEN_TCS_CMD0_DATA			0x0000E
#define A6XX_RSCC_TIMESTAMP_UNIT0_TIMESTAMP_L_DRV0	0x00082
#define A6XX_RSCC_TIMESTAMP_UNIT0_TIMESTAMP_H_DRV0	0x00083
#define A6XX_RSCC_TIMESTAMP_UNIT1_EN_DRV0		0x00089
#define A6XX_RSCC_TIMESTAMP_UNIT1_OUTPUT_DRV0		0x0008C
#define A6XX_RSCC_OVERRIDE_START_ADDR			0x00100
#define A6XX_RSCC_SEQ_BUSY_DRV0				0x00101
#define A6XX_RSCC_SEQ_MEM_0_DRV0			0x00180
#define A6XX_RSCC_TCS0_DRV0_STATUS			0x00346
#define A6XX_RSCC_TCS1_DRV0_STATUS                      0x003EE
#define A6XX_RSCC_TCS2_DRV0_STATUS                      0x00496
#define A6XX_RSCC_TCS3_DRV0_STATUS                      0x0053E

/* GPU PDC sequencer registers in AOSS.RPMh domain */
#define PDC_GPU_ENABLE_PDC			0x1140
#define PDC_GPU_SEQ_START_ADDR			0x1148
#define PDC_GPU_TCS0_CONTROL			0x1540
#define PDC_GPU_TCS0_CMD_ENABLE_BANK		0x1541
#define PDC_GPU_TCS0_CMD_WAIT_FOR_CMPL_BANK	0x1542
#define PDC_GPU_TCS0_CMD0_MSGID			0x1543
#define PDC_GPU_TCS0_CMD0_ADDR			0x1544
#define PDC_GPU_TCS0_CMD0_DATA			0x1545
#define PDC_GPU_TCS1_CONTROL			0x1572
#define PDC_GPU_TCS1_CMD_ENABLE_BANK		0x1573
#define PDC_GPU_TCS1_CMD_WAIT_FOR_CMPL_BANK	0x1574
#define PDC_GPU_TCS1_CMD0_MSGID			0x1575
#define PDC_GPU_TCS1_CMD0_ADDR			0x1576
#define PDC_GPU_TCS1_CMD0_DATA			0x1577
#define PDC_GPU_TCS2_CONTROL			0x15A4
#define PDC_GPU_TCS2_CMD_ENABLE_BANK		0x15A5
#define PDC_GPU_TCS2_CMD_WAIT_FOR_CMPL_BANK	0x15A6
#define PDC_GPU_TCS2_CMD0_MSGID			0x15A7
#define PDC_GPU_TCS2_CMD0_ADDR			0x15A8
#define PDC_GPU_TCS2_CMD0_DATA			0x15A9
#define PDC_GPU_TCS3_CONTROL			0x15D6
#define PDC_GPU_TCS3_CMD_ENABLE_BANK		0x15D7
#define PDC_GPU_TCS3_CMD_WAIT_FOR_CMPL_BANK	0x15D8
#define PDC_GPU_TCS3_CMD0_MSGID			0x15D9
#define PDC_GPU_TCS3_CMD0_ADDR			0x15DA
#define PDC_GPU_TCS3_CMD0_DATA			0x15DB

/*
 * Legacy DTSI used an offset from the start of the PDC resource
 * for PDC SEQ programming. We are now using PDC subsections so
 * start the PDC SEQ offset at zero.
 */
#define PDC_GPU_SEQ_MEM_0			0x0

/*
 * Legacy RSCC register range was a part of the GMU register space
 * now we are using a separate section for RSCC regsiters. Add the
 * offset for backward compatibility.
 */
#define RSCC_OFFSET_LEGACY			0x23400

/* RGMU(PCC) registers in A6X_GMU_CX_0_NON_CONTEXT_DEC domain */
#define A6XX_RGMU_CX_INTR_GEN_EN		0x1F80F
#define A6XX_RGMU_CX_RGMU_TIMER0		0x1F834
#define A6XX_RGMU_CX_RGMU_TIMER1		0x1F835
#define A6XX_RGMU_CX_PCC_CTRL			0x1F838
#define A6XX_RGMU_CX_PCC_INIT_RESULT		0x1F839
#define A6XX_RGMU_CX_PCC_BKPT_CFG		0x1F83A
#define A6XX_RGMU_CX_PCC_BKPT_ADDR		0x1F83B
#define A6XX_RGMU_CX_PCC_STATUS			0x1F83C
#define A6XX_RGMU_CX_PCC_DEBUG			0x1F83D

/* GPU CX_MISC registers */
#define A6XX_GPU_CX_MISC_SYSTEM_CACHE_CNTL_0	0x1
#define A6XX_GPU_CX_MISC_SYSTEM_CACHE_CNTL_1	0x2
#define A6XX_LLC_NUM_GPU_SCIDS			5
#define A6XX_GPU_LLC_SCID_NUM_BITS		5
#define A6XX_GPU_LLC_SCID_MASK \
	((1 << (A6XX_LLC_NUM_GPU_SCIDS * A6XX_GPU_LLC_SCID_NUM_BITS)) - 1)
#define A6XX_GPUHTW_LLC_SCID_SHIFT		25
#define A6XX_GPUHTW_LLC_SCID_MASK \
	(((1 << A6XX_GPU_LLC_SCID_NUM_BITS) - 1) << A6XX_GPUHTW_LLC_SCID_SHIFT)

#endif /* _A6XX_REG_H */

/* IFPC & Preemption static powerup restore list */
static u32 a6xx_pwrup_reglist[] = {
	A6XX_VSC_ADDR_MODE_CNTL,
	A6XX_GRAS_ADDR_MODE_CNTL,
	A6XX_RB_ADDR_MODE_CNTL,
	A6XX_PC_ADDR_MODE_CNTL,
	A6XX_HLSQ_ADDR_MODE_CNTL,
	A6XX_VFD_ADDR_MODE_CNTL,
	A6XX_VPC_ADDR_MODE_CNTL,
	A6XX_UCHE_ADDR_MODE_CNTL,
	A6XX_SP_ADDR_MODE_CNTL,
	A6XX_TPL1_ADDR_MODE_CNTL,
	A6XX_UCHE_WRITE_RANGE_MAX_LO,
	A6XX_UCHE_WRITE_RANGE_MAX_HI,
	A6XX_UCHE_TRAP_BASE_LO,
	A6XX_UCHE_TRAP_BASE_HI,
	A6XX_UCHE_WRITE_THRU_BASE_LO,
	A6XX_UCHE_WRITE_THRU_BASE_HI,
	A6XX_UCHE_GMEM_RANGE_MIN_LO,
	A6XX_UCHE_GMEM_RANGE_MIN_HI,
	A6XX_UCHE_GMEM_RANGE_MAX_LO,
	A6XX_UCHE_GMEM_RANGE_MAX_HI,
	A6XX_UCHE_FILTER_CNTL,
	A6XX_UCHE_CACHE_WAYS,
	A6XX_UCHE_MODE_CNTL,
	A6XX_RB_NC_MODE_CNTL,
	A6XX_TPL1_NC_MODE_CNTL,
	A6XX_SP_NC_MODE_CNTL,
	A6XX_PC_DBG_ECO_CNTL,
	A6XX_RB_CONTEXT_SWITCH_GMEM_SAVE_RESTORE,
};

/* IFPC only static powerup restore list */
static u32 a6xx_ifpc_pwrup_reglist[] = {
	A6XX_CP_CHICKEN_DBG,
	A6XX_CP_DBG_ECO_CNTL,
	A6XX_CP_PROTECT_CNTL,
	A6XX_CP_PROTECT_REG,
	A6XX_CP_PROTECT_REG+1,
	A6XX_CP_PROTECT_REG+2,
	A6XX_CP_PROTECT_REG+3,
	A6XX_CP_PROTECT_REG+4,
	A6XX_CP_PROTECT_REG+5,
	A6XX_CP_PROTECT_REG+6,
	A6XX_CP_PROTECT_REG+7,
	A6XX_CP_PROTECT_REG+8,
	A6XX_CP_PROTECT_REG+9,
	A6XX_CP_PROTECT_REG+10,
	A6XX_CP_PROTECT_REG+11,
	A6XX_CP_PROTECT_REG+12,
	A6XX_CP_PROTECT_REG+13,
	A6XX_CP_PROTECT_REG+14,
	A6XX_CP_PROTECT_REG+15,
	A6XX_CP_PROTECT_REG+16,
	A6XX_CP_PROTECT_REG+17,
	A6XX_CP_PROTECT_REG+18,
	A6XX_CP_PROTECT_REG+19,
	A6XX_CP_PROTECT_REG+20,
	A6XX_CP_PROTECT_REG+21,
	A6XX_CP_PROTECT_REG+22,
	A6XX_CP_PROTECT_REG+23,
	A6XX_CP_PROTECT_REG+24,
	A6XX_CP_PROTECT_REG+25,
	A6XX_CP_PROTECT_REG+26,
	A6XX_CP_PROTECT_REG+27,
	A6XX_CP_PROTECT_REG+28,
	A6XX_CP_PROTECT_REG+29,
	A6XX_CP_PROTECT_REG+30,
	A6XX_CP_PROTECT_REG+31,
	A6XX_CP_AHB_CNTL,
};

/* Applicable to a620 and a650 */
static u32 a650_ifpc_pwrup_reglist[] = {
	A6XX_CP_PROTECT_REG+32,
	A6XX_CP_PROTECT_REG+33,
	A6XX_CP_PROTECT_REG+34,
	A6XX_CP_PROTECT_REG+35,
	A6XX_CP_PROTECT_REG+36,
	A6XX_CP_PROTECT_REG+37,
	A6XX_CP_PROTECT_REG+38,
	A6XX_CP_PROTECT_REG+39,
	A6XX_CP_PROTECT_REG+40,
	A6XX_CP_PROTECT_REG+41,
	A6XX_CP_PROTECT_REG+42,
	A6XX_CP_PROTECT_REG+43,
	A6XX_CP_PROTECT_REG+44,
	A6XX_CP_PROTECT_REG+45,
	A6XX_CP_PROTECT_REG+46,
	A6XX_CP_PROTECT_REG+47,
};

static u32 a650_pwrup_reglist[] = {
	A6XX_RBBM_GBIF_CLIENT_QOS_CNTL,
	A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_0,
	A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_1,
	A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_2,
	A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_3,
	A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_4,
};

/* Applicable to a640 and a680 */
static u32 a640_pwrup_reglist[] = {
	A6XX_RBBM_GBIF_CLIENT_QOS_CNTL,
};

/* Applicable to a630 */
static u32 a630_pwrup_reglist[] = {
	A6XX_RBBM_VBIF_CLIENT_QOS_CNTL,
};

/* Applicable to a615 family */
static u32 a615_pwrup_reglist[] = {
	A6XX_RBBM_VBIF_CLIENT_QOS_CNTL,
	A6XX_UCHE_GBIF_GX_CONFIG,
};

/* Applicable to a612 */
static u32 a612_pwrup_reglist[] = {
	A6XX_RBBM_GBIF_CLIENT_QOS_CNTL,
	A6XX_RBBM_PERFCTR_CNTL,
};

static void _update_always_on_regs(struct adreno_device *adreno_dev)
{
	struct adreno_gpudev *gpudev = ADRENO_GPU_DEVICE(adreno_dev);
	unsigned int *const regs = gpudev->reg_offsets->offsets;

	regs[ADRENO_REG_RBBM_ALWAYSON_COUNTER_LO] =
		A6XX_CP_ALWAYS_ON_COUNTER_LO;
	regs[ADRENO_REG_RBBM_ALWAYSON_COUNTER_HI] =
		A6XX_CP_ALWAYS_ON_COUNTER_HI;
}

static void a6xx_init(struct adreno_device *adreno_dev)
{
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);

	adreno_dev->highest_bank_bit = 13;
	of_property_read_u32(device->pdev->dev.of_node,
		"qcom,highest-bank-bit", &adreno_dev->highest_bank_bit);

	if (WARN(adreno_dev->highest_bank_bit < 13 ||
			adreno_dev->highest_bank_bit > 16,
			"The highest-bank-bit property is invalid\n"))
		adreno_dev->highest_bank_bit =
			clamp_t(unsigned int, adreno_dev->highest_bank_bit,
				13, 16);

	/* LP DDR4 highest bank bit is different and needs to be overridden */
	if (adreno_is_a650(adreno_dev) && of_fdt_get_ddrtype() == 0x7)
		adreno_dev->highest_bank_bit = 15;
	else if ((adreno_is_a610(adreno_dev) || adreno_is_a702(adreno_dev))
			&& of_fdt_get_ddrtype() == 0x5) {
		/*
		 * LPDDR3 has multiple different highest bank bit value
		 * based on different DDR density. Query this value from
		 * FDT, in case FDT returns error fallback to value in GPU
		 * DT node.
		 */
		int hbb = of_fdt_get_ddrhbb(0, 0);

		if (hbb > 0)
			adreno_dev->highest_bank_bit = hbb;
	}

	a6xx_crashdump_init(adreno_dev);

	/*
	 * If the GMU is not enabled, rewrite the offset for the always on
	 * counters to point to the CP always on instead of GMU always on
	 */
	if (!gmu_core_isenabled(device))
		_update_always_on_regs(adreno_dev);

	kgsl_allocate_global(device, &adreno_dev->pwrup_reglist,
		PAGE_SIZE, 0, KGSL_MEMDESC_CONTIG | KGSL_MEMDESC_PRIVILEGED,
		"powerup_register_list");
}

static void a6xx_protect_init(struct adreno_device *adreno_dev)
{
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);
	const struct adreno_a6xx_core *a6xx_core = to_a6xx_core(adreno_dev);
	const struct a6xx_protected_regs *regs = a6xx_core->protected_regs;
	int i;

	/*
	 * Enable access protection to privileged registers, fault on an access
	 * protect violation and select the last span to protect from the start
	 * address all the way to the end of the register address space
	 */
	kgsl_regwrite(device, A6XX_CP_PROTECT_CNTL,
		(1 << 0) | (1 << 1) | (1 << 3));

	/* Program each register defined by the core definition */
	for (i = 0; regs[i].reg; i++) {
		u32 count;

		/*
		 * This is the offset of the end register as counted from the
		 * start, i.e. # of registers in the range - 1
		 */
		count = regs[i].end - regs[i].start;

		kgsl_regwrite(device, regs[i].reg,
			(regs[i].start & 0x3ffff) | ((count & 0x1fff) << 18) |
			(regs[i].noaccess << 31));
	}
}

static void a6xx_enable_64bit(struct adreno_device *adreno_dev)
{
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);

	kgsl_regwrite(device, A6XX_CP_ADDR_MODE_CNTL, 0x1);
	kgsl_regwrite(device, A6XX_VSC_ADDR_MODE_CNTL, 0x1);
	kgsl_regwrite(device, A6XX_GRAS_ADDR_MODE_CNTL, 0x1);
	kgsl_regwrite(device, A6XX_RB_ADDR_MODE_CNTL, 0x1);
	kgsl_regwrite(device, A6XX_PC_ADDR_MODE_CNTL, 0x1);
	kgsl_regwrite(device, A6XX_HLSQ_ADDR_MODE_CNTL, 0x1);
	kgsl_regwrite(device, A6XX_VFD_ADDR_MODE_CNTL, 0x1);
	kgsl_regwrite(device, A6XX_VPC_ADDR_MODE_CNTL, 0x1);
	kgsl_regwrite(device, A6XX_UCHE_ADDR_MODE_CNTL, 0x1);
	kgsl_regwrite(device, A6XX_SP_ADDR_MODE_CNTL, 0x1);
	kgsl_regwrite(device, A6XX_TPL1_ADDR_MODE_CNTL, 0x1);
	kgsl_regwrite(device, A6XX_RBBM_SECVID_TSB_ADDR_MODE_CNTL, 0x1);
}

static inline unsigned int
__get_rbbm_clock_cntl_on(struct adreno_device *adreno_dev)
{
	if (adreno_is_a630(adreno_dev))
		return 0x8AA8AA02;
	else if (adreno_is_a612(adreno_dev) || adreno_is_a610(adreno_dev))
		return 0xAAA8AA82;
	else if (adreno_is_a702(adreno_dev))
		return 0xAAAAAA82;
	else
		return 0x8AA8AA82;
}

static inline unsigned int
__get_gmu_ao_cgc_mode_cntl(struct adreno_device *adreno_dev)
{
	if (adreno_is_a612(adreno_dev))
		return 0x00000022;
	else if (adreno_is_a615_family(adreno_dev))
		return 0x00000222;
	else
		return 0x00020202;
}

static inline unsigned int
__get_gmu_ao_cgc_delay_cntl(struct adreno_device *adreno_dev)
{
	if (adreno_is_a612(adreno_dev))
		return 0x00000011;
	else if (adreno_is_a615_family(adreno_dev))
		return 0x00000111;
	else
		return 0x00010111;
}

static inline unsigned int
__get_gmu_ao_cgc_hyst_cntl(struct adreno_device *adreno_dev)
{
	if (adreno_is_a612(adreno_dev))
		return 0x00000055;
	else if (adreno_is_a615_family(adreno_dev))
		return 0x00000555;
	else
		return 0x00005555;
}

static unsigned int __get_gmu_wfi_config(struct adreno_device *adreno_dev)
{
	if (adreno_is_a620(adreno_dev) || adreno_is_a640(adreno_dev) ||
		adreno_is_a650(adreno_dev))
		return 0x00000002;

	return 0x00000000;
}

static void a6xx_hwcg_set(struct adreno_device *adreno_dev, bool on)
{
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);
	const struct adreno_a6xx_core *a6xx_core = to_a6xx_core(adreno_dev);
	unsigned int value;
	int i;

	if (!test_bit(ADRENO_HWCG_CTRL, &adreno_dev->pwrctrl_flag))
		on = false;

	if (gmu_core_isenabled(device)) {
		gmu_core_regwrite(device, A6XX_GPU_GMU_AO_GMU_CGC_MODE_CNTL,
			on ? __get_gmu_ao_cgc_mode_cntl(adreno_dev) : 0);
		gmu_core_regwrite(device, A6XX_GPU_GMU_AO_GMU_CGC_DELAY_CNTL,
			on ? __get_gmu_ao_cgc_delay_cntl(adreno_dev) : 0);
		gmu_core_regwrite(device, A6XX_GPU_GMU_AO_GMU_CGC_HYST_CNTL,
			on ? __get_gmu_ao_cgc_hyst_cntl(adreno_dev) : 0);
		gmu_core_regwrite(device, A6XX_GMU_CX_GMU_WFI_CONFIG,
			on ? __get_gmu_wfi_config(adreno_dev) : 0);
	}

	kgsl_regread(device, A6XX_RBBM_CLOCK_CNTL, &value);

	if (value == __get_rbbm_clock_cntl_on(adreno_dev) && on)
		return;

	if (value == 0 && !on)
		return;

	/*
	 * Disable SP clock before programming HWCG registers.
	 * A612 and A610 GPU is not having the GX power domain.
	 * Hence skip GMU_GX registers for A12 and A610.
	 */

	if (gmu_core_isenabled(device) && !adreno_is_a612(adreno_dev) &&
		!adreno_is_a610(adreno_dev) && !(adreno_is_a702(adreno_dev)))
		gmu_core_regrmw(device,
			A6XX_GPU_GMU_GX_SPTPRAC_CLOCK_CONTROL, 1, 0);

	for (i = 0; i < a6xx_core->hwcg_count; i++)
		kgsl_regwrite(device, a6xx_core->hwcg[i].offset,
			on ? a6xx_core->hwcg[i].value : 0);

	/*
	 * Enable SP clock after programming HWCG registers.
	 * A612 and A610 GPU is not having the GX power domain.
	 * Hence skip GMU_GX registers for A612.
	 */
	if (gmu_core_isenabled(device) && !adreno_is_a612(adreno_dev) &&
		!adreno_is_a610(adreno_dev) && !adreno_is_a702(adreno_dev))
		gmu_core_regrmw(device,
			A6XX_GPU_GMU_GX_SPTPRAC_CLOCK_CONTROL, 0, 1);

	/* enable top level HWCG */
	kgsl_regwrite(device, A6XX_RBBM_CLOCK_CNTL,
		on ? __get_rbbm_clock_cntl_on(adreno_dev) : 0);
}

struct a6xx_reglist_list {
	u32 *regs;
	u32 count;
};

#define REGLIST(_a) \
	 (struct a6xx_reglist_list) { .regs = _a, .count = ARRAY_SIZE(_a), }

static void a6xx_patch_pwrup_reglist(struct adreno_device *adreno_dev)
{
	struct a6xx_reglist_list reglist[4];
	void *ptr = adreno_dev->pwrup_reglist.hostptr;
	struct cpu_gpu_lock *lock = ptr;
	int items = 0, i, j;
	u32 *dest = ptr + sizeof(*lock);
	u16 list_offset = 0;

	/* Static IFPC-only registers */
	reglist[items] = REGLIST(a6xx_ifpc_pwrup_reglist);
	list_offset += reglist[items++].count * 2;

	if (adreno_is_a650_family(adreno_dev)) {
		reglist[items] = REGLIST(a650_ifpc_pwrup_reglist);
		list_offset += reglist[items++].count * 2;
	}

	/* Static IFPC + preemption registers */
	reglist[items++] = REGLIST(a6xx_pwrup_reglist);

	/* Add target specific registers */
	if (adreno_is_a612(adreno_dev))
		reglist[items++] = REGLIST(a612_pwrup_reglist);
	else if (adreno_is_a615_family(adreno_dev))
		reglist[items++] = REGLIST(a615_pwrup_reglist);
	else if (adreno_is_a630(adreno_dev))
		reglist[items++] = REGLIST(a630_pwrup_reglist);
	else if (adreno_is_a640(adreno_dev) || adreno_is_a680(adreno_dev))
		reglist[items++] = REGLIST(a640_pwrup_reglist);
	else if (adreno_is_a650(adreno_dev) || adreno_is_a620(adreno_dev))
		reglist[items++] = REGLIST(a650_pwrup_reglist);

	/*
	 * For each entry in each of the lists, write the offset and the current
	 * register value into the GPU buffer
	 */
	for (i = 0; i < items; i++) {
		u32 *r = reglist[i].regs;

		for (j = 0; j < reglist[i].count; j++) {
			*dest++ = r[j];
			kgsl_regread(KGSL_DEVICE(adreno_dev), r[j], dest++);
		}

		lock->list_length += reglist[i].count * 2;
	}

	/*
	 * The overall register list is composed of
	 * 1. Static IFPC-only registers
	 * 2. Static IFPC + preemption registers
	 * 3. Dynamic IFPC + preemption registers (ex: perfcounter selects)
	 *
	 * The CP views the second and third entries as one dynamic list
	 * starting from list_offset. list_length should be the total dwords in
	 * all the lists and list_offset should be specified as the size in
	 * dwords of the first entry in the list.
	 */
	lock->list_offset = list_offset;
}

/*
 * a6xx_start() - Device start
 * @adreno_dev: Pointer to adreno device
 *
 * a6xx device start
 */
static void a6xx_start(struct adreno_device *adreno_dev)
{
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);
	const struct adreno_a6xx_core *a6xx_core = to_a6xx_core(adreno_dev);
	unsigned int bit, lower_bit, mal, mode, upper_bit;
	unsigned int uavflagprd_inv;
	unsigned int amsbc = 0;
	unsigned int rgb565_predicator = 0;
	static bool patch_reglist;

	/* runtime adjust callbacks based on feature sets */
	if (!gmu_core_isenabled(device))
		/* Legacy idle management if gmu is disabled */
		ADRENO_GPU_DEVICE(adreno_dev)->hw_isidle = NULL;
	/* enable hardware clockgating */
	a6xx_hwcg_set(adreno_dev, true);

	/* Set up VBIF registers from the GPU core definition */
	adreno_reglist_write(adreno_dev, a6xx_core->vbif,
		a6xx_core->vbif_count);

	if (ADRENO_QUIRK(adreno_dev, ADRENO_QUIRK_LIMIT_UCHE_GBIF_RW))
		kgsl_regwrite(device, A6XX_UCHE_GBIF_GX_CONFIG, 0x10200F9);

	/* Make all blocks contribute to the GPU BUSY perf counter */
	kgsl_regwrite(device, A6XX_RBBM_PERFCTR_GPU_BUSY_MASKED, 0xFFFFFFFF);

	/*
	 * Set UCHE_WRITE_THRU_BASE to the UCHE_TRAP_BASE effectively
	 * disabling L2 bypass
	 */
	kgsl_regwrite(device, A6XX_UCHE_WRITE_RANGE_MAX_LO, 0xffffffc0);
	kgsl_regwrite(device, A6XX_UCHE_WRITE_RANGE_MAX_HI, 0x0001ffff);
	kgsl_regwrite(device, A6XX_UCHE_TRAP_BASE_LO, 0xfffff000);
	kgsl_regwrite(device, A6XX_UCHE_TRAP_BASE_HI, 0x0001ffff);
	kgsl_regwrite(device, A6XX_UCHE_WRITE_THRU_BASE_LO, 0xfffff000);
	kgsl_regwrite(device, A6XX_UCHE_WRITE_THRU_BASE_HI, 0x0001ffff);

	/*
	 * Some A6xx targets no longer use a programmed UCHE GMEM base
	 * address so only write the registers if this address is
	 * non zero.
	 */
	if (adreno_dev->uche_gmem_base) {
		kgsl_regwrite(device, A6XX_UCHE_GMEM_RANGE_MIN_LO,
				adreno_dev->uche_gmem_base);
		kgsl_regwrite(device, A6XX_UCHE_GMEM_RANGE_MIN_HI, 0x0);
		kgsl_regwrite(device, A6XX_UCHE_GMEM_RANGE_MAX_LO,
				adreno_dev->uche_gmem_base +
				adreno_dev->gpucore->gmem_size - 1);
		kgsl_regwrite(device, A6XX_UCHE_GMEM_RANGE_MAX_HI, 0x0);
	}

	kgsl_regwrite(device, A6XX_UCHE_FILTER_CNTL, 0x804);
	kgsl_regwrite(device, A6XX_UCHE_CACHE_WAYS, 0x4);

	if (adreno_is_a640_family(adreno_dev) ||
		adreno_is_a650_family(adreno_dev)) {
		kgsl_regwrite(device, A6XX_CP_ROQ_THRESHOLDS_2, 0x02000140);
		kgsl_regwrite(device, A6XX_CP_ROQ_THRESHOLDS_1, 0x8040362C);
	} else if (adreno_is_a612(adreno_dev) || adreno_is_a610(adreno_dev) ||
			adreno_is_a702(adreno_dev)) {
		kgsl_regwrite(device, A6XX_CP_ROQ_THRESHOLDS_2, 0x00800060);
		kgsl_regwrite(device, A6XX_CP_ROQ_THRESHOLDS_1, 0x40201b16);
	} else {
		kgsl_regwrite(device, A6XX_CP_ROQ_THRESHOLDS_2, 0x010000C0);
		kgsl_regwrite(device, A6XX_CP_ROQ_THRESHOLDS_1, 0x8040362C);
	}

	if (adreno_is_a612(adreno_dev) || adreno_is_a610(adreno_dev)) {
		/* For A612 and A610 Mem pool size is reduced to 48 */
		kgsl_regwrite(device, A6XX_CP_MEM_POOL_SIZE, 48);
		kgsl_regwrite(device, A6XX_CP_MEM_POOL_DBG_ADDR, 47);
	} else if (adreno_is_a702(adreno_dev)) {
		kgsl_regwrite(device, A6XX_CP_MEM_POOL_SIZE, 64);
		kgsl_regwrite(device, A6XX_CP_MEM_POOL_DBG_ADDR, 63);
	} else {
		kgsl_regwrite(device, A6XX_CP_MEM_POOL_SIZE, 128);
	}

	/* Setting the primFifo thresholds values */
	kgsl_regwrite(device, A6XX_PC_DBG_ECO_CNTL,
		a6xx_core->prim_fifo_threshold);

	/* Set the AHB default slave response to "ERROR" */
	kgsl_regwrite(device, A6XX_CP_AHB_CNTL, 0x1);

	/* Turn on performance counters */
	kgsl_regwrite(device, A6XX_RBBM_PERFCTR_CNTL, 0x1);

	/* Turn on the IFPC counter (countable 4 on XOCLK4) */
	if (gmu_core_isenabled(device))
		gmu_core_regrmw(device, A6XX_GMU_CX_GMU_POWER_COUNTER_SELECT_1,
			0xff, 0x4);

	/* Turn on GX_MEM retention */
	if (gmu_core_isenabled(device) && adreno_is_a612(adreno_dev)) {
		kgsl_regwrite(device, A6XX_RBBM_BLOCK_GX_RETENTION_CNTL, 0x7FB);
		/* For CP IPC interrupt */
		kgsl_regwrite(device, A6XX_RBBM_INT_2_MASK, 0x00000010);
	}

	if (of_property_read_u32(device->pdev->dev.of_node,
		"qcom,min-access-length", &mal))
		mal = 32;

	if (of_property_read_u32(device->pdev->dev.of_node,
		"qcom,ubwc-mode", &mode))
		mode = 0;

	switch (mode) {
	case KGSL_UBWC_1_0:
		mode = 1;
		break;
	case KGSL_UBWC_2_0:
		mode = 0;
		break;
	case KGSL_UBWC_3_0:
		mode = 0;
		amsbc = 1; /* Only valid for A640 and A680 */
		break;
	case KGSL_UBWC_4_0:
		mode = 0;
		rgb565_predicator = 1;
		amsbc = 1;
		break;
	default:
		break;
	}

	bit = adreno_dev->highest_bank_bit ?
		adreno_dev->highest_bank_bit - 13 : 0;
	lower_bit = bit & 0x3;
	upper_bit = (bit >> 0x2) & 1;
	mal = (mal == 64) ? 1 : 0;

	uavflagprd_inv = (adreno_is_a650_family(adreno_dev)) ? 2 : 0;

	kgsl_regwrite(device, A6XX_RB_NC_MODE_CNTL, (rgb565_predicator << 11)|
				(upper_bit << 10) | (amsbc << 4) | (mal << 3) |
				(lower_bit << 1) | mode);

	kgsl_regwrite(device, A6XX_TPL1_NC_MODE_CNTL, (upper_bit << 4) |
				(mal << 3) | (lower_bit << 1) | mode);

	kgsl_regwrite(device, A6XX_SP_NC_MODE_CNTL, (upper_bit << 10) |
				(mal << 3) | (uavflagprd_inv << 4) |
				(lower_bit << 1) | mode);

	kgsl_regwrite(device, A6XX_UCHE_MODE_CNTL, (mal << 23) |
		(lower_bit << 21));

	kgsl_regwrite(device, A6XX_RBBM_INTERFACE_HANG_INT_CNTL,
				(1 << 30) | a6xx_core->hang_detect_cycles);

	kgsl_regwrite(device, A6XX_UCHE_CLIENT_PF, 1);

	/* Set weights for bicubic filtering */
	if (adreno_is_a650_family(adreno_dev)) {
		kgsl_regwrite(device, A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_0, 0);
		kgsl_regwrite(device, A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_1,
			0x3FE05FF4);
		kgsl_regwrite(device, A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_2,
			0x3FA0EBEE);
		kgsl_regwrite(device, A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_3,
			0x3F5193ED);
		kgsl_regwrite(device, A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_4,
			0x3F0243F0);
	}

	/* Set TWOPASSUSEWFI in A6XX_PC_DBG_ECO_CNTL if requested */
	if (ADRENO_QUIRK(adreno_dev, ADRENO_QUIRK_TWO_PASS_USE_WFI))
		kgsl_regrmw(device, A6XX_PC_DBG_ECO_CNTL, 0, (1 << 8));

	/* Set the bit vccCacheSkipDis=1 to get rid of TSEskip logic */
	if (a6xx_core->disable_tseskip)
		kgsl_regrmw(device, A6XX_PC_DBG_ECO_CNTL, 0, (1 << 9));

	/*
	 * Set the bit HLSQCluster3ContextDis for A702 as HLSQ doesn't
	 * have context buffer for third context
	 */
	if (adreno_is_a702(adreno_dev))
		kgsl_regwrite(device, A6XX_CP_CHICKEN_DBG, (1 << 24));

	/* Enable the GMEM save/restore feature for preemption */
	if (adreno_is_preemption_enabled(adreno_dev))
		kgsl_regwrite(device, A6XX_RB_CONTEXT_SWITCH_GMEM_SAVE_RESTORE,
			0x1);

	/*
	 * Enable GMU power counter 0 to count GPU busy. This is applicable to
	 * all a6xx targets
	 */
	kgsl_regwrite(device, A6XX_GPU_GMU_AO_GPU_CX_BUSY_MASK, 0xff000000);
	kgsl_regrmw(device, A6XX_GMU_CX_GMU_POWER_COUNTER_SELECT_0, 0xff, 0x20);
	kgsl_regwrite(device, A6XX_GMU_CX_GMU_POWER_COUNTER_ENABLE, 0x1);

	a6xx_protect_init(adreno_dev);

	if (!patch_reglist && (adreno_dev->pwrup_reglist.gpuaddr != 0)) {
		a6xx_patch_pwrup_reglist(adreno_dev);
		patch_reglist = true;
	}

	a6xx_preemption_start(adreno_dev);

	/*
	 * We start LM here because we want all the following to be up
	 * 1. GX HS
	 * 2. SPTPRAC
	 * 3. HFI
	 * At this point, we are guaranteed all.
	 */
	gmu_core_dev_enable_lm(device);
}

/*
 * a6xx_zap_load() - Load zap shader
 * @adreno_dev: Pointer to adreno device
 */
static int a6xx_zap_load(struct adreno_device *adreno_dev)
{
	const struct adreno_a6xx_core *a6xx_core = to_a6xx_core(adreno_dev);
	void *zap;
	int ret = 0;

	/* Load the zap shader firmware through PIL if its available */
	if (a6xx_core->zap_name && !adreno_dev->zap_loaded) {
		zap = subsystem_get(a6xx_core->zap_name);

		/* Return error if the zap shader cannot be loaded */
		if (IS_ERR_OR_NULL(zap)) {
			ret = (zap == NULL) ? -ENODEV : PTR_ERR(zap);
			zap = NULL;
			dev_err(adreno_dev->dev.dev,
				"subsystem_get() for zap failed. zap = NULL\n");
		} else {
			adreno_dev->zap_loaded = 1;
			dev_err(adreno_dev->dev.dev,
				"subsystem_get() for zap succeed.\n");
		}
	}

	return ret;
}


/*
 * CP_INIT_MAX_CONTEXT bit tells if the multiple hardware contexts can
 * be used at once of if they should be serialized
 */
#define CP_INIT_MAX_CONTEXT BIT(0)

/* Enables register protection mode */
#define CP_INIT_ERROR_DETECTION_CONTROL BIT(1)

/* Header dump information */
#define CP_INIT_HEADER_DUMP BIT(2) /* Reserved */

/* Default Reset states enabled for PFP and ME */
#define CP_INIT_DEFAULT_RESET_STATE BIT(3)

/* Drawcall filter range */
#define CP_INIT_DRAWCALL_FILTER_RANGE BIT(4)

/* Ucode workaround masks */
#define CP_INIT_UCODE_WORKAROUND_MASK BIT(5)

/*
 * Operation mode mask
 *
 * This ordinal provides the option to disable the
 * save/restore of performance counters across preemption.
 */
#define CP_INIT_OPERATION_MODE_MASK BIT(6)

/* Register initialization list */
#define CP_INIT_REGISTER_INIT_LIST BIT(7)

/* Register initialization list with spinlock */
#define CP_INIT_REGISTER_INIT_LIST_WITH_SPINLOCK BIT(8)

#define CP_INIT_MASK (CP_INIT_MAX_CONTEXT | \
		CP_INIT_ERROR_DETECTION_CONTROL | \
		CP_INIT_HEADER_DUMP | \
		CP_INIT_DEFAULT_RESET_STATE | \
		CP_INIT_UCODE_WORKAROUND_MASK | \
		CP_INIT_OPERATION_MODE_MASK | \
		CP_INIT_REGISTER_INIT_LIST_WITH_SPINLOCK)

static void _set_ordinals(struct adreno_device *adreno_dev,
		unsigned int *cmds, unsigned int count)
{
	unsigned int *start = cmds;

	/* Enabled ordinal mask */
	*cmds++ = CP_INIT_MASK;

	if (CP_INIT_MASK & CP_INIT_MAX_CONTEXT)
		*cmds++ = 0x00000003;

	if (CP_INIT_MASK & CP_INIT_ERROR_DETECTION_CONTROL)
		*cmds++ = 0x20000000;

	if (CP_INIT_MASK & CP_INIT_HEADER_DUMP) {
		/* Header dump address */
		*cmds++ = 0x00000000;
		/* Header dump enable and dump size */
		*cmds++ = 0x00000000;
	}

	if (CP_INIT_MASK & CP_INIT_UCODE_WORKAROUND_MASK)
		*cmds++ = 0x00000000;

	if (CP_INIT_MASK & CP_INIT_OPERATION_MODE_MASK)
		*cmds++ = 0x00000002;

	if (CP_INIT_MASK & CP_INIT_REGISTER_INIT_LIST_WITH_SPINLOCK) {
		uint64_t gpuaddr = adreno_dev->pwrup_reglist.gpuaddr;

		*cmds++ = lower_32_bits(gpuaddr);
		*cmds++ = upper_32_bits(gpuaddr);
		*cmds++ =  0;
	}

	/* Pad rest of the cmds with 0's */
	while ((unsigned int)(cmds - start) < count)
		*cmds++ = 0x0;
}

/*
 * a6xx_send_cp_init() - Initialize ringbuffer
 * @adreno_dev: Pointer to adreno device
 * @rb: Pointer to the ringbuffer of device
 *
 * Submit commands for ME initialization,
 */
static int a6xx_send_cp_init(struct adreno_device *adreno_dev,
			 struct adreno_ringbuffer *rb)
{
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);
	unsigned int *cmds;
	int ret;

	cmds = adreno_ringbuffer_allocspace(rb, 12);
	if (IS_ERR(cmds))
		return PTR_ERR(cmds);

	*cmds++ = cp_type7_packet(CP_ME_INIT, 11);

	_set_ordinals(adreno_dev, cmds, 11);

	ret = adreno_ringbuffer_submit_spin(rb, NULL, 2000);
	if (ret) {
		adreno_spin_idle_debug(adreno_dev,
				"CP initialization failed to idle\n");

		if (!adreno_is_a3xx(adreno_dev))
			kgsl_sharedmem_writel(device, &device->scratch,
					SCRATCH_RPTR_OFFSET(rb->id), 0);
		rb->wptr = 0;
		rb->_wptr = 0;
	}

	return ret;
}

/*
 * Follow the ME_INIT sequence with a preemption yield to allow the GPU to move
 * to a different ringbuffer, if desired
 */
static int _preemption_init(struct adreno_device *adreno_dev,
		struct adreno_ringbuffer *rb, unsigned int *cmds,
		struct kgsl_context *context)
{
	unsigned int *cmds_orig = cmds;

	/* Turn CP protection OFF on legacy targets */
	if (!ADRENO_FEATURE(adreno_dev, ADRENO_APRIV))
		cmds += cp_protected_mode(adreno_dev, cmds, 0);

	*cmds++ = cp_type7_packet(CP_SET_PSEUDO_REGISTER, 6);
	*cmds++ = 1;
	cmds += cp_gpuaddr(adreno_dev, cmds,
			rb->preemption_desc.gpuaddr);

	*cmds++ = 2;
	cmds += cp_gpuaddr(adreno_dev, cmds,
			rb->secure_preemption_desc.gpuaddr);

	/* Turn CP protection back ON */
	if (!ADRENO_FEATURE(adreno_dev, ADRENO_APRIV))
		cmds += cp_protected_mode(adreno_dev, cmds, 1);

	*cmds++ = cp_type7_packet(CP_CONTEXT_SWITCH_YIELD, 4);
	cmds += cp_gpuaddr(adreno_dev, cmds, 0x0);
	*cmds++ = 0;
	/* generate interrupt on preemption completion */
	*cmds++ = 0;

	return cmds - cmds_orig;
}

static int a6xx_post_start(struct adreno_device *adreno_dev)
{
	int ret;
	unsigned int *cmds, *start;
	struct adreno_ringbuffer *rb = adreno_dev->cur_rb;
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);

	if (!adreno_is_preemption_enabled(adreno_dev))
		return 0;

	cmds = adreno_ringbuffer_allocspace(rb, 42);
	if (IS_ERR(cmds)) {
		dev_err(device->dev,
			     "error allocating preemption init cmds\n");
		return PTR_ERR(cmds);
	}
	start = cmds;

	cmds += _preemption_init(adreno_dev, rb, cmds, NULL);

	rb->_wptr = rb->_wptr - (42 - (cmds - start));

	ret = adreno_ringbuffer_submit_spin_nosync(rb, NULL, 2000);
	if (ret)
		adreno_spin_idle_debug(adreno_dev,
			"hw preemption initialization failed to idle\n");

	return ret;
}

/*
 * Some targets support marking certain transactions as always privileged which
 * allows us to mark more memory as privileged without having to explicitly set
 * the APRIV bit.  For those targets, choose the following transactions to be
 * privileged by default:
 * CDWRITE     [6:6] - Crashdumper writes
 * CDREAD      [5:5] - Crashdumper reads
 * RBRPWB      [3:3] - RPTR shadow writes
 * RBPRIVLEVEL [2:2] - Memory accesses from PM4 packets in the ringbuffer
 * RBFETCH     [1:1] - Ringbuffer reads
 */
#define A6XX_APRIV_DEFAULT \
	((1 << 6) | (1 << 5) | (1 << 3) | (1 << 2) | (1 << 1))

/*
 * a6xx_rb_start() - Start the ringbuffer
 * @adreno_dev: Pointer to adreno device
 */
static int a6xx_rb_start(struct adreno_device *adreno_dev)
{
	struct adreno_gpudev *gpudev = ADRENO_GPU_DEVICE(adreno_dev);
	struct adreno_ringbuffer *rb = ADRENO_CURRENT_RINGBUFFER(adreno_dev);
	struct kgsl_device *device = &adreno_dev->dev;
	struct adreno_firmware *fw = ADRENO_FW(adreno_dev, ADRENO_FW_SQE);
	uint64_t addr;
	int ret;

	addr = SCRATCH_RPTR_GPU_ADDR(device, rb->id);

	adreno_writereg64(adreno_dev, ADRENO_REG_CP_RB_RPTR_ADDR_LO,
				ADRENO_REG_CP_RB_RPTR_ADDR_HI, addr);

	/*
	 * The size of the ringbuffer in the hardware is the log2
	 * representation of the size in quadwords (sizedwords / 2).
	 */
	adreno_writereg(adreno_dev, ADRENO_REG_CP_RB_CNTL,
					gpudev->cp_rb_cntl);

	adreno_writereg64(adreno_dev, ADRENO_REG_CP_RB_BASE,
			ADRENO_REG_CP_RB_BASE_HI, rb->buffer_desc.gpuaddr);

	if (ADRENO_FEATURE(adreno_dev, ADRENO_APRIV))
		kgsl_regwrite(device, A6XX_CP_APRIV_CNTL, A6XX_APRIV_DEFAULT);

	/* Program the ucode base for CP */
	kgsl_regwrite(device, A6XX_CP_SQE_INSTR_BASE_LO,
			lower_32_bits(fw->memdesc.gpuaddr));

	kgsl_regwrite(device, A6XX_CP_SQE_INSTR_BASE_HI,
			upper_32_bits(fw->memdesc.gpuaddr));

	/* Clear the SQE_HALT to start the CP engine */
	kgsl_regwrite(device, A6XX_CP_SQE_CNTL, 1);

	ret = a6xx_send_cp_init(adreno_dev, rb);
	if (ret)
		return ret;

	ret = a6xx_zap_load(adreno_dev);
	if (ret)
		return ret;

	/* GPU comes up in secured mode, make it unsecured by default */
	ret = adreno_set_unsecured_mode(adreno_dev, rb);
	if (ret)
		return ret;

	return a6xx_post_start(adreno_dev);
}

/*
 * a6xx_sptprac_enable() - Power on SPTPRAC
 * @adreno_dev: Pointer to Adreno device
 */
static int a6xx_sptprac_enable(struct adreno_device *adreno_dev)
{
	return a6xx_gmu_sptprac_enable(adreno_dev);
}

/*
 * a6xx_sptprac_disable() - Power off SPTPRAC
 * @adreno_dev: Pointer to Adreno device
 */
static void a6xx_sptprac_disable(struct adreno_device *adreno_dev)
{
	a6xx_gmu_sptprac_disable(adreno_dev);
}

/*
 * a6xx_sptprac_is_on() - Check if SPTP is on using pwr status register
 * @adreno_dev - Pointer to adreno_device
 * This check should only be performed if the keepalive bit is set or it
 * can be guaranteed that the power state of the GPU will remain unchanged
 */
bool a6xx_sptprac_is_on(struct adreno_device *adreno_dev)
{
	if (!adreno_has_sptprac_gdsc(adreno_dev))
		return true;

	return a6xx_gmu_sptprac_is_on(adreno_dev);
}

unsigned int a6xx_set_marker(
		unsigned int *cmds, enum adreno_cp_marker_type type)
{
	unsigned int cmd = 0;

	*cmds++ = cp_type7_packet(CP_SET_MARKER, 1);

	/*
	 * Indicate the beginning and end of the IB1 list with a SET_MARKER.
	 * Among other things, this will implicitly enable and disable
	 * preemption respectively. IFPC can also be disabled and enabled
	 * with a SET_MARKER. Bit 8 tells the CP the marker is for IFPC.
	 */
	switch (type) {
	case IFPC_DISABLE:
		cmd = 0x101;
		break;
	case IFPC_ENABLE:
		cmd = 0x100;
		break;
	case IB1LIST_START:
		cmd = 0xD;
		break;
	case IB1LIST_END:
		cmd = 0xE;
		break;
	}

	*cmds++ = cmd;
	return 2;
}

static int _load_firmware(struct kgsl_device *device, const char *fwfile,
			  struct adreno_firmware *firmware)
{
	const struct firmware *fw = NULL;
	int ret;

	ret = request_firmware(&fw, fwfile, device->dev);

	if (ret) {
		dev_err(device->dev, "request_firmware(%s) failed: %d\n",
				fwfile, ret);
		return ret;
	}

	ret = kgsl_allocate_global(device, &firmware->memdesc, fw->size - 4,
				KGSL_MEMFLAGS_GPUREADONLY, KGSL_MEMDESC_UCODE,
				"ucode");

	if (!ret) {
		memcpy(firmware->memdesc.hostptr, &fw->data[4], fw->size - 4);
		firmware->size = (fw->size - 4) / sizeof(uint32_t);
		firmware->version = adreno_get_ucode_version((u32 *)fw->data);
	}

	release_firmware(fw);
	return ret;
}

/*
 * a6xx_gpu_keepalive() - GMU reg write to request GPU stays on
 * @adreno_dev: Pointer to the adreno device that has the GMU
 * @state: State to set: true is ON, false is OFF
 */
static inline void a6xx_gpu_keepalive(struct adreno_device *adreno_dev,
		bool state)
{
	if (!gmu_core_isenabled(KGSL_DEVICE(adreno_dev)))
		return;

	adreno_write_gmureg(adreno_dev,
			ADRENO_REG_GMU_PWR_COL_KEEPALIVE, state);
}

/* Bitmask for GPU idle status check */
#define GPUBUSYIGNAHB		BIT(23)
static bool a6xx_hw_isidle(struct adreno_device *adreno_dev)
{
	unsigned int reg;

	gmu_core_regread(KGSL_DEVICE(adreno_dev),
		A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS, &reg);
	if (reg & GPUBUSYIGNAHB)
		return false;
	return true;
}

/*
 * a6xx_microcode_read() - Read microcode
 * @adreno_dev: Pointer to adreno device
 */
static int a6xx_microcode_read(struct adreno_device *adreno_dev)
{
	int ret;
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);
	struct adreno_firmware *sqe_fw = ADRENO_FW(adreno_dev, ADRENO_FW_SQE);
	const struct adreno_a6xx_core *a6xx_core = to_a6xx_core(adreno_dev);

	if (sqe_fw->memdesc.hostptr == NULL) {
		ret = _load_firmware(device, a6xx_core->sqefw_name, sqe_fw);
		if (ret)
			return ret;
	}

	return 0;
}

static int a6xx_soft_reset(struct adreno_device *adreno_dev)
{
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);
	unsigned int reg;

	if (gmu_core_isenabled(device))
		return 0;

	adreno_writereg(adreno_dev, ADRENO_REG_RBBM_SW_RESET_CMD, 1);
	/*
	 * Do a dummy read to get a brief read cycle delay for the
	 * reset to take effect
	 */
	adreno_readreg(adreno_dev, ADRENO_REG_RBBM_SW_RESET_CMD, &reg);
	adreno_writereg(adreno_dev, ADRENO_REG_RBBM_SW_RESET_CMD, 0);

	/* Clear GBIF client halt and CX arbiter halt */
	adreno_deassert_gbif_halt(adreno_dev);

	a6xx_sptprac_enable(adreno_dev);

	return 0;
}

static int64_t a6xx_read_throttling_counters(struct adreno_device *adreno_dev)
{
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);
	int64_t adj = -1;
	u32 a, b, c;
	struct adreno_busy_data *busy = &adreno_dev->busy_data;

	if (!ADRENO_FEATURE(adreno_dev, ADRENO_LM) ||
			!test_bit(ADRENO_LM_CTRL, &adreno_dev->pwrctrl_flag))
		return 0;

	/* The counters are selected in a6xx_gmu_enable_lm() */
	a = counter_delta(device, A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_1_L,
		&busy->throttle_cycles[0]);

	b = counter_delta(device, A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_2_L,
		&busy->throttle_cycles[1]);

	c = counter_delta(device, A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_3_L,
		&busy->throttle_cycles[2]);


	/*
	 * The adjustment is the number of cycles lost to throttling, which
	 * is calculated as a weighted average of the cycles throttled
	 * at different levels. The adjustment is negative because in A6XX,
	 * the busy count includes the throttled cycles. Therefore, we want
	 * to remove them to prevent appearing to be busier than
	 * we actually are.
	 */
	if (adreno_is_a620(adreno_dev) || adreno_is_a650(adreno_dev))
		/*
		 * With the newer generations, CRC throttle from SIDs of 0x14
		 * and above cannot be observed in power counters. Since 90%
		 * throttle uses SID 0x16 the adjustment calculation needs
		 * correction. The throttling is in increments of 4.2%, and the
		 * 91.7% counter does a weighted count by the value of sid used
		 * which are taken into consideration for the final formula.
		 */
		adj *= div_s64((a * 42) + (b * 500) +
			(div_s64((int64_t)c - a - b * 12, 22) * 917), 1000);
	else
		adj *= ((a * 5) + (b * 50) + (c * 90)) / 100;

	trace_kgsl_clock_throttling(0, b, c, a, adj);

	return adj;
}

/**
 * a6xx_reset() - Helper function to reset the GPU
 * @device: Pointer to the KGSL device structure for the GPU
 * @fault: Type of fault. Needed to skip soft reset for MMU fault
 *
 * Try to reset the GPU to recover from a fault.  First, try to do a low latency
 * soft reset.  If the soft reset fails for some reason, then bring out the big
 * guns and toggle the footswitch.
 */
static int a6xx_reset(struct kgsl_device *device, int fault)
{
	struct adreno_device *adreno_dev = ADRENO_DEVICE(device);
	int ret;
	unsigned long flags = device->pwrctrl.ctrl_flags;

	/* Use the regular reset sequence for No GMU */
	if (!gmu_core_isenabled(device))
		return adreno_reset(device, fault);

	/* Clear ctrl_flags to ensure clocks and regulators are turned off */
	device->pwrctrl.ctrl_flags = 0;

	/* Transition from ACTIVE to RESET state */
	kgsl_pwrctrl_change_state(device, KGSL_STATE_RESET);

	/* since device is officially off now clear start bit */
	clear_bit(ADRENO_DEVICE_STARTED, &adreno_dev->priv);

	ret = adreno_start(device, 0);
	if (ret)
		return ret;

	kgsl_pwrctrl_change_state(device, KGSL_STATE_ACTIVE);

	device->pwrctrl.ctrl_flags = flags;

	/*
	 * If active_cnt is zero, there is no need to keep the GPU active. So,
	 * we should transition to SLUMBER.
	 */
	if (!atomic_read(&device->active_cnt))
		kgsl_pwrctrl_change_state(device, KGSL_STATE_SLUMBER);

	return 0;
}

static void a6xx_cp_hw_err_callback(struct adreno_device *adreno_dev, int bit)
{
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);
	unsigned int status1, status2;

	kgsl_regread(device, A6XX_CP_INTERRUPT_STATUS, &status1);

	if (status1 & BIT(A6XX_CP_OPCODE_ERROR)) {
		unsigned int opcode;

		kgsl_regwrite(device, A6XX_CP_SQE_STAT_ADDR, 1);
		kgsl_regread(device, A6XX_CP_SQE_STAT_DATA, &opcode);
		dev_crit_ratelimited(device->dev,
			"CP opcode error interrupt | opcode=0x%8.8x\n", opcode);
	}
	if (status1 & BIT(A6XX_CP_UCODE_ERROR))
		dev_crit_ratelimited(device->dev, "CP ucode error interrupt\n");
	if (status1 & BIT(A6XX_CP_HW_FAULT_ERROR)) {
		kgsl_regread(device, A6XX_CP_HW_FAULT, &status2);
		dev_crit_ratelimited(device->dev,
			"CP | Ringbuffer HW fault | status=%x\n", status2);
	}
	if (status1 & BIT(A6XX_CP_REGISTER_PROTECTION_ERROR)) {
		kgsl_regread(device, A6XX_CP_PROTECT_STATUS, &status2);
		dev_crit_ratelimited(device->dev,
			"CP | Protected mode error | %s | addr=%x | status=%x\n",
			status2 & (1 << 20) ? "READ" : "WRITE",
			status2 & 0x3FFFF, status2);
	}
	if (status1 & BIT(A6XX_CP_AHB_ERROR))
		dev_crit_ratelimited(device->dev,
			"CP AHB error interrupt\n");
	if (status1 & BIT(A6XX_CP_VSD_PARITY_ERROR))
		dev_crit_ratelimited(device->dev,
			"CP VSD decoder parity error\n");
	if (status1 & BIT(A6XX_CP_ILLEGAL_INSTR_ERROR))
		dev_crit_ratelimited(device->dev,
			"CP Illegal instruction error\n");

}

static void a6xx_err_callback(struct adreno_device *adreno_dev, int bit)
{
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);

	switch (bit) {
	case A6XX_INT_CP_AHB_ERROR:
		dev_crit_ratelimited(device->dev, "CP: AHB bus error\n");
		break;
	case A6XX_INT_ATB_ASYNCFIFO_OVERFLOW:
		dev_crit_ratelimited(device->dev,
					"RBBM: ATB ASYNC overflow\n");
		break;
	case A6XX_INT_RBBM_ATB_BUS_OVERFLOW:
		dev_crit_ratelimited(device->dev,
					"RBBM: ATB bus overflow\n");
		break;
	case A6XX_INT_UCHE_OOB_ACCESS:
		dev_crit_ratelimited(device->dev,
					"UCHE: Out of bounds access\n");
		break;
	case A6XX_INT_UCHE_TRAP_INTR:
		dev_crit_ratelimited(device->dev, "UCHE: Trap interrupt\n");
		break;
	case A6XX_INT_TSB_WRITE_ERROR:
		dev_crit_ratelimited(device->dev, "TSB: Write error interrupt\n");
		break;
	default:
		dev_crit_ratelimited(device->dev, "Unknown interrupt %d\n",
					bit);
	}
}

/*
 * a6xx_llc_configure_gpu_scid() - Program the sub-cache ID for all GPU blocks
 * @adreno_dev: The adreno device pointer
 */
static void a6xx_llc_configure_gpu_scid(struct adreno_device *adreno_dev)
{
	uint32_t gpu_scid;
	uint32_t gpu_cntl1_val = 0;
	int i;
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);
	struct kgsl_mmu *mmu = &device->mmu;

	gpu_scid = adreno_llc_get_scid(adreno_dev->gpu_llc_slice);
	for (i = 0; i < A6XX_LLC_NUM_GPU_SCIDS; i++)
		gpu_cntl1_val = (gpu_cntl1_val << A6XX_GPU_LLC_SCID_NUM_BITS)
			| gpu_scid;

	if (mmu->subtype == KGSL_IOMMU_SMMU_V500)
		kgsl_regrmw(device, A6XX_GBIF_SCACHE_CNTL1,
			A6XX_GPU_LLC_SCID_MASK, gpu_cntl1_val);
	else
		adreno_cx_misc_regrmw(adreno_dev,
				A6XX_GPU_CX_MISC_SYSTEM_CACHE_CNTL_1,
				A6XX_GPU_LLC_SCID_MASK, gpu_cntl1_val);
}

/*
 * a6xx_llc_configure_gpuhtw_scid() - Program the SCID for GPU pagetables
 * @adreno_dev: The adreno device pointer
 */
static void a6xx_llc_configure_gpuhtw_scid(struct adreno_device *adreno_dev)
{
	uint32_t gpuhtw_scid;
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);
	struct kgsl_mmu *mmu = &device->mmu;

	/*
	 * On SMMU-v500, the GPUHTW SCID is configured via a NoC override in
	 * the XBL image.
	 */
	if (mmu->subtype == KGSL_IOMMU_SMMU_V500)
		return;

	gpuhtw_scid = adreno_llc_get_scid(adreno_dev->gpuhtw_llc_slice);

	adreno_cx_misc_regrmw(adreno_dev,
			A6XX_GPU_CX_MISC_SYSTEM_CACHE_CNTL_1,
			A6XX_GPUHTW_LLC_SCID_MASK,
			gpuhtw_scid << A6XX_GPUHTW_LLC_SCID_SHIFT);
}

/*
 * a6xx_llc_enable_overrides() - Override the page attributes
 * @adreno_dev: The adreno device pointer
 */
static void a6xx_llc_enable_overrides(struct adreno_device *adreno_dev)
{
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);
	struct kgsl_mmu *mmu = &device->mmu;

	/*
	 * Attributes override through GBIF is not supported with MMU-500.
	 * Attributes are used as configured through SMMU pagetable entries.
	 */
	if (mmu->subtype == KGSL_IOMMU_SMMU_V500)
		return;

	/*
	 * 0x3: readnoallocoverrideen=0
	 *      read-no-alloc=0 - Allocate lines on read miss
	 *      writenoallocoverrideen=1
	 *      write-no-alloc=1 - Do not allocates lines on write miss
	 */
	adreno_cx_misc_regwrite(adreno_dev,
			A6XX_GPU_CX_MISC_SYSTEM_CACHE_CNTL_0, 0x3);
}

static const char *uche_client[7][3] = {
	{"SP | VSC | VPC | HLSQ | PC | LRZ", "TP", "VFD"},
	{"VSC | VPC | HLSQ | PC | LRZ", "TP | VFD", "SP"},
	{"SP | VPC | HLSQ | PC | LRZ", "TP | VFD", "VSC"},
	{"SP | VSC | HLSQ | PC | LRZ", "TP | VFD", "VPC"},
	{"SP | VSC | VPC | PC | LRZ", "TP | VFD", "HLSQ"},
	{"SP | VSC | VPC | HLSQ | LRZ", "TP | VFD", "PC"},
	{"SP | VSC | VPC | HLSQ | PC", "TP | VFD", "LRZ"},
};

#define SCOOBYDOO 0x5c00bd00

static const char *a6xx_fault_block_uche(struct kgsl_device *device,
		unsigned int mid)
{
	unsigned int uche_client_id = 0;
	static char str[40];

	/*
	 * Smmu driver takes a vote on CX gdsc before calling the kgsl pagefault
	 * handler. If there is contention for device mutex in this path and the
	 * dispatcher fault handler is holding this lock, trying to turn off CX
	 * gdsc will fail during the reset. So to avoid blocking here, try to
	 * lock device mutex and return if it fails.
	 */
	if (!mutex_trylock(&device->mutex))
		return "UCHE";

	if (!kgsl_state_is_awake(device)) {
		mutex_unlock(&device->mutex);
		return "UCHE";
	}

	kgsl_regread(device, A6XX_UCHE_CLIENT_PF, &uche_client_id);
	mutex_unlock(&device->mutex);

	/* Ignore the value if the gpu is in IFPC */
	if (uche_client_id == SCOOBYDOO)
		return "UCHE";

	uche_client_id &= A6XX_UCHE_CLIENT_PF_CLIENT_ID_MASK;
	snprintf(str, sizeof(str), "UCHE: %s",
			uche_client[uche_client_id][mid - 1]);

	return str;
}

static const char *a6xx_iommu_fault_block(struct kgsl_device *device,
		unsigned int fsynr1)
{
	unsigned int mid = fsynr1 & 0xff;

	switch (mid) {
	case 0:
		return "CP";
	case 1:
	case 2:
	case 3:
		return a6xx_fault_block_uche(device, mid);
	case 4:
		return "CCU";
	case 6:
		return "CDP Prefetch";
	case 7:
		return "GPMU";
	}

	return "Unknown";
}

static void a6xx_cp_callback(struct adreno_device *adreno_dev, int bit)
{
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);

	if (adreno_is_preemption_enabled(adreno_dev))
		a6xx_preemption_trigger(adreno_dev);

	adreno_dispatcher_schedule(device);
}

/*
 * a6xx_gpc_err_int_callback() - Isr for GPC error interrupts
 * @adreno_dev: Pointer to device
 * @bit: Interrupt bit
 */
static void a6xx_gpc_err_int_callback(struct adreno_device *adreno_dev, int bit)
{
	struct kgsl_device *device = KGSL_DEVICE(adreno_dev);

	/*
	 * GPC error is typically the result of mistake SW programming.
	 * Force GPU fault for this interrupt so that we can debug it
	 * with help of register dump.
	 */

	dev_crit_ratelimited(device->dev, "RBBM: GPC error\n");
	adreno_irqctrl(adreno_dev, 0);

	/* Trigger a fault in the dispatcher - this will effect a restart */
	adreno_set_gpu_fault(adreno_dev, ADRENO_SOFT_FAULT);
	adreno_dispatcher_schedule(device);
}

#define A6XX_INT_MASK \
	((1 << A6XX_INT_CP_AHB_ERROR) |			\
	 (1 << A6XX_INT_ATB_ASYNCFIFO_OVERFLOW) |	\
	 (1 << A6XX_INT_RBBM_GPC_ERROR) |		\
	 (1 << A6XX_INT_CP_SW) |			\
	 (1 << A6XX_INT_CP_HW_ERROR) |			\
	 (1 << A6XX_INT_CP_IB2) |			\
	 (1 << A6XX_INT_CP_IB1) |			\
	 (1 << A6XX_INT_CP_RB) |			\
	 (1 << A6XX_INT_CP_CACHE_FLUSH_TS) |		\
	 (1 << A6XX_INT_RBBM_ATB_BUS_OVERFLOW) |	\
	 (1 << A6XX_INT_RBBM_HANG_DETECT) |		\
	 (1 << A6XX_INT_UCHE_OOB_ACCESS) |		\
	 (1 << A6XX_INT_UCHE_TRAP_INTR) |		\
	 (1 << A6XX_INT_TSB_WRITE_ERROR))

static struct adreno_irq_funcs a6xx_irq_funcs[32] = {
	ADRENO_IRQ_CALLBACK(NULL),              /* 0 - RBBM_GPU_IDLE */
	ADRENO_IRQ_CALLBACK(a6xx_err_callback), /* 1 - RBBM_AHB_ERROR */
	ADRENO_IRQ_CALLBACK(NULL), /* 2 - UNUSED */
	ADRENO_IRQ_CALLBACK(NULL), /* 3 - UNUSED */
	ADRENO_IRQ_CALLBACK(NULL), /* 4 - UNUSED */
	ADRENO_IRQ_CALLBACK(NULL), /* 5 - UNUSED */
	/* 6 - RBBM_ATB_ASYNC_OVERFLOW */
	ADRENO_IRQ_CALLBACK(a6xx_err_callback),
	ADRENO_IRQ_CALLBACK(a6xx_gpc_err_int_callback), /* 7 - GPC_ERR */
	ADRENO_IRQ_CALLBACK(a6xx_preemption_callback),/* 8 - CP_SW */
	ADRENO_IRQ_CALLBACK(a6xx_cp_hw_err_callback), /* 9 - CP_HW_ERROR */
	ADRENO_IRQ_CALLBACK(NULL),  /* 10 - CP_CCU_FLUSH_DEPTH_TS */
	ADRENO_IRQ_CALLBACK(NULL), /* 11 - CP_CCU_FLUSH_COLOR_TS */
	ADRENO_IRQ_CALLBACK(NULL), /* 12 - CP_CCU_RESOLVE_TS */
	ADRENO_IRQ_CALLBACK(adreno_cp_callback), /* 13 - CP_IB2_INT */
	ADRENO_IRQ_CALLBACK(adreno_cp_callback), /* 14 - CP_IB1_INT */
	ADRENO_IRQ_CALLBACK(adreno_cp_callback), /* 15 - CP_RB_INT */
	ADRENO_IRQ_CALLBACK(NULL), /* 16 - UNUSED */
	ADRENO_IRQ_CALLBACK(NULL), /* 17 - CP_RB_DONE_TS */
	ADRENO_IRQ_CALLBACK(NULL), /* 18 - CP_WT_DONE_TS */
	ADRENO_IRQ_CALLBACK(NULL), /* 19 - UNUSED */
	ADRENO_IRQ_CALLBACK(a6xx_cp_callback), /* 20 - CP_CACHE_FLUSH_TS */
	ADRENO_IRQ_CALLBACK(NULL), /* 21 - UNUSED */
	ADRENO_IRQ_CALLBACK(a6xx_err_callback), /* 22 - RBBM_ATB_BUS_OVERFLOW */
	/* 23 - MISC_HANG_DETECT */
	ADRENO_IRQ_CALLBACK(adreno_hang_int_callback),
	ADRENO_IRQ_CALLBACK(a6xx_err_callback), /* 24 - UCHE_OOB_ACCESS */
	ADRENO_IRQ_CALLBACK(a6xx_err_callback), /* 25 - UCHE_TRAP_INTR */
	ADRENO_IRQ_CALLBACK(NULL), /* 26 - DEBBUS_INTR_0 */
	ADRENO_IRQ_CALLBACK(NULL), /* 27 - DEBBUS_INTR_1 */
	ADRENO_IRQ_CALLBACK(a6xx_err_callback), /* 28 - TSBWRITEERROR */
	ADRENO_IRQ_CALLBACK(NULL), /* 29 - UNUSED */
	ADRENO_IRQ_CALLBACK(NULL), /* 30 - ISDB_CPU_IRQ */
	ADRENO_IRQ_CALLBACK(NULL), /* 31 - ISDB_UNDER_DEBUG */
};

static struct adreno_irq a6xx_irq = {
	.funcs = a6xx_irq_funcs,
	.mask = A6XX_INT_MASK,
};

static struct adreno_coresight_register a6xx_coresight_regs[] = {
	{ A6XX_DBGC_CFG_DBGBUS_SEL_A },
	{ A6XX_DBGC_CFG_DBGBUS_SEL_B },
	{ A6XX_DBGC_CFG_DBGBUS_SEL_C },
	{ A6XX_DBGC_CFG_DBGBUS_SEL_D },
	{ A6XX_DBGC_CFG_DBGBUS_CNTLT },
	{ A6XX_DBGC_CFG_DBGBUS_CNTLM },
	{ A6XX_DBGC_CFG_DBGBUS_OPL },
	{ A6XX_DBGC_CFG_DBGBUS_OPE },
	{ A6XX_DBGC_CFG_DBGBUS_IVTL_0 },
	{ A6XX_DBGC_CFG_DBGBUS_IVTL_1 },
	{ A6XX_DBGC_CFG_DBGBUS_IVTL_2 },
	{ A6XX_DBGC_CFG_DBGBUS_IVTL_3 },
	{ A6XX_DBGC_CFG_DBGBUS_MASKL_0 },
	{ A6XX_DBGC_CFG_DBGBUS_MASKL_1 },
	{ A6XX_DBGC_CFG_DBGBUS_MASKL_2 },
	{ A6XX_DBGC_CFG_DBGBUS_MASKL_3 },
	{ A6XX_DBGC_CFG_DBGBUS_BYTEL_0 },
	{ A6XX_DBGC_CFG_DBGBUS_BYTEL_1 },
	{ A6XX_DBGC_CFG_DBGBUS_IVTE_0 },
	{ A6XX_DBGC_CFG_DBGBUS_IVTE_1 },
	{ A6XX_DBGC_CFG_DBGBUS_IVTE_2 },
	{ A6XX_DBGC_CFG_DBGBUS_IVTE_3 },
	{ A6XX_DBGC_CFG_DBGBUS_MASKE_0 },
	{ A6XX_DBGC_CFG_DBGBUS_MASKE_1 },
	{ A6XX_DBGC_CFG_DBGBUS_MASKE_2 },
	{ A6XX_DBGC_CFG_DBGBUS_MASKE_3 },
	{ A6XX_DBGC_CFG_DBGBUS_NIBBLEE },
	{ A6XX_DBGC_CFG_DBGBUS_PTRC0 },
	{ A6XX_DBGC_CFG_DBGBUS_PTRC1 },
	{ A6XX_DBGC_CFG_DBGBUS_LOADREG },
	{ A6XX_DBGC_CFG_DBGBUS_IDX },
	{ A6XX_DBGC_CFG_DBGBUS_CLRC },
	{ A6XX_DBGC_CFG_DBGBUS_LOADIVT },
	{ A6XX_DBGC_VBIF_DBG_CNTL },
	{ A6XX_DBGC_DBG_LO_HI_GPIO },
	{ A6XX_DBGC_EXT_TRACE_BUS_CNTL },
	{ A6XX_DBGC_READ_AHB_THROUGH_DBG },
	{ A6XX_DBGC_CFG_DBGBUS_TRACE_BUF1 },
	{ A6XX_DBGC_CFG_DBGBUS_TRACE_BUF2 },
	{ A6XX_DBGC_EVT_CFG },
	{ A6XX_DBGC_EVT_INTF_SEL_0 },
	{ A6XX_DBGC_EVT_INTF_SEL_1 },
	{ A6XX_DBGC_PERF_ATB_CFG },
	{ A6XX_DBGC_PERF_ATB_COUNTER_SEL_0 },
	{ A6XX_DBGC_PERF_ATB_COUNTER_SEL_1 },
	{ A6XX_DBGC_PERF_ATB_COUNTER_SEL_2 },
	{ A6XX_DBGC_PERF_ATB_COUNTER_SEL_3 },
	{ A6XX_DBGC_PERF_ATB_TRIG_INTF_SEL_0 },
	{ A6XX_DBGC_PERF_ATB_TRIG_INTF_SEL_1 },
	{ A6XX_DBGC_PERF_ATB_DRAIN_CMD },
	{ A6XX_DBGC_ECO_CNTL },
	{ A6XX_DBGC_AHB_DBG_CNTL },
};

static struct adreno_coresight_register a6xx_coresight_regs_cx[] = {
	{ A6XX_CX_DBGC_CFG_DBGBUS_SEL_A },
	{ A6XX_CX_DBGC_CFG_DBGBUS_SEL_B },
	{ A6XX_CX_DBGC_CFG_DBGBUS_SEL_C },
	{ A6XX_CX_DBGC_CFG_DBGBUS_SEL_D },
	{ A6XX_CX_DBGC_CFG_DBGBUS_CNTLT },
	{ A6XX_CX_DBGC_CFG_DBGBUS_CNTLM },
	{ A6XX_CX_DBGC_CFG_DBGBUS_OPL },
	{ A6XX_CX_DBGC_CFG_DBGBUS_OPE },
	{ A6XX_CX_DBGC_CFG_DBGBUS_IVTL_0 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_IVTL_1 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_IVTL_2 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_IVTL_3 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_MASKL_0 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_MASKL_1 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_MASKL_2 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_MASKL_3 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_BYTEL_0 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_BYTEL_1 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_IVTE_0 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_IVTE_1 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_IVTE_2 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_IVTE_3 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_MASKE_0 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_MASKE_1 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_MASKE_2 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_MASKE_3 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_NIBBLEE },
	{ A6XX_CX_DBGC_CFG_DBGBUS_PTRC0 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_PTRC1 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_LOADREG },
	{ A6XX_CX_DBGC_CFG_DBGBUS_IDX },
	{ A6XX_CX_DBGC_CFG_DBGBUS_CLRC },
	{ A6XX_CX_DBGC_CFG_DBGBUS_LOADIVT },
	{ A6XX_CX_DBGC_VBIF_DBG_CNTL },
	{ A6XX_CX_DBGC_DBG_LO_HI_GPIO },
	{ A6XX_CX_DBGC_EXT_TRACE_BUS_CNTL },
	{ A6XX_CX_DBGC_READ_AHB_THROUGH_DBG },
	{ A6XX_CX_DBGC_CFG_DBGBUS_TRACE_BUF1 },
	{ A6XX_CX_DBGC_CFG_DBGBUS_TRACE_BUF2 },
	{ A6XX_CX_DBGC_EVT_CFG },
	{ A6XX_CX_DBGC_EVT_INTF_SEL_0 },
	{ A6XX_CX_DBGC_EVT_INTF_SEL_1 },
	{ A6XX_CX_DBGC_PERF_ATB_CFG },
	{ A6XX_CX_DBGC_PERF_ATB_COUNTER_SEL_0 },
	{ A6XX_CX_DBGC_PERF_ATB_COUNTER_SEL_1 },
	{ A6XX_CX_DBGC_PERF_ATB_COUNTER_SEL_2 },
	{ A6XX_CX_DBGC_PERF_ATB_COUNTER_SEL_3 },
	{ A6XX_CX_DBGC_PERF_ATB_TRIG_INTF_SEL_0 },
	{ A6XX_CX_DBGC_PERF_ATB_TRIG_INTF_SEL_1 },
	{ A6XX_CX_DBGC_PERF_ATB_DRAIN_CMD },
	{ A6XX_CX_DBGC_ECO_CNTL },
	{ A6XX_CX_DBGC_AHB_DBG_CNTL },
};

static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_sel_a, &a6xx_coresight_regs[0]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_sel_b, &a6xx_coresight_regs[1]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_sel_c, &a6xx_coresight_regs[2]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_sel_d, &a6xx_coresight_regs[3]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_cntlt, &a6xx_coresight_regs[4]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_cntlm, &a6xx_coresight_regs[5]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_opl, &a6xx_coresight_regs[6]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_ope, &a6xx_coresight_regs[7]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_ivtl_0, &a6xx_coresight_regs[8]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_ivtl_1, &a6xx_coresight_regs[9]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_ivtl_2, &a6xx_coresight_regs[10]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_ivtl_3, &a6xx_coresight_regs[11]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_maskl_0, &a6xx_coresight_regs[12]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_maskl_1, &a6xx_coresight_regs[13]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_maskl_2, &a6xx_coresight_regs[14]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_maskl_3, &a6xx_coresight_regs[15]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_bytel_0, &a6xx_coresight_regs[16]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_bytel_1, &a6xx_coresight_regs[17]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_ivte_0, &a6xx_coresight_regs[18]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_ivte_1, &a6xx_coresight_regs[19]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_ivte_2, &a6xx_coresight_regs[20]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_ivte_3, &a6xx_coresight_regs[21]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_maske_0, &a6xx_coresight_regs[22]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_maske_1, &a6xx_coresight_regs[23]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_maske_2, &a6xx_coresight_regs[24]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_maske_3, &a6xx_coresight_regs[25]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_nibblee, &a6xx_coresight_regs[26]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_ptrc0, &a6xx_coresight_regs[27]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_ptrc1, &a6xx_coresight_regs[28]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_loadreg, &a6xx_coresight_regs[29]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_idx, &a6xx_coresight_regs[30]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_clrc, &a6xx_coresight_regs[31]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_loadivt, &a6xx_coresight_regs[32]);
static ADRENO_CORESIGHT_ATTR(vbif_dbg_cntl, &a6xx_coresight_regs[33]);
static ADRENO_CORESIGHT_ATTR(dbg_lo_hi_gpio, &a6xx_coresight_regs[34]);
static ADRENO_CORESIGHT_ATTR(ext_trace_bus_cntl, &a6xx_coresight_regs[35]);
static ADRENO_CORESIGHT_ATTR(read_ahb_through_dbg, &a6xx_coresight_regs[36]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_trace_buf1, &a6xx_coresight_regs[37]);
static ADRENO_CORESIGHT_ATTR(cfg_dbgbus_trace_buf2, &a6xx_coresight_regs[38]);
static ADRENO_CORESIGHT_ATTR(evt_cfg, &a6xx_coresight_regs[39]);
static ADRENO_CORESIGHT_ATTR(evt_intf_sel_0, &a6xx_coresight_regs[40]);
static ADRENO_CORESIGHT_ATTR(evt_intf_sel_1, &a6xx_coresight_regs[41]);
static ADRENO_CORESIGHT_ATTR(perf_atb_cfg, &a6xx_coresight_regs[42]);
static ADRENO_CORESIGHT_ATTR(perf_atb_counter_sel_0, &a6xx_coresight_regs[43]);
static ADRENO_CORESIGHT_ATTR(perf_atb_counter_sel_1, &a6xx_coresight_regs[44]);
static ADRENO_CORESIGHT_ATTR(perf_atb_counter_sel_2, &a6xx_coresight_regs[45]);
static ADRENO_CORESIGHT_ATTR(perf_atb_counter_sel_3, &a6xx_coresight_regs[46]);
static ADRENO_CORESIGHT_ATTR(perf_atb_trig_intf_sel_0,
				&a6xx_coresight_regs[47]);
static ADRENO_CORESIGHT_ATTR(perf_atb_trig_intf_sel_1,
				&a6xx_coresight_regs[48]);
static ADRENO_CORESIGHT_ATTR(perf_atb_drain_cmd, &a6xx_coresight_regs[49]);
static ADRENO_CORESIGHT_ATTR(eco_cntl, &a6xx_coresight_regs[50]);
static ADRENO_CORESIGHT_ATTR(ahb_dbg_cntl, &a6xx_coresight_regs[51]);

/*CX debug registers*/
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_sel_a,
				&a6xx_coresight_regs_cx[0]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_sel_b,
				&a6xx_coresight_regs_cx[1]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_sel_c,
				&a6xx_coresight_regs_cx[2]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_sel_d,
				&a6xx_coresight_regs_cx[3]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_cntlt,
				&a6xx_coresight_regs_cx[4]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_cntlm,
				&a6xx_coresight_regs_cx[5]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_opl,
				&a6xx_coresight_regs_cx[6]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_ope,
				&a6xx_coresight_regs_cx[7]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_ivtl_0,
				&a6xx_coresight_regs_cx[8]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_ivtl_1,
				&a6xx_coresight_regs_cx[9]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_ivtl_2,
				&a6xx_coresight_regs_cx[10]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_ivtl_3,
				&a6xx_coresight_regs_cx[11]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_maskl_0,
				&a6xx_coresight_regs_cx[12]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_maskl_1,
				&a6xx_coresight_regs_cx[13]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_maskl_2,
				&a6xx_coresight_regs_cx[14]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_maskl_3,
				&a6xx_coresight_regs_cx[15]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_bytel_0,
				&a6xx_coresight_regs_cx[16]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_bytel_1,
				&a6xx_coresight_regs_cx[17]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_ivte_0,
				&a6xx_coresight_regs_cx[18]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_ivte_1,
				&a6xx_coresight_regs_cx[19]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_ivte_2,
				&a6xx_coresight_regs_cx[20]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_ivte_3,
				&a6xx_coresight_regs_cx[21]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_maske_0,
				&a6xx_coresight_regs_cx[22]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_maske_1,
				&a6xx_coresight_regs_cx[23]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_maske_2,
				&a6xx_coresight_regs_cx[24]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_maske_3,
				&a6xx_coresight_regs_cx[25]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_nibblee,
				&a6xx_coresight_regs_cx[26]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_ptrc0,
				&a6xx_coresight_regs_cx[27]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_ptrc1,
				&a6xx_coresight_regs_cx[28]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_loadreg,
				&a6xx_coresight_regs_cx[29]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_idx,
				&a6xx_coresight_regs_cx[30]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_clrc,
				&a6xx_coresight_regs_cx[31]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_loadivt,
				&a6xx_coresight_regs_cx[32]);
static ADRENO_CORESIGHT_ATTR(cx_vbif_dbg_cntl,
				&a6xx_coresight_regs_cx[33]);
static ADRENO_CORESIGHT_ATTR(cx_dbg_lo_hi_gpio,
				&a6xx_coresight_regs_cx[34]);
static ADRENO_CORESIGHT_ATTR(cx_ext_trace_bus_cntl,
				&a6xx_coresight_regs_cx[35]);
static ADRENO_CORESIGHT_ATTR(cx_read_ahb_through_dbg,
				&a6xx_coresight_regs_cx[36]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_trace_buf1,
				&a6xx_coresight_regs_cx[37]);
static ADRENO_CORESIGHT_ATTR(cx_cfg_dbgbus_trace_buf2,
				&a6xx_coresight_regs_cx[38]);
static ADRENO_CORESIGHT_ATTR(cx_evt_cfg,
				&a6xx_coresight_regs_cx[39]);
static ADRENO_CORESIGHT_ATTR(cx_evt_intf_sel_0,
				&a6xx_coresight_regs_cx[40]);
static ADRENO_CORESIGHT_ATTR(cx_evt_intf_sel_1,
				&a6xx_coresight_regs_cx[41]);
static ADRENO_CORESIGHT_ATTR(cx_perf_atb_cfg,
				&a6xx_coresight_regs_cx[42]);
static ADRENO_CORESIGHT_ATTR(cx_perf_atb_counter_sel_0,
				&a6xx_coresight_regs_cx[43]);
static ADRENO_CORESIGHT_ATTR(cx_perf_atb_counter_sel_1,
				&a6xx_coresight_regs_cx[44]);
static ADRENO_CORESIGHT_ATTR(cx_perf_atb_counter_sel_2,
				&a6xx_coresight_regs_cx[45]);
static ADRENO_CORESIGHT_ATTR(cx_perf_atb_counter_sel_3,
				&a6xx_coresight_regs_cx[46]);
static ADRENO_CORESIGHT_ATTR(cx_perf_atb_trig_intf_sel_0,
				&a6xx_coresight_regs_cx[47]);
static ADRENO_CORESIGHT_ATTR(cx_perf_atb_trig_intf_sel_1,
				&a6xx_coresight_regs_cx[48]);
static ADRENO_CORESIGHT_ATTR(cx_perf_atb_drain_cmd,
				&a6xx_coresight_regs_cx[49]);
static ADRENO_CORESIGHT_ATTR(cx_eco_cntl,
				&a6xx_coresight_regs_cx[50]);
static ADRENO_CORESIGHT_ATTR(cx_ahb_dbg_cntl,
				&a6xx_coresight_regs_cx[51]);

static struct attribute *a6xx_coresight_attrs[] = {
	&coresight_attr_cfg_dbgbus_sel_a.attr.attr,
	&coresight_attr_cfg_dbgbus_sel_b.attr.attr,
	&coresight_attr_cfg_dbgbus_sel_c.attr.attr,
	&coresight_attr_cfg_dbgbus_sel_d.attr.attr,
	&coresight_attr_cfg_dbgbus_cntlt.attr.attr,
	&coresight_attr_cfg_dbgbus_cntlm.attr.attr,
	&coresight_attr_cfg_dbgbus_opl.attr.attr,
	&coresight_attr_cfg_dbgbus_ope.attr.attr,
	&coresight_attr_cfg_dbgbus_ivtl_0.attr.attr,
	&coresight_attr_cfg_dbgbus_ivtl_1.attr.attr,
	&coresight_attr_cfg_dbgbus_ivtl_2.attr.attr,
	&coresight_attr_cfg_dbgbus_ivtl_3.attr.attr,
	&coresight_attr_cfg_dbgbus_maskl_0.attr.attr,
	&coresight_attr_cfg_dbgbus_maskl_1.attr.attr,
	&coresight_attr_cfg_dbgbus_maskl_2.attr.attr,
	&coresight_attr_cfg_dbgbus_maskl_3.attr.attr,
	&coresight_attr_cfg_dbgbus_bytel_0.attr.attr,
	&coresight_attr_cfg_dbgbus_bytel_1.attr.attr,
	&coresight_attr_cfg_dbgbus_ivte_0.attr.attr,
	&coresight_attr_cfg_dbgbus_ivte_1.attr.attr,
	&coresight_attr_cfg_dbgbus_ivte_2.attr.attr,
	&coresight_attr_cfg_dbgbus_ivte_3.attr.attr,
	&coresight_attr_cfg_dbgbus_maske_0.attr.attr,
	&coresight_attr_cfg_dbgbus_maske_1.attr.attr,
	&coresight_attr_cfg_dbgbus_maske_2.attr.attr,
	&coresight_attr_cfg_dbgbus_maske_3.attr.attr,
	&coresight_attr_cfg_dbgbus_nibblee.attr.attr,
	&coresight_attr_cfg_dbgbus_ptrc0.attr.attr,
	&coresight_attr_cfg_dbgbus_ptrc1.attr.attr,
	&coresight_attr_cfg_dbgbus_loadreg.attr.attr,
	&coresight_attr_cfg_dbgbus_idx.attr.attr,
	&coresight_attr_cfg_dbgbus_clrc.attr.attr,
	&coresight_attr_cfg_dbgbus_loadivt.attr.attr,
	&coresight_attr_vbif_dbg_cntl.attr.attr,
	&coresight_attr_dbg_lo_hi_gpio.attr.attr,
	&coresight_attr_ext_trace_bus_cntl.attr.attr,
	&coresight_attr_read_ahb_through_dbg.attr.attr,
	&coresight_attr_cfg_dbgbus_trace_buf1.attr.attr,
	&coresight_attr_cfg_dbgbus_trace_buf2.attr.attr,
	&coresight_attr_evt_cfg.attr.attr,
	&coresight_attr_evt_intf_sel_0.attr.attr,
	&coresight_attr_evt_intf_sel_1.attr.attr,
	&coresight_attr_perf_atb_cfg.attr.attr,
	&coresight_attr_perf_atb_counter_sel_0.attr.attr,
	&coresight_attr_perf_atb_counter_sel_1.attr.attr,
	&coresight_attr_perf_atb_counter_sel_2.attr.attr,
	&coresight_attr_perf_atb_counter_sel_3.attr.attr,
	&coresight_attr_perf_atb_trig_intf_sel_0.attr.attr,
	&coresight_attr_perf_atb_trig_intf_sel_1.attr.attr,
	&coresight_attr_perf_atb_drain_cmd.attr.attr,
	&coresight_attr_eco_cntl.attr.attr,
	&coresight_attr_ahb_dbg_cntl.attr.attr,
	NULL,
};

/*cx*/
static struct attribute *a6xx_coresight_attrs_cx[] = {
	&coresight_attr_cx_cfg_dbgbus_sel_a.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_sel_b.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_sel_c.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_sel_d.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_cntlt.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_cntlm.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_opl.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_ope.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_ivtl_0.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_ivtl_1.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_ivtl_2.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_ivtl_3.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_maskl_0.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_maskl_1.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_maskl_2.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_maskl_3.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_bytel_0.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_bytel_1.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_ivte_0.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_ivte_1.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_ivte_2.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_ivte_3.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_maske_0.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_maske_1.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_maske_2.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_maske_3.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_nibblee.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_ptrc0.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_ptrc1.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_loadreg.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_idx.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_clrc.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_loadivt.attr.attr,
	&coresight_attr_cx_vbif_dbg_cntl.attr.attr,
	&coresight_attr_cx_dbg_lo_hi_gpio.attr.attr,
	&coresight_attr_cx_ext_trace_bus_cntl.attr.attr,
	&coresight_attr_cx_read_ahb_through_dbg.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_trace_buf1.attr.attr,
	&coresight_attr_cx_cfg_dbgbus_trace_buf2.attr.attr,
	&coresight_attr_cx_evt_cfg.attr.attr,
	&coresight_attr_cx_evt_intf_sel_0.attr.attr,
	&coresight_attr_cx_evt_intf_sel_1.attr.attr,
	&coresight_attr_cx_perf_atb_cfg.attr.attr,
	&coresight_attr_cx_perf_atb_counter_sel_0.attr.attr,
	&coresight_attr_cx_perf_atb_counter_sel_1.attr.attr,
	&coresight_attr_cx_perf_atb_counter_sel_2.attr.attr,
	&coresight_attr_cx_perf_atb_counter_sel_3.attr.attr,
	&coresight_attr_cx_perf_atb_trig_intf_sel_0.attr.attr,
	&coresight_attr_cx_perf_atb_trig_intf_sel_1.attr.attr,
	&coresight_attr_cx_perf_atb_drain_cmd.attr.attr,
	&coresight_attr_cx_eco_cntl.attr.attr,
	&coresight_attr_cx_ahb_dbg_cntl.attr.attr,
	NULL,
};

static const struct attribute_group a6xx_coresight_group = {
	.attrs = a6xx_coresight_attrs,
};

static const struct attribute_group *a6xx_coresight_groups[] = {
	&a6xx_coresight_group,
	NULL,
};

static const struct attribute_group a6xx_coresight_group_cx = {
	.attrs = a6xx_coresight_attrs_cx,
};

static const struct attribute_group *a6xx_coresight_groups_cx[] = {
	&a6xx_coresight_group_cx,
	NULL,
};

static struct adreno_coresight a6xx_coresight = {
	.registers = a6xx_coresight_regs,
	.count = ARRAY_SIZE(a6xx_coresight_regs),
	.groups = a6xx_coresight_groups,
};

static struct adreno_coresight a6xx_coresight_cx = {
	.registers = a6xx_coresight_regs_cx,
	.count = ARRAY_SIZE(a6xx_coresight_regs_cx),
	.groups = a6xx_coresight_groups_cx,
};

static struct adreno_perfcount_register a6xx_perfcounters_cp[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CP_0_LO,
		A6XX_RBBM_PERFCTR_CP_0_HI, 0, A6XX_CP_PERFCTR_CP_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CP_1_LO,
		A6XX_RBBM_PERFCTR_CP_1_HI, 1, A6XX_CP_PERFCTR_CP_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CP_2_LO,
		A6XX_RBBM_PERFCTR_CP_2_HI, 2, A6XX_CP_PERFCTR_CP_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CP_3_LO,
		A6XX_RBBM_PERFCTR_CP_3_HI, 3, A6XX_CP_PERFCTR_CP_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CP_4_LO,
		A6XX_RBBM_PERFCTR_CP_4_HI, 4, A6XX_CP_PERFCTR_CP_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CP_5_LO,
		A6XX_RBBM_PERFCTR_CP_5_HI, 5, A6XX_CP_PERFCTR_CP_SEL_5 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CP_6_LO,
		A6XX_RBBM_PERFCTR_CP_6_HI, 6, A6XX_CP_PERFCTR_CP_SEL_6 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CP_7_LO,
		A6XX_RBBM_PERFCTR_CP_7_HI, 7, A6XX_CP_PERFCTR_CP_SEL_7 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CP_8_LO,
		A6XX_RBBM_PERFCTR_CP_8_HI, 8, A6XX_CP_PERFCTR_CP_SEL_8 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CP_9_LO,
		A6XX_RBBM_PERFCTR_CP_9_HI, 9, A6XX_CP_PERFCTR_CP_SEL_9 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CP_10_LO,
		A6XX_RBBM_PERFCTR_CP_10_HI, 10, A6XX_CP_PERFCTR_CP_SEL_10 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CP_11_LO,
		A6XX_RBBM_PERFCTR_CP_11_HI, 11, A6XX_CP_PERFCTR_CP_SEL_11 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CP_12_LO,
		A6XX_RBBM_PERFCTR_CP_12_HI, 12, A6XX_CP_PERFCTR_CP_SEL_12 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CP_13_LO,
		A6XX_RBBM_PERFCTR_CP_13_HI, 13, A6XX_CP_PERFCTR_CP_SEL_13 },
};

static struct adreno_perfcount_register a6xx_perfcounters_rbbm[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RBBM_0_LO,
		A6XX_RBBM_PERFCTR_RBBM_0_HI, 14, A6XX_RBBM_PERFCTR_RBBM_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RBBM_1_LO,
		A6XX_RBBM_PERFCTR_RBBM_1_HI, 15, A6XX_RBBM_PERFCTR_RBBM_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RBBM_2_LO,
		A6XX_RBBM_PERFCTR_RBBM_2_HI, 16, A6XX_RBBM_PERFCTR_RBBM_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RBBM_3_LO,
		A6XX_RBBM_PERFCTR_RBBM_3_HI, 17, A6XX_RBBM_PERFCTR_RBBM_SEL_3 },
};

static struct adreno_perfcount_register a6xx_perfcounters_pc[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_PC_0_LO,
		A6XX_RBBM_PERFCTR_PC_0_HI, 18, A6XX_PC_PERFCTR_PC_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_PC_1_LO,
		A6XX_RBBM_PERFCTR_PC_1_HI, 19, A6XX_PC_PERFCTR_PC_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_PC_2_LO,
		A6XX_RBBM_PERFCTR_PC_2_HI, 20, A6XX_PC_PERFCTR_PC_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_PC_3_LO,
		A6XX_RBBM_PERFCTR_PC_3_HI, 21, A6XX_PC_PERFCTR_PC_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_PC_4_LO,
		A6XX_RBBM_PERFCTR_PC_4_HI, 22, A6XX_PC_PERFCTR_PC_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_PC_5_LO,
		A6XX_RBBM_PERFCTR_PC_5_HI, 23, A6XX_PC_PERFCTR_PC_SEL_5 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_PC_6_LO,
		A6XX_RBBM_PERFCTR_PC_6_HI, 24, A6XX_PC_PERFCTR_PC_SEL_6 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_PC_7_LO,
		A6XX_RBBM_PERFCTR_PC_7_HI, 25, A6XX_PC_PERFCTR_PC_SEL_7 },
};

static struct adreno_perfcount_register a6xx_perfcounters_vfd[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VFD_0_LO,
		A6XX_RBBM_PERFCTR_VFD_0_HI, 26, A6XX_VFD_PERFCTR_VFD_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VFD_1_LO,
		A6XX_RBBM_PERFCTR_VFD_1_HI, 27, A6XX_VFD_PERFCTR_VFD_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VFD_2_LO,
		A6XX_RBBM_PERFCTR_VFD_2_HI, 28, A6XX_VFD_PERFCTR_VFD_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VFD_3_LO,
		A6XX_RBBM_PERFCTR_VFD_3_HI, 29, A6XX_VFD_PERFCTR_VFD_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VFD_4_LO,
		A6XX_RBBM_PERFCTR_VFD_4_HI, 30, A6XX_VFD_PERFCTR_VFD_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VFD_5_LO,
		A6XX_RBBM_PERFCTR_VFD_5_HI, 31, A6XX_VFD_PERFCTR_VFD_SEL_5 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VFD_6_LO,
		A6XX_RBBM_PERFCTR_VFD_6_HI, 32, A6XX_VFD_PERFCTR_VFD_SEL_6 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VFD_7_LO,
		A6XX_RBBM_PERFCTR_VFD_7_HI, 33, A6XX_VFD_PERFCTR_VFD_SEL_7 },
};

static struct adreno_perfcount_register a6xx_perfcounters_hlsq[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_HLSQ_0_LO,
		A6XX_RBBM_PERFCTR_HLSQ_0_HI, 34, A6XX_HLSQ_PERFCTR_HLSQ_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_HLSQ_1_LO,
		A6XX_RBBM_PERFCTR_HLSQ_1_HI, 35, A6XX_HLSQ_PERFCTR_HLSQ_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_HLSQ_2_LO,
		A6XX_RBBM_PERFCTR_HLSQ_2_HI, 36, A6XX_HLSQ_PERFCTR_HLSQ_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_HLSQ_3_LO,
		A6XX_RBBM_PERFCTR_HLSQ_3_HI, 37, A6XX_HLSQ_PERFCTR_HLSQ_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_HLSQ_4_LO,
		A6XX_RBBM_PERFCTR_HLSQ_4_HI, 38, A6XX_HLSQ_PERFCTR_HLSQ_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_HLSQ_5_LO,
		A6XX_RBBM_PERFCTR_HLSQ_5_HI, 39, A6XX_HLSQ_PERFCTR_HLSQ_SEL_5 },
};

static struct adreno_perfcount_register a6xx_perfcounters_vpc[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VPC_0_LO,
		A6XX_RBBM_PERFCTR_VPC_0_HI, 40, A6XX_VPC_PERFCTR_VPC_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VPC_1_LO,
		A6XX_RBBM_PERFCTR_VPC_1_HI, 41, A6XX_VPC_PERFCTR_VPC_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VPC_2_LO,
		A6XX_RBBM_PERFCTR_VPC_2_HI, 42, A6XX_VPC_PERFCTR_VPC_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VPC_3_LO,
		A6XX_RBBM_PERFCTR_VPC_3_HI, 43, A6XX_VPC_PERFCTR_VPC_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VPC_4_LO,
		A6XX_RBBM_PERFCTR_VPC_4_HI, 44, A6XX_VPC_PERFCTR_VPC_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VPC_5_LO,
		A6XX_RBBM_PERFCTR_VPC_5_HI, 45, A6XX_VPC_PERFCTR_VPC_SEL_5 },
};

static struct adreno_perfcount_register a6xx_perfcounters_ccu[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CCU_0_LO,
		A6XX_RBBM_PERFCTR_CCU_0_HI, 46, A6XX_RB_PERFCTR_CCU_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CCU_1_LO,
		A6XX_RBBM_PERFCTR_CCU_1_HI, 47, A6XX_RB_PERFCTR_CCU_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CCU_2_LO,
		A6XX_RBBM_PERFCTR_CCU_2_HI, 48, A6XX_RB_PERFCTR_CCU_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CCU_3_LO,
		A6XX_RBBM_PERFCTR_CCU_3_HI, 49, A6XX_RB_PERFCTR_CCU_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CCU_4_LO,
		A6XX_RBBM_PERFCTR_CCU_4_HI, 50, A6XX_RB_PERFCTR_CCU_SEL_4 },
};

static struct adreno_perfcount_register a6xx_perfcounters_tse[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TSE_0_LO,
		A6XX_RBBM_PERFCTR_TSE_0_HI, 51, A6XX_GRAS_PERFCTR_TSE_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TSE_1_LO,
		A6XX_RBBM_PERFCTR_TSE_1_HI, 52, A6XX_GRAS_PERFCTR_TSE_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TSE_2_LO,
		A6XX_RBBM_PERFCTR_TSE_2_HI, 53, A6XX_GRAS_PERFCTR_TSE_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TSE_3_LO,
		A6XX_RBBM_PERFCTR_TSE_3_HI, 54, A6XX_GRAS_PERFCTR_TSE_SEL_3 },
};

static struct adreno_perfcount_register a6xx_perfcounters_ras[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RAS_0_LO,
		A6XX_RBBM_PERFCTR_RAS_0_HI, 55, A6XX_GRAS_PERFCTR_RAS_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RAS_1_LO,
		A6XX_RBBM_PERFCTR_RAS_1_HI, 56, A6XX_GRAS_PERFCTR_RAS_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RAS_2_LO,
		A6XX_RBBM_PERFCTR_RAS_2_HI, 57, A6XX_GRAS_PERFCTR_RAS_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RAS_3_LO,
		A6XX_RBBM_PERFCTR_RAS_3_HI, 58, A6XX_GRAS_PERFCTR_RAS_SEL_3 },
};

static struct adreno_perfcount_register a6xx_perfcounters_uche[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_UCHE_0_LO,
		A6XX_RBBM_PERFCTR_UCHE_0_HI, 59, A6XX_UCHE_PERFCTR_UCHE_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_UCHE_1_LO,
		A6XX_RBBM_PERFCTR_UCHE_1_HI, 60, A6XX_UCHE_PERFCTR_UCHE_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_UCHE_2_LO,
		A6XX_RBBM_PERFCTR_UCHE_2_HI, 61, A6XX_UCHE_PERFCTR_UCHE_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_UCHE_3_LO,
		A6XX_RBBM_PERFCTR_UCHE_3_HI, 62, A6XX_UCHE_PERFCTR_UCHE_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_UCHE_4_LO,
		A6XX_RBBM_PERFCTR_UCHE_4_HI, 63, A6XX_UCHE_PERFCTR_UCHE_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_UCHE_5_LO,
		A6XX_RBBM_PERFCTR_UCHE_5_HI, 64, A6XX_UCHE_PERFCTR_UCHE_SEL_5 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_UCHE_6_LO,
		A6XX_RBBM_PERFCTR_UCHE_6_HI, 65, A6XX_UCHE_PERFCTR_UCHE_SEL_6 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_UCHE_7_LO,
		A6XX_RBBM_PERFCTR_UCHE_7_HI, 66, A6XX_UCHE_PERFCTR_UCHE_SEL_7 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_UCHE_8_LO,
		A6XX_RBBM_PERFCTR_UCHE_8_HI, 67, A6XX_UCHE_PERFCTR_UCHE_SEL_8 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_UCHE_9_LO,
		A6XX_RBBM_PERFCTR_UCHE_9_HI, 68, A6XX_UCHE_PERFCTR_UCHE_SEL_9 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_UCHE_10_LO,
		A6XX_RBBM_PERFCTR_UCHE_10_HI, 69,
					A6XX_UCHE_PERFCTR_UCHE_SEL_10 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_UCHE_11_LO,
		A6XX_RBBM_PERFCTR_UCHE_11_HI, 70,
					A6XX_UCHE_PERFCTR_UCHE_SEL_11 },
};

static struct adreno_perfcount_register a6xx_perfcounters_tp[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TP_0_LO,
		A6XX_RBBM_PERFCTR_TP_0_HI, 71, A6XX_TPL1_PERFCTR_TP_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TP_1_LO,
		A6XX_RBBM_PERFCTR_TP_1_HI, 72, A6XX_TPL1_PERFCTR_TP_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TP_2_LO,
		A6XX_RBBM_PERFCTR_TP_2_HI, 73, A6XX_TPL1_PERFCTR_TP_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TP_3_LO,
		A6XX_RBBM_PERFCTR_TP_3_HI, 74, A6XX_TPL1_PERFCTR_TP_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TP_4_LO,
		A6XX_RBBM_PERFCTR_TP_4_HI, 75, A6XX_TPL1_PERFCTR_TP_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TP_5_LO,
		A6XX_RBBM_PERFCTR_TP_5_HI, 76, A6XX_TPL1_PERFCTR_TP_SEL_5 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TP_6_LO,
		A6XX_RBBM_PERFCTR_TP_6_HI, 77, A6XX_TPL1_PERFCTR_TP_SEL_6 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TP_7_LO,
		A6XX_RBBM_PERFCTR_TP_7_HI, 78, A6XX_TPL1_PERFCTR_TP_SEL_7 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TP_8_LO,
		A6XX_RBBM_PERFCTR_TP_8_HI, 79, A6XX_TPL1_PERFCTR_TP_SEL_8 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TP_9_LO,
		A6XX_RBBM_PERFCTR_TP_9_HI, 80, A6XX_TPL1_PERFCTR_TP_SEL_9 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TP_10_LO,
		A6XX_RBBM_PERFCTR_TP_10_HI, 81, A6XX_TPL1_PERFCTR_TP_SEL_10 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_TP_11_LO,
		A6XX_RBBM_PERFCTR_TP_11_HI, 82, A6XX_TPL1_PERFCTR_TP_SEL_11 },
};

static struct adreno_perfcount_register a6xx_perfcounters_sp[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_0_LO,
		A6XX_RBBM_PERFCTR_SP_0_HI, 83, A6XX_SP_PERFCTR_SP_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_1_LO,
		A6XX_RBBM_PERFCTR_SP_1_HI, 84, A6XX_SP_PERFCTR_SP_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_2_LO,
		A6XX_RBBM_PERFCTR_SP_2_HI, 85, A6XX_SP_PERFCTR_SP_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_3_LO,
		A6XX_RBBM_PERFCTR_SP_3_HI, 86, A6XX_SP_PERFCTR_SP_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_4_LO,
		A6XX_RBBM_PERFCTR_SP_4_HI, 87, A6XX_SP_PERFCTR_SP_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_5_LO,
		A6XX_RBBM_PERFCTR_SP_5_HI, 88, A6XX_SP_PERFCTR_SP_SEL_5 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_6_LO,
		A6XX_RBBM_PERFCTR_SP_6_HI, 89, A6XX_SP_PERFCTR_SP_SEL_6 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_7_LO,
		A6XX_RBBM_PERFCTR_SP_7_HI, 90, A6XX_SP_PERFCTR_SP_SEL_7 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_8_LO,
		A6XX_RBBM_PERFCTR_SP_8_HI, 91, A6XX_SP_PERFCTR_SP_SEL_8 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_9_LO,
		A6XX_RBBM_PERFCTR_SP_9_HI, 92, A6XX_SP_PERFCTR_SP_SEL_9 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_10_LO,
		A6XX_RBBM_PERFCTR_SP_10_HI, 93, A6XX_SP_PERFCTR_SP_SEL_10 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_11_LO,
		A6XX_RBBM_PERFCTR_SP_11_HI, 94, A6XX_SP_PERFCTR_SP_SEL_11 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_12_LO,
		A6XX_RBBM_PERFCTR_SP_12_HI, 95, A6XX_SP_PERFCTR_SP_SEL_12 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_13_LO,
		A6XX_RBBM_PERFCTR_SP_13_HI, 96, A6XX_SP_PERFCTR_SP_SEL_13 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_14_LO,
		A6XX_RBBM_PERFCTR_SP_14_HI, 97, A6XX_SP_PERFCTR_SP_SEL_14 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_15_LO,
		A6XX_RBBM_PERFCTR_SP_15_HI, 98, A6XX_SP_PERFCTR_SP_SEL_15 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_16_LO,
		A6XX_RBBM_PERFCTR_SP_16_HI, 99, A6XX_SP_PERFCTR_SP_SEL_16 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_17_LO,
		A6XX_RBBM_PERFCTR_SP_17_HI, 100, A6XX_SP_PERFCTR_SP_SEL_17 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_18_LO,
		A6XX_RBBM_PERFCTR_SP_18_HI, 101, A6XX_SP_PERFCTR_SP_SEL_18 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_19_LO,
		A6XX_RBBM_PERFCTR_SP_19_HI, 102, A6XX_SP_PERFCTR_SP_SEL_19 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_20_LO,
		A6XX_RBBM_PERFCTR_SP_20_HI, 103, A6XX_SP_PERFCTR_SP_SEL_20 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_21_LO,
		A6XX_RBBM_PERFCTR_SP_21_HI, 104, A6XX_SP_PERFCTR_SP_SEL_21 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_22_LO,
		A6XX_RBBM_PERFCTR_SP_22_HI, 105, A6XX_SP_PERFCTR_SP_SEL_22 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_SP_23_LO,
		A6XX_RBBM_PERFCTR_SP_23_HI, 106, A6XX_SP_PERFCTR_SP_SEL_23 },
};

static struct adreno_perfcount_register a6xx_perfcounters_rb[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RB_0_LO,
		A6XX_RBBM_PERFCTR_RB_0_HI, 107, A6XX_RB_PERFCTR_RB_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RB_1_LO,
		A6XX_RBBM_PERFCTR_RB_1_HI, 108, A6XX_RB_PERFCTR_RB_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RB_2_LO,
		A6XX_RBBM_PERFCTR_RB_2_HI, 109, A6XX_RB_PERFCTR_RB_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RB_3_LO,
		A6XX_RBBM_PERFCTR_RB_3_HI, 110, A6XX_RB_PERFCTR_RB_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RB_4_LO,
		A6XX_RBBM_PERFCTR_RB_4_HI, 111, A6XX_RB_PERFCTR_RB_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RB_5_LO,
		A6XX_RBBM_PERFCTR_RB_5_HI, 112, A6XX_RB_PERFCTR_RB_SEL_5 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RB_6_LO,
		A6XX_RBBM_PERFCTR_RB_6_HI, 113, A6XX_RB_PERFCTR_RB_SEL_6 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_RB_7_LO,
		A6XX_RBBM_PERFCTR_RB_7_HI, 114, A6XX_RB_PERFCTR_RB_SEL_7 },
};

static struct adreno_perfcount_register a6xx_perfcounters_vsc[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VSC_0_LO,
		A6XX_RBBM_PERFCTR_VSC_0_HI, 115, A6XX_VSC_PERFCTR_VSC_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_VSC_1_LO,
		A6XX_RBBM_PERFCTR_VSC_1_HI, 116, A6XX_VSC_PERFCTR_VSC_SEL_1 },
};

static struct adreno_perfcount_register a6xx_perfcounters_lrz[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_LRZ_0_LO,
		A6XX_RBBM_PERFCTR_LRZ_0_HI, 117, A6XX_GRAS_PERFCTR_LRZ_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_LRZ_1_LO,
		A6XX_RBBM_PERFCTR_LRZ_1_HI, 118, A6XX_GRAS_PERFCTR_LRZ_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_LRZ_2_LO,
		A6XX_RBBM_PERFCTR_LRZ_2_HI, 119, A6XX_GRAS_PERFCTR_LRZ_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_LRZ_3_LO,
		A6XX_RBBM_PERFCTR_LRZ_3_HI, 120, A6XX_GRAS_PERFCTR_LRZ_SEL_3 },
};

static struct adreno_perfcount_register a6xx_perfcounters_cmp[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CMP_0_LO,
		A6XX_RBBM_PERFCTR_CMP_0_HI, 121, A6XX_RB_PERFCTR_CMP_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CMP_1_LO,
		A6XX_RBBM_PERFCTR_CMP_1_HI, 122, A6XX_RB_PERFCTR_CMP_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CMP_2_LO,
		A6XX_RBBM_PERFCTR_CMP_2_HI, 123, A6XX_RB_PERFCTR_CMP_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_CMP_3_LO,
		A6XX_RBBM_PERFCTR_CMP_3_HI, 124, A6XX_RB_PERFCTR_CMP_SEL_3 },
};

static struct adreno_perfcount_register a6xx_perfcounters_vbif[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_VBIF_PERF_CNT_LOW0,
		A6XX_VBIF_PERF_CNT_HIGH0, -1, A6XX_VBIF_PERF_CNT_SEL0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_VBIF_PERF_CNT_LOW1,
		A6XX_VBIF_PERF_CNT_HIGH1, -1, A6XX_VBIF_PERF_CNT_SEL1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_VBIF_PERF_CNT_LOW2,
		A6XX_VBIF_PERF_CNT_HIGH2, -1, A6XX_VBIF_PERF_CNT_SEL2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_VBIF_PERF_CNT_LOW3,
		A6XX_VBIF_PERF_CNT_HIGH3, -1, A6XX_VBIF_PERF_CNT_SEL3 },
};

static struct adreno_perfcount_register a6xx_perfcounters_vbif_pwr[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_VBIF_PERF_PWR_CNT_LOW0,
		A6XX_VBIF_PERF_PWR_CNT_HIGH0, -1, A6XX_VBIF_PERF_PWR_CNT_EN0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_VBIF_PERF_PWR_CNT_LOW1,
		A6XX_VBIF_PERF_PWR_CNT_HIGH1, -1, A6XX_VBIF_PERF_PWR_CNT_EN1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_VBIF_PERF_PWR_CNT_LOW2,
		A6XX_VBIF_PERF_PWR_CNT_HIGH2, -1, A6XX_VBIF_PERF_PWR_CNT_EN2 },
};


static struct adreno_perfcount_register a6xx_perfcounters_gbif[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_GBIF_PERF_CNT_LOW0,
		A6XX_GBIF_PERF_CNT_HIGH0, -1, A6XX_GBIF_PERF_CNT_SEL },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_GBIF_PERF_CNT_LOW1,
		A6XX_GBIF_PERF_CNT_HIGH1, -1, A6XX_GBIF_PERF_CNT_SEL },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_GBIF_PERF_CNT_LOW2,
		A6XX_GBIF_PERF_CNT_HIGH2, -1, A6XX_GBIF_PERF_CNT_SEL },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_GBIF_PERF_CNT_LOW3,
		A6XX_GBIF_PERF_CNT_HIGH3, -1, A6XX_GBIF_PERF_CNT_SEL },
};

static struct adreno_perfcount_register a6xx_perfcounters_gbif_pwr[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_GBIF_PWR_CNT_LOW0,
		A6XX_GBIF_PWR_CNT_HIGH0, -1, A6XX_GBIF_PERF_PWR_CNT_EN },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_GBIF_PWR_CNT_LOW1,
		A6XX_GBIF_PWR_CNT_HIGH1, -1, A6XX_GBIF_PERF_PWR_CNT_EN },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_GBIF_PWR_CNT_LOW2,
		A6XX_GBIF_PWR_CNT_HIGH2, -1, A6XX_GBIF_PERF_PWR_CNT_EN },
};

static struct adreno_perfcount_register a6xx_perfcounters_alwayson[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_CP_ALWAYS_ON_COUNTER_LO,
		A6XX_CP_ALWAYS_ON_COUNTER_HI, -1 },
};

static struct adreno_perfcount_register a6xx_perfcounters_glc[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, 0x522,
		0x523, -1, 0x8E90 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_GLC_1_LO,
		A6XX_RBBM_PERFCTR_GLC_1_HI, -1, A6XX_RB_PERFCTR_GLC_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_GLC_2_LO,
		A6XX_RBBM_PERFCTR_GLC_2_HI, -1, A6XX_RB_PERFCTR_GLC_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_GLC_3_LO,
		A6XX_RBBM_PERFCTR_GLC_3_HI, -1, A6XX_RB_PERFCTR_GLC_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_GLC_4_LO,
		A6XX_RBBM_PERFCTR_GLC_4_HI, -1, A6XX_RB_PERFCTR_GLC_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_GLC_5_LO,
		A6XX_RBBM_PERFCTR_GLC_5_HI, -1, A6XX_RB_PERFCTR_GLC_SEL_5 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_GLC_6_LO,
		A6XX_RBBM_PERFCTR_GLC_6_HI, -1, A6XX_RB_PERFCTR_GLC_SEL_6 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_GLC_7_LO,
		A6XX_RBBM_PERFCTR_GLC_7_HI, -1, A6XX_RB_PERFCTR_GLC_SEL_7 },
};

static struct adreno_perfcount_register a6xx_perfcounters_fche[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_FCHE_0_LO,
		A6XX_RBBM_PERFCTR_FCHE_0_HI, -1, A6XX_RB_PERFCTR_FCHE_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_FCHE_1_LO,
		A6XX_RBBM_PERFCTR_FCHE_1_HI, -1, A6XX_RB_PERFCTR_FCHE_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_FCHE_2_LO,
		A6XX_RBBM_PERFCTR_FCHE_2_HI, -1, A6XX_RB_PERFCTR_FCHE_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_FCHE_3_LO,
		A6XX_RBBM_PERFCTR_FCHE_3_HI, -1, A6XX_RB_PERFCTR_FCHE_SEL_3 },
};

static struct adreno_perfcount_register a6xx_perfcounters_mhub[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_MHUB_0_LO,
		A6XX_RBBM_PERFCTR_MHUB_0_HI, -1, A6XX_RB_PERFCTR_MHUB_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_MHUB_1_LO,
		A6XX_RBBM_PERFCTR_MHUB_1_HI, -1, A6XX_RB_PERFCTR_MHUB_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_MHUB_2_LO,
		A6XX_RBBM_PERFCTR_MHUB_2_HI, -1, A6XX_RB_PERFCTR_MHUB_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A6XX_RBBM_PERFCTR_MHUB_3_LO,
		A6XX_RBBM_PERFCTR_MHUB_3_HI, -1, A6XX_RB_PERFCTR_MHUB_SEL_3 },
};

/*
 * ADRENO_PERFCOUNTER_GROUP_RESTORE flag is enabled by default
 * because most of the perfcounter groups need to be restored
 * as part of preemption and IFPC. Perfcounter groups that are
 * not restored as part of preemption and IFPC should be defined
 * using A6XX_PERFCOUNTER_GROUP_FLAGS macro
 */
#define A6XX_PERFCOUNTER_GROUP(offset, name) \
	ADRENO_PERFCOUNTER_GROUP_FLAGS(a6xx, offset, name, \
	ADRENO_PERFCOUNTER_GROUP_RESTORE)

#define A6XX_PERFCOUNTER_GROUP_FLAGS(offset, name, flags) \
	ADRENO_PERFCOUNTER_GROUP_FLAGS(a6xx, offset, name, flags)

#define A6XX_POWER_COUNTER_GROUP(offset, name) \
	ADRENO_POWER_COUNTER_GROUP(a6xx, offset, name)

static struct adreno_perfcount_group a6xx_perfcounter_groups
				[KGSL_PERFCOUNTER_GROUP_MAX] = {
	A6XX_PERFCOUNTER_GROUP(CP, cp),
	A6XX_PERFCOUNTER_GROUP_FLAGS(RBBM, rbbm, 0),
	A6XX_PERFCOUNTER_GROUP(PC, pc),
	A6XX_PERFCOUNTER_GROUP(VFD, vfd),
	A6XX_PERFCOUNTER_GROUP(HLSQ, hlsq),
	A6XX_PERFCOUNTER_GROUP(VPC, vpc),
	A6XX_PERFCOUNTER_GROUP(CCU, ccu),
	A6XX_PERFCOUNTER_GROUP(CMP, cmp),
	A6XX_PERFCOUNTER_GROUP(TSE, tse),
	A6XX_PERFCOUNTER_GROUP(RAS, ras),
	A6XX_PERFCOUNTER_GROUP(LRZ, lrz),
	A6XX_PERFCOUNTER_GROUP(UCHE, uche),
	A6XX_PERFCOUNTER_GROUP(TP, tp),
	A6XX_PERFCOUNTER_GROUP(SP, sp),
	A6XX_PERFCOUNTER_GROUP(RB, rb),
	A6XX_PERFCOUNTER_GROUP(VSC, vsc),
	A6XX_PERFCOUNTER_GROUP_FLAGS(VBIF, vbif, 0),
	A6XX_PERFCOUNTER_GROUP_FLAGS(VBIF_PWR, vbif_pwr,
		ADRENO_PERFCOUNTER_GROUP_FIXED),
	A6XX_PERFCOUNTER_GROUP_FLAGS(ALWAYSON, alwayson,
		ADRENO_PERFCOUNTER_GROUP_FIXED),
};

static struct adreno_perfcounters a6xx_perfcounters = {
	a6xx_perfcounter_groups,
	ARRAY_SIZE(a6xx_perfcounter_groups),
};

static void a6xx_efuse_speed_bin(struct adreno_device *adreno_dev)
{
	unsigned int val;
	unsigned int speed_bin[3];
	struct kgsl_device *device = &adreno_dev->dev;

	if (of_property_read_u32_array(device->pdev->dev.of_node,
		"qcom,gpu-speed-bin", speed_bin, 3))
		return;

	adreno_efuse_read_u32(adreno_dev, speed_bin[0], &val);

	adreno_dev->speed_bin = (val & speed_bin[1]) >> speed_bin[2];
}

static const struct {
	int (*check)(struct adreno_device *adreno_dev);
	void (*func)(struct adreno_device *adreno_dev);
} a6xx_efuse_funcs[] = {
	{ adreno_is_a615_family, a6xx_efuse_speed_bin },
	{ adreno_is_a612, a6xx_efuse_speed_bin },
};

static void a6xx_check_features(struct adreno_device *adreno_dev)
{
	unsigned int i;

	if (adreno_efuse_map(adreno_dev))
		return;
	for (i = 0; i < ARRAY_SIZE(a6xx_efuse_funcs); i++) {
		if (a6xx_efuse_funcs[i].check(adreno_dev))
			a6xx_efuse_funcs[i].func(adreno_dev);
	}

	adreno_efuse_unmap(adreno_dev);
}
static void a6xx_platform_setup(struct adreno_device *adreno_dev)
{
	struct adreno_gpudev *gpudev = ADRENO_GPU_DEVICE(adreno_dev);

	if (adreno_has_gbif(adreno_dev)) {
		a6xx_perfcounter_groups[KGSL_PERFCOUNTER_GROUP_VBIF].regs =
				a6xx_perfcounters_gbif;
		a6xx_perfcounter_groups[KGSL_PERFCOUNTER_GROUP_VBIF].reg_count
				= ARRAY_SIZE(a6xx_perfcounters_gbif);

		a6xx_perfcounter_groups[KGSL_PERFCOUNTER_GROUP_VBIF_PWR].regs =
				a6xx_perfcounters_gbif_pwr;
		a6xx_perfcounter_groups[
			KGSL_PERFCOUNTER_GROUP_VBIF_PWR].reg_count
				= ARRAY_SIZE(a6xx_perfcounters_gbif_pwr);

		gpudev->gbif_client_halt_mask = A6XX_GBIF_CLIENT_HALT_MASK;
		gpudev->gbif_arb_halt_mask = A6XX_GBIF_ARB_HALT_MASK;
		gpudev->gbif_gx_halt_mask = A6XX_GBIF_GX_HALT_MASK;
	} else
		gpudev->vbif_xin_halt_ctrl0_mask =
				A6XX_VBIF_XIN_HALT_CTRL0_MASK;

	if (adreno_is_a702(adreno_dev)) {
		a6xx_perfcounter_groups[KGSL_PERFCOUNTER_GROUP_GLC].regs =
				a6xx_perfcounters_glc;
		a6xx_perfcounter_groups[KGSL_PERFCOUNTER_GROUP_GLC].reg_count
				= ARRAY_SIZE(a6xx_perfcounters_glc);

		a6xx_perfcounter_groups[KGSL_PERFCOUNTER_GROUP_FCHE].regs =
				a6xx_perfcounters_fche;
		a6xx_perfcounter_groups[KGSL_PERFCOUNTER_GROUP_FCHE].reg_count
				= ARRAY_SIZE(a6xx_perfcounters_fche);

		a6xx_perfcounter_groups[KGSL_PERFCOUNTER_GROUP_MHUB].regs =
				a6xx_perfcounters_mhub;
		a6xx_perfcounter_groups[KGSL_PERFCOUNTER_GROUP_MHUB].reg_count
				= ARRAY_SIZE(a6xx_perfcounters_mhub);
	}

	/* Set the GPU busy counter for frequency scaling */
	adreno_dev->perfctr_pwr_lo = A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_0_L;

	/* Set the counter for IFPC */
	if (ADRENO_FEATURE(adreno_dev, ADRENO_IFPC))
		adreno_dev->perfctr_ifpc_lo =
			A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_4_L;

	if (ADRENO_FEATURE(adreno_dev, ADRENO_SPTP_PC))
		set_bit(ADRENO_SPTP_PC_CTRL, &adreno_dev->pwrctrl_flag);

	if (!ADRENO_FEATURE(adreno_dev, ADRENO_APRIV))
		gpudev->cp_rb_cntl |= (1 << 27);

	/* Check efuse bits for various capabilties */
	a6xx_check_features(adreno_dev);
}


static unsigned int a6xx_ccu_invalidate(struct adreno_device *adreno_dev,
	unsigned int *cmds)
{
	/* CCU_INVALIDATE_DEPTH */
	*cmds++ = cp_packet(adreno_dev, CP_EVENT_WRITE, 1);
	*cmds++ = 24;

	/* CCU_INVALIDATE_COLOR */
	*cmds++ = cp_packet(adreno_dev, CP_EVENT_WRITE, 1);
	*cmds++ = 25;

	return 4;
}

/* Register offset defines for A6XX, in order of enum adreno_regs */
static unsigned int a6xx_register_offsets[ADRENO_REG_REGISTER_MAX] = {

	ADRENO_REG_DEFINE(ADRENO_REG_CP_RB_BASE, A6XX_CP_RB_BASE),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_RB_BASE_HI, A6XX_CP_RB_BASE_HI),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_RB_RPTR_ADDR_LO,
				A6XX_CP_RB_RPTR_ADDR_LO),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_RB_RPTR_ADDR_HI,
				A6XX_CP_RB_RPTR_ADDR_HI),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_RB_RPTR, A6XX_CP_RB_RPTR),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_RB_WPTR, A6XX_CP_RB_WPTR),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_RB_CNTL, A6XX_CP_RB_CNTL),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_ME_CNTL, A6XX_CP_SQE_CNTL),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_CNTL, A6XX_CP_MISC_CNTL),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_HW_FAULT, A6XX_CP_HW_FAULT),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_IB1_BASE, A6XX_CP_IB1_BASE),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_IB1_BASE_HI, A6XX_CP_IB1_BASE_HI),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_IB1_BUFSZ, A6XX_CP_IB1_REM_SIZE),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_IB2_BASE, A6XX_CP_IB2_BASE),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_IB2_BASE_HI, A6XX_CP_IB2_BASE_HI),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_IB2_BUFSZ, A6XX_CP_IB2_REM_SIZE),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_ROQ_ADDR, A6XX_CP_ROQ_DBG_ADDR),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_ROQ_DATA, A6XX_CP_ROQ_DBG_DATA),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_PREEMPT, A6XX_CP_CONTEXT_SWITCH_CNTL),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_CONTEXT_SWITCH_SMMU_INFO_LO,
			A6XX_CP_CONTEXT_SWITCH_SMMU_INFO_LO),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_CONTEXT_SWITCH_SMMU_INFO_HI,
			A6XX_CP_CONTEXT_SWITCH_SMMU_INFO_HI),
	ADRENO_REG_DEFINE(
		ADRENO_REG_CP_CONTEXT_SWITCH_PRIV_NON_SECURE_RESTORE_ADDR_LO,
			A6XX_CP_CONTEXT_SWITCH_PRIV_NON_SECURE_RESTORE_ADDR_LO),
	ADRENO_REG_DEFINE(
		ADRENO_REG_CP_CONTEXT_SWITCH_PRIV_NON_SECURE_RESTORE_ADDR_HI,
			A6XX_CP_CONTEXT_SWITCH_PRIV_NON_SECURE_RESTORE_ADDR_HI),
	ADRENO_REG_DEFINE(
		ADRENO_REG_CP_CONTEXT_SWITCH_PRIV_SECURE_RESTORE_ADDR_LO,
			A6XX_CP_CONTEXT_SWITCH_PRIV_SECURE_RESTORE_ADDR_LO),
	ADRENO_REG_DEFINE(
		ADRENO_REG_CP_CONTEXT_SWITCH_PRIV_SECURE_RESTORE_ADDR_HI,
			A6XX_CP_CONTEXT_SWITCH_PRIV_SECURE_RESTORE_ADDR_HI),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_CONTEXT_SWITCH_NON_PRIV_RESTORE_ADDR_LO,
			A6XX_CP_CONTEXT_SWITCH_NON_PRIV_RESTORE_ADDR_LO),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_CONTEXT_SWITCH_NON_PRIV_RESTORE_ADDR_HI,
			A6XX_CP_CONTEXT_SWITCH_NON_PRIV_RESTORE_ADDR_HI),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_PREEMPT_LEVEL_STATUS,
			A6XX_CP_CONTEXT_SWITCH_LEVEL_STATUS),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_STATUS, A6XX_RBBM_STATUS),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_STATUS3, A6XX_RBBM_STATUS3),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_PERFCTR_CTL, A6XX_RBBM_PERFCTR_CNTL),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_PERFCTR_LOAD_CMD0,
					A6XX_RBBM_PERFCTR_LOAD_CMD0),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_PERFCTR_LOAD_CMD1,
					A6XX_RBBM_PERFCTR_LOAD_CMD1),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_PERFCTR_LOAD_CMD2,
					A6XX_RBBM_PERFCTR_LOAD_CMD2),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_PERFCTR_LOAD_CMD3,
					A6XX_RBBM_PERFCTR_LOAD_CMD3),

	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_INT_0_MASK, A6XX_RBBM_INT_0_MASK),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_INT_0_STATUS, A6XX_RBBM_INT_0_STATUS),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_CLOCK_CTL, A6XX_RBBM_CLOCK_CNTL),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_INT_CLEAR_CMD,
				A6XX_RBBM_INT_CLEAR_CMD),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_SW_RESET_CMD, A6XX_RBBM_SW_RESET_CMD),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_BLOCK_SW_RESET_CMD,
					  A6XX_RBBM_BLOCK_SW_RESET_CMD),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_BLOCK_SW_RESET_CMD2,
					  A6XX_RBBM_BLOCK_SW_RESET_CMD2),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_PERFCTR_LOAD_VALUE_LO,
				A6XX_RBBM_PERFCTR_LOAD_VALUE_LO),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_PERFCTR_LOAD_VALUE_HI,
				A6XX_RBBM_PERFCTR_LOAD_VALUE_HI),
	ADRENO_REG_DEFINE(ADRENO_REG_VBIF_VERSION, A6XX_VBIF_VERSION),
	ADRENO_REG_DEFINE(ADRENO_REG_VBIF_XIN_HALT_CTRL0,
				A6XX_VBIF_XIN_HALT_CTRL0),
	ADRENO_REG_DEFINE(ADRENO_REG_VBIF_XIN_HALT_CTRL1,
				A6XX_VBIF_XIN_HALT_CTRL1),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_GPR0_CNTL, A6XX_RBBM_GPR0_CNTL),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_VBIF_GX_RESET_STATUS,
				A6XX_RBBM_VBIF_GX_RESET_STATUS),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_GBIF_HALT,
				A6XX_RBBM_GBIF_HALT),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_GBIF_HALT_ACK,
				A6XX_RBBM_GBIF_HALT_ACK),
	ADRENO_REG_DEFINE(ADRENO_REG_GBIF_HALT, A6XX_GBIF_HALT),
	ADRENO_REG_DEFINE(ADRENO_REG_GBIF_HALT_ACK, A6XX_GBIF_HALT_ACK),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_ALWAYSON_COUNTER_LO,
				A6XX_GMU_ALWAYS_ON_COUNTER_L),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_ALWAYSON_COUNTER_HI,
				A6XX_GMU_ALWAYS_ON_COUNTER_H),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_AO_AHB_FENCE_CTRL,
				A6XX_GMU_AO_AHB_FENCE_CTRL),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_AO_INTERRUPT_EN,
				A6XX_GMU_AO_INTERRUPT_EN),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_AO_HOST_INTERRUPT_CLR,
				A6XX_GMU_AO_HOST_INTERRUPT_CLR),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_AO_HOST_INTERRUPT_STATUS,
				A6XX_GMU_AO_HOST_INTERRUPT_STATUS),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_AO_HOST_INTERRUPT_MASK,
				A6XX_GMU_AO_HOST_INTERRUPT_MASK),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_PWR_COL_KEEPALIVE,
				A6XX_GMU_GMU_PWR_COL_KEEPALIVE),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_AHB_FENCE_STATUS,
				A6XX_GMU_AHB_FENCE_STATUS),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_HFI_CTRL_STATUS,
				A6XX_GMU_HFI_CTRL_STATUS),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_HFI_VERSION_INFO,
				A6XX_GMU_HFI_VERSION_INFO),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_HFI_SFR_ADDR,
				A6XX_GMU_HFI_SFR_ADDR),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_RPMH_POWER_STATE,
				A6XX_GPU_GMU_CX_GMU_RPMH_POWER_STATE),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_GMU2HOST_INTR_CLR,
				A6XX_GMU_GMU2HOST_INTR_CLR),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_GMU2HOST_INTR_INFO,
				A6XX_GMU_GMU2HOST_INTR_INFO),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_GMU2HOST_INTR_MASK,
				A6XX_GMU_GMU2HOST_INTR_MASK),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_HOST2GMU_INTR_SET,
				A6XX_GMU_HOST2GMU_INTR_SET),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_HOST2GMU_INTR_CLR,
				A6XX_GMU_HOST2GMU_INTR_CLR),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_HOST2GMU_INTR_RAW_INFO,
				A6XX_GMU_HOST2GMU_INTR_RAW_INFO),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_NMI_CONTROL_STATUS,
				A6XX_GMU_NMI_CONTROL_STATUS),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_CM3_CFG,
				A6XX_GMU_CM3_CFG),
	ADRENO_REG_DEFINE(ADRENO_REG_GMU_RBBM_INT_UNMASKED_STATUS,
				A6XX_GMU_RBBM_INT_UNMASKED_STATUS),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_SECVID_TRUST_CONTROL,
				A6XX_RBBM_SECVID_TRUST_CNTL),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_SECVID_TSB_TRUSTED_BASE,
				A6XX_RBBM_SECVID_TSB_TRUSTED_BASE_LO),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_SECVID_TSB_TRUSTED_BASE_HI,
				A6XX_RBBM_SECVID_TSB_TRUSTED_BASE_HI),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_SECVID_TSB_TRUSTED_SIZE,
				A6XX_RBBM_SECVID_TSB_TRUSTED_SIZE),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_SECVID_TSB_CONTROL,
				A6XX_RBBM_SECVID_TSB_CNTL),
};

static const struct adreno_reg_offsets a6xx_reg_offsets = {
	.offsets = a6xx_register_offsets,
	.offset_0 = ADRENO_REG_REGISTER_MAX,
};

static int cpu_gpu_lock(struct cpu_gpu_lock *lock)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(1000);

	/* Indicate that the CPU wants the lock */
	lock->flag_kmd = 1;

	/* post the request */
	wmb();

	/* Wait for our turn */
	lock->turn = 0;

	/* Finish all memory transactions before moving on */
	mb();

	/*
	 * Spin here while GPU ucode holds the lock, lock->flag_ucode will
	 * be set to 0 after GPU ucode releases the lock. Minimum wait time
	 * is 1 second and this should be enough for GPU to release the lock
	 */
	while (lock->flag_ucode == 1 && lock->turn == 0) {
		cpu_relax();
		/* Get the latest updates from GPU */
		rmb();

		if (time_after(jiffies, timeout))
			break;
	}

	if (lock->flag_ucode == 1 && lock->turn == 0)
		return -EBUSY;

	return 0;
}

static void cpu_gpu_unlock(struct cpu_gpu_lock *lock)
{
	/* Make sure all writes are done before releasing the lock */
	wmb();
	lock->flag_kmd = 0;
}

static int a6xx_perfcounter_update(struct adreno_device *adreno_dev,
	struct adreno_perfcount_register *reg, bool update_reg)
{
	void *ptr = adreno_dev->pwrup_reglist.hostptr;
	struct cpu_gpu_lock *lock = ptr;
	u32 *data = ptr + sizeof(*lock);
	int i, offset = 0;
	bool select_reg_present = false;

	if (select_reg_present) {
		data[offset + 1] = reg->countable;
		goto update;
	}


	if (cpu_gpu_lock(lock)) {
		cpu_gpu_unlock(lock);
		return -EBUSY;
	}

	/*
	 * If the perfcounter select register is already present in reglist
	 * update it, otherwise append the <select register, value> pair to
	 * the end of the list.
	 */
	for (i = 0; i < lock->list_length >> 1; i++) {
		if (data[offset] == reg->select) {
			data[offset + 1] = reg->countable;
			goto update;
		}

		offset += 2;
	}

	/*
	 * For a612 targets A6XX_RBBM_PERFCTR_CNTL needs to be the last entry,
	 * so overwrite the existing A6XX_RBBM_PERFCNTL_CTRL and add it back to
	 * the end. All other targets just append the new counter to the end.
	 */
	if (adreno_is_a612(adreno_dev)) {
		data[offset - 2] = reg->select;
		data[offset - 1] = reg->countable;

		data[offset] = A6XX_RBBM_PERFCTR_CNTL,
		data[offset + 1] = 1;
	} else {
		data[offset] = reg->select;
		data[offset + 1] = reg->countable;
	}

	lock->list_length += 2;

update:
	if (update_reg)
		kgsl_regwrite(KGSL_DEVICE(adreno_dev), reg->select,
			reg->countable);

	cpu_gpu_unlock(lock);
	return 0;
}

static void a6xx_clk_set_options(struct adreno_device *adreno_dev,
	const char *name, struct clk *clk, bool on)
{
	if (!adreno_is_a610(adreno_dev) && !adreno_is_a702(adreno_dev))
		return;

	/* Handle clock settings for GFX PSCBCs */
	if (on) {
		if (!strcmp(name, "mem_iface_clk")) {
			clk_set_flags(clk, CLKFLAG_NORETAIN_PERIPH);
			clk_set_flags(clk, CLKFLAG_NORETAIN_MEM);
		} else if (!strcmp(name, "core_clk")) {
			clk_set_flags(clk, CLKFLAG_RETAIN_PERIPH);
			clk_set_flags(clk, CLKFLAG_RETAIN_MEM);
		}
	} else {
		if (!strcmp(name, "core_clk")) {
			clk_set_flags(clk, CLKFLAG_NORETAIN_PERIPH);
			clk_set_flags(clk, CLKFLAG_NORETAIN_MEM);
		}
	}
}

struct adreno_gpudev adreno_a6xx_gpudev = {
	.reg_offsets = &a6xx_reg_offsets,
	.start = a6xx_start,
	.snapshot = a6xx_snapshot,
	.irq = &a6xx_irq,
	.irq_trace = trace_kgsl_a6xx_irq_status,
	.num_prio_levels = KGSL_PRIORITY_MAX_RB_LEVELS,
	.cp_rb_cntl = A6XX_CP_RB_CNTL_DEFAULT,
	.platform_setup = a6xx_platform_setup,
	.init = a6xx_init,
	.rb_start = a6xx_rb_start,
	.regulator_enable = a6xx_sptprac_enable,
	.regulator_disable = a6xx_sptprac_disable,
	.perfcounters = &a6xx_perfcounters,
	.read_throttling_counters = a6xx_read_throttling_counters,
	.microcode_read = a6xx_microcode_read,
	.enable_64bit = a6xx_enable_64bit,
	.llc_configure_gpu_scid = a6xx_llc_configure_gpu_scid,
	.llc_configure_gpuhtw_scid = a6xx_llc_configure_gpuhtw_scid,
	.llc_enable_overrides = a6xx_llc_enable_overrides,
	.gpu_keepalive = a6xx_gpu_keepalive,
	.hw_isidle = a6xx_hw_isidle, /* Replaced by NULL if GMU is disabled */
	.iommu_fault_block = a6xx_iommu_fault_block,
	.reset = a6xx_reset,
	.soft_reset = a6xx_soft_reset,
	.preemption_pre_ibsubmit = a6xx_preemption_pre_ibsubmit,
	.preemption_post_ibsubmit = a6xx_preemption_post_ibsubmit,
	.preemption_init = a6xx_preemption_init,
	.preemption_close = a6xx_preemption_close,
	.preemption_schedule = a6xx_preemption_schedule,
	.set_marker = a6xx_set_marker,
	.preemption_context_init = a6xx_preemption_context_init,
	.preemption_context_destroy = a6xx_preemption_context_destroy,
	.sptprac_is_on = a6xx_sptprac_is_on,
	.ccu_invalidate = a6xx_ccu_invalidate,
	.perfcounter_update = a6xx_perfcounter_update,
	.coresight = {&a6xx_coresight, &a6xx_coresight_cx},
	.clk_set_options = a6xx_clk_set_options,
};
