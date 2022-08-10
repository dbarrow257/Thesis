thesis: 
	pdflatex Thesis && bibtex Thesis && pdflatex Thesis && pdflatex Thesis

clean:
	@rm -f thesis.pdf thesis.log thesis.aux
	@rm -f *.bbl *.blg *.lof *.cut *.log *.bcf *.maf *.aux *.mtc *.mtc0 *~
	@rm -f *.lot *.out *.toc *.xml *-blx.bib *.pdf
