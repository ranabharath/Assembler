   adj -6                    ; Store 5 at memory[SP + 5]
outer_loop:
    ldl 0                    ; Load array length (5) into A
    adc -1                   ; Subtract 1 (5 - 1 = 4)
    brz end                  ; If array length - 1 == 0, sorting is complete, go to end
    stl 0                    ; Store (array length - 1) back in memory[SP + 0]
    ldc 1                    ; Initialize inner loop index to 1
    stl 6                    ; Store inner loop index in memory[SP + 6]
inner_loop:
    ldl 0                    ; Load array length - 1
    ldl 6                    ; Load inner loop index
    sub                      ; Subtract inner loop index from array length - 1
    brz outer_loop           ; If we've reached the end of the inner loop, go to outer loop
    ; Load array[i] into A
    ldl 6                    ; Load inner loop index into A
    ldnl 0                   ; Load memory[SP + index] into A (array[i])
    ; Load array[i+1] into B
    ldl 6                    ; Load inner loop index into A
    adc 1                    ; Add 1 to index
    ldnl 0                   ; Load memory[SP + (index + 1)] into A, effectively B = array[i+1]
    ; Compare array[i] and array[i+1]
    sub                      ; A = array[i] - array[i+1]
    brlz skip_swap           ; If A < 0, no swap needed, go to skip_swap
    ; Swap array[i] and array[i+1]
    ldl 6
    ldnl 0
    stl 7
    ldl 6
    ldnl 1
    ldl 6
    stnl 0
    ldl 7
    ldl 6
    stnl 1
skip_swap:
    ldc 1                    ; Load 1 into A
    ldl 6                    ; Load inner loop index
    add                      ; Increment index by 1
    stl 6                    ; Store updated index back in memory[SP + 6]
    br inner_loop            ; Repeat inner loop

end:
    HALT                     ; Stop execution

data 6 ; size of array + 1
data 10
data 20
data 60
data 40
data 5