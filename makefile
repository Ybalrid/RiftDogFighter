CC = g++
CFLAGS = -Wall
LDFLAGS =  -L../OculusSDK/LibOVR/Lib/Linux/Release/x86_64 -L/usr/local/lib -L/usr/local/lib/OGRE/ -L/usr/local/lib/Annwvyn -lAnnwvyn -lovr -lOgreMain -lOIS -lopenal -lBulletDynamics -lBulletCollision -lLinearMath -lsndfile -lX11 -lXinerama -ludev -lboost_system -lCEGUIBase-0 -lCEGUIOgreRenderer-0
IFLAGS = -I/usr/local/include/OGRE  -I../OculusSDK/LibOVR/Include  -I/usr/include/AL -I/usr/include/bullet  -I/usr/include/OIS -I/usr/include/boost -I./include/ -I/usr/local/include/Annwvyn -I/usr/local/include/cegui-0

INSTALL_PREFIX = /usr/local

ifeq ($(shell uname), Linux)

all: bin/RiftDogFighter


bin/RiftDogFighter: obj/main.o obj/UserPlane.o obj/StereoscopicWindow.o
	$(CC)  obj/main.o obj/UserPlane.o obj/StereoscopicWindow.o -o bin/RiftDogFighter $(CFLAGS) $(LDFLAGS) $(IFLAGS) 

obj/main.o: include/UserPlane.hpp include/StereoscopicWindow.hpp src/main.cpp
	$(CC) -c src/main.cpp  -o obj/main.o $(CFLAGS) $(LDFLAGS) $(IFLAGS) 

obj/StereoscopicWindow.o: src/StereoscopicWindow.cpp include/StereoscopicWindow.hpp
	$(CC) -c src/StereoscopicWindow.cpp  -o obj/StereoscopicWindow.o $(CFLAGS) $(LDFLAGS) $(IFLAGS) 


obj/UserPlane.o: src/UserPlane.cpp include/UserPlane.hpp
	$(CC) -c src/UserPlane.cpp  -o obj/UserPlane.o $(CFLAGS) $(LDFLAGS) $(IFLAGS) 


.PHONY: clean

clean:
	rm -r ./bin/RiftDogFighter ./obj/*

endif
