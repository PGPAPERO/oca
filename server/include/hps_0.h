#ifndef _ALTERA_HPS_0_H_
#define _ALTERA_HPS_0_H_

/*
 * This file was automatically generated by the swinfo2header utility.
 *
 * Created from SOPC Builder system 'soc_system' in
 * file './soc_system.sopcinfo'.
 */

/*
 * This file contains macros for module 'hps_0' and devices
 * connected to the following masters:
 *   h2f_axi_master
 *   h2f_lw_axi_master
 *
 * Do not include this header file and another header file created for a
 * different module or master group at the same time.
 * Doing so may result in duplicate macro names.
 * Instead, use the system header file which has macros with unique names.
 */

/*
 * Macros for device 'fast_fifo_FPGA_to_HPS_out_csr', class 'altera_avalon_fifo'
 * The macros are prefixed with 'FAST_FIFO_FPGA_TO_HPS_OUT_CSR_'.
 * The prefix is the slave descriptor.
 */
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_COMPONENT_TYPE altera_avalon_fifo
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_COMPONENT_NAME fast_fifo_FPGA_to_HPS
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_BASE 0x0
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_SPAN 32
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_END 0x1f
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_AVALONMM_AVALONST_DATA_WIDTH 32
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_BITS_PER_SYMBOL 16
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_CHANNEL_WIDTH 8
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_ERROR_WIDTH 8
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_FIFO_DEPTH 4096
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_SINGLE_CLOCK_MODE 0
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_SYMBOLS_PER_BEAT 2
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_USE_AVALONMM_READ_SLAVE 1
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_USE_AVALONMM_WRITE_SLAVE 1
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_USE_AVALONST_SINK 0
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_USE_AVALONST_SOURCE 0
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_USE_BACKPRESSURE 1
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_USE_IRQ 0
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_USE_PACKET 1
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_USE_READ_CONTROL 1
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_USE_REGISTER 0
#define FAST_FIFO_FPGA_TO_HPS_OUT_CSR_USE_WRITE_CONTROL 1

/*
 * Macros for device 'fifo_FPGA_to_HPS_out_csr', class 'altera_avalon_fifo'
 * The macros are prefixed with 'FIFO_FPGA_TO_HPS_OUT_CSR_'.
 * The prefix is the slave descriptor.
 */
#define FIFO_FPGA_TO_HPS_OUT_CSR_COMPONENT_TYPE altera_avalon_fifo
#define FIFO_FPGA_TO_HPS_OUT_CSR_COMPONENT_NAME fifo_FPGA_to_HPS
#define FIFO_FPGA_TO_HPS_OUT_CSR_BASE 0x20
#define FIFO_FPGA_TO_HPS_OUT_CSR_SPAN 32
#define FIFO_FPGA_TO_HPS_OUT_CSR_END 0x3f
#define FIFO_FPGA_TO_HPS_OUT_CSR_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FIFO_FPGA_TO_HPS_OUT_CSR_AVALONMM_AVALONST_DATA_WIDTH 32
#define FIFO_FPGA_TO_HPS_OUT_CSR_BITS_PER_SYMBOL 16
#define FIFO_FPGA_TO_HPS_OUT_CSR_CHANNEL_WIDTH 8
#define FIFO_FPGA_TO_HPS_OUT_CSR_ERROR_WIDTH 8
#define FIFO_FPGA_TO_HPS_OUT_CSR_FIFO_DEPTH 1024
#define FIFO_FPGA_TO_HPS_OUT_CSR_SINGLE_CLOCK_MODE 0
#define FIFO_FPGA_TO_HPS_OUT_CSR_SYMBOLS_PER_BEAT 2
#define FIFO_FPGA_TO_HPS_OUT_CSR_USE_AVALONMM_READ_SLAVE 1
#define FIFO_FPGA_TO_HPS_OUT_CSR_USE_AVALONMM_WRITE_SLAVE 1
#define FIFO_FPGA_TO_HPS_OUT_CSR_USE_AVALONST_SINK 0
#define FIFO_FPGA_TO_HPS_OUT_CSR_USE_AVALONST_SOURCE 0
#define FIFO_FPGA_TO_HPS_OUT_CSR_USE_BACKPRESSURE 1
#define FIFO_FPGA_TO_HPS_OUT_CSR_USE_IRQ 0
#define FIFO_FPGA_TO_HPS_OUT_CSR_USE_PACKET 1
#define FIFO_FPGA_TO_HPS_OUT_CSR_USE_READ_CONTROL 1
#define FIFO_FPGA_TO_HPS_OUT_CSR_USE_REGISTER 0
#define FIFO_FPGA_TO_HPS_OUT_CSR_USE_WRITE_CONTROL 1

