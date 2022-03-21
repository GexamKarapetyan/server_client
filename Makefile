CC		= g++ -std=c++2a
THREADFLAG	= -lpthread
GET_OBJ    	= -o
SERVER_NAME  	= main-server.cpp 
CLIENT_NAME  	= main-client.cpp
EXE_C_N		= client
EXE_S_N		= server

all :
	${CC} ${SERVER_NAME} ${GET_OBJ} ${EXE_S_N} ${THREADFLAG}
	${CC} ${CLIENT_NAME} ${GET_OBJ} ${EXE_C_N}
