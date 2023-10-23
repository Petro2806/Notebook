LATEXCMD = pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:
export max_print_line = 1048576

help:
	@echo "This makefile builds LNU notebook"
	@echo ""
	@echo "Available commands are:"
	@echo "	make Koni		- to build Koni notebook"
	@echo "	make clean		- to clean up the build process"
	@echo ""
	@echo "For more information go to blackbox Makefile"

Koni: | build
	$(LATEXCMD) content/kactl.tex && $(LATEXCMD) content/kactl.tex
	cp build/kactl.pdf Koni.pdf

clean:
	rm -f header.tmp && cd build && rm -f kactl.aux kactl.log kactl.tmp kactl.toc kactl.ptc kactl.out kactltmp.tex kactl.pdf


