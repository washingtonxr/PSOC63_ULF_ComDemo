# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Tornado\Documents\PSoC Creator\CE220291_TCPWM_Square_Wave01\CE220291_TCPWM_Square_Wave01.cydsn\CE220291_TCPWM_Square_Wave01.cyprj
# Date: Thu, 21 Mar 2019 09:19:02 GMT
#set_units -time ns
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyClk_LF} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyFLL} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/fll}]]
create_clock -name {CyClk_HF0} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/hfclk_0}]]
create_clock -name {CyClk_Fast} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/fastclk}]]
create_clock -name {CyClk_Peri} -period 20 -waveform {0 10} [list [get_pins {ClockBlock/periclk}]]
create_generated_clock -name {CyClk_Slow} -source [get_pins {ClockBlock/periclk}] -edges {1 2 3} [list [get_pins {ClockBlock/slowclk}]]
create_generated_clock -name {SysClk_1M} -source [get_pins {ClockBlock/periclk}] -edges {1 51 101} [list [get_pins {ClockBlock/ff_div_11}]]
create_generated_clock -name {ULF_Cap_Clk} -source [get_pins {ClockBlock/periclk}] -edges {1 51 101} [list [get_pins {ClockBlock/ff_div_12}]]
create_generated_clock -name {Clock} -source [get_pins {ClockBlock/periclk}] -edges {1 51 101} [list [get_pins {ClockBlock/ff_div_13}] [get_pins {ClockBlock/ff_div_14}]]
create_generated_clock -name {UART_DEBUG_SCBCLK} -source [get_pins {ClockBlock/periclk}] -edges {1 37 73} [list [get_pins {ClockBlock/ff_div_5}]]
create_clock -name {CyPeriClk_App} -period 20 -waveform {0 10} [list [get_pins {ClockBlock/periclk_App}]]
create_clock -name {CyIMO} -period 125 -waveform {0 62.5} [list [get_pins {ClockBlock/imo}]]


# Component constraints for C:\Users\Tornado\Documents\PSoC Creator\CE220291_TCPWM_Square_Wave01\CE220291_TCPWM_Square_Wave01.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Tornado\Documents\PSoC Creator\CE220291_TCPWM_Square_Wave01\CE220291_TCPWM_Square_Wave01.cydsn\CE220291_TCPWM_Square_Wave01.cyprj
# Date: Thu, 21 Mar 2019 09:18:45 GMT
