INCLUDE Irvine32.inc

.DATA
    signed_val  SBYTE -50
    unsigned_val BYTE 200

.CODE
main PROC
    movzx eax, unsigned_val
    movsx ebx, signed_val
    call DumpRegs
    exit
main ENDP
END main
