# wordnet-sematics

wordnet semantics is a project based on finding the shortest common ancestor in a directed graphs 
it takes two input files. 


First:- synsets file which contains the nouns in each synsets, noun may be found in several synsets.


Second:- hypernyms file which contains the relations between these synsets "each line has at the first synset number and it's parents next to it".

- Used Trie data structure to store each noun and it's corresponding synsets numbers. 

- Used BFS to find the shortest commen ancestor and distance between two synsets numbers. 

We find the shortest commen ancestor and distance between two nouns, by searching the trie and have the synsets numbers for each noun and make pairs of each synsets numbers. The output is the shortest distance between them.
