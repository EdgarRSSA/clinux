#!/usr/bin/env bash
LOG="./logger.sh"
${LOG} "clear";


# Start ssh-server in container
${LOG} "run" "docker exec clinux_clinux_1 sudo /etc/init.d/ssh start" || exit $?;

# Remove old localhost:2222 known-port
${LOG} "run" "ssh-keygen -f ${HOME}/.ssh/known_hosts -R [127.0.0.1]:2222" || exit $?;

# Copy id_rsa.pub
${LOG} "run" "docker cp ${HOME}/.ssh/id_rsa.pub clinux_clinux_1:/home/coder/.ssh/authorized_keys" || exit $?;


# CONNECT TO CONTAINER USING SSH
sleep 1
${LOG} "log" "USE ->> ssh -A -p 2222 coder@localhost <<-";
