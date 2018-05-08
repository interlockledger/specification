# FileID

## Authors 

* Chino, F. J. T.

## Description

The Interlock FileID is a hash based method to uniquely identify
a given file or document by its contents.

contents to non authorized individuals by allowing its contents to
be identifiable even when encrypted.

### Status of this document

This document is a draft to this standard.

## Background

TODO.

## Definitions

* Document
* Document Data
* Access Key
* File

## The FileID format

The FileID is a value composed by a DocumentID and an optional KeyID
that can be used to uniquely identify a given file inside the
distributed file library implemented by InterlockLedger.

### DocumentID

The DocumentID is sequence of one or more hash values from distinct
cryptographic values. Those hash values are computed directly from
the unencrypted Document Data.

At least one of those hashes must be computed using the SHA256, in
order to make the

### KeyID

The KeyID is a pair composed by the symmetric algorithm ID and the
signature of the key. The signature of the key is defined as the
HMAC-SHA256 of the DocumentID field computed by SHA256 using the key
as the HMAC key.

## Sharing encrypted files

TODO