/*
 * Macros for device 'fifo_HPS_to_FPGA_in_csr', class 'altera_avalon_fifo'
 * The macros are prefixed with 'FIFO_HPS_TO_FPGA_IN_CSR_'.
 * The prefix is the slave descriptor.
 */
#define FIFO_HPS_TO_FPGA_IN_CSR_COMPONENT_TYPE altera_avalon_fifo
#define FIFO_HPS_TO_FPGA_IN_CSR_COMPONENT_NAME fifo_HPS_to_FPGA
#define FIFO_HPS_TO_FPGA_IN_CSR_BASE 0x40
#define FIFO_HPS_TO_FPGA_IN_CSR_SPAN 32
#define FIFO_HPS_TO_FPGA_IN_CSR_END 0x5f
#define FIFO_HPS_TO_FPGA_IN_CSR_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FIFO_HPS_TO_FPGA_IN_CSR_AVALONMM_AVALONST_DATA_WIDTH 32
#define FIFO_HPS_TO_FPGA_IN_CSR_BITS_PER_SYMBOL 16
#define FIFO_HPS_TO_FPGA_IN_CSR_CHANNEL_WIDTH 8
#define FIFO_HPS_TO_FPGA_IN_CSR_ERROR_WIDTH 8
#define FIFO_HPS_TO_FPGA_IN_CSR_FIFO_DEPTH 1024
#define FIFO_HPS_TO_FPGA_IN_CSR_SINGLE_CLOCK_MODE 0
#define FIFO_HPS_TO_FPGA_IN_CSR_SYMBOLS_PER_BEAT 2
#define FIFO_HPS_TO_FPGA_IN_CSR_USE_AVALONMM_READ_SLAVE 1
#define FIFO_HPS_TO_FPGA_IN_CSR_USE_AVALONMM_WRITE_SLAVE 1
#define FIFO_HPS_TO_FPGA_IN_CSR_USE_AVALONST_SINK 0
#define FIFO_HPS_TO_FPGA_IN_CSR_USE_AVALONST_SOURCE 0
#define FIFO_HPS_TO_FPGA_IN_CSR_USE_BACKPRESSURE 1
#define FIFO_HPS_TO_FPGA_IN_CSR_USE_IRQ 0
#define FIFO_HPS_TO_FPGA_IN_CSR_USE_PACKET 1
#define FIFO_HPS_TO_FPGA_IN_CSR_USE_READ_CONTROL 1
#define FIFO_HPS_TO_FPGA_IN_CSR_USE_REGISTER 0
#define FIFO_HPS_TO_FPGA_IN_CSR_USE_WRITE_CONTROL 1

/*
 * Macros for device 'fast_fifo_FPGA_to_HPS_out', class 'altera_avalon_fifo'
 * The macros are prefixed with 'FAST_FIFO_FPGA_TO_HPS_OUT_'.
 * The prefix is the slave descriptor.
 */
