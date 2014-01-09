CC = g++
CFLAGS = -Wall
LDFLAGS =  -L../OculusSDK/LibOVR/Lib/Linux/Release/x86_64 -L/usr/local/lib -L/usr/local/lib/OGRE/ -L/usr/local/lib/Annwvyn -lX11 -lXinerama -ludev -lboost_system -lAnnwvyn -lovr -lOgreMain -lOIS -lopenal -lBulletDynamics -lBulletCollision -lLinearMath -lsndfile -lCEGUIBase-0 -lCEGUIOgreRenderer-0 -lpthread
IFLAGS = -I/usr/local/include/OGRE  -I../OculusSDK/LibOVR/Include  -I/usr/include/AL -I/usr/include/bullet  -I/usr/include/OIS -I/usr/include/boost -I./include/ -I/usr/local/include/Annwvyn -I/usr/local/include/cegui-0

INSTALL_PREFIX = /usr/local

ifeq ($(shell uname), Linux)

all: bin/RiftDogFighter

#obj/StereoscopicWindow.o
bin/RiftDogFighter: obj/main.o obj/UserPlane.o 	
	$(CC)  obj/main.o obj/UserPlane.o obj/StereoscopicWindow.o -o bin/RiftDogFighter $(CFLAGS) $(LDFLAGS) $(IFLAGS) 

#include/StereoscopicWindow.hpp 
obj/main.o: include/UserPlane.hpp src/main.cpp	
	$(CC) -c src/main.cpp  -o obj/main.o $(CFLAGS) $(LDFLAGS) $(IFLAGS) 

#obj/StereoscopicWindow.o: src/StereoscopicWindow.cpp include/StereoscopicWindow.hpp
#	$(CC) -c src/StereoscopicWindow.cpp  -o obj/StereoscopicWindow.o $(CFLAGS) $(LDFLAGS) $(IFLAGS) 

obj/UserPlane.o: src/UserPlane.cpp include/UserPlane.hpp
	$(CC) -c src/UserPlane.cpp  -o obj/UserPlane.o $(CFLAGS) $(LDFLAGS) $(IFLAGS) 


.PHONY: clean

clean:
	rm -r ./bin/RiftDogFighter ./obj/*

endif
