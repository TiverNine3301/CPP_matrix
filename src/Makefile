CFLAGS = -Wall -Werror -Wextra

all: clean s21_matrix_oop.a

s21_matrix_oop.a:
	g++ -c $(CFLAGS) -lstdc++ -std=c++17 s21_matrix_oop.cc help.cc
	ar rcs s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a

clean:
	rm -rf *.o *.out s21_matrix_oop.a  test
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report *.info

leaks: test
	valgrind --tool=memcheck --leak-check=yes  ./test
	leaks -atExit -- ./test | grep LEAK:

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.cc *.h
	clang-format -style=Google -n *.cc *.h
	rm .clang-format

test: clean
	g++ -lstdc++ -std=c++17 s21_matrix_oop.cc help.cc s21_matrix_oop_test.cc -o test -lgtest
	./test

gcov_report: clean
	g++ s21_matrix_oop.cc help.cc s21_matrix_oop_test.cc -o test --coverage -lgtest
	./test
	lcov -d ./ --capture --output-file s21_matrix_oop.info 
	genhtml s21_matrix_oop.info --output-directory report
	open report/index.html
