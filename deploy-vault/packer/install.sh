#!/bin/bash

# https://learn.hashicorp.com/vault/operations/ops-deployment-guide

# Refactor this to use functions

set -ex

VAULT_VERSION="1.1.3"
curl --silent --remote-name https://releases.hashicorp.com/vault/${VAULT_VERSION}/vault_${VAULT_VERSION}_linux_amd64.zip
curl --silent --remote-name https://releases.hashicorp.com/vault/${VAULT_VERSION}/vault_${VAULT_VERSION}_SHA256SUMS
grep linux_amd64 vault_*_SHA256SUMS | sha256sum -c -

sudo apt update
sleep 5
sudo apt install unzip

unzip vault_${VAULT_VERSION}_linux_amd64.zip
sudo chown root:root vault
sudo mv vault /usr/local/bin/
vault --version

sudo setcap cap_ipc_lock=+ep /usr/local/bin/vault
sudo useradd --system --home /etc/vault.d --shell /bin/false vault

sudo mv /tmp/vault.service /etc/systemd/system/vault.service

sudo mkdir --parents /etc/vault.d
sudo mv /tmp/vault.hcl /etc/vault.d/vault.hcl
sudo chown --recursive vault:vault /etc/vault.d
sudo chmod 644 /etc/vault.d/vault.hcl

if grep -q "/vault" /etc/vault.d/vault.hcl
then
  sudo mkdir /vault
  sudo chown -R vault:vault /vault
fi

sudo systemctl enable vault
