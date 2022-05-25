./build.sh
docker run \
    -v $(eval echo ~/.ssh/id_rsa:/root/.ssh/id_rsa):ro \
    -w /root/repos/pman \
    -it pman /bin/bash
