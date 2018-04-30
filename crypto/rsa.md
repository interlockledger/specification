# RSA

* Chino, F. J. T.
* 

## Introduction

This document describes the usage of RSA on the InterlockLedger standard.

## Key sizes and security

Due to security restrictions, the minimum allowed key size is 2048.

## Supported modes

The InterlockLedger standard supports digital signature using RSA in the following standards:

* RSASSA-PKCS1-v1_5 (legacy)
* RSASSA-PSS (preferencial)

## Serialization

The serialization of the keys will be based on the ASN.1 format but will use the
ILTags[OPENCS] format instead of the DER encoding.

### Public key

The public key serialization for RSA is defined by the tags encoding:

* rsa_pub: IL_ILTAGSEQ_TAG
    * modulus: IL_BINT_TAG
    * publicExponent: IL_BINT_TAG

### Signature

The signature value will have the following format:

* sig_val: IL_ILTAGSEQ_TAG
    * s: IL_BINT_TAG

### Private key (emergency key only)

Simple private key:

* rsa_priv: IL_ILTAGSEQ_TAG
    * type: IL_UINT8_TAG = 0
    * modulus: IL_BINT_TAG
    * publicExponent: IL_BINT_TAG

Certificate private key:

* rsa_priv: IL_ILTAGSEQ_TAG
    * type: IL_UINT8_TAG = 1
    * modulus: IL_BINT_TAG
    * publicExponent: IL_BINT_TAG
    * privateExponent: IL_BINT_TAG
    * prime1: IL_BINT_TAG
    * prime2: IL_BINT_TAG
    * exponent1: IL_BINT_TAG
    * exponent2: IL_BINT_TAG
    * coefficient: IL_BINT_TAG

The emergency public key will always be encoded using the rsa_priv format.

## References

* [OPENCS] ["ILTags Specification"] Chino, F. J. T. and Teixeira, A. R. D.; ["ILTags Specification"](https://github.com/interlockledger/specification/tree/master/ILTags), Open Communications Security, 2017;
* [PKCS1] K. Moriarty, Ed, B. Kaliski, J. Jonsson and  A. Rusch; ["PKCS #1: RSA Cryptography Specifications Version 2.2"](https://tools.ietf.org/html/rfc8017), IETF, November 2016;
