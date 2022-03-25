FROM centos:latest
COPY lab2.S /home
RUN yum -y install gcc
RUN dnf --enablerepo=powertools install nasm
RUN chmod +x home/lab2.S 
