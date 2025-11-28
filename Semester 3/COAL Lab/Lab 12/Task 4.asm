; Murtaza Hunaid Terai  24K-0782

INCLUDE Irvine32.inc

.data
    arr DWORD 1,2,3
        DWORD 4,5,6  
        DWORD 7,8,9
    RowSize = ($ - arr) / 3  ; Calculate row size in bytes
    sum DWORD 0
    msg BYTE "Sum of all elements: ", 0

.code
main PROC
    mov ebx, OFFSET arr    
    mov ecx, 3  ; Outer loop counter (rows)

OuterLoop:
    push ecx    ; Save outer loop counter
    dec ecx ; Convert to zero-based row index
    mov eax, RowSize 
    mul ecx ; eax = RowSize * row_index
    mov edx, ebx            
    add edx, eax             
    mov ecx, 3  ; Inner loop counter
    mov esi, 0  ; esi = column index 

InnerLoop:
    mov eax, [edx + esi*4]  ; Access arr[row][col] using base-index
    add sum, eax  
    inc esi ; Move to next column
    loop InnerLoop          

    pop ecx ; Restore outer loop counter
    loop OuterLoop           

    mov edx, OFFSET msg     
    call WriteString
    mov eax, sum
    call WriteInt
    call Crlf
    exit
main ENDP
END main
