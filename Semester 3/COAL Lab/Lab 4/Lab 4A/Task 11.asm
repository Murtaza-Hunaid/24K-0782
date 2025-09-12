; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
val1 BYTE 10h
val2 WORD 8000h
val3 DWORD 0FFFFh
val4 WORD 7FFFh

msg1 BYTE "After incrementing val2:",0
msg2 BYTE "After subtracting val3 from EAX:",0
msg3 BYTE "After subtracting val4 from val2:",0
msg4 BYTE "Value of BL after moving val1:",0

.code
main PROC
    ; Task i: increment val2
    inc val2
    call DumpRegs

    ; Task ii: subtract val3 from EAX
    mov eax, 12345678h    ; load some test value in eax
    sub eax, val3
    call DumpRegs

    ; Task iii: subtract val4 from val2
    mov ax, val2
    sub ax, val4
    mov val2, ax
    call DumpRegs

    ; Task iv: move val1 into BL
    mov bl, val1
    call DumpRegs

    exit
main ENDP
END main
