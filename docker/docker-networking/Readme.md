
<h2>Docker networking  tutorial does not include docker swarm

Create two networks called as web and app </h2>

docker network create web

docker network create app

<h3>Assuming you have two images created called as web:v1.0 and app:v1.0</h3>

docker run -itd -rm --network web --name web web:v1.0

docker run -itd --rm --network app --name app app:v1.0

<h3> both the containers will be in their own isolated networks and will be segmented from each other.
</h3>

<h3>MAC VLAN network</h3>

docker network create -d macvlan --subnet 10.1.1.0/24  --gateway 10.1.1.1 -o parent=eth0  macvlan01

<h3>Stop the web container and lauch it in macvlan</h3>
docker stop web
<h3>launch it in macvlan01</h3>
docker run -itd -rm --network macvlan01 --ip 10.1.1.100 --name web web:v.10

(if you cannot ping the default gateway go up the chain and verify if promisc is on)

ip link set eth0  promisc on

>If you still cannot ping the gateway you have to go up the chain and verify if promiscus mode is on

<h3>Cleanup insatnces and network</h3>
docker stop web

docker network rm macvlan01

<h3>Example of IPVLAN (L2) </h3>

docker network create -d ipvlan --subnet 10.1.1.0/24  --gateway 10.1.1.1 -o parent=eth0 ipvlan01

docker run -itd --rm --network ipvlan01  --name app:v1.0

docker run -itd --network ipvlan01 --name web web:v1.0


<h3>IPVLAN L3 network 
creating 2 networks 192.168.10.0/24 and 10.168.11.0/24 with host as a router</h3>

docker network create -d ipvlan02 --subnet 192.168.10.0/24 -o parent=eth0  -o ipvlan_mode=l3 --subnet 192.168.11.0/24 mars

docker run -itd --rm --network ipvlan02  --ip 192.168.10.21 --name web web:v1.0


docket run -itd -rm --network ipvlan02 --ip 10.168.11.21 --name app app:v1.0

<h3>Want to inspect what's running and state of your network</h3>
docker inspect ipvlan02


# Make sure you have static route on route for these networks.
#
