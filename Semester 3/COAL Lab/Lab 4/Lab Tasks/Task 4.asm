; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.DATA
    Xval DWORD 25
    Yval DWORD 15
    Zval DWORD 40
    Rval DWORD ?

.CODE
main PROC
    mov eax, Xval
    add eax, Yval
    sub eax, Zval
    neg eax
    mov Rval, eax
    exit
main ENDP
END main
