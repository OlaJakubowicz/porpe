#dumped old makefile
	
clean: 
	@rm -f *.o
	@echo "Clean rule"
	
debug:
	$(CC) $(OPTS) main main.cpp $(BOOST_INCLUDE) $(BOOST_LIB_DIR) $(BOOST_LIBS) $(DEBUG)
	@echo "Debug rule"
	
test:
	$(CC) $(OPTS) test test_case.cpp $(BOOST_INCLUDE) $(BOOST_LIB_DIR) $(BOOST_UNIT_TEST_LIBS)
	@clear
	@mv test tmp_test
	@echo 'Start Testing!'
	@./tmp_test
	@rm -f tmp_test
	@echo "Test rule"