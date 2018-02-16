# ILTags Specification

## Introduction

The **ILTags** is a TLV (type, lenght and value) format that uses the 
[**ILInt**](https://github.com/interlockledger/specification/tree/master/ILInt)
to encode the integer types. Its main design goals are:

* Be as compact as possible;
* Lightweight;
* Easy to implement;
* Allow the representation of hierarchical data;

## Format

As a TLV (type, lenght and value) encoding, each tag will be composed by a type (an
unsigned 64-bit integer), length (an unsigned 64-bit integer) and the value (an array
of bytes).

In order to keep the format as compact as possible, the **ILTags** format defines two
distinct formats, one called **explicit** and other called **implicit**. The **explicit** tags are used to represent general values while the **implicit** tags are used to represent basic types.

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

The definition of the TagIds are:

TagId | Type | Size | Value Type | Tag name
----- | ---- | ---- | ---------- | --------
0 | NULL | 0 | The NULL value. | IL_NULL_TAG
1 | BOOL | 1 | A boolean value. | IL_BOOL_TAG
2 | INT8 | 1 | 8-bit signed int. | IL_INT8_TAG
3 | UINT8 | 1 | 8-bit unsigned int. | IL_UINT8_TAG
4 | INT16 | 2 | 16-bit signed int. | IL_INT16_TAG
5 | UINT16 | 2 | 16-bit unsigned int. | IL_UINT16_TAG
6 | INT32 | 4 | 32-bit signed int. | IL_INT32_TAG
7 | UINT32 | 4 | 32-bit unsigned int. | IL_UINT32_TAG
8 | INT64 | 8 | 64-bit signed int. | IL_INT64_TAG
9 | UINT64 | 8 | 64-bit unsigned int. | IL_UINT64_TAG
10 | ILInt | 1 to 9 | A ILInt value. | IL_ILINT_TAG
11 | binary32 | 4 | IEEE754 32-bit floating point. | IL_BIN32_TAG
12 | binary64 | 8 | IEEE754 64-bit floating point. | IL_BIN64_TAG
13 | binary128 | 16 | IEEE754 128-bit floating point. | IL_BIN128_TAG
14 | Reserved | - | Reserved for future uses. | -
15 | Reserved | - | Reserved for future uses. | -

All integer values are encoded in big endian (most significant bit first) format while
the floating point values are represented according to IEEE754, also encoded in BigEndian.

### Reserved TagID ranges

The ILTag reserves all TagID values from 0 to 31 to the standard. All standards based on the ILTags format are free to allocate TagIDs from 32 onward.

### Standard explicit tags

TagId | Type | Value Type | Tag name
----- | ---- | ---------- | --------
16 | ByteArray | A raw byte array. | IL_BYTES_TAG
17 | String |  UTF-8 encoded string. | IL_STRING_TAG
18 | BigInteger | A big integer encoded in big endian format. | IL_BINT_TAG
19 | BigDecimal | A big decimal number. | IL_BDEC_TAG
20 | ILIntArray | An array of ILint. | IL_ILINTARRAY_TAG
21 | ILTagArray | An array of ILTag | IL_ILTAGARRAY_TAG
22 | ILTagSequence | An sequence of ILTag | IL_ILTAGSEQ_TAG

All values from 22 to 31 are reserved for future uses.

#### ByteArray

The ByteArray is a simple byte array value. It uses that TagID 16 and holds a raw byte array as its value.

#### String

The String represents a text value. It uses that TagID 17 and holds a UTF-8 encoded value.

#### BigInteger

The BigInteger represents a big integer value. It uses that TagID 18 and holds the big integer value encoded as a two's complement big endian value.

#### BigDecimal

The BigDecimal represents a big decimal value. It uses that TagID 19 and holds two fields. The first field is an 32-bit signed integer that represents the scale of the value followed by the integral part of the value encoded as a two's complement big endian value. The actual value is computed as follows:

    v = integralPart * 10^(-scale)

#### ILIntArray

The ILIntArray is a simple array of ILInt values. It uses that TagID 20 and holds a length as an encoded ILInt followed by that number of ILInt encoded values.

#### ILTagArray

The ILTagArray is a simple array of ILTag values. It uses that TagID 21 and contains
an ILInt that represents the number of elements followed by the serizalization of
the tags.

#### ILTagSequence

The ILTagSequence is a simple sequence of ILTag values. It uses that TagID 22 and holds
a sequence of ILTag. It is similar to **ILTagArray** but it does not encode
the number of elements prior to the tags.
