# Project 3: Building a model for the solar system using ODEs.
In this folder there are 3 subfolders [code](https://github.com/SigurdSundberg/FYS3150/tree/master/project3/code), [report](https://github.com/SigurdSundberg/FYS3150/tree/master/project3/report) and [sample data](https://github.com/SigurdSundberg/FYS3150/tree/master/project3/sample_data).
Which contains what is self explanatory.
## Code
All the code was run on the following specs:

Computer  : Lenovo IdeaPad Flexx 5 14IIL05<br />
Version   : Ubuntu 20.04 1 LTS <br />
Processor : Intel Core i5-1035G1 Processor 6MB @ 1.00GHz x8 <br />
Memory    : 8.0GB DDR4-3200 DDR4 Soldered 3200MHz <br />
Graphics  : Mesa Intel® UHD Graphics (ICL GT1) <br />

Important to note is that ```main.py``` does not recreate all the data from the article. It only simulates the solar system for ``two-body`` problem, ``three-body`` problem and ``eigth-body`` problem, for fixed values of dt and n. This is due to time constraints and structure in main. In the file ```main.txt``` different main functions written in c++ can be found, which each does something different. Such as timing the two algorithms for different n or checking if the inverse square law holds for a fixed dt and n.