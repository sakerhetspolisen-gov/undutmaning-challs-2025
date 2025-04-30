.PHONY: all clean dirstuff runbash runscripts builddatasheet

BAUD = 115200
SAMP_FREQ = 691200

all: dirstuff clean runbash runscripts builddatasheet rmmetadata

dirstuff:
	mkdir -p buildoutputs

runbash:
	# Create radiodata and raw data
	cd src && bash generate_radiodata.sh

runscripts:
	# Create the captured trace
	python3 src/uart_sim.py $(BAUD) $(SAMP_FREQ)

	# Create screenshot
	python3 src/plot_uart.py $(SAMP_FREQ) $(BAUD) 200 50

	# Artefacts
	mv buildoutputs/encrypted_radio_msg download/encrypted_radio_msg
	mv buildoutputs/captured download/captured
	mv buildoutputs/screenshot.png download/screenshot.png

builddatasheet: download/datasheet.pdf

download/datasheet.pdf: src/datasheet.tex
	# Create datasheet
	pdflatex -output-directory=buildoutputs src/datasheet.tex
	pdflatex -output-directory=buildoutputs src/datasheet.tex
	mv buildoutputs/datasheet.pdf download/datasheet.pdf

rmmetadata:
	exiftool -overwrite_original -all= download/screenshot.png

clean:
	rm -rf buildoutputs/*
	rm -rf download/*