; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    msg1 BYTE "Original Value = ",0
    msg2 BYTE "Encrypted Value = ",0

.code
main PROC
    mov edx, OFFSET msg1
    call WriteString
    call ReadInt
    mov bl, al
    rol bl, 2
    shr bl, 1   
    mov edx, OFFSET msg2
    call WriteString
    movzx eax, bl
    call WriteBin
    call Crlf
    exit
main ENDP
END main
