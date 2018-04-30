# Cryptographic digital signature algorithms

## Introduction

This are the list of cryptographic digital signature algorithms that may be
used in the **InterlockRecord** construction. New algorithms
may be introduced in the future.

## Status of this document

This document is still a draft.

## Terms and notations

### Support status description

Status | Description
------ | -----------
Deprecated | Supported due to backward compatibility but should not be used by new instances.
Legacy | Supported only as a legacy algorithm when no other option is availble (specially for older hardware devices). They should be avoided whenever possible due to security issues.
Mandatory | It must be supported by all implementations.
Planned | It will be included by future releases.
Reserved | It is reserved for future uses but should not be used.

## List of algorithms

ID | Name | Support status | References
-- | ---- | -------------- | ----------
0 | [RSA SSA-PSS](rsa.md) | Mandatory | PKCS#1
1 | [RSA v1.5](rsa.md) | Mandatory (legacy support) | PKCS#1
2 | [DSA](dsa.md) | Planned | FIPS 186-4
3 | [ElGamal Signature Scheme](elgamal.md) | Planned | ElGamal,T.; *A public key cryptosystem and a signature scheme based on discrete logarithms*;  IEEE Transactions on Information Theory (Volume: 31, Issue: 4, Jul 1985)
4 | [ECDSA](ecdsa.md) | Planned | X9.62-2005 and FIPS 186-3
5 | [EdDSA](eddsa.md) | Mandatory | RFC8032
