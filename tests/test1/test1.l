0x00000000 00000000 ldc 0
0x00000001 FFFFFB00 ldc -5
0x00000002 00000500 ldc +5
0x00000003 FFFFFF11 loop: br loop ; an infinite loop
0x00000004 00000011 br next	;offset should be zero
0x00000005 00000300 ldc loop ; load code address
0x00000006 00000700 ldc var1 ; forward ref
0x00000007 00000000 var1: data 0 ; a variable
