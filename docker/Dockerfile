FROM alpine:3.16 as pman

RUN apk upgrade
RUN apk add --no-cache gcc musl-dev
RUN apk add --no-cache  bash fish python3
RUN apk add --no-cache  zsh
RUN apk add --no-cache  meson vim
RUN apk add --no-cache automake autoconf
RUN apk add --no-cache make cmake 
RUN apk add --no-cache sed
RUN apk add --no-cache ninja
RUN apk add --no-cache git
RUN cp /bin/sed /bin/gsed
RUN git clone https://github.com/clarkwang/passh /repos/passh
RUN cd /repos/passh && gcc -o /bin/passh passh.c
RUN apk add --no-cache pkgconfig
RUN apk add --no-cache libvterm libvterm-dev
RUN apk add --no-cache gd
RUN apk add curl curl-dev
#ADD ./pman /root/pman
#RUN cd /root/pman && ls


#RUN cd /root/pman && make all -bn
#R#UN cd /root/pman && make all
RUN git clone https://github.com/clibs/clib.git /clib
RUN cd /clib && make && make install
RUN passh clib upgrade
RUN apk add jq
RUN apk add nodejs npm
RUN git clone https://github.com/binRick/pman /root/repos/pman
RUN apk add gd-dev
RUN apk add gd-dev openssh



#RUN cd /root/repos/pman && git pull --reset hard
RUN rm -rf /root/repos/pman/submodules/libansilove
RUN rm -rf /root/repos/pman/submodules/libansilove
RUN git clone https://github.com/ansilove/libansilove /root/repos/pman/submodules/libansilove
RUN git clone https://github.com/binRick/ansi /ansi

RUN cd /ansi && make install
RUN cd /root/repos/pman/submodules/libansilove && cmake . && make install
RUN apk add gd-dev file bat ripgrep
RUN cp /root/repos/pman/bins/uptime/0/uptime0.c /tmp/uptime0.c
RUN cd /root/repos/pman && git reset --hard && git pull
RUN rm -rf /root/pman/deps /root/repos/pman/submodules
COPY ./submodules /root/repos/pman/submodules
COPY ./deps /root/repos/pman/deps




#RUN cd /root/repos/pman && git pull
#RUN cd /root/repos/pman && ls
#RUN cd /root/repos/pman && git pull
#RUN cd /root/repos/pman && make clean
#RUN rm -rf /root/repos/pman/build
#RUN cd /root/repos/pman && clib i -C 1 -f -c
#RUN cd /root/repos/pman && rm -rf o al uild
#RUN cd /root/repos/pman && make clean
#RUN cd /root/repos/pman && passh scripts/submodule-cmds.sh
#RUN cd /root/repos/pman && git pull
#RUN cd /root/repos/pman && git reset --hard
#RUN rm -rf  /root/repos/pman/submodules
#RUN rm -rf  /root/repos/pman/build
#RUN cd /root/repos/pman && ./scripts/submodule-cmds.sh|bash
#RUN cd /root/repos/pman && passh -P continue -p y make setup||true
#RUN cd /root/repos/pman && passh scripts/clib-cmds.sh
#RUN rm -rf /root/repos/pman/uild
#RUN rm -rf /root/repos/pman/build
#RUN cd /root/repos/pman && meson build --wipe||true
#RUN cd /root/repos/pman && meson build --wipe||true
#RUN cd /root/repos/pman && meson build --reconfigure||true
#RUN cd /root/repos/pman && make all||true
#RUN cd /root/repos/pman/build && ninja||true
#RUN rm -rf /root/repos/pman/build
#RUN cd /root/repos/pman && meson build
#RUN cd /root/repos/pman/build && ninja
#meson build
#RUN cd /root/repos/pman/build && passh ninja -C build
#meson build
#RUN cd /root/repos/pman/build && passh ninja
#RUN cd /root/repos/pman && ninja -C b1


