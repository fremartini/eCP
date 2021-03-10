#! /usr/bin/env bash

# Kills and cleans all Docker

echo "This script will kill all Docker instances and remove ALL images."
read -p "Press enter to continue"

echo "Closing running instances..."
docker ps -a -q | xargs docker rm

echo "Removing all images..."
docker images -a -q | xargs docker rmi -f

echo "Done."
