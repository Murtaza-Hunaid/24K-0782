; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
val SBYTE -10

.code
main PROC
    movsx ax, val
    movzx bx, val
    call DumpRegs
    exit
main ENDP
END main
