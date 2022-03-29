FROM ubuntu
COPY lab2.S /home
RUN apt update
RUN apt install gcc
RUN apt install gcc-multilib
RUN chmod +x home/lab2.S 
