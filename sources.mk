# /*======================================================================*/
# /* TIMA LABORATORY                                                      */
# /* Spike with signal and image visual presentation                      */ 
# /* noureddine-as                                                        */
# /* noureddine.aitsaid0@gmail.com                                        */
# /*======================================================================*/

SOURCES = $(SRC_DIR)entry.S \
			$(SRC_DIR)main.c \
			$(SRC_DIR)syscalls.c \
			$(SRC_DIR)trap_handler.c \
 			$(SRC_DIR)oscillo.s \

INCLUDES = -I./include


##################################################################
#  SPECIFIC PARAMETERS
##################################################################
PROJi  = executable
N_PROC ?= 1
ISA ?= rv64imafd
ABI ?= lp64
SPIKE_RBB_PORT = 9824
CEMUL_RBB_PORT = 9823
#SPIKE_SIMULATION ?= -DSPIKE_SIMULATION
ENABLE_DEBUG = 0
MONITOR_BASE = 0x81000000
OSCILLO_BASE = 0x82000000