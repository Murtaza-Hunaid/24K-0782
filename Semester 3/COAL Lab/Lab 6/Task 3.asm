; Murtaza Hunaid Terai   24K-0782

INCLUDE Irvine32.inc

.data
    count DWORD 1
    star BYTE '*'

.code
main PROC
    mov ecx, 5    
    mov ebx, 1          

    OuterLoop:
        mov edx, ecx           
        mov ecx, count
        
    InnerLoop:
        mov al, star
        call WriteChar
        loop InnerLoop

        call Crlf        
        inc count           
        mov ecx, edx           
        loop OuterLoop

    exit
main ENDP
END main
