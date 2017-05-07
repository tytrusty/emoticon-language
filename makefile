.DEFAULT_GOAL := test
test:
	cd src && $(MAKE) 

clean:
	cd src && make clean 

