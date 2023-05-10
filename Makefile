NAME = SmartCalc

UNIT = test

LIST = model.cc calculator.cc

FLAGS = -std=c++17 -Wall -Wextra -Werror

all: test

install:
	@mkdir $(NAME)
	@cd $(NAME) && cmake ../SMART_V2 && make

uninstall: $(NAME)
	@cd $(NAME) && make clean
	@rm -rf $(NAME)
	@echo
	@echo UNINSTALLED
	@echo

dist: $(NAME)
	@test -d Calculator2.0 || mkdir Calculator2.0
	@cp -R ./$(NAME)/SMART_V2.app Calculator2.0
	@tar -czf Calculator2.0.tar.gz Calculator2.0
	@rm -rf Calculator2.0

clean: 
	@rm -fr $(UNIT) *.tar.gz
	@clear

test: clean
	@echo
	@g++ $(FLAGS) $(UNIT).cc $(LIST) -lgtest -o $(UNIT)
	@./$(UNIT)
	@echo

re: clean all

dvi:
	@open doc.txt
open:
	@open SmartCalc/SMART_V2.app

leaks: test
	@CK_FORK=no leaks -atExit -- ./test