# wordnet-sematics
wordnet semantics is a project based on finding the shortest common ancestor in a directed graphs 
it takes two input files. 
first :- synsets file which contains the nouns in each synsets,may noun be found in several synsets.


second :- hypernyms file which contains the relations between these synsets "each line has at the firstsynset number and it's parents next to it".

-i had used trie data structure to store  each noun and it's  corresponding  synsets numbers. 

-i had used bfs to find the shortest commen ancestor and distance between two synsets numbers. 

-to find  the shortest commen ancestor and distance between two nouns ,by searching the trie and have the synsets numbers for each noun
,and make pairs of each synsets numbers and find the shortest distance between them to be the output  