#define FAST_FIFO_FPGA_TO_HPS_OUT_COMPONENT_TYPE altera_avalon_fifo
#define FAST_FIFO_FPGA_TO_HPS_OUT_COMPONENT_NAME fast_fifo_FPGA_to_HPS
#define FAST_FIFO_FPGA_TO_HPS_OUT_BASE 0x60
#define FAST_FIFO_FPGA_TO_HPS_OUT_SPAN 4
#define FAST_FIFO_FPGA_TO_HPS_OUT_END 0x63
#define FAST_FIFO_FPGA_TO_HPS_OUT_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FAST_FIFO_FPGA_TO_HPS_OUT_AVALONMM_AVALONST_DATA_WIDTH 32
#define FAST_FIFO_FPGA_TO_HPS_OUT_BITS_PER_SYMBOL 16
#define FAST_FIFO_FPGA_TO_HPS_OUT_CHANNEL_WIDTH 8
#define FAST_FIFO_FPGA_TO_HPS_OUT_ERROR_WIDTH 8
#define FAST_FIFO_FPGA_TO_HPS_OUT_FIFO_DEPTH 4096
#define FAST_FIFO_FPGA_TO_HPS_OUT_SINGLE_CLOCK_MODE 0
#define FAST_FIFO_FPGA_TO_HPS_OUT_SYMBOLS_PER_BEAT 2
#define FAST_FIFO_FPGA_TO_HPS_OUT_USE_AVALONMM_READ_SLAVE 1
#define FAST_FIFO_FPGA_TO_HPS_OUT_USE_AVALONMM_WRITE_SLAVE 1
#define FAST_FIFO_FPGA_TO_HPS_OUT_USE_AVALONST_SINK 0
#define FAST_FIFO_FPGA_TO_HPS_OUT_USE_AVALONST_SOURCE 0
#define FAST_FIFO_FPGA_TO_HPS_OUT_USE_BACKPRESSURE 1
#define FAST_FIFO_FPGA_TO_HPS_OUT_USE_IRQ 0
#define FAST_FIFO_FPGA_TO_HPS_OUT_USE_PACKET 1
#define FAST_FIFO_FPGA_TO_HPS_OUT_USE_READ_CONTROL 1
#define FAST_FIFO_FPGA_TO_HPS_OUT_USE_REGISTER 0
#define FAST_FIFO_FPGA_TO_HPS_OUT_USE_WRITE_CONTROL 1

/*
 * Macros for device 'fifo_FPGA_to_HPS_out', class 'altera_avalon_fifo'
 * The macros are prefixed with 'FIFO_FPGA_TO_HPS_OUT_'.
 * The prefix is the slave descriptor.
 */
#define FIFO_FPGA_TO_HPS_OUT_COMPONENT_TYPE altera_avalon_fifo
#define FIFO_FPGA_TO_HPS_OUT_COMPONENT_NAME fifo_FPGA_to_HPS
#define FIFO_FPGA_TO_HPS_OUT_BASE 0x64
#define FIFO_FPGA_TO_HPS_OUT_SPAN 4
#define FIFO_FPGA_TO_HPS_OUT_END 0x67
#define FIFO_FPGA_TO_HPS_OUT_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FIFO_FPGA_TO_HPS_OUT_AVALONMM_AVALONST_DATA_WIDTH 32
#define FIFO_FPGA_TO_HPS_OUT_BITS_PER_SYMBOL 16
#define FIFO_FPGA_TO_HPS_OUT_CHANNEL_WIDTH 8
#define FIFO_FPGA_TO_HPS_OUT_ERROR_WIDTH 8
#define FIFO_FPGA_TO_HPS_OUT_FIFO_DEPTH 1024
#define FIFO_FPGA_TO_HPS_OUT_SINGLE_CLOCK_MODE 0
#define FIFO_FPGA_TO_HPS_OUT_SYMBOLS_PER_BEAT 2
#define FIFO_FPGA_TO_HPS_OUT_USE_AVALONMM_READ_SLAVE 1
#define FIFO_FPGA_TO_HPS_OUT_USE_AVALONMM_WRITE_SLAVE 1
#define FIFO_FPGA_TO_HPS_OUT_USE_AVALONST_SINK 0
#define FIFO_FPGA_TO_HPS_OUT_USE_AVALONST_SOURCE 0
#define FIFO_FPGA_TO_HPS_OUT_USE_BACKPRESSURE 1
#define FIFO_FPGA_TO_HPS_OUT_USE_IRQ 0
#define FIFO_FPGA_TO_HPS_OUT_USE_PACKET 1
#define FIFO_FPGA_TO_HPS_OUT_USE_READ_CONTROL 1
#define FIFO_FPGA_TO_HPS_OUT_USE_REGISTER 0
#define FIFO_FPGA_TO_HPS_OUT_USE_WRITE_CONTROL 1

/*
 * Macros for device 'fifo_HPS_to_FPGA_in', class 'altera_avalon_fifo'
 * The macros are prefixed with 'FIFO_HPS_TO_FPGA_IN_'.
 * The prefix is the slave descriptor.
 */
