0x00000000 00000600 ldc 6                    ; Number of elements in the array + 1
0x00000001 00000003 stl 0                    ; Store the array length in memory[SP + 0]
0x00000002 00002700 ldc 39                   ; Load 39 into A
0x00000003 00000103 stl 1                    ; Store 39 at memory[SP + 1]
0x00000004 00000200 ldc 2                    ; Load 2 into A
0x00000005 00000203 stl 2                    ; Store 2 at memory[SP + 2]
0x00000006 00003800 ldc 56                   ; Load 56 into A
0x00000007 00000303 stl 3                    ; Store 56 at memory[SP + 3]
0x00000008 00000C00 ldc 12                    ; Load 12 into A
0x00000009 00000403 stl 4                    ; Store 12 at memory[SP + 4]
0x0000000A 00003600 ldc 54                    ; Load 54 into A
0x0000000B 00000503 stl 5                    ; Store 54 at memory[SP + 5]
0x0000000C 00000000 ldc 0                    ; Initialize sum to 0
0x0000000D 00000703 stl 7                    ; Store sum in memory[SP + 7]
0x0000000E 00000100 ldc 1                    ; Set index to start of array (1)
0x0000000F 00000603 stl 6                    ; Store index in memory[SP + 6]
0x00000010 00000002 ldl 0                    ; Load array length
0x00000011 00000602 ldl 6                    ; Load current index
0x00000012 00000007 sub                      ; Subtract index from length
0x00000013 00000A0F brz end_sum              ; If index == length, go to end_sum
0x00000014 00000702 ldl 7                    ; Load current sum
0x00000015 00000602 ldl 6                    ; Load index
0x00000016 00000004 ldnl 0                   ; Load array[index] into A
0x00000017 00000006 add                      ; Add array[index] to sum
0x00000018 00000703 stl 7                    ; Store updated sum in memory[SP + 7]
0x00000019 00000100 ldc 1                    ; Load 1 into A
0x0000001A 00000602 ldl 6                    ; Load current index
0x0000001B 00000006 add                      ; Increment index by 1
0x0000001C 00000603 stl 6                    ; Store updated index back in memory[SP + 6]
0x0000001D FFFFF211 br sum_loop              ; Repeat loop
0x0000001E 00000702 ldl 7                    ; Load final sum
0x0000001F 00000012 HALT                     ; Stop execution
