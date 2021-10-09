#!/usr/bin/env bash

set -x
set -euo pipefail
git config --global user.name 'Cole Botkens'
git config --global user.email 'cole.mickens+colebot@gmail.com'
git remote add swaywm 'https://github.com/swaywm/wlroots'
git remote add danvd 'https://github.com/danvd/wlroots-eglstreams'
git remote update

cat .git/config

git format-patch -1 master master^ --stdout | tee /tmp/patch

# get us that eglstreams goodness
git reset --hard danvd/master

# base on swaywm/master
git rebase swaywm/master

# grab back the GHA commit
cat /tmp/patch | git am -3

# check and see if we actually did anything...
if ! git diff-tree --exit-code origin/master master; then
  echo "we must have had some real work, so lets actually push"
  git push origin HEAD -f
else
  echo "there must not have been any actual rebase done, lets not churn the commit"
fi
