# IR Key Storage

## Description

This document is a draft of a cryptographic crypto container. It should be used to store
cryptographic keys on the software only implementation of Interlock Record.

## Background

This format is based on the ILTags format.

## Custom tags

### IRKS_ROOT

It is a tag array with the ID 0x49524C4B. With this ID, the prefix of
the file will always be:

* FB 49 52 4B 53

This will generate the string IRKS starting on the second byte of the file.

All tags inside this array will assume the type IRKS_KEY.

### IRKS_KEY

This is a Tag sequence


