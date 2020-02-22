##############################
## MAKEFILE FOR THIS SERVER ##
##############################
CC = gcc

CFLAGS = -Wall -lwiringPi

TARGET = power-switch

all: $(TARGET)

$(TARGET): main.c switch.c common.c
		$(CC) $(CFLAGS) -o $(TARGET) main.c switch.c common.c
		
clean:
		$(RM) power-switch