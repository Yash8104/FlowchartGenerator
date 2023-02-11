//
//  parser.cpp
//  flowchart_generator
//
//  Created by Yash Jain on 19/07/22.
//

#include "parser.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <sstream>




using namespace std;


list<string> Parser::get_content(){
    return content;
}

void Parser::parse_file(){
    string line;
    ifstream code("/Users/yashjain/Desktop/sample.cpp");
    while (getline(code,line)) {

        if ((!(line.empty())) && !(line[0] == '/') && !(line[0] == '#')) {
            content.push_back(line);

        }
    }
    
    code.close();
    
}




Parser::Parser(){
    cout << "Parser object created!\n";
    parse_file();
    string keywords[] = {"break","case","char","const","continue","default","do", "double","else","enum","float","for","goto","if","int","long","register","return","short","sizeof","static","static","struct","switch","typedef","union","void","while","cout","cin"};
    

    string types_of_code[] = {
    "declaration","operation","if-condition","switch-condition","output","input","ignore","for-loop","while-loop"
    };
    
    
    
    
    struct variable v1;
}

bool Parser::element_in_array(string elem,string data_types[]){
    

    for(int i = 0 ; i < 6;i++){
        if(data_types[i] == elem){
            return true;
        }
    }
    
    return false;
}

bool Parser::element_in_list(string elem,list<string> list){
    
    ::list<string>::iterator it;
    for (it = identifiers.begin(); it != identifiers.end(); it++) {

        if(elem == *it){
            return true;
        }
    }
    
    
    return false;
}

string Parser::parse_statement(string line){
//    parsers one line at a time
    
    istringstream ss(line);
    
    string word;
    
    while(ss >> word){
        
        if(word == "using"){
            return "ignore";
        }
        
        

         
        
        if(element_in_array(word, data_types)){
//            the word is a data type that means it is either being declared or initialized so we need to print either

            return "declaration";
        }else if(element_in_list(word, identifiers)){
            
            return "operation";
        }else if(word == "cin"){
            
            return "input";
        }else if (word == "cout"){
            
            return "output";
        }else if(word == "if" || word.find("if") != string::npos){
            
            if(context == "if" && lines_left_context != 0){
                lines_left_context--;
                return "ignore";
            }else{
                context = "";
            }
            
            
            return "if-condition";
        }
        
    }
    
    
    return "ignore";
}



void Parser::words_to_list(string line){
    
    istringstream ss(line);
    
    string word;
    
    while(ss >> word){
        words.push_back(word);
    }
    
}

void Parser::words_clear(){
    words.clear();
}

string Parser::determine_code(string type_of_code, string line){
    if(type_of_code == "declaration"){
//            declaration
        words_to_list(line);
        list<string>::iterator word_it;
        word_it = words.begin();

        v1.dataType = *word_it;

        word_it++;
        v1.identifier = *word_it;
        identifiers.push_back(v1.identifier);
        
        word_it++;
        while(word_it!= words.end()){
            v1.value = v1.value + " "  +*word_it;

            word_it++;
        }
        
        if(v1.value.empty()){
            v1.identifier.pop_back();
        }else{
            v1.value.pop_back();
        }
        identifiers.push_back(v1.identifier);
        


        string statement = "2Declare " + v1.dataType + " " + v1.identifier + " " + v1.value;
        v1.value = "";
        v1.dataType = "";
        v1.identifier = "";
        words.clear();
        return statement;
        
        

    }else if (type_of_code == "operation"){
//            x = 20;
//            operations
        words_to_list(line);
        list<string>::iterator word_it;
        word_it = words.begin();
        v1.identifier = *word_it;
        
        word_it++;
        while(word_it!= words.end()){
            v1.value = v1.value + " "  +*word_it;

            word_it++;
        }
        v1.value.pop_back();
        string statement = "2" + v1.identifier + v1.value;
        v1.value = "";
        v1.dataType = "";
        v1.identifier = "";
        words.clear();
        return statement;
        
    }else if (type_of_code == "input"){
//            input eg. cin >> x;
        words_to_list(line);
        words.reverse();
        v1.value = words.front();
        v1.value.pop_back();
        string statement = "2Read " + v1.value;
        v1.value = "";
        v1.dataType = "";
        v1.identifier = "";
        words.clear();
        return statement;

        
        
    }else if (type_of_code == "output"){
//            output eg. cout << "Something blah blah" << x;
        
        istringstream ss(line);
        string token;
        while(getline(ss, token, '<')){
            words.push_back(token);
        }
        
        list<string>::iterator word_it;
        words.pop_front();
        for(word_it = words.begin(); word_it != words.end(); word_it++){
            string word_ = *word_it;
            if(!word_.empty() && word_.length() >= 1){
                v1.value = v1.value + word_ + "+";
            }
        }
        
        v1.value.pop_back();
        v1.value.pop_back();
        string statement = "2Display" + v1.value;
        v1.value = "";
        v1.dataType = "";
        v1.identifier = "";
        words.clear();
        return statement;
    }else{
        return "";
    }
    
    
}

