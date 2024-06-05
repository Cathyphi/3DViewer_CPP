FLAGS = -Wall -Werror -Wextra -std=c++17

all: install tests


install:
	cd View && qmake && make && make clean
	cp -r View/QOpenGLWidget.app  ~/Desktop

uninstall:
	rm -rf View/QOpenGLWidget.app 
	rm -rf ~/Desktop/QOpenGLWidget.app
	rm -rf View/Makefile

clean:
	rm -rf *.o *.a *.gcno  *.gcda *.gcov *.css report html latex *.dSYM report *.info *.gz
	rm -rf test

dvi:
	doxygen Doxyfile
	open ./html/index.html

dist: install
	mkdir archiv
	cp -r *.cc Model/ View/ Controller/ Makefile archiv
	tar -cvzf 3DViewer.tar.gz archiv
	rm -rf archiv

tests: clean
	g++ $(FLAGS) test.cc Model/model.cc -lgtest -o test -lstdc++
	./test

	
gcov_report: clean
	g++ $(FLAGS) --coverage test.cc Model/model.cc -o test -lgtest 
	./test
	lcov -t "test" -o test.info -c -d . --no-external
	genhtml -o report test.info
	open report/index.html

style:
	clang-format -n Model/model.cc Model/model.h Controller/*.h View/*.cpp View/*.h test.cc

leaks:
	leaks -atExit -- ./test
