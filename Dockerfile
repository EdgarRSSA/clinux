FROM gcc:10 as DEVGCC

# User
ARG USERNAME=coder
ARG USER_UID=1000
ARG USER_GID=$USER_UID
ARG WORKDIR=/home/${USERNAME}/clinux

# Update
RUN apt-get update && \
    export DEBIAN_FRONTEND=noninteractive && \
    apt-get install -y --no-install-recommends \
		git \
        vim \
        sudo \
        gdb \
        openssh-server;

# Create the user and set for sudo:
RUN groupadd --gid $USER_GID $USERNAME && \
    useradd --uid $USER_UID --gid $USER_GID -m -s /bin/bash $USERNAME && \
    echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME && \
    chmod 0440 /etc/sudoers.d/$USERNAME

# Volumenes para Extensiones VSCODE:
RUN mkdir -p /home/$USERNAME/.vscode-server/extensions \
        /home/$USERNAME/.vscode-server-insiders/extensions \
    && chown -R $USERNAME \
        /home/$USERNAME/.vscode-server \
        /home/$USERNAME/.vscode-server-insiders

# Usuario de desasrrollo y sus directorios:
RUN mkdir -p ${WORKDIR} \
    && chown -R $USERNAME ${WORKDIR}

# CMD
USER $USERNAME
WORKDIR ${WORKDIR}
EXPOSE 22
SHELL [ "/bin/bash" ]
CMD ["/bin/bash"]
