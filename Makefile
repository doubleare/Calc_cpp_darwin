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
	@g++ $(FLAGS) $(UNIT).cc $(LIST) -lgtest -lgtest_main -lpthread -o $(UNIT)
	@./$(UNIT)
	@echo

re: clean all

linter:
	@cp ../materials/linters/.clang-format ./.clang-format
	@clang-format -i *.h ./SMART_V2/form.h ./SMART_V2/graphx.h ./SMART_V2/mainwindow.h
	@clang-format -i *.cc ./SMART_V2/form.cpp ./SMART_V2/graphx.cpp ./SMART_V2/main.cpp ./SMART_V2/mainwindow.cpp
	clang-format -n *.h *.cc ./SMART_V2/form.h ./SMART_V2/graphx.h ./SMART_V2/mainwindow.h ./SMART_V2/form.cpp ./SMART_V2/graphx.cpp ./SMART_V2/main.cpp ./SMART_V2/mainwindow.cpp
	@rm ./.clang-format

dvi:
	open doc.txt
open:
	@open SmartCalc/SMART_V2.app

leaks: test
	CK_FORK=no leaks -atExit -- ./test