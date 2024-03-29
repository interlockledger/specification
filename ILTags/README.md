# ILTags Specification

* Chino, F. J. T.
* Teixeira, A. R. D.

## Introduction

The **ILTags** is a TLV (type, lenght and value) format that uses the **ILInt** [OPENCS]
to encode the integer types. Its main design goals are:

* Be as compact as possible;
* Lightweight;
* Easy to implement;
* Allow the representation of hierarchical data;

## Format

As a TLV (type, lenght and value) encoding, each tag will be composed by a type (an
unsigned 64-bit integer), length (an unsigned 64-bit integer, which is ommited for the implicit format, see below) 
and the value (an array of bytes).

In order to keep the format as compact as possible, the **ILTags** format defines two
distinct formats, one called **explicit** and other called **implicit**. The **explicit** tags are used to represent 
general values while the **implicit** tags are used to represent basic types.

### Explicit tags

The explicit tags are composed by 3 fields:

Field | Type | Description
----- | ---- | -----------
TagID | ILInt | The tag name.
ValueLength | ILInt | The size of value in bytes.
Value | byte[ValueLength] | The value of the tag as a byte array.

It is important to notice that the TagID of all explicit tags will be always equal or greater than 16.

### Implicit tags

The implicit tags are composed by two fields:

Field | Type | Description
----- | ---- | -----------
TagID | ILInt | The tag name.
Value | byte[n] | The value of the tag as a byte array. Its size will depend on the TagID.

It is important to notice that the TagID of all implicit tags will be always smaller than 16.

The definition of the TagIDs are:

TagID | Type | Size | Value Type | Tag name | ASN.1 Equivalent
----- | ---- | ---- | ---------- | -------- | ----------------
0 | NULL | 0 | The NULL value. | IL_NULL_TAG | EOC
1 | BOOL | 1 | A boolean value. | IL_BOOL_TAG | BOOLEAN
2 | INT8 | 1 | 8-bit signed int. | IL_INT8_TAG | - 
3 | UINT8 | 1 | 8-bit unsigned int. | IL_UINT8_TAG | -
4 | INT16 | 2 | 16-bit signed int. | IL_INT16_TAG | -
5 | UINT16 | 2 | 16-bit unsigned int. | IL_UINT16_TAG | -
6 | INT32 | 4 | 32-bit signed int. | IL_INT32_TAG | -
7 | UINT32 | 4 | 32-bit unsigned int. | IL_UINT32_TAG | -
8 | INT64 | 8 | 64-bit signed int. | IL_INT64_TAG | -
9 | UINT64 | 8 | 64-bit unsigned int. | IL_UINT64_TAG | -
10 | ILInt | 1 to 9 | A ILInt value. | IL_ILINT_TAG | -
11 | binary32 | 4 | IEEE754 32-bit floating point. | IL_BIN32_TAG | -
12 | binary64 | 8 | IEEE754 64-bit floating point. | IL_BIN64_TAG | -
13 | binary128 | 16 | IEEE754 128-bit floating point. | IL_BIN128_TAG | -
14 | ILIntSigned | 1 to 9 | A ILIntSigned value. | IL_ILINT_SIGNED_TAG | -
15 | Reserved | - | Reserved for future uses. | - | -

All integer values are encoded in big endian (most significant bit first) format while
the floating point values are represented according to IEEE754, also encoded in BigEndian.

### Reserved TagID ranges

The ILTag reserves all TagID values from 0 to 31 to the standard. All standards based on the ILTags format are free to allocate TagIDs from 32 onward.

### Standard explicit tags

TagID | Type | Value Type | Tag name | ASN.1 Equivalent
----- | ---- | ---------- | -------- | ----------------
16 | ByteArray | A raw byte array. | IL_BYTES_TAG | OCTET STRING
17 | String |  UTF-8 encoded string. | IL_STRING_TAG | CHARACTER STRING (limited to UTF-8) 
18 | BigInteger | A big integer encoded in big endian format. | IL_BINT_TAG | INTEGER
19 | BigDecimal | A big decimal number. | IL_BDEC_TAG | -
20 | ILIntArray | An array of ILint. | IL_ILINTARRAY_TAG | -
21 | ILTagArray | An array of ILTag | IL_ILTAGARRAY_TAG | - 
22 | ILTagSequence | An sequence of ILTag | IL_ILTAGSEQ_TAG | -
23 | Range | A range of TagID | IL_RANGE_TAG | -
24 | Version | Semantic version number (major.minor.revision.build) | IL_VERSION_TAG | -
25 | ITU Object Identifier | An array of ILint (reserved for future uses). | IL_OID_TAG | OBJECT IDENTIFIER
26 | Reserved | - | Reserved for future uses. | - 
27 | Reserved | - | Reserved for future uses. | - 
28 | Reserved | - | Reserved for future uses. | - 
29 | Reserved | - | Reserved for future uses. | - 
30 | Dictionary | A dictionary with string keys and ILTags as values (may have different kinds of values for each entry) | IL_DICTIONARY_TAG | - 
31 | StringDictionary | A dictionary with string keys and string values | IL_STRING_DICTIONARY_TAG | -

