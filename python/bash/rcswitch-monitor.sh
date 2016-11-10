#!/bin/bash
until python /home/elsupport/haxx/socketListener.py; do
    echo "Image deamon 'socketListener.py' crashed with exit code $?.  Respawning.." >&2
    sleep 1
done
