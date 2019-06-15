#!/bin/bash

# Eventually, this should be part of a base AMI. It will include things like
# automatically applying security patches, etc...

set -ex

GOSS_VERSION=v0.3.7
sudo curl -L https://github.com/aelsabbahy/goss/releases/download/${GOSS_VERSION}/goss-linux-amd64 -o /usr/local/bin/goss
sudo chmod +rx /usr/local/bin/goss
