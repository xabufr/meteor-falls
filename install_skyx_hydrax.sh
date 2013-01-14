#!/bin/sh
cd SkyX
cmake .
make -j3
make install
cd ..
cd CommunityHydrax-master
make -j3
make install
cd ..
exit
