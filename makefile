all : main soone.so

main : main.cpp
	g++ -g -Wl,-E -o $@ $^ -ldl

soone.so : soone.cpp
	g++ -g -shared -fPIC -o $@ $^ -ldl

clean :
	rm -rf main soone.so *~
