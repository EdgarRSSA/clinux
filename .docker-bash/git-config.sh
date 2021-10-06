GITCONFIG="${HOME}/.gitconfig";
CONTAINER="clinux1";
CONTAINER_HOME="/home/coder/";

docker cp ${GITCONFIG} "${CONTAINER}:${CONTAINER_HOME}"
