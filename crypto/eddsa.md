# EdDSA

## Status of this document

This document is a draft.

## Serialization

### Public key

The public key serialization for EdDSA is defined by tags:

* instance: IL_STRING_TAG
* A: IL_BYTES_TAG

The contents of the tags follows the [RFC 8032](https://tools.ietf.org/html/rfc8032).

The mandatory instance is:

* Ed25519

Other instances may be added in the future.

### Signature

The signature will be:

* r: IL_BYTES_TAG
* s: IL_BYTES_TAG

### Private key (emergency key only)

* instance: IL_STRING_TAG
* k: IL_BYTES_TAG