#define FIFO_HPS_TO_FPGA_IN_COMPONENT_TYPE altera_avalon_fifo
#define FIFO_HPS_TO_FPGA_IN_COMPONENT_NAME fifo_HPS_to_FPGA
#define FIFO_HPS_TO_FPGA_IN_BASE 0x68
#define FIFO_HPS_TO_FPGA_IN_SPAN 4
#define FIFO_HPS_TO_FPGA_IN_END 0x6b
#define FIFO_HPS_TO_FPGA_IN_AVALONMM_AVALONMM_DATA_WIDTH 32
#define FIFO_HPS_TO_FPGA_IN_AVALONMM_AVALONST_DATA_WIDTH 32
#define FIFO_HPS_TO_FPGA_IN_BITS_PER_SYMBOL 16
#define FIFO_HPS_TO_FPGA_IN_CHANNEL_WIDTH 8
#define FIFO_HPS_TO_FPGA_IN_ERROR_WIDTH 8
#define FIFO_HPS_TO_FPGA_IN_FIFO_DEPTH 1024
#define FIFO_HPS_TO_FPGA_IN_SINGLE_CLOCK_MODE 0
#define FIFO_HPS_TO_FPGA_IN_SYMBOLS_PER_BEAT 2
#define FIFO_HPS_TO_FPGA_IN_USE_AVALONMM_READ_SLAVE 1
#define FIFO_HPS_TO_FPGA_IN_USE_AVALONMM_WRITE_SLAVE 1
#define FIFO_HPS_TO_FPGA_IN_USE_AVALONST_SINK 0
#define FIFO_HPS_TO_FPGA_IN_USE_AVALONST_SOURCE 0
#define FIFO_HPS_TO_FPGA_IN_USE_BACKPRESSURE 1
#define FIFO_HPS_TO_FPGA_IN_USE_IRQ 0
#define FIFO_HPS_TO_FPGA_IN_USE_PACKET 1
#define FIFO_HPS_TO_FPGA_IN_USE_READ_CONTROL 1
#define FIFO_HPS_TO_FPGA_IN_USE_REGISTER 0
#define FIFO_HPS_TO_FPGA_IN_USE_WRITE_CONTROL 1

/*
 * Macros for device 'RegAddr_pio', class 'altera_avalon_pio'
 * The macros are prefixed with 'REGADDR_PIO_'.
 * The prefix is the slave descriptor.
 */
#define REGADDR_PIO_COMPONENT_TYPE altera_avalon_pio
#define REGADDR_PIO_COMPONENT_NAME RegAddr_pio
#define REGADDR_PIO_BASE 0x1000
#define REGADDR_PIO_SPAN 16
#define REGADDR_PIO_END 0x100f
#define REGADDR_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define REGADDR_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define REGADDR_PIO_CAPTURE 0
#define REGADDR_PIO_DATA_WIDTH 32
#define REGADDR_PIO_DO_TEST_BENCH_WIRING 0
#define REGADDR_PIO_DRIVEN_SIM_VALUE 0
#define REGADDR_PIO_EDGE_TYPE NONE
#define REGADDR_PIO_FREQ 50000000
#define REGADDR_PIO_HAS_IN 0
#define REGADDR_PIO_HAS_OUT 1
#define REGADDR_PIO_HAS_TRI 0
#define REGADDR_PIO_IRQ_TYPE NONE
#define REGADDR_PIO_RESET_VALUE 0

/*
 * Macros for device 'RegContent_pio', class 'altera_avalon_pio'
 * The macros are prefixed with 'REGCONTENT_PIO_'.
 * The prefix is the slave descriptor.
 */
#define REGCONTENT_PIO_COMPONENT_TYPE altera_avalon_pio
#define REGCONTENT_PIO_COMPONENT_NAME RegContent_pio
#define REGCONTENT_PIO_BASE 0x2000
#define REGCONTENT_PIO_SPAN 16
#define REGCONTENT_PIO_END 0x200f
#define REGCONTENT_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define REGCONTENT_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define REGCONTENT_PIO_CAPTURE 0
#define REGCONTENT_PIO_DATA_WIDTH 32
#define REGCONTENT_PIO_DO_TEST_BENCH_WIRING 0
#define REGCONTENT_PIO_DRIVEN_SIM_VALUE 0
#define REGCONTENT_PIO_EDGE_TYPE NONE
#define REGCONTENT_PIO_FREQ 50000000
#define REGCONTENT_PIO_HAS_IN 1
#define REGCONTENT_PIO_HAS_OUT 0
#define REGCONTENT_PIO_HAS_TRI 0
#define REGCONTENT_PIO_IRQ_TYPE NONE
#define REGCONTENT_PIO_RESET_VALUE 0

