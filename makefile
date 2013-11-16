CC = g++
CFLAGS =
LDFLAGS =  -L../OculusSDK/LibOVR/Lib/Linux/Release/x86_64 -L/usr/local/lib -L/usr/local/lib/OGRE/ -L/usr/local/lib/Annwvyn -lAnnwvyn -lovr -lOgreMain -lOIS -lopenal -lBulletDynamics -lBulletCollision -lLinearMath -lsndfile -lX11 -lXinerama -ludev -lboost_system -lCEGUIBase-0 -lCEGUIOgreRenderer-0
IFLAGS = -I/usr/local/include/OGRE  -I../OculusSDK/LibOVR/Include  -I/usr/include/AL -I/usr/include/bullet  -I/usr/include/OIS -I/usr/include/boost -I./include/ -I/usr/local/include/Annwvyn -I/usr/local/include/cegui-0

INSTALL_PREFIX = /usr/local

ifeq ($(shell uname), Linux)

all: 
	$(CC) src/*.cpp -o bin/RiftDogFighter $(CFLAGS) $(LDFLAGS) $(IFLAGS) 

.PHONY: clean

clean:
	rm -r ./bin/*

endif
