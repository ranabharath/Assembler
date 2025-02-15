0x00000000 00000500 ldc 5
0x00000001 00000103 stl 1
0x00000002 00000400 ldc 4
0x00000003 00000203 stl 2
0x00000004 00000000 ldc 0                   ; Load 0 into A
0x00000005 00000303 stl 3                   ; Store 0 in SP + 3 (sum)
0x00000006 00000102 ldl 1                   ; Load b from SP + 1
0x00000007 00000403 stl 4                   ; Store b temporarily in SP + 4
0x00000008 00000202 ldl 2                   ; Load h from SP + 2 (height)
0x00000009 00000503 stl 5                   ; Store h in SP + 5 as loop counter
0x0000000A 00000502 ldl 5                   ; Load h (loop counter)
0x0000000B 0000090F brz divide_by_two       ; If h is 0, go to divide by two
0x0000000C 00000302 ldl 3                   ; Load current sum
0x0000000D 00000402 ldl 4                   ; Load b
0x0000000E 00000006 add                     ; Add b to sum
0x0000000F 00000303 stl 3                   ; Store updated sum
0x00000010 FFFFFF00 ldc -1                  ; Load -1
0x00000011 00000502 ldl 5                   ; Load current h
0x00000012 00000006 add                     ; Decrement h
0x00000013 00000503 stl 5                   ; Store updated h
0x00000014 FFFFF511 br multiply_loop        ; Repeat until h is 0
0x00000015 00000302 ldl 3                   ; Load b * h result from SP + 3
0x00000016 00000100 ldc 1
0x00000017 00000009 shr                     ; Perform right shift to divide by 2 (logical shift)
0x00000018 00000003 stl 0                   ; Store result (area) at SP + 0
0x00000019 00000012 HALT                    ; End of program
