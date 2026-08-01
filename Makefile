LATEXCMD = pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:
export max_print_line = 1048576

help:
	@echo "This makefile builds KACTL (KTH Algorithm Competition Template Library)"
	@echo ""
	@echo "Available commands are:"
	@echo "	make fast		- to build KACTL, quickly (only runs LaTeX once)"
	@echo "	make kactl		- to build KACTL"
	@echo "	make clean		- to clean up the build process"
	@echo "	make test-compiles	- to test compiling all headers, except those in scrips/skip_headers"
	@echo "	make help		- to show this information"
	@echo "	make showexcluded	- to show files that are not included in the doc"
	@echo ""

fast: | build
	$(LATEXCMD) content/kactl.tex </dev/null
	cp build/kactl.pdf kactl.pdf

kactl: test-session.pdf | build
	$(LATEXCMD) content/kactl.tex && $(LATEXCMD) content/kactl.tex
	cp build/kactl.pdf kactl.pdf

clean:
	cd build && rm -f kactl.aux kactl.log kactl.tmp kactl.toc kactl.pdf kactl.ptc

.PHONY: help fast kactl clean

build:
	mkdir -p build/

test-compiles:
	./scripts/compile-all.sh .

test-session.pdf: content/test-session/test-session.tex content/test-session/chapter.tex | build
	$(LATEXCMD) content/test-session/test-session.tex
	cp build/test-session.pdf test-session.pdf

showexcluded: build
	grep -RoPh '^\s*\\kactlimport{\K.*' content/ | sed 's/.$$//' > build/headers_included
	find ./content -name "*.h" -o -name "*.py" -o -name "*.java" | grep -vFf build/headers_included