All values from 26 to 29 are reserved for future uses.

#### ByteArray

The ByteArray is a simple byte array value. It uses the TagID 16 and holds a raw byte array as its value.

#### String

The String represents a text value. It uses the TagID 17 and holds a UTF-8 encoded value. Examples:

- "value" => `[17, 5, 118, 97, 108, 117, 101]`
- "ação" => `[17, 6, 97, 195, 167, 195, 163, 111]`

#### BigInteger

The BigInteger represents a big integer value. It uses the TagID 18 and holds the big integer value encoded as a two's complement big endian value. The payload of this tag must have at least 1 byte.

These are some examples of two's complement big endian values:

- 0: `[0x00]`;
- 127: `[0x7F]`;
- 255: `[0x00, 0xFF]`;
- -1: `[0xFF]`;

Notice that, if the number of bits is divisible by 8, the encoding will start with a 0x00. This is required because all values with the most significant bit set to 1 is a negative value.

The values must be encoded with the smallest number of bytes.

Both positive and negative numbers must be encoded using the smallest possible number of bytes.

#### BigDecimal

The BigDecimal represents a big decimal value. It uses the TagID 19 and holds two fields. The first field is an 32-bit signed integer that 
represents the scale of the value followed by the integral part of the value encoded as a two's complement big endian value. The actual value is computed by the equation: 

- `v = integralPart * 10^(-scale)`

For example, the value -6.02214076E-23 will have the exponent set to 31 and the integral part set to -602214076. The payload tag serialization will be `[0x13, 0x08, 0x00, 0x00, 0x00, 0x1F, 0xDC, 0x1A, 0xF1, 0x44]`.

This can be decomposed in:

- `[0x13]`: The tag id;
- `[0x08]`: The payload size;
- `[0x00, 0x00, 0x00, 0x1F]`: The exponent (31) encoded as a signed 32-bit integer in big endian format;
- `[0xDC, 0x1A, 0xF1, 0x44]`: The integral part (-602214076) encoded in two's complement;

The payload of this tag must have at least 5 bytes. One for the integral part and 4 for the scale.

#### ILIntArray

The ILIntArray is a simple array of ILInt values. It uses the TagID 20 and holds a length as an encoded ILInt followed by that number of ILInt encoded values.

#### ILTagArray

The ILTagArray is a simple array of ILTag values. It uses the TagID 21 and contains
an ILInt that represents the number of elements followed by the serialization of
the tags.

#### ILTagSequence

The ILTagSequence is a simple sequence of ILTag values. It uses the TagID 22 and holds
a sequence of ILTag. It is similar to **ILTagArray** but it does not encode
the number of elements prior to the tags.

#### Range

The Range defines a contiguous range of UINT64 numbers, at least 1 and a maximum of 65535 numbers. It uses the TagID 23 and holds
one ILInt for the first number in the range, followed by a count of sequential numbers in the range serialized 
as one unsigned short (16 bits) in big-endian format.

	Ex.: [128-136] => 23, 3, 128, 0, 8

#### Version

The Version defines a Semantic Version Number with four parts (major.minor.revision.build). It uses the TagID 24 and holds
four signed integers (32 bits) serialized in big-endian format in the order of 'major', 'minor', 'revision' and 'build'.

	Ex.: 1.2.3.4 => 24, 16, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4

#### ITU Object Identifier

This tag stores the ITU Object identifier. Each element will be stored as a 64 bit
unsigned integer encoded using a ILInt format. In other words, it is just a sequence of ILInt values (one for each element) 
preceeded by an ILInt that encodes the number of elements. It follows the same serialization of IL_ILINTARRAY_TAG.

#### Dictionary

The Dictionary is a simple array of pairs of string keys and ILTag values. It uses the TagID 30 and contains
an ILInt that represents the number of pairs followed by the serialization of each pair, first the key as a String and then the tagged value.

	Ex.: ["key"] = true => 30, 8, 1, 17, 3, 107, 101, 121, 1, 1
	
#### StringDictionary

The StringDictionary is a simple array of pairs of string keys and string values. It uses the TagID 31 and contains
an ILInt that represents the number of pairs followed by the serialization of each pair, first the key and then the value.

	Ex.: ["key"] = "value" => 31, 13, 1, 17, 3, 107, 101, 121, 17, 5, 118, 97, 108, 117, 101

## References

* [OPENCS] Chino, F. J. T. and Teixeira, A. R. D.; ["ILInt Specification"](https://github.com/interlockledger/specification/blob/master/ILInt), Open Communications Security, 2017;
