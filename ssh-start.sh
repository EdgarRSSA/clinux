#!/usr/bin/env bash
LOG="./logger.sh"
${LOG} "clear";

# Start ssh-server in container
${LOG} "log" "SSH-TO-CONTAINER";

${LOG} "run" "docker exec clinux_clinux_1 sudo /etc/init.d/ssh start " || exit $?;

${LOG} "log" "USE ->> ssh -A -p 2222 coder@localhost <<-";
