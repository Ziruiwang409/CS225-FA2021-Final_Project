# CS225 Final Project Development Log
**Team (ziruiw3-weixuan6-hua13-zixuanl9)**

## Project Development:
- Nov. 8th - Nov. 14th:
    We meet on Nov.10th 6p.m. this week to decide how to delegate beginning tasks for our project. We decided to begin by creating a CSV parser  to make our covid19 data easier to use. The Covid19 dataset comes from John Hopkins University as well as the Fernando Lasso (links to the dataset can be found in Proposal.md). 

- Nov. 15th - Nov. 21th:
    This week, we meet on Nov. 17th 6p.m. to distribute works to each group mate, trying to implement all helper functions (Zirui Wang), constructors and destructors (Zhiheng Hua & Zixuan Liu), as well as basic graph traversal BFS (Weixuan Sun). We intend to meet again on Nov.21th in order to compile our current work and then begin writing basic test cases.

- Nov. 22th - Nov. 28th
    This week, we meet on Nov. 24th, 2 p.m. to finish up our algorithm and function regarding covidgraph. We wrote basic test cases, and use the testing dataset (links to the dataset can be found in ./tests). Based on our test case, we eliminate bugs in our program. So far, before the mid Check, we are able to finish:
    - Zhiheng Hua & Zixuan Liu: Data parsing, construct classes, store the COVID-19 dataset into the graph
	- Zirui Wang: Implement all get methods that will serve as helper functions (e.g. getDeaths()/getConfirmed())
	- Weixuan Sun: fix BFS traversal and make test cases working
    - Finish writing test cases

- Nov. 29th - Dec. 5th
    This week, we finish our mid-project check on Dec. 1, and meet in group at Dec. 4th 7 p.m. We decides to start our second part of the project- data visualization. We find a world map on google and decides to implement our visualization similar to the MP Stickers, in which we treat each country node as a sticker and put it onto the world map at particular location. Therefore, we are compiling all the useful data structure from our course (such as the disjoint sets, graphs, linked list, etc) to create the structure and use the functions. We are able to complete the static visualization (Zirui Wang), dynamic visualization (Zhiheng Hua),  Dijkstra’s algorithm (Weixuan Sun) for find shortest path, as well as rest of the test cases, including edge cases (Zixuan Liu).

- Dec. 6th - Dec. 12th
    This week, we meet on Dec. 6th 4 p.m. to finalize our project. We store our result of static visualization to png file and dynamic visualization to gif files(all output file is under the directory ‘sample-output’) All member assisted with filming the final project video. Project complete.

## Project ChangeLog: 
    2021-12–12: fixed small problems in test cases function call
    2021-12–11: covidgraph-getter.cpp bugs fixed
    2021-12–11: mock test dataset & test cases written, generated test images
    2021-12–10: Some test cases added
    2021-12–08: Finish Static visualization & merge Image-static.cpp and Image.cpp
    2021-12–08: finish dynamic visualization
    2021-12–08: modified and complete confirmed static and dynamic visualization, improve visualization design
    2021-12–07: now able to draw gif, added some sample outputs
    2021-12–07: created testcases for findShortestPath
    2021-12–07: added a map that maps the name of the country (state/province) to its node pointer
    2021-12–07: updated Makefile for test case and renamed testcases file
    2021-12–07: added image-static visual-static to avoid conflict in dev
    2021-12–06: modified draw risk level signature to allow other functionality extension
    2021-12–06: add new files, change cs225 directory, start on image and visualization
    2021-12–02: fix continentMap naming convention, breaking covidgraph.cpp into sub files
    2021-12–01: fixed bug in covidgraph constructor, all nodes now guaranteed  to be connected as a single component
    2021-11–30: Implemented partial BFS (bugs needed to be fixed)
    2021-11–29: update on Getter function & revision on hierarchy of classes
    2021-11–28: destructor complete
    2021-11–28: modified dataset
    2021-11–27: updated _initConnections to allow more than four neighbors
    2021-11–25: Node Initialization Complete
    2021-11–25: Distance function added
    2021-11–19: updated Makefile
    2021-11–19: Node neighboring logic works in a simple version
    2021-11–18: Covid graph constructor half done
    2021-11–18: created makefile
    2021-11–18: fixed some bugs and built info map
    2021-11–17: add a bunch of starter code for Covid Graph
    2021-11–16: final project proposal modified 
    2021-11–07: updated format for proposal and contract
    2021-11–06: created proposal for final project
    2021-11–06: modified README.md
    2021-11–06: Zixuan Liu Signed
    2021-11–06: Zirui Wang Signed
    2021-11–06: zhiheng Signed
    2021-11–06: created Contract.md