void Parser::parse_statements(){
    
    list<string>::iterator it;
    for(it = content.begin(); it != content.end(); it++){
        string line = *it;
        current_line++;
        string type_of_code = parse_statement(line);
        
        if(type_of_code == "if-condition"){
            string condition_context;
            int current_line_if = current_line;
            list<string>::iterator it_if;
            it_if = content.begin();
            advance(it_if, current_line_if-1);
            lines_left_context = 0;
            for(;it_if != content.end();it_if++){
                lines_left_context++;
                string line_if = *it_if;
                
                words_to_list(line_if);
                list<string>::iterator word_it;
                word_it = words.begin();
                
                if (line_if.find("if") != string::npos) {
//                    if code
                    context = "if";
                    condition_context = "if";
                    word_it++;
                    string condition = "";
                    while (word_it != words.end()) {
                        condition = condition + " " + *word_it;
                        word_it++;
                    }
                    condition.erase(1,1);
                    condition.pop_back();
                    string statement = "3if " + condition;
                    structure_of_flowchart.push_back(statement);
                    words.clear();
                    
                    
                }else if(line_if.find("if") != string::npos && line_if.find("else") != string::npos){
//                    else if
                    
                }else if(line_if.find("else") != string::npos){
//                    else
                    
                    condition_context = "else";
                    
                    
                    
                }else{
                    
//                    {
                    if(line_if == "{"){
                        words.clear();
                        current_line_if++;
                        continue;
                    }
                    
                    if(line_if == "}"){
                        words.clear();
                        break;
                    }
                    
//                  operations
                    
                    string type_of_code_1 = parse_statement(line_if);
//                    cout << type_of_code_1 << endl;
                    words.clear();
                    string result = determine_code(type_of_code_1, line_if);
                    if (condition_context == "else") {
                        string statement = result;
                        if(!statement.empty()){
                            structure_of_flowchart.push_back(statement);
                        }
                    }else{
                        string statement =  result;
                        if(!statement.empty()){
                            structure_of_flowchart.push_back(statement);
                        }
                    }
                    
                    
                    
                    
                }
                
                words.clear();
                current_line_if++;
            }
            
//            cout << *it_if << "THIS IS THE IF CONDITION SHIT!"<< endl;
            
            advance(it, lines_left_context-1);
        }else{
            string statement = determine_code(type_of_code, line);
            if(!statement.empty()){
                structure_of_flowchart.push_back(statement);
            }
            
            statement = "";
            words.clear();
        }
    }
    
}



Flowchart::Flowchart(){
//    Parser();
    cout << "Flowchart object created!\n";
    structure_of_flowchart.push_back("1Start");
//    cout << structure_of_flowchart.front() << endl;
}

void Flowchart::print_structure(){
    list<string>::iterator it;
    for(it = structure_of_flowchart.begin(); it != structure_of_flowchart.end(); it++){
        string line = *it;
        cout << line << endl;
    }
    
}

void Flowchart::to_array(string arr[]){
    
    list<string>::iterator it;
    int i = 0;
    for(it = structure_of_flowchart.begin(); it != structure_of_flowchart.end(); it++){
        string line = *it;
        arr[i] = line;
        i++;
    }
    arr[i] = "1Stop";
    
    
    
}

int Flowchart::get_n(){
    return (int)structure_of_flowchart.size()+1;
}
