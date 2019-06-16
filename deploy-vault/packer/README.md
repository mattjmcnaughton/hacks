# packer

Configure via Packer.

## TODO:

- Instead of building from the 18.04 image, I'd like to have my own base image
  that is 18.04, with added security hardening and other generic configs.

- https://www.packer.io/docs/templates/provisioners.html#run-on-specific-builds
Install different configuration files based on the builder.

- Install self-signed https certs. In the long term, I will have a base set of
  certs stored in vault (I will have public and private certs stored in vault).
  Most likely vault will have its own unique set of certs.
  - I can set up all my personal computers/servers to treat these self-signed
    certs as valid.

- Unique build name. Either based on git commit (most likely) or time.