/*
 * Macros for device 'led_pio', class 'altera_avalon_pio'
 * The macros are prefixed with 'LED_PIO_'.
 * The prefix is the slave descriptor.
 */
#define LED_PIO_COMPONENT_TYPE altera_avalon_pio
#define LED_PIO_COMPONENT_NAME led_pio
#define LED_PIO_BASE 0x3000
#define LED_PIO_SPAN 16
#define LED_PIO_END 0x300f
#define LED_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define LED_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_PIO_CAPTURE 0
#define LED_PIO_DATA_WIDTH 7
#define LED_PIO_DO_TEST_BENCH_WIRING 0
#define LED_PIO_DRIVEN_SIM_VALUE 0
#define LED_PIO_EDGE_TYPE NONE
#define LED_PIO_FREQ 50000000
#define LED_PIO_HAS_IN 0
#define LED_PIO_HAS_OUT 1
#define LED_PIO_HAS_TRI 0
#define LED_PIO_IRQ_TYPE NONE
#define LED_PIO_RESET_VALUE 127

/*
 * Macros for device 'dipsw_pio', class 'altera_avalon_pio'
 * The macros are prefixed with 'DIPSW_PIO_'.
 * The prefix is the slave descriptor.
 */
#define DIPSW_PIO_COMPONENT_TYPE altera_avalon_pio
#define DIPSW_PIO_COMPONENT_NAME dipsw_pio
#define DIPSW_PIO_BASE 0x4000
#define DIPSW_PIO_SPAN 16
#define DIPSW_PIO_END 0x400f
#define DIPSW_PIO_IRQ 0
#define DIPSW_PIO_BIT_CLEARING_EDGE_REGISTER 1
#define DIPSW_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define DIPSW_PIO_CAPTURE 1
#define DIPSW_PIO_DATA_WIDTH 4
#define DIPSW_PIO_DO_TEST_BENCH_WIRING 0
#define DIPSW_PIO_DRIVEN_SIM_VALUE 0
#define DIPSW_PIO_EDGE_TYPE ANY
#define DIPSW_PIO_FREQ 50000000
#define DIPSW_PIO_HAS_IN 1
#define DIPSW_PIO_HAS_OUT 0
#define DIPSW_PIO_HAS_TRI 0
#define DIPSW_PIO_IRQ_TYPE EDGE
#define DIPSW_PIO_RESET_VALUE 0

/*
 * Macros for device 'button_pio', class 'altera_avalon_pio'
 * The macros are prefixed with 'BUTTON_PIO_'.
 * The prefix is the slave descriptor.
 */
#define BUTTON_PIO_COMPONENT_TYPE altera_avalon_pio
#define BUTTON_PIO_COMPONENT_NAME button_pio
#define BUTTON_PIO_BASE 0x5000
#define BUTTON_PIO_SPAN 16
#define BUTTON_PIO_END 0x500f
#define BUTTON_PIO_IRQ 1
#define BUTTON_PIO_BIT_CLEARING_EDGE_REGISTER 1
#define BUTTON_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BUTTON_PIO_CAPTURE 1
#define BUTTON_PIO_DATA_WIDTH 2
#define BUTTON_PIO_DO_TEST_BENCH_WIRING 0
#define BUTTON_PIO_DRIVEN_SIM_VALUE 0
#define BUTTON_PIO_EDGE_TYPE FALLING
#define BUTTON_PIO_FREQ 50000000
#define BUTTON_PIO_HAS_IN 1
#define BUTTON_PIO_HAS_OUT 0
#define BUTTON_PIO_HAS_TRI 0
#define BUTTON_PIO_IRQ_TYPE EDGE
#define BUTTON_PIO_RESET_VALUE 0


#endif /* _ALTERA_HPS_0_H_ */
