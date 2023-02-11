//
//  parser.hpp
//  flowchart_generator
//
//  Created by Yash Jain on 19/07/22.
//

#ifndef parser_hpp
#define parser_hpp


#endif /* parser_hpp */

#include <stdio.h>
#include <string>

#include <iostream>
#include <fstream>
#include <list>
using namespace std;

class Flowchart{
protected:
    list<string> structure_of_flowchart;
public:
    
    Flowchart();
    void print_structure();
    void to_array(string arr[]);
    int get_n();
    
};


class Parser: public Flowchart{
private:
    list<string> content;
    list<string> words;
    string types_of_code[100];
    string context;
    int lines_left_context;
    list<string> identifiers;
    int current_line = 0;
    int counter = -1;
    
public:
    Parser();
    string data_types[6] = {
        "int","float","double","string","char","bool"
    };
    void words_to_list(string line);
    void words_clear();
    string keywords[100];
    void parse_statements();
    string determine_code(string type_of_code , string line);
    string parse_statement(string line);
    
    list<string> get_content();
    
    void parse_file();
    
    struct variable{
        string dataType;
        string identifier;
        string value;
    } v1;
    
    bool element_in_array(string elem,string data_types[]);
    bool element_in_list(string elem,list<string> list);
    
};

