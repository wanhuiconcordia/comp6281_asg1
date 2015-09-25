# Last Update:20150924
INCLPATH +=/usr/include
#CFLAGS += -std=c99
CFLAGS += -std=c11
OBJECTS = fileExplorer.o  findandreplace.o  log.o  main.o  tools.o

YaoApp: $(OBJECTS)
	gcc $(OBJECTS) $(LIBS) -o YaoApp

fileExplorer.o: ../fileExplorer.c ../fileExplorer.h
	gcc $(CFLAGS) -o fileExplorer.o -c ../fileExplorer.c -I$(INCLPATH)
findandreplace.o: ../findandreplace.c ../findandreplace.h
	gcc $(CFLAGS) -o findandreplace.o -c ../findandreplace.c -I$(INCLPATH)
log.o: ../log.c ../log.h
	gcc $(CFLAGS) -o log.o -c ../log.c -I$(INCLPATH)
main.o: ../main.c
	gcc $(CFLAGS) -o main.o -c ../main.c -I$(INCLPATH)
tools.o: ../tools.c ../tools.h
	gcc $(CFLAGS) -o tools.o -c ../tools.c -I$(INCLPATH)

clean:
	rm *.o

