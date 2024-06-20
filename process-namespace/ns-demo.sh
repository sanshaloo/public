#!/bin/sh
#
#

#  Total idea == Create a process namespace, network namespae and use both of them together
#  with a mounted filesystem for complete process isolation
#  Why docker or containerd can't be used ::  Sure they can be 
# 
#  It's more fun to do it this way

echo '
**************************************
Process Namespace magic
**************************************
'
# sleep 2 

echo '
=============================================================================
Check out process space"
you will be placed in a shell, play with it and type exit to return"
atleast run ps -aef to check number of running proces to realize you are
in a process namespace
=============================================================================
'

ps -aef | head -10


# sudo unshare -pf --mount-proc /bin/bash


echo '
========================================
Lets create a network namespace
========================================
'
NS_NAME=test
dont_create=0

for net_ns in  `ip netns list`
do 
  if [ "X${net_ns}" =  "X${NS_NAME}" ]; then
    dont_create=1
  fi
done



if [ $dont_create -ne  0 ] ; then
  echo "$NS_NAME exist deleteing and recreating it"
  sudo ip netns delete ${NS_NAME}
  sudo ip netns add ${NS_NAME}
fi
