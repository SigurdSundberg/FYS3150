./report/report.pdf: ./report/report.pdf ./code/plots/plot_specialized.png ./code/plots/plot_general.png
	pdflatex ./report/report.tex
	
./code/plot.py: 
	python3 plot.py plot specialized plot_specialized 3 2
	python3 plot.py rel specialized error_specialized 7 2
	python3 plot.py plot general plot_general 3 2
	python3 plot.py rel general error_general 6 2 
