FROM centos:latest
COPY lab2.S /home
RUN dnf --disablerepo '*' --enablerepo=extras swap centos-linux-repos centos-stream-repos
RUN dnf distro-sync
RUN yum -y install gcc
RUN dnf --enablerepo=powertools install nasm
RUN chmod +x home/lab2.S 
