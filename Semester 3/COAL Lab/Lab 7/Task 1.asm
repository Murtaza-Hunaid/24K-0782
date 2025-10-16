; Murtaza Hunaid Terai   24K-0782

INCLUDE Irvine32.inc

.data
    msg_on  BYTE "Bit 0 is ON", 0
    msg_off BYTE "Bit 0 is OFF", 0

.code
main PROC
    mov al, 10101010b
    mov bl, 11001100b
    mov cl, 11110000b

    and al, 10101010b
    and bl, 10101010b
    and cl, 10101010b

    or al, 01010101b
    or bl, 01010101b
    or cl, 01010101b

    xor al, 11111111b
    xor bl, 11111111b
    xor cl, 11111111b

    test al, 00000001b
    jz bitoff

    mov edx, OFFSET msg_on
    jmp display

bitoff:
    mov edx, OFFSET msg_off

display:
    call WriteString
    call Crlf
    exit
main ENDP
END main
