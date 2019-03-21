// ======================================================================
// CE220291_TCPWM_Square_Wave01.v generated from TopDesign.cysch
// 03/21/2019 at 09:27
// This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
// ======================================================================

`define CYDEV_CHIP_FAMILY_PSOC3 1
`define CYDEV_CHIP_FAMILY_PSOC4 2
`define CYDEV_CHIP_FAMILY_PSOC5 3
`define CYDEV_CHIP_FAMILY_PSOC6 4
`define CYDEV_CHIP_FAMILY_FM0P 5
`define CYDEV_CHIP_FAMILY_FM3 6
`define CYDEV_CHIP_FAMILY_FM4 7
`define CYDEV_CHIP_FAMILY_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_3A 1
`define CYDEV_CHIP_REVISION_3A_PRODUCTION 3
`define CYDEV_CHIP_REVISION_3A_ES3 3
`define CYDEV_CHIP_REVISION_3A_ES2 1
`define CYDEV_CHIP_REVISION_3A_ES1 0
`define CYDEV_CHIP_MEMBER_5B 2
`define CYDEV_CHIP_REVISION_5B_PRODUCTION 0
`define CYDEV_CHIP_REVISION_5B_ES0 0
`define CYDEV_CHIP_MEMBER_5A 3
`define CYDEV_CHIP_REVISION_5A_PRODUCTION 1
`define CYDEV_CHIP_REVISION_5A_ES1 1
`define CYDEV_CHIP_REVISION_5A_ES0 0
`define CYDEV_CHIP_MEMBER_4G 4
`define CYDEV_CHIP_REVISION_4G_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4G_ES 17
`define CYDEV_CHIP_REVISION_4G_ES2 33
`define CYDEV_CHIP_MEMBER_4U 5
`define CYDEV_CHIP_REVISION_4U_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4E 6
`define CYDEV_CHIP_REVISION_4E_PRODUCTION 0
`define CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD 0
`define CYDEV_CHIP_MEMBER_4O 7
`define CYDEV_CHIP_REVISION_4O_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4R 8
`define CYDEV_CHIP_REVISION_4R_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4T 9
`define CYDEV_CHIP_REVISION_4T_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4N 10
`define CYDEV_CHIP_REVISION_4N_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4S 11
`define CYDEV_CHIP_REVISION_4S_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4Q 12
`define CYDEV_CHIP_REVISION_4Q_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4D 13
`define CYDEV_CHIP_REVISION_4D_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4J 14
`define CYDEV_CHIP_REVISION_4J_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4K 15
`define CYDEV_CHIP_REVISION_4K_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4V 16
`define CYDEV_CHIP_REVISION_4V_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4H 17
`define CYDEV_CHIP_REVISION_4H_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4A 18
`define CYDEV_CHIP_REVISION_4A_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4A_ES0 17
`define CYDEV_CHIP_MEMBER_4F 19
`define CYDEV_CHIP_REVISION_4F_PRODUCTION 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0
`define CYDEV_CHIP_MEMBER_4P 20
`define CYDEV_CHIP_REVISION_4P_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4M 21
`define CYDEV_CHIP_REVISION_4M_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4L 22
`define CYDEV_CHIP_REVISION_4L_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4I 23
`define CYDEV_CHIP_REVISION_4I_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_6A 24
`define CYDEV_CHIP_REVISION_6A_ES 17
`define CYDEV_CHIP_REVISION_6A_PRODUCTION 33
`define CYDEV_CHIP_REVISION_6A_NO_UDB 33
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1 25
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2 26
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3 27
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_FM3 28
`define CYDEV_CHIP_REVISION_FM3_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_FM4 29
`define CYDEV_CHIP_REVISION_FM4_PRODUCTION 0
`define CYDEV_CHIP_FAMILY_USED 4
`define CYDEV_CHIP_MEMBER_USED 24
`define CYDEV_CHIP_REVISION_USED 33
// TCPWM_PWM_PDL_v1_0(ClockPrescaler=0, Compare0=4, Compare1=16384, CountInput=7, CountInputMasked=3, DeadClocks=0, EnableCompareSwap=false, EnablePeriodSwap=false, InterruptSource=1, InvertPwm=false, InvertPwm_n=false, KillInput=7, KillInputMasked=3, KillMode=2, Period0=7, Period1=32768, PwmAlignment=0, PwmMode=4, ReloadInput=7, ReloadInputMasked=3, Resolution=16, RunMode=0, StartInput=7, StartInputMasked=3, SwapInput=7, SwapInputMasked=3, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=TCPWM_PWM_PDL_v1_0, CY_CONFIG_TITLE=ULF_Carrier, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=ULF_Carrier, CY_INSTANCE_SHORT_NAME=ULF_Carrier, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=0, CY_PDL_DRIVER_NAME=tcpwm, CY_PDL_DRIVER_REQ_VERSION=1.0.0, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.2, INSTANCE_NAME=ULF_Carrier, )
module TCPWM_PWM_PDL_v1_0_0 (
    kill,
    reload,
    start,
    count,
    swap,
    interrupt,
    ovrflw,
    undrflw,
    compare,
    clock,
    pwm,
    pwm_n);
    input       kill;
    input       reload;
    input       start;
    input       count;
    input       swap;
    output      interrupt;
    output      ovrflw;
    output      undrflw;
    output      compare;
    input       clock;
    output      pwm;
    output      pwm_n;



    cy_mxs40_tcpwm_v1_0 TCPWM (
        .clock(clock),
        .capture(swap),
        .count(count),
        .reload(reload),
        .stop(kill),
        .start(start),
        .tr_underflow(undrflw),
        .tr_compare_match(compare),
        .tr_overflow(ovrflw),
        .line_compl(pwm_n),
        .line(pwm),
        .interrupt(interrupt));
    defparam TCPWM.exact_width = 0;
    defparam TCPWM.width = 16;



