#!/bin/bash

cd $(dirname $0)

mkdir -p ./image/ubuntu
cd ./image/ubuntu
wget http://cdimage.ubuntu.com/ubuntu-base/releases/22.04/release/ubuntu-base-22.04.4-base-amd64.tar.gz
tar xzf ubuntu-base-22.04.4-base-amd64.tar.gz
rm ubuntu-base-22.04.4-base-amd64.tar.gz
