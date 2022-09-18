# CS 225 Final Project Proposal
**Team Proposal (ziruiw3-weixuan6-hua13-zixuanl9)**


## Leading Question:
- The ultimate goal of this project is to provide an efficient search tool for a given global COVID-19 dataset. The result will then be used for data visualization. Here are some example concrete problems we want to solve  
  1. Over a specific time period, which country has the most death/confirmed/recovered rate, we will provide a ranking of those countries using vectors.  
  2. What about searching over continent/region (using latitude and longitude) for these information?
  3. Find the shorest path from one location to another, observe all regions death/confirmed/recovered rate on the path over a certain time period.
  4. Visualizing data by projecting the data onto a map, representing the data with descriptive color, also planning to make `.gif` to provide dynamic visualization.  
  5. Filter: this is a idea of providing different data visualization output by inputing the desired feature and output corresponding data, such as providing a image for all countries with same initial letter, and countries with similar COVID-19 status
- The mininum result is to implement the three algorithms describe below (and therefore enable traversing, path searching and data visualization on map). Extra work that can be done has been mentioned above

## Dataset Acquisition and Processing:  
- Datasets
  1. [COVID-19 2020 Jan-Mar Global](https://github.com/CSSEGISandData/COVID-19/tree/master/archived_data/archived_time_series)
  2. [World Countries' Info](https://www.kaggle.com/fernandol/countries-of-the-world)
    - Attributes to use: location, latitude, longitude, date, death/confirmed/recovered data, countries' area, coutries' region (will be converted to continents)
    - The datasets are all in `.csv` format, can be parsed using c++ fstream line by line, and we can easily extract actual data by get rid of commas
- Data Structure:  
  1. Graph
  2. Nodes: each node represent a specific country (or a state of a country), storing the COVID data in the entire time period (using vector, because finding a single date can be done by indexing)  
  3. Edges: weighted edges (by [Great-circle distance](https://en.wikipedia.org/wiki/Great-circle_distance), calculated using Haversine formula), edges will connect nearby regions only
- Implementation Details:
  - [World Countries' Info](https://www.kaggle.com/fernandol/countries-of-the-world) dataset will be first used to construct a (*string->collection*) map that maps country names to their information {areas, regions, ...}, so that we can put those information in the nodes later.
  - [COVID-19 2020 Jan-Mar Global](https://github.com/CSSEGISandData/COVID-19/tree/master/archived_data/archived_time_series) will then be used to create new nodes, the nodes (pointers) are then put in a vector (private field) of the CovidGraph class
  - Finding neighboring nodes and connect them: For simplicity, we are going to represent nodes as circles with different size. Size is determined by the countries/regions' area, which can be used to find the `radius`. If `dist(curr_node, check_node) <= (curr->radius + check_node->radius)`, then connect the two nodes. (one possible implementation is shown in the comment in `covidgraph.h`) Since our approximation is not a perfect model of the real shape, sometimes a node can find no neighbors when the "center" is too far away from one border than it should be, we then slowly increase the radius and check again to make sure that the node can find at least one neigbor, because we want our graph to be all connected.
  - If the "World Countries' Info" does not have the info we want for nodes, we would just provide the nodes with a default value, or check them beforehand and make some modifications to the dataset

## Graph Algorithms:    
- Traversal: BFS. Used for testing, traverse the entire graph from a random starting node, output the number of nodes in the graph (make sure that all nodes are connected)
- Use Shortest Path Algorithm (Dijkstra's algorithm) (Time Complexity: O(E logV), Space Complexity: O(V + E) to find shortest path between two location and observer the COVID data on the path, return a vector containing all nodes on the path  
- Graphic Output of Graph: Project onto map for data visualization. Following the leading question, this visualization will out put `.png` or `.gif` using the provided cs225 package. The specific output and running time depend on the function. For example, a COVID-19 global growth rate visualization will out put a `.gif` that draw nodes on a simplified world map PNG image, nodes will then be colored differently according to the growth rate, the size of the "node" will be determined by the area of the "node". In this case, the running time will be O(V + E)

## Timeline:
- Nov. 8th - Nov. 14th
  - Data parsing, construct classes, store the COVID-19 dataset into the graph
  - Regular testings
- Nov. 15th - Nov. 21th
  - Implement all get methods that will serve as helper functions (e.g. getDeaths()/getConfirmed())
  - Regular testings
- Nov. 22th - Nov. 28th
  - Complete remaining get functions.
  - Implement Dijkstra's algorithm
  - Regular testings
- Nov. 29th - Dec. 5th
  - Dec 1: mid-project presentation (meeting time TBD)
  - Implement project onto map data visualization (draw on PNG)
  - Utilize exisiting functions for customized searching (output on PNG)
  - Regular testings
- Dec. 6th - Nov. 12th
  - Finalizing the project, including testing and possibly implementations of other interesting functionalities
