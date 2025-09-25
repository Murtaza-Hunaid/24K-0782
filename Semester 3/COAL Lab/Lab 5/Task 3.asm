; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    array1  WORD 45, 32, 71, 44, 92
    array2  WORD 32, 44, 45, 71, 92  
    msg     BYTE "Sorted Array: ",0

.code
main PROC
    mov edx, OFFSET msg
    call WriteString
    call Crlf
    mov ecx, LENGTHOF array2      
    mov esi, OFFSET array2

looper:
    movzx eax, WORD PTR [esi]    
    call WriteDec                
    mov al, ' '                  
    call WriteChar
    add esi, TYPE array2          
    loop looper
    call Crlf
    exit
main ENDP
END main
