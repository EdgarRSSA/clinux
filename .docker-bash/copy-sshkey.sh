SSH_KEY="id_rsa.pub";
SSH_KEY_DIR="${HOME}/.ssh";
SSH_CONT_AUTH_DIR="/home/coder/.ssh";
SSH_CONT_AUTH="authorized_keys";
CONTAINER="clinux1";

# copy from pc to container
docker cp "${SSH_KEY_DIR}/${SSH_KEY}" "${CONTAINER}:${SSH_CONT_AUTH_DIR}/"

# write key in authorized_keys in container
docker exec ${CONTAINER} bash -c "cat ${SSH_CONT_AUTH_DIR}/${SSH_KEY} >> ${SSH_CONT_AUTH_DIR}/${SSH_CONT_AUTH}"
