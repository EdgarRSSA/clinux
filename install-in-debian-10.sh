sudo apt-get update || exit $?

sudo apt-get install -y \
    g++ \
    git \
    vim \
    gdb \
    rsync \
    openssh-server \
    zip || exit $?