endmodule

// TCPWM_Counter_PDL_v1_0(CaptureInput=7, CaptureInputMasked=3, ClockPrescaler=0, Compare0=16384, Compare1=16384, CompareOrCapture=2, CountDirection=0, CountInput=7, CountInputMasked=3, EnableCompareSwap=false, InterruptSource=1, Period=7, ReloadInput=7, ReloadInputMasked=3, Resolution=16, RunMode=0, StartInput=7, StartInputMasked=3, StopInput=7, StopInputMasked=3, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=TCPWM_Counter_PDL_v1_0, CY_CONFIG_TITLE=ULF_Counter, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=ULF_Counter, CY_INSTANCE_SHORT_NAME=ULF_Counter, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=0, CY_PDL_DRIVER_NAME=tcpwm, CY_PDL_DRIVER_REQ_VERSION=1.0.0, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.2, INSTANCE_NAME=ULF_Counter, )
module TCPWM_Counter_PDL_v1_0_1 (
    stop,
    reload,
    start,
    count,
    capture,
    interrupt,
    ovrflw,
    undrflw,
    compare,
    clock);
    input       stop;
    input       reload;
    input       start;
    input       count;
    input       capture;
    output      interrupt;
    output      ovrflw;
    output      undrflw;
    output      compare;
    input       clock;


          wire  Net_2;
          wire  Net_1;

    cy_mxs40_tcpwm_v1_0 TCPWM (
        .clock(clock),
        .capture(capture),
        .count(count),
        .reload(reload),
        .stop(stop),
        .start(start),
        .tr_underflow(undrflw),
        .tr_compare_match(compare),
        .tr_overflow(ovrflw),
        .line_compl(Net_1),
        .line(Net_2),
        .interrupt(interrupt));
    defparam TCPWM.exact_width = 0;
    defparam TCPWM.width = 16;



endmodule

// TCPWM_Counter_PDL_v1_0(CaptureInput=7, CaptureInputMasked=3, ClockPrescaler=4, Compare0=16384, Compare1=16384, CompareOrCapture=2, CountDirection=0, CountInput=7, CountInputMasked=3, EnableCompareSwap=false, InterruptSource=1, Period=625, ReloadInput=7, ReloadInputMasked=3, Resolution=16, RunMode=0, StartInput=7, StartInputMasked=3, StopInput=7, StopInputMasked=3, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=TCPWM_Counter_PDL_v1_0, CY_CONFIG_TITLE=System_Tick, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=System_Tick, CY_INSTANCE_SHORT_NAME=System_Tick, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=0, CY_PDL_DRIVER_NAME=tcpwm, CY_PDL_DRIVER_REQ_VERSION=1.0.0, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.2, INSTANCE_NAME=System_Tick, )
module TCPWM_Counter_PDL_v1_0_2 (
    stop,
    reload,
    start,
    count,
    capture,
    interrupt,
    ovrflw,
    undrflw,
    compare,
    clock);
    input       stop;
    input       reload;
    input       start;
    input       count;
    input       capture;
    output      interrupt;
    output      ovrflw;
    output      undrflw;
    output      compare;
    input       clock;


          wire  Net_2;
          wire  Net_1;

    cy_mxs40_tcpwm_v1_0 TCPWM (
        .clock(clock),
        .capture(capture),
        .count(count),
        .reload(reload),
        .stop(stop),
        .start(start),
        .tr_underflow(undrflw),
        .tr_compare_match(compare),
        .tr_overflow(ovrflw),
        .line_compl(Net_1),
        .line(Net_2),
        .interrupt(interrupt));
    defparam TCPWM.exact_width = 0;
    defparam TCPWM.width = 16;



