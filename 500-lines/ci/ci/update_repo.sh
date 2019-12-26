#!/bin/bash

set -e

source run_or_fail.sh

rm -f .commit_id
run_or_fail "Repository folder not found!" pushd $1 1> /dev/null
run_or_fail "Could not reset git" git reset --hard HEAD

# get the most recent commit
COMMIT_ID=$(run_or_fail "Could not call 'git log' on repo" git rev-parse HEAD)
if [ $? != 0 ]; then
  echo "Could not call 'git log' on repo"
  exit 1
fi

# update the repo
run_or_fail "Could not pull from repository" git pull

# get the most recent commit after the update
NEW_COMMIT_ID=$(run_or_fail "Could not call 'git log' on repo" git rev-parse HEAD)
if [ $? != 0 ]; then
  echo "Could not call 'git log' on repo"
  exit 1
fi

echo $COMMIT_ID $NEW_COMMIT_ID

# if the id changed, then write it to a file
if [ $NEW_COMMIT_ID != $COMMIT_ID ]; then
  popd 1> /dev/null
  echo $NEW_COMMIT_ID > .commit_id
fi
