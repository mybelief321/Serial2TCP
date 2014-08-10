main: main.o SerialPort.o
	gcc main.o SerialPort.o -o main -lpthread

main.o:main.c 
	gcc -c main.c -lpthread
	
SerialPort.o:SerialPort.c
	gcc -c SerialPort.c
	
clean:
	rm -rf *.o main
