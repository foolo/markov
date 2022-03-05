## Building

	meson build
	cd build
	ninja

## Running

	cd build
	./markov

### Example:

	./markov --text file.txt --order 4 --save model.txt
	./markov --load model.txt --count 100

## Run unittests

	cd build
	meson test
	# or
	./unittests
