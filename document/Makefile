NAME = document

all:
	make clean
	latex $(NAME).tex
	xdvi $(NAME).dvi

pdf:
	make all
	xdvipdfmx $(NAME).dvi

.PHONY:clean
clean:
	rm -rf *.aux *.log *.dvi *.toc 
