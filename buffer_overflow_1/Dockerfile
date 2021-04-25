FROM ubuntu:18.04

RUN mkdir /srv/challenge
ADD . /srv/challenge/

RUN apt update && apt install -y socat && rm -rf /var/lib/apt/lists/*

RUN chmod -R 755 /srv/challenge
RUN adduser --system --shell /bin/bash hhctf
USER hhctf
WORKDIR /srv/challenge

CMD ["socat", "-s", "tcp-l:1337,reuseaddr,fork", "exec:/srv/challenge/chal,stderr"]
