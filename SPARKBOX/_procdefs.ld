/*************************************************************************
 * Processor-specific object file.  Contains SFR definitions.
 *************************************************************************/
INPUT("processor.o")

/*************************************************************************
 * For interrupt vector handling
 *************************************************************************/
PROVIDE(_vector_spacing = 0x00000001);
_ebase_address  = 0x9D00A000;

/*************************************************************************
 * Memory Address Equates
 *************************************************************************/
_RESET_ADDR              = 0x9D009000;
_BEV_EXCPT_ADDR          = 0x9D009380;
_DBG_EXCPT_ADDR          = 0x9D009480;
_DBG_CODE_ADDR           = 0xBFC02000;
_GEN_EXCPT_ADDR          = _ebase_address + 0x180;

/*************************************************************************
 * Memory Regions
 *
 * Memory regions without attributes cannot be used for orphaned sections.
 * Only sections specifically assigned to these regions can be allocated
 * into these regions.
 *************************************************************************/
MEMORY
{
  kseg0_program_mem    (rx)  : ORIGIN = 0x9D00B000, LENGTH = 0x75000
  kseg0_boot_mem             : ORIGIN = 0x9D009490, LENGTH = 0xB70
  exception_mem              : ORIGIN = 0x9D00A000, LENGTH = 0x1000
  kseg1_boot_mem             : ORIGIN = 0x9D009000, LENGTH = 0x490
  kseg1_data_mem       (w!x) : ORIGIN = 0xA0000000, LENGTH = 0x20000
  sfrs                       : ORIGIN = 0xBF800000, LENGTH = 0x100000
}
