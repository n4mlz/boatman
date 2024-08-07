## boatman

boatman is a toy rootless container.

### usage

```bash
# clone repository
git clone https://github.com/n4mlz/boatman.git
cd boatman

# build
make

# pull image
# (ubuntu)
./ubuntu.sh
# (alpine)
./alpine.sh

# run container
# (ubuntu)
./boatman run ubuntu bash
# (alpine)
./boatman run alpine /bin/sh
```

