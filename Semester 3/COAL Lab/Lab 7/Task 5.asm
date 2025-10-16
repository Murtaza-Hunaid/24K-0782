; Murtaza Hunaid Terai   24K-0782

INCLUDE Irvine32.inc

.code
main PROC
    mov eax, 10
    
L1:
    cmp eax, 0
    jl L2
    sub eax, 3
    jmp L1
    
L2:
    call WriteInt
    call Crlf
    exit
main ENDP
END main
