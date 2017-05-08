.DEFAULT_GOAL := test
test:
	cd src && $(MAKE) 

format:
	cd src && make format

clean:
	cd src && make clean 
