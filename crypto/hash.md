# Cryptographic hash algorithms

## Introduction

This are the list of cryptographic hash algorithms that may be
used in the **InterlockRecord** construction. New algorithms
may be introduced in the future.

## Status of this document

This document is still a draft.

## Terms and notations

### Usage description

Usage | Description
----- | -----------
Deprecated | Supported due to backward compatibility but should not be used by new instances.
Legacy | Supported only as a legacy algorithm when no other option is availble (specially for older hardware devices). They should be avoided whenever possible due to security issues.
General | Those algorithms can be used for any purpose.
Signature | Those algorithms are restricted to signature generation only.

### Support status description

Status | Description
------ | -----------
Mandatory | It must be supported by all implementations.
Planned | It will be included by future releases.
Reserved | It is reserved for future uses but should not be used.

## List of algorithms

ID | Name | Usage | Support status | References
-- | ---- | ----- | -------------- | ----------
0 | SHA-1 | Legacy | Mandatory | FIPS PUB 180
1 | SHA-256 | General | Mandatory | FIPS PUB 180-2 
2 | SHA-512 | General | Mandatory | FIPS PUB 180-2 
3 | SHA3-256 | General | Mandatory | FIPS PUB 202
4 | SHA3-512 | General | Mandatory | FIPS PUB 202
5 | SHA-224 | General | Reserved | FIPS PUB 180-2 
6 | SHA-384 | General | Reserved | FIPS PUB 180-2
7 | SHA3-224 | General | Reserved | FIPS PUB 202
8 | SHA3-384 | General | Reserved | FIPS PUB 202
9 | Whirlpool | General | Planned | ISO/IEC 10118-3
10 | RIPEMD-160 | General | Reserved | [The hash function RIPEMD-160](https://homes.esat.kuleuven.be/~bosselae/ripemd160.html) and ISO/IEC 10118-3
65535 | COPY | Signature | Mandatory | -

## Algorithms notes

### SHA-1

The **SHA-1** algorithm as defined by FIPS PUB 180. Due to known attacks over this algorithm, such as https://shattered.io/, its use must be restricted to cases when no other option is supported by the existing hardware devices.

### COPY

The COPY hash algorithm uses the actual value of the input as
the output. This is specially useful when creating endorsement
records.
