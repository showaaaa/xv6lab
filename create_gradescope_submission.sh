#!/usr/bin/env bash

BASE_HASH=$(git log --format="%H" -n 1 origin/main)

git archive --output=project.zip HEAD $(git diff --diff-filter=ACMRTUXB --name-only $BASE_HASH HEAD)
 
