FROM centos:latest
COPY script.sh /home
RUN chmod +x home/script.sh