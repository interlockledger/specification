# ECDSA

## Status of this document

This document is a draft.

## Serialization

### Public key

The public key serialization for ECDSA is defined by tags:

* curve: IL_STRING_TAG
* Qx: IL_BYTES_TAG
* Qy: IL_BYTES_TAG

The curve names can be found in http://www.secg.org/sec2-v2.pdf and FIPS PUB 186-4. The use of random curves are not supported by this tag. mandatory supported curves are:

* P-256
* Secp256k1

Other curves may be added in the future.

### Signature

The signature will be:

* r: IL_BYTES_TAG
* s: IL_BYTES_TAG

### Private key (emergency key only)

* curve: IL_STRING_TAG
* d: IL_BINT_TAG
