    ldc 6                    ; Number of elements in the array + 1
    stl 0                    ; Store the array length in memory[SP + 0]
    ; Initialize array at SP + 1, SP + 2, SP + 3, SP + 4, SP + 5
    ; load array : {39,2,56,12,54}
    ldc 39                   ; Load 39 into A
    stl 1                    ; Store 39 at memory[SP + 1]
    ldc 2                    ; Load 2 into A
    stl 2                    ; Store 2 at memory[SP + 2]
    ldc 56                   ; Load 56 into A
    stl 3                    ; Store 56 at memory[SP + 3]
    ldc 12                    ; Load 12 into A
    stl 4                    ; Store 12 at memory[SP + 4]
    ldc 54                    ; Load 54 into A
    stl 5                    ; Store 54 at memory[SP + 5]
    ldc 0                    ; Initialize sum to 0
    stl 7                    ; Store sum in memory[SP + 7]
    ldc 1                    ; Set index to start of array (1)
    stl 6                    ; Store index in memory[SP + 6]
sum_loop:
    ldl 0                    ; Load array length
    ldl 6                    ; Load current index
    sub                      ; Subtract index from length
    brz end_sum              ; If index == length, go to end_sum
    ; Add current element to sum
    ldl 7                    ; Load current sum
    ldl 6                    ; Load index
    ldnl 0                   ; Load array[index] into A
    add                      ; Add array[index] to sum
    stl 7                    ; Store updated sum in memory[SP + 7]
    ; Increment index
    ldc 1                    ; Load 1 into A
    ldl 6                    ; Load current index
    add                      ; Increment index by 1
    stl 6                    ; Store updated index back in memory[SP + 6]
    br sum_loop              ; Repeat loop

end_sum:
    ldl 7                    ; Load final sum
    ; Output sum or continue with further processing
    HALT                     ; Stop execution
