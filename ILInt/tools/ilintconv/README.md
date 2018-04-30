# ILIntConv

## Description

The **ILIntConv** is a simple command line tool designed to make convertions between the
ILInt format and numerical values and vice-versa.

## Usage

```
ilintconv [-c] [-d] [-x] [-h] [<value>]
```

* -c: Reads the output from the standard input;
* -d: Decodes the value;
* -h: Prints the help screen;
* -x: Outputs/inputs numeric values as hexadecimal instead of decimal;
* <value>: The value to be converted

When encoding, the value must be a valid decimal and/or hexadecimal (if -x is used)
value that can be stored inside an unsigned 64-bit integer.

When decoding, the input must be a valid hexadecimal string with 2 to 18 charactes.

