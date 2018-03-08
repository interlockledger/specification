# ElGamal Signature Scheme

## Serialization

### Public key

The public key serialization for ElGamal is defined by tags:

* p: IL_BINT_TAG
* g: IL_BINT_TAG
* y: IL_BINT_TAG (the public key itself)

### Signature

The signature will be:

* r: IL_BINT_TAG
* s: IL_BINT_TAG

### Private key (emergency key only)

* p: IL_BINT_TAG
* g: IL_BINT_TAG
* x: IL_BINT_TAG (the private key itself)
