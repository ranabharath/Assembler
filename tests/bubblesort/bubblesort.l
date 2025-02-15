0x00000000 FFFFFA0A adj -6                    ; Store 5 at memory[SP + 5]
0x00000001 00000002 ldl 0                    ; Load array length (5) into A
0x00000002 FFFFFF01 adc -1                   ; Subtract 1 (5 - 1 = 4)
0x00000003 00001D0F brz end                  ; If array length - 1 == 0, sorting is complete, go to end
0x00000004 00000003 stl 0                    ; Store (array length - 1) back in memory[SP + 0]
0x00000005 00000100 ldc 1                    ; Initialize inner loop index to 1
0x00000006 00000603 stl 6                    ; Store inner loop index in memory[SP + 6]
0x00000007 00000002 ldl 0                    ; Load array length - 1
0x00000008 00000602 ldl 6                    ; Load inner loop index
0x00000009 00000007 sub                      ; Subtract inner loop index from array length - 1
0x0000000A FFFFF60F brz outer_loop           ; If we've reached the end of the inner loop, go to outer loop
0x0000000B 00000602 ldl 6                    ; Load inner loop index into A
0x0000000C 00000004 ldnl 0                   ; Load memory[SP + index] into A (array[i])
0x0000000D 00000602 ldl 6                    ; Load inner loop index into A
0x0000000E 00000101 adc 1                    ; Add 1 to index
0x0000000F 00000004 ldnl 0                   ; Load memory[SP + (index + 1)] into A, effectively B = array[i+1]
0x00000010 00000007 sub                      ; A = array[i] - array[i+1]
0x00000011 00000A10 brlz skip_swap           ; If A < 0, no swap needed, go to skip_swap
0x00000012 00000602 ldl 6
0x00000013 00000004 ldnl 0
0x00000014 00000703 stl 7
0x00000015 00000602 ldl 6
0x00000016 00000104 ldnl 1
0x00000017 00000602 ldl 6
0x00000018 00000005 stnl 0
0x00000019 00000702 ldl 7
0x0000001A 00000602 ldl 6
0x0000001B 00000105 stnl 1
0x0000001C 00000100 ldc 1                    ; Load 1 into A
0x0000001D 00000602 ldl 6                    ; Load inner loop index
0x0000001E 00000006 add                      ; Increment index by 1
0x0000001F 00000603 stl 6                    ; Store updated index back in memory[SP + 6]
0x00000020 FFFFE611 br inner_loop            ; Repeat inner loop
0x00000021 00000012 HALT                     ; Stop execution
0x00000022 00000006 data 6 ; size of array + 1
0x00000023 0000000A data 10
0x00000024 00000014 data 20
0x00000025 0000003C data 60
0x00000026 00000028 data 40
0x00000027 00000005 data 5
