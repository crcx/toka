# =======================
# You may want to override CFLAGS or add OTHER
# flags when building.
# =======================

.PHONY : library poharu toka

default:
	@echo Compiling Toka...
	@cd toka && make
	@mv toka/toka bin/
	@cp toka/bootstrap.toka bin/
clean:
	@rm -f `find . | grep \~ `
	@rm -f source/*.o source/a.out
	@rm -f bin/toka
install:
	@echo Installing Toka...
	@mkdir -p /usr/share/toka
	@cp bin/toka /usr/bin
	@cp toka/bootstrap.toka /usr/share/toka