endmodule

// Component: cy_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`endif

// Component: ZeroTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`endif

// Component: or_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0\or_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0\or_v1_0.v"
`endif

// SCB_UART_PDL_v2_0(BaudRate=115200, BitsOrder=0, BreakSignalBits=11, BufferMinSize=64, ByteMode=true, ClkFreqDes=1382.4, ClkMinusTolerance=5, ClkPlusTolerance=5, ClockFromTerm=false, ComMode=0, CtsPolarity=0, CtsTermEnable=false, DataWidth=8, Direction=3, DropOnFrameErr=false, DropOnParityErr=false, EnableCts=false, EnableInputFilter=false, EnableMultiProc=false, EnableRts=false, EnableRxOutput=false, EnableTxEn=false, EnableTxOutput=false, InterruptMode=1, InterruptTermEnable=false, IntrRxBreakDetected=false, IntrRxFrameErr=false, IntrRxFull=false, IntrRxNotEmpty=false, IntrRxOverflow=false, IntrRxParityErr=false, IntrRxTrigger=false, IntrRxUnderflow=false, IntrTxEmpty=false, IntrTxNotFull=false, IntrTxOverflow=false, IntrTxTrigger=false, IntrTxUartDone=false, IntrTxUartLostArb=false, IntrTxUartNack=false, IntrTxUnderflow=false, IrdaLowPower=false, IrdaPolarity=0, IsCtsPinAllowed=true, IsDmaCapable=true, IsEnableInputFilterVisible=true, IsMultiprocessorModeAvailable=false, IsRtsPinAllowed=true, IsRtsTriggerLevelVisible=false, IsRxIntrSourcesVisible=false, IsRxTriggerLevelVisible=false, IsTxIntrSourcesVisible=false, IsTxTriggerLevelVisible=false, MaxFifoLevel=127, MpRxAcceptAddress=false, MpRxAddress=0, MpRxAddressMask=255, OvsFactor=12, ParityType=0, PreconfigureIO=false, RemoveCtsPin=true, RemoveIntr=false, RemoveRtsPin=true, RemoveRxPin=false, RemoveRxTxPin=true, RemoveTxEnPin=true, RemoveTxPin=false, RtsPolarity=0, RtsTermEnable=false, RtsTriggerLevel=63, RxIntrMask=0, RxTermEnable=false, RxTriggerLevel=63, RxTxTermEnable=false, ShowTerminals=false, SmCardRetryOnNack=false, StopBits=2, SymbolShape=0, TriggerOutputEnable=false, TxEnTermEnable=false, TxIntrMask=0, TxTermEnable=false, TxTriggerLevel=63, UartMode=2, UseIntr=true, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=SCB_UART_PDL_v2_0, CY_CONFIG_TITLE=UART_DEBUG, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=UART_DEBUG, CY_INSTANCE_SHORT_NAME=UART_DEBUG, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=0, CY_PDL_DRIVER_NAME=scb, CY_PDL_DRIVER_REQ_VERSION=2.0.0, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.2, INSTANCE_NAME=UART_DEBUG, )
module SCB_UART_PDL_v2_0_3 (
    cts_in,
    tx_out,
    rts_out,
    interrupt,
    clock,
    rx_dma,
    tx_dma,
    rx_in,
    rx_tx_out,
    tx_en_out);
    input       cts_in;
    output      tx_out;
    output      rts_out;
    output      interrupt;
    input       clock;
    output      rx_dma;
    output      tx_dma;
    input       rx_in;
    output      rx_tx_out;
    output      tx_en_out;


          wire  rx_wire;
          wire  tx_wire;
          wire  rts_wire;
          wire  cts_wire;
          wire  intr_wire;
          wire  clock_wire;
          wire  Net_161;
          wire  Net_157;
          wire  Net_156;
          wire [3:0] Net_155;
          wire  Net_154;
          wire  Net_150;
          wire  Net_149;
          wire  Net_148;
          wire  Net_147;
          wire  Net_146;
          wire  Net_145;
          wire  Net_1172;
          wire  Net_23;
          wire  tx_en_wire;
          wire  Net_47;
          wire  Net_22;
          wire  Net_24;
          wire  Net_847;


	cy_clock_v1_0
		#(.id("cebea611-5e3e-4589-8be1-fcab02586490/b68e5b9d-7828-482d-a282-930f990e3b3e"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("723379629.62963"),
		  .is_direct(0),
		  .is_digital(0))
		SCBCLK
		 (.clock_out(Net_847));


	// clock_VM (cy_virtualmux_v1_0)
	assign clock_wire = Net_847;

    ZeroTerminal ZeroTerminal_7 (
        .z(Net_22));


    assign Net_23 = Net_22 | Net_847;

	wire [0:0] tmpFB_0__tx_net;
	wire [0:0] tmpIO_0__tx_net;
	electrical [0:0] tmpSIOVREF__tx_net;

	cy_mxs40_gpio_v1_0
		#(.id("cebea611-5e3e-4589-8be1-fcab02586490/65f3af6c-759b-4ccb-8c66-5c95ba1f5f4f"),
		  .width(1),
		  .sio_grp_cnt(0),
		  .drive_mode("6"),
		  .ibuf_enabled("0"),
		  .init_dr_st("1"),
		  .input_sync("0"),
		  .intr_mode("0"),
		  .io_voltage(""),
		  .output_conn("1"),
		  .oe_conn("0"),
		  .output_sync("0"),
		  .oe_sync("0"),
		  .drive_strength("0"),
		  .max_frequency("100"),
		  .i2c_mode("0"),
		  .output_current_cap("8"),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .slew_rate("0"),
		  .vtrip("0"),
		  .use_annotation("0"),
		  .hotswap_needed("0"))
		tx
		 (.oe({1'b1}),
		  .y({tx_wire}),
		  .fb({tmpFB_0__tx_net[0:0]}),
		  .io({tmpIO_0__tx_net[0:0]}),
		  .siovref(tmpSIOVREF__tx_net));


	wire [0:0] tmpIO_0__rx_net;
	electrical [0:0] tmpSIOVREF__rx_net;

	cy_mxs40_gpio_v1_0
		#(.id("cebea611-5e3e-4589-8be1-fcab02586490/b7e8018e-1ef7-49c0-b5a5-61641a03e31c"),
		  .width(1),
		  .sio_grp_cnt(0),
		  .drive_mode("0"),
		  .ibuf_enabled("1"),
		  .init_dr_st("1"),
		  .input_sync("0"),
		  .intr_mode("0"),
		  .io_voltage(""),
		  .output_conn("0"),
		  .oe_conn("0"),
		  .output_sync("0"),
		  .oe_sync("0"),
		  .drive_strength("0"),
		  .max_frequency("100"),
		  .i2c_mode("0"),
		  .output_current_cap("8"),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .slew_rate("0"),
		  .vtrip("0"),
		  .use_annotation("0"),
		  .hotswap_needed("0"))
		rx
		 (.oe({1'b1}),
		  .y({1'b0}),
		  .fb({Net_1172}),
		  .io({tmpIO_0__rx_net[0:0]}),
		  .siovref(tmpSIOVREF__rx_net));


	// rx_VM (cy_virtualmux_v1_0)
	assign rx_wire = Net_1172;

	// cts_VM (cy_virtualmux_v1_0)
	assign cts_wire = cts_in;


	cy_mxs40_isr_v1_0
		#(.deepsleep_required(0),
		  .int_type(2'b10))
		SCB_IRQ
		 (.int_signal(intr_wire));


    cy_mxs40_scb_v1_10 SCB (
        .clock(clock_wire),
        .uart_rx(rx_wire),
        .uart_cts(cts_wire),
        .i2c_scl(Net_145),
        .i2c_sda(Net_146),
        .spi_clk_s(1'b0),
        .spi_select_s(1'b0),
        .spi_miso_m(1'b0),
        .spi_mosi_s(1'b0),
        .uart_tx(tx_wire),
        .uart_rts(rts_wire),
        .uart_tx_en(tx_en_wire),
        .spi_clk_m(Net_154),
        .spi_select_m(Net_155[3:0]),
        .spi_mosi_m(Net_156),
        .spi_miso_s(Net_157),
        .interrupt(intr_wire),
        .tr_tx_req(tx_dma),
        .tr_rx_req(rx_dma),
        .tr_i2c_scl_filtered(Net_161));
    defparam SCB.master = 0;
    defparam SCB.mode = 2;
    defparam SCB.requires_io_preconfigure = 0;


    assign tx_out = tx_wire;

    assign rts_out = rts_wire;

    assign interrupt = intr_wire;

    assign rx_tx_out = tx_wire;

    assign tx_en_out = tx_en_wire;


endmodule

// TCPWM_Counter_PDL_v1_0(CaptureInput=2, CaptureInputMasked=2, ClockPrescaler=0, Compare0=16384, Compare1=16384, CompareOrCapture=2, CountDirection=0, CountInput=7, CountInputMasked=3, EnableCompareSwap=false, InterruptSource=2, Period=65535, ReloadInput=7, ReloadInputMasked=3, Resolution=16, RunMode=0, StartInput=7, StartInputMasked=3, StopInput=7, StopInputMasked=3, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=TCPWM_Counter_PDL_v1_0, CY_CONFIG_TITLE=ULF_Capture, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=ULF_Capture, CY_INSTANCE_SHORT_NAME=ULF_Capture, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=0, CY_PDL_DRIVER_NAME=tcpwm, CY_PDL_DRIVER_REQ_VERSION=1.0.0, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.2, INSTANCE_NAME=ULF_Capture, )
module TCPWM_Counter_PDL_v1_0_4 (
    stop,
    reload,
    start,
    count,
    capture,
    interrupt,
    ovrflw,
    undrflw,
    compare,
    clock);
    input       stop;
    input       reload;
    input       start;
    input       count;
    input       capture;
    output      interrupt;
    output      ovrflw;
    output      undrflw;
    output      compare;
    input       clock;


          wire  Net_2;
          wire  Net_1;

    cy_mxs40_tcpwm_v1_0 TCPWM (
        .clock(clock),
        .capture(capture),
        .count(count),
        .reload(reload),
        .stop(stop),
        .start(start),
        .tr_underflow(undrflw),
        .tr_compare_match(compare),
        .tr_overflow(ovrflw),
        .line_compl(Net_1),
        .line(Net_2),
        .interrupt(interrupt));
    defparam TCPWM.exact_width = 0;
    defparam TCPWM.width = 16;



endmodule

// top
module top ;

          wire  Net_248;
          wire  Net_247;
          wire  Net_246;
          wire  Net_245;
          wire  Net_244;
          wire  Net_243;
          wire  Net_242;
          wire  Net_241;
          wire  Net_129;
          wire  Net_128;
          wire  Net_127;
          wire  Net_126;
          wire  Net_125;
          wire  Net_124;
          wire  Net_123;
          wire  Net_122;
          wire  Net_121;
          wire  Net_120;
          wire  Net_113;
          wire  Net_108;
          wire  Net_107;
          wire  Net_106;
          wire  Net_104;
          wire  Net_103;
          wire  Net_102;
          wire  Net_101;
          wire  Net_100;
          wire  Net_92;
          wire  Net_91;
          wire  Net_90;
          wire  Net_130;
          wire  Net_87;
          wire  Net_86;
          wire  Net_85;
          wire  Net_84;
          wire  Net_26;
          wire  Net_266;
          wire  Net_265;
          wire  Net_264;
          wire  Net_263;
          wire  Net_262;
          wire  Net_261;
          wire  Net_260;
          wire  Net_259;
          wire  Net_258;
          wire  Net_272;
          wire  Net_269;
          wire  Net_32;
          wire  Net_116;
          wire  Net_140;
          wire  Net_149;
          wire  Net_164;
          wire  Net_151;
          wire  Net_97;
          wire  Net_114;
          wire  Net_109;
          wire  Net_10;

    TCPWM_PWM_PDL_v1_0_0 ULF_Carrier (
        .kill(1'b0),
        .reload(1'b0),
        .start(1'b0),
        .count(1'b1),
        .swap(1'b0),
        .interrupt(Net_32),
        .ovrflw(Net_263),
        .undrflw(Net_264),
        .compare(Net_265),
        .clock(Net_10),
        .pwm(Net_266),
        .pwm_n(Net_116));


	cy_clock_v1_0
		#(.id("a368800e-ab5c-421c-a161-daae557802f6"),
		  .source_clock_id("2FB4EC85-8328-4C5A-9ED9-8B63060178EB"),
		  .divisor(0),
		  .period("1000000000"),
		  .is_direct(0),
		  .is_digital(0))
		Clock
		 (.clock_out(Net_10));


	wire [0:0] tmpFB_0__ULF_OUT_net;
	wire [0:0] tmpIO_0__ULF_OUT_net;
	electrical [0:0] tmpSIOVREF__ULF_OUT_net;

	cy_mxs40_gpio_v1_0
		#(.id("a61270bc-07ec-447d-ac9e-34cfe85c30e9"),
		  .width(1),
		  .sio_grp_cnt(0),
		  .drive_mode("6"),
		  .ibuf_enabled("0"),
		  .init_dr_st("1"),
		  .input_sync("0"),
		  .intr_mode("0"),
		  .io_voltage(""),
		  .output_conn("1"),
		  .oe_conn("0"),
		  .output_sync("0"),
		  .oe_sync("0"),
		  .drive_strength("0"),
		  .max_frequency("100"),
		  .i2c_mode("0"),
		  .output_current_cap("8"),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .slew_rate("0"),
		  .vtrip("0"),
		  .use_annotation("0"),
		  .hotswap_needed("0"))
		ULF_OUT
		 (.oe({1'b1}),
		  .y({Net_116}),
		  .fb({tmpFB_0__ULF_OUT_net[0:0]}),
		  .io({tmpIO_0__ULF_OUT_net[0:0]}),
		  .siovref(tmpSIOVREF__ULF_OUT_net));


	wire [0:0] tmpIO_0__ULF_IN_net;
	electrical [0:0] tmpSIOVREF__ULF_IN_net;

	cy_mxs40_gpio_v1_0
		#(.id("dd07b6f8-34a1-4650-b372-2e9c028f770a"),
		  .width(1),
		  .sio_grp_cnt(0),
		  .drive_mode("0"),
		  .ibuf_enabled("1"),
		  .init_dr_st("0"),
		  .input_sync("0"),
		  .intr_mode("0"),
		  .io_voltage(""),
		  .output_conn("0"),
		  .oe_conn("0"),
		  .output_sync("0"),
		  .oe_sync("0"),
		  .drive_strength("0"),
		  .max_frequency("100"),
		  .i2c_mode("0"),
		  .output_current_cap("8"),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .slew_rate("0"),
		  .vtrip("0"),
		  .use_annotation("0"),
		  .hotswap_needed("0"))
		ULF_IN
		 (.oe({1'b1}),
		  .y({1'b0}),
		  .fb({Net_164}),
		  .io({tmpIO_0__ULF_IN_net[0:0]}),
		  .siovref(tmpSIOVREF__ULF_IN_net));


	wire [0:0] tmpFB_0__ULF_BB_net;
	wire [0:0] tmpIO_0__ULF_BB_net;
	electrical [0:0] tmpSIOVREF__ULF_BB_net;

	cy_mxs40_gpio_v1_0
		#(.id("c6c640e9-3022-42d1-957e-5f4b827a4274"),
		  .width(1),
		  .sio_grp_cnt(0),
		  .drive_mode("6"),
		  .ibuf_enabled("0"),
		  .init_dr_st("0"),
		  .input_sync("0"),
		  .intr_mode("0"),
		  .io_voltage(""),
		  .output_conn("0"),
		  .oe_conn("0"),
		  .output_sync("0"),
		  .oe_sync("0"),
		  .drive_strength("0"),
		  .max_frequency("100"),
		  .i2c_mode("0"),
		  .output_current_cap("8"),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .slew_rate("0"),
		  .vtrip("0"),
		  .use_annotation("0"),
		  .hotswap_needed("0"))
		ULF_BB
		 (.oe({1'b1}),
		  .y({1'b0}),
		  .fb({tmpFB_0__ULF_BB_net[0:0]}),
		  .io({tmpIO_0__ULF_BB_net[0:0]}),
		  .siovref(tmpSIOVREF__ULF_BB_net));



	cy_mxs40_isr_v1_0
		#(.deepsleep_required(0),
		  .int_type(2'b10))
		SysInt_ULFCarrierCnt
		 (.int_signal(Net_32));


    TCPWM_Counter_PDL_v1_0_1 ULF_Counter (
        .stop(1'b0),
        .reload(1'b0),
        .start(1'b0),
        .count(1'b1),
        .capture(1'b0),
        .interrupt(Net_97),
        .ovrflw(Net_90),
        .undrflw(Net_91),
        .compare(Net_92),
        .clock(Net_10));

	wire [0:0] tmpFB_0__SW2_net;
	wire [0:0] tmpIO_0__SW2_net;
	electrical [0:0] tmpSIOVREF__SW2_net;

	cy_mxs40_gpio_v1_0
		#(.id("4cca878b-77b5-471d-8aeb-ad6925202455"),
		  .width(1),
		  .sio_grp_cnt(0),
		  .drive_mode("2"),
		  .ibuf_enabled("1"),
		  .init_dr_st("1"),
		  .input_sync("0"),
		  .intr_mode("2"),
		  .io_voltage(""),
		  .output_conn("0"),
		  .oe_conn("0"),
		  .output_sync("0"),
		  .oe_sync("0"),
		  .drive_strength("0"),
		  .max_frequency("100"),
		  .i2c_mode("0"),
		  .output_current_cap("8"),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .slew_rate("0"),
		  .vtrip("0"),
		  .use_annotation("0"),
		  .hotswap_needed("0"))
		SW2
		 (.oe({1'b1}),
		  .y({1'b0}),
		  .fb({tmpFB_0__SW2_net[0:0]}),
		  .io({tmpIO_0__SW2_net[0:0]}),
		  .siovref(tmpSIOVREF__SW2_net));



	cy_mxs40_isr_v1_0
		#(.deepsleep_required(0),
		  .int_type(2'b10))
		SysInt_ULFMainCnt
		 (.int_signal(Net_97));


	wire [0:0] tmpFB_0__Red_LED_net;
	wire [0:0] tmpIO_0__Red_LED_net;
	electrical [0:0] tmpSIOVREF__Red_LED_net;

	cy_mxs40_gpio_v1_0
		#(.id("7520b3c1-2a28-4a48-9750-6ba5cf03ac56"),
		  .width(1),
		  .sio_grp_cnt(0),
		  .drive_mode("6"),
		  .ibuf_enabled("0"),
		  .init_dr_st("0"),
		  .input_sync("0"),
		  .intr_mode("0"),
		  .io_voltage(""),
		  .output_conn("0"),
		  .oe_conn("0"),
		  .output_sync("0"),
		  .oe_sync("0"),
		  .drive_strength("0"),
		  .max_frequency("100"),
		  .i2c_mode("0"),
		  .output_current_cap("8"),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .slew_rate("0"),
		  .vtrip("0"),
		  .use_annotation("0"),
		  .hotswap_needed("0"))
		Red_LED
		 (.oe({1'b1}),
		  .y({1'b0}),
		  .fb({tmpFB_0__Red_LED_net[0:0]}),
		  .io({tmpIO_0__Red_LED_net[0:0]}),
		  .siovref(tmpSIOVREF__Red_LED_net));


	wire [0:0] tmpFB_0__Orange_LED_net;
	wire [0:0] tmpIO_0__Orange_LED_net;
	electrical [0:0] tmpSIOVREF__Orange_LED_net;

	cy_mxs40_gpio_v1_0
		#(.id("882a4d54-6321-45a4-9a46-a77406a03b3a"),
		  .width(1),
		  .sio_grp_cnt(0),
		  .drive_mode("6"),
		  .ibuf_enabled("0"),
		  .init_dr_st("0"),
		  .input_sync("0"),
		  .intr_mode("0"),
		  .io_voltage(""),
		  .output_conn("0"),
		  .oe_conn("0"),
		  .output_sync("0"),
		  .oe_sync("0"),
		  .drive_strength("0"),
		  .max_frequency("100"),
		  .i2c_mode("0"),
		  .output_current_cap("8"),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .slew_rate("0"),
		  .vtrip("0"),
		  .use_annotation("0"),
		  .hotswap_needed("0"))
		Orange_LED
		 (.oe({1'b1}),
		  .y({1'b0}),
		  .fb({tmpFB_0__Orange_LED_net[0:0]}),
		  .io({tmpIO_0__Orange_LED_net[0:0]}),
		  .siovref(tmpSIOVREF__Orange_LED_net));


    TCPWM_Counter_PDL_v1_0_2 System_Tick (
        .stop(1'b0),
        .reload(1'b0),
        .start(1'b0),
        .count(1'b1),
        .capture(1'b0),
        .interrupt(Net_114),
        .ovrflw(Net_106),
        .undrflw(Net_107),
        .compare(Net_108),
        .clock(Net_109));


	cy_clock_v1_0
		#(.id("cf4a4c6a-af97-4f3f-b4ba-5b66884dad4c"),
		  .source_clock_id("2FB4EC85-8328-4C5A-9ED9-8B63060178EB"),
		  .divisor(0),
		  .period("1000000000"),
		  .is_direct(0),
		  .is_digital(0))
		SysClk_1M
		 (.clock_out(Net_109));



	cy_mxs40_isr_v1_0
		#(.deepsleep_required(0),
		  .int_type(2'b10))
		SysInt_Tick
		 (.int_signal(Net_114));


    SCB_UART_PDL_v2_0_3 UART_DEBUG (
        .cts_in(1'b0),
        .tx_out(Net_121),
        .rts_out(Net_122),
        .interrupt(Net_123),
        .clock(1'b0),
        .rx_dma(Net_125),
        .tx_dma(Net_126),
        .rx_in(1'b0),
        .rx_tx_out(Net_128),
        .tx_en_out(Net_129));

    TCPWM_Counter_PDL_v1_0_4 ULF_Capture (
        .stop(1'b0),
        .reload(1'b0),
        .start(1'b0),
        .count(1'b1),
        .capture(Net_164),
        .interrupt(Net_149),
        .ovrflw(Net_245),
        .undrflw(Net_246),
        .compare(Net_247),
        .clock(Net_140));


	cy_clock_v1_0
		#(.id("942ae398-75c4-47c8-9af6-6fa57fac65ba"),
		  .source_clock_id("2FB4EC85-8328-4C5A-9ED9-8B63060178EB"),
		  .divisor(0),
		  .period("1000000000"),
		  .is_direct(0),
		  .is_digital(0))
		ULF_Cap_Clk
		 (.clock_out(Net_140));



	cy_mxs40_isr_v1_0
		#(.deepsleep_required(0),
		  .int_type(2'b10))
		SysInt_ULFBasebandCnt
		 (.int_signal(Net_149));


	wire [0:0] tmpFB_0__ULF_BO_net;
	wire [0:0] tmpIO_0__ULF_BO_net;
	electrical [0:0] tmpSIOVREF__ULF_BO_net;

	cy_mxs40_gpio_v1_0
		#(.id("9e94cdbb-df49-4335-b2cd-cde5f6ea9bf8"),
		  .width(1),
		  .sio_grp_cnt(0),
		  .drive_mode("6"),
		  .ibuf_enabled("0"),
		  .init_dr_st("0"),
		  .input_sync("0"),
		  .intr_mode("0"),
		  .io_voltage(""),
		  .output_conn("0"),
		  .oe_conn("0"),
		  .output_sync("0"),
		  .oe_sync("0"),
		  .drive_strength("0"),
		  .max_frequency("100"),
		  .i2c_mode("0"),
		  .output_current_cap("8"),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .slew_rate("0"),
		  .vtrip("0"),
		  .use_annotation("0"),
		  .hotswap_needed("0"))
		ULF_BO
		 (.oe({1'b1}),
		  .y({1'b0}),
		  .fb({tmpFB_0__ULF_BO_net[0:0]}),
		  .io({tmpIO_0__ULF_BO_net[0:0]}),
		  .siovref(tmpSIOVREF__ULF_BO_net));


	wire [0:0] tmpFB_0__ULF_TXen_net;
	wire [0:0] tmpIO_0__ULF_TXen_net;
	electrical [0:0] tmpSIOVREF__ULF_TXen_net;

	cy_mxs40_gpio_v1_0
		#(.id("05c113f4-54f0-437a-b503-54a987a94963"),
		  .width(1),
		  .sio_grp_cnt(0),
		  .drive_mode("6"),
		  .ibuf_enabled("0"),
		  .init_dr_st("0"),
		  .input_sync("0"),
		  .intr_mode("0"),
		  .io_voltage(""),
		  .output_conn("0"),
		  .oe_conn("0"),
		  .output_sync("0"),
		  .oe_sync("0"),
		  .drive_strength("0"),
		  .max_frequency("100"),
		  .i2c_mode("0"),
		  .output_current_cap("8"),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .slew_rate("0"),
		  .vtrip("0"),
		  .use_annotation("0"),
		  .hotswap_needed("0"))
		ULF_TXen
		 (.oe({1'b1}),
		  .y({1'b0}),
		  .fb({tmpFB_0__ULF_TXen_net[0:0]}),
		  .io({tmpIO_0__ULF_TXen_net[0:0]}),
		  .siovref(tmpSIOVREF__ULF_TXen_net));


	wire [0:0] tmpFB_0__SW3_net;
	wire [0:0] tmpIO_0__SW3_net;
	electrical [0:0] tmpSIOVREF__SW3_net;

	cy_mxs40_gpio_v1_0
		#(.id("a953aec0-263b-4feb-91da-793994dce3e5"),
		  .width(1),
		  .sio_grp_cnt(0),
		  .drive_mode("0"),
		  .ibuf_enabled("1"),
		  .init_dr_st("0"),
		  .input_sync("0"),
		  .intr_mode("3"),
		  .io_voltage(""),
		  .output_conn("0"),
		  .oe_conn("0"),
		  .output_sync("0"),
		  .oe_sync("0"),
		  .drive_strength("0"),
		  .max_frequency("100"),
		  .i2c_mode("0"),
		  .output_current_cap("8"),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .slew_rate("0"),
		  .vtrip("0"),
		  .use_annotation("0"),
		  .hotswap_needed("0"))
		SW3
		 (.oe({1'b1}),
		  .y({1'b0}),
		  .fb({tmpFB_0__SW3_net[0:0]}),
		  .io({tmpIO_0__SW3_net[0:0]}),
		  .siovref(tmpSIOVREF__SW3_net));



	cy_mxs40_isr_v1_0
		#(.deepsleep_required(0),
		  .int_type(2'b10))
		SysInt_SW3
		 (.int_signal(Net_269));



	cy_mxs40_isr_v1_0
		#(.deepsleep_required(0),
		  .int_type(2'b10))
		SysInt_SW
		 (.int_signal(Net_272));



	cy_gsref_v1_0
		#(.guid("8C3B410E-0600-5ECF-95DD-0AF91BF8D8A7"))
		GS4SW2
		 (.sig_out(Net_272));



	cy_gsref_v1_0
		#(.guid("C752BC24-D910-59DF-BA09-8582177BFFE2"))
		GS4SW3
		 (.sig_out(Net_269));




endmodule

