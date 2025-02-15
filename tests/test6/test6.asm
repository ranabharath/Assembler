; Assume b is loaded into SP + 1 and h is loaded into SP + 2
; We will store the result (area) at SP + 0

ldc 5
stl 1
ldc 4
stl 2
; Initialize sum to 0
ldc 0                   ; Load 0 into A
stl 3                   ; Store 0 in SP + 3 (sum)

; Load b and h
ldl 1                   ; Load b from SP + 1
stl 4                   ; Store b temporarily in SP + 4
ldl 2                   ; Load h from SP + 2 (height)
stl 5                   ; Store h in SP + 5 as loop counter

multiply_loop:
ldl 5                   ; Load h (loop counter)
brz divide_by_two       ; If h is 0, go to divide by two

ldl 3                   ; Load current sum
ldl 4                   ; Load b
add                     ; Add b to sum
stl 3                   ; Store updated sum

; Decrement h (loop counter)
ldc -1                  ; Load -1
ldl 5                   ; Load current h
add                     ; Decrement h
stl 5                   ; Store updated h
br multiply_loop        ; Repeat until h is 0

divide_by_two:
ldl 3                   ; Load b * h result from SP + 3
ldc 1
shr                     ; Perform right shift to divide by 2 (logical shift)
stl 0                   ; Store result (area) at SP + 0

HALT                    ; End of program
