CCX := g++
CCXFLAGS := -std=c++17 -Wall

all:
	for dir in day*; do \
  		mkdir -p $$dir/build/; \
  		if [ -e $$dir/input.txt ]; then \
  		  cp $$dir/input.txt $$dir/build/; \
	    fi; \
  		for file in $$dir/*.cpp; do \
  			target=$$(basename $$file .cpp); \
			$(CCX) $(CCXFLAGS) $$file -o $$dir/build/$$target; \
		done \
	done

clean:
	rm -rf day*/build