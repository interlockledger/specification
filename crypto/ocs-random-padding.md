# OpenCS Random Padding

## Introduction

The **OpenCS Random Padding** is a block cipher padding scheme designed to make attacks against password based encryption harder
by denying the ability to discard failed trials using the padding
integrity inspection (a failed attempt can be easily discared by
a simple inspection of the padding).

It has been used by **OpenCS** in multiple projects since its introduction in 2006.

## Notation

Symbol | Description
------ | -----------
*a* \|\| *b* | *a*

## The scheme

The **OpenCS Random Padding** generator take as input:
    
* *blockSize*: The block size in bytes (a value from 1 to 255);
* *data*: The data to be padded as an array of octets;
* *random(n)*: A random or pseudo-random function that outputs arrays of *n* octets with random values;

and outputs:

* *paddedData*: The padded data as an array of octets;

The *paddedData* is computed as:

* *paddedData* = *data* || *ocspad(len(data), blockSize, random())*

The function *ocspad(dataSize, blockSize, random())* is defined as:

1. Let *paddingSize* = *blockSize* - (dataSize mod blockSize)
2. Let *padding = random(paddingSize)*;
3. Let *padding[paddingSize - 1] = padding[paddingSize - 1] - ((padding[paddingSize - 1] mod blocksize) + (paddingSize mod blocksize)*
4. Return *padding*;

The function that recovers the size of the padding takes as the input:

* *blockSize*: The block size in bytes (a value from 1 to 255);
* *paddedData*: The padded data as an array of octets; 

and outputs:

* *paddingSize*: The size of the padding in octets;

The value *paddingSize* is computed as:

1. Let *paddingSize = paddedData[len(paddedData) - 1] mod blockSize*;
1. If *paddingSize* is 0, let *paddingSize = blockSize*;
1. Return *paddingSize*

Examples with *blockSize* as 4:

 Data | Padding size | Random padded | Padded data 
 ---- | ------------ | ------------- | -----------
 xx | 3 | 8e a3 cf | xx 8e a3 cf
 xx xx | 2 | 50 0c | xx xx 50 0e
 xx xx xx | 1 | b8 | xx xx xx b9
 xx xx xx xx | 4 | 92 b5 32 26 | xx xx xx xx 92 b5 32 28

## Advantages and disavantages

The main advantage of the **OpenCS Random Padding** is the fact that
any random block of data can be viewed as a valid padding block. This
alone makes it impossible to distinguish between random data and a
valid block by a simple inspection of the padding.

This fact alone makes the usage of this padding scheme suitable for
password based encryption because a wrong password cannot be
discarded by this padding scheme alone because all passwords,
including the incorrect ones, will generate a correct padding.

This, however, can pose a serious problem if the application uses
the padding as the only way to determine the actual size of the data
and its integrity.

As other byte based padding schemes, the **OpenCS Random Padding**
cannot be used if the block size is larger than 255.

### Compatibility with other paddings

Padding generated with both **ISO 10126** and **PKCS#7** are valid
paddings according to **OpenCS Random Padding** rules. This means
that paddings generated with those two schemes can be correctly
decoded by a **OpenCS Random Padding** decoder, making the migration
very easy. 

On the other hand, paddings generated with **OpenCS Random Padding**
cannot be decoded with **ISO 10126** and **PKCS#7** decoders.

## Licensing

This file is made available under the Creative Commons CC0 1.0 Universal Public Domain Dedication.

The person who associated a work with this deed has dedicated the
work to the public domain by waiving all of his or her rights to the
work worldwide under copyright law, including all related and
neighboring rights, to the extent allowed by law. You can copy,
modify, distribute and perform the work, even for commercial purposes,
all without asking permission.
