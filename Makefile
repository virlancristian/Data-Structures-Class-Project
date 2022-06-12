build:
	gcc *.c -o lanParty
run: build
	./lanParty c.in d.in r.out
clean:
	rm lanParty