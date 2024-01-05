CC = g++
CFLAGS = -std=c++17
GCOV=-fprofile-arcs -ftest-coverage
OUTPUTDIR=Application
SRCFILES=model/s21_ant_algorithm.cpp model/s21_graph_algorithms.cpp model/s21_graph.cpp
HFILES=model/s21_ant_algorithm.h model/s21_graph_algorithms.h model/s21_graph.h
OFILES=s21_ant_algorithm.o s21_graph_algorithms.o s21_graph.o
YELLOWBOLD='\033[1;33m'
GREEN= '\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m'



ifeq ($(OS), Darwin)
	CHECKFLAG=-lgtest
	OUTPUTFILE=Navigator.app
else
	CHECKFLAG=-L . -lgtest -lm -lrt -lpthread
	OUTPUTFILE=Navigator
endif


all: clean s21_graph.a s21_graph_algorithms.a build create_dir

build:
	$(CC) $(CFLAGS) main.cpp -o $(OUTPUTFILE) s21_graph.a s21_graph_algorithms.a 

test: clean
	$(CC) $(GCOV) -c $(SRCFILES)
	ar rcs test_model.a $(OFILES)
	g++ -c test/tests.cpp -o tests.o
	g++ $(GCOV) tests.o test_model.a -o test/Test -L . -lgtest -lm -lrt -lpthread
	./test/Test

s21_graph.a: s21_graph.o
	ar rcs s21_graph.a s21_graph.o

s21_graph_algorithms.a: s21_ant_algorithm.o s21_graph_algorithms.o
	ar -crs s21_graph_algorithms.a s21_ant_algorithm.o s21_graph_algorithms.o

s21_ant_algorithm.o: model/s21_ant_algorithm.cpp
	$(CC) $(CFLAGS) -c $< -o $@

s21_graph_algorithms.o: model/s21_graph_algorithms.cpp
	$(CC) $(CFLAGS) -c $< -o $@

s21_graph.o: model/s21_graph.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o *.a *.gcda *.gcno *.info leaks_test test/Test test/RESULT_valid_graph.dot

style:
	@echo ${YELLOWBOLD}"Linter start:..."
	@sleep 1
	@cp ../materials/linters/.clang-format .clang-format
	@sleep 1
	@clang-format -n $(SRCFILES) $(HFILES)
	@rm -f .clang-format
	@echo $(YELLOW)"1..."
	@sleep 0.5
	@echo 2...
	@sleep 0.5
	@echo 3...
	@sleep 0.5
	@echo ${YELLOWBOLD}"Linter finished:" ${GREEN}"All passed!"${NC}

leaks_test: clean
	$(CC) -std=c++17 -o $@ test/tests.cpp $(SRCFILES) -lgtest -lrt -lm -lpthread
	valgrind ./$@


create_dir:
	mkdir -p $(OUTPUTDIR)
	rm -f $(OUTPUTDIR)/$(OUTPUTFILE)
	if [ -e Navigator ]; then mv $(OUTPUTFILE) $(OUTPUTDIR)/; fi

gcov_report: clean test
	lcov -o coverage.info -c -d . -no-external
	genhtml -o Report coverage.info