.model small
.stack
.data
b3 dw 0
b4 dw 0
.code
mov AX,b3b4_marks
push AX
mov AX,marks_marks
pop DX
push AX
mov AX,b4b3_marks
push AX
mov AX,marks_marks
pop DX
pop DX
add AX,DX
pop DX
add AX,DX
mov b3, AX
mov AX,b4
push AX
mov AX,12
pop DX
cmp AX,DX
jl true_29_9383
jmp false_29_9383
true_29_9383:
mov AX, 0
false_29_9383:
mov AX, 1
cmp AX,1
jne else29
jmp then29
then29:
mov AX,123
mov b4, AX
else29:
mov AX,212
mov b4, AX
true:
mov AX,0
false:
mov AX,1
ret
end
