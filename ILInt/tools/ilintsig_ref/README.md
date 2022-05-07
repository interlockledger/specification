# ILIntSig_Ref

## Description

The **ILIntSig_Ref** is a simple command line tool that generates the test
vectors for the **ILIntSignEnc** and **ILIntSignDec** functions.

## Usage

```
ilintsig_ref
```

It will output A TSV with the following fields:

- Value (decimal):
- Value (hexadecimal):
- Value (binary):
- Encoded (decimal):
- Encoded (hexadecimal):
- Encoded (binary):

## How to build

This program is a single file program that can be compiled with **CMake** or
directly with the compiler.

If you plan to use **CMake**, execute the following steps:

1. Create a subdirectory called `build`;
2. Go to this directory and execute `cmake ..`;
3. Build it with the command `cmake --build .`;

If you plan to build it directly with the compiler:

```
$ gcc src/main.c -o ilintsig_ref
```

or

```
$ clang src/main.c -o ilintsig_ref
```

## How to run

Once the code is compiled, just run **ilintsig_ref**. It will output the TSV 
into *stdout*, just like this:

```
Value	Value (hex)	Value (bin)	Encoded	Encoded (hex)	Encoded (bin)
0	0000000000000000	0000000000000000000000000000000000000000000000000000000000000000	0	0000000000000000	0000000000000000000000000000000000000000000000000000000000000000
1	0000000000000001	0000000000000000000000000000000000000000000000000000000000000001	2	0000000000000002	0000000000000000000000000000000000000000000000000000000000000010
-1	FFFFFFFFFFFFFFFF	1111111111111111111111111111111111111111111111111111111111111111	1	0000000000000001	0000000000000000000000000000000000000000000000000000000000000001
256	0000000000000100	0000000000000000000000000000000000000000000000000000000100000000	512	0000000000000200	0000000000000000000000000000000000000000000000000000001000000000
-256	FFFFFFFFFFFFFF00	1111111111111111111111111111111111111111111111111111111100000000	511	00000000000001FF	0000000000000000000000000000000000000000000000000000000111111111
-257	FFFFFFFFFFFFFEFF	1111111111111111111111111111111111111111111111111111111011111111	513	0000000000000201	0000000000000000000000000000000000000000000000000000001000000001
4294967295	00000000FFFFFFFF	0000000000000000000000000000000011111111111111111111111111111111	8589934590	00000001FFFFFFFE	0000000000000000000000000000000111111111111111111111111111111110
-4294967296	FFFFFFFF00000000	1111111111111111111111111111111100000000000000000000000000000000	8589934591	00000001FFFFFFFF	0000000000000000000000000000000111111111111111111111111111111111
9223372036854775807	7FFFFFFFFFFFFFFF	0111111111111111111111111111111111111111111111111111111111111111	18446744073709551614	FFFFFFFFFFFFFFFE	1111111111111111111111111111111111111111111111111111111111111110
-9223372036854775807	8000000000000001	1000000000000000000000000000000000000000000000000000000000000001	18446744073709551613	FFFFFFFFFFFFFFFD	1111111111111111111111111111111111111111111111111111111111111101
5001005247085758579	456723C698694873	0100010101100111001000111100011010011000011010010100100001110011	10002010494171517158	8ACE478D30D290E6	1000101011001110010001111000110100110000110100101001000011100110
6652200377377249516	5C515CFF944A58EC	0101110001010001010111001111111110010100010010100101100011101100	13304400754754499032	B8A2B9FF2894B1D8	1011100010100010101110011111111100101000100101001011000111011000
2245463110619682731	1F297CCD58BAD7AB	0001111100101001011111001100110101011000101110101101011110101011	4490926221239365462	3E52F99AB175AF56	0011111001010010111110011001101010110001011101011010111101010110
4751894623065203014	41F21EFBA9E3E146	0100000111110010000111101111101110101001111000111110000101000110	9503789246130406028	83E43DF753C7C28C	1000001111100100001111011111011101010011110001111100001010001100
-9188360554239744008	807C62C2085427F8	1000000001111100011000101100001000001000010101000010011111111000	18376721108479488015	FF073A7BEF57B00F	1111111100000111001110100111101111101111010101111011000000001111
-6693499235059940467	A31BE9E8CDE7438D	1010001100011011111010011110100011001101111001110100001110001101	13386998470119880933	B9C82C2E643178E5	1011100111001000001011000010111001100100001100010111100011100101
-8109253006376144285	8F76255AF92E7263	1000111101110110001001010101101011111001001011100111001001100011	16218506012752288569	E113B54A0DA31B39	1110000100010011101101010100101000001101101000110001101100111001
-4452978525338007654	C233D79FC4C9079A	1100001000110011110101111001111111000100110010010000011110011010	8905957050676015307	7B9850C0766DF0CB	0111101110011000010100001100000001110110011011011111000011001011
```

## License

This program is licensed under a 3-Clause BSD license.