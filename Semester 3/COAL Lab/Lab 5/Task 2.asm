Murtaza Hunaid Terai  24K-0782

mov ax, 0A7FF0h 
add al, 15h ; a CF = 1, SF = 0, ZF = 0, OF = 0
add ah, 1h ; b CF = 0, SF = 1, ZF = 0, OF = 0
add ax, 2h ; c CF = 0, SF = 1, ZF = 0, OF = 0
