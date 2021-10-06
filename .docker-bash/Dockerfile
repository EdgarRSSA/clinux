#
# Image Base on Debian-10-buster Docker Official.
#
FROM debian:buster as dev

# User
ARG USERNAME=coder
ARG USER_UID=1000
ARG USER_GID=$USER_UID
ARG USERHOME=/home/${USERNAME}

# Update
RUN export DEBIAN_FRONTEND=noninteractive && \
    apt-get update && \
    apt-get install -y --no-install-recommends --no-show-upgraded \
        ca-certificates \
        gcc g++ libc6-dev autoconf automake gcc-multilib make manpages-dev gdb \
        sudo \
		git \
        vim \
        rsync \
        openssh-server

# Create the user and set for sudo:
RUN groupadd --gid $USER_GID $USERNAME && \
    useradd --uid $USER_UID --gid $USER_GID -m -s /bin/bash $USERNAME && \
    echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME && \
    chmod 0440 /etc/sudoers.d/$USERNAME

USER ${USERNAME}
# Usuario de desasrrollo y sus directorios:
RUN mkdir ${USERHOME}/.ssh && \
    touch ${USERHOME}/.ssh/authorized_keys && \
    echo "alias ls='ls -AF --color=auto --time-style=+\"%x %X\" --group-directories-first'" > ${USERHOME}/.bash_aliases && \
    echo "alias ll='ls -lh'" >> ${USERHOME}/.bash_aliases && \
    chown -R $USERNAME ${USERHOME} && chgrp -R $USERNAME ${USERHOME}

# CMD
USER $USERNAME
WORKDIR ${USERHOME}
EXPOSE 22
CMD ["/bin/bash"]
