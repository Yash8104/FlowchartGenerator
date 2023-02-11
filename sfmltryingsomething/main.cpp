#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <list>
#include "parser.hpp"
#include <string.h>
#include <fstream>
//#define n 7
#define distance 50
#define diamond_radius 80
#define circle_radius 80
#define length 220
#define breadth 100
using namespace std;







int main()
{
//     create the window
    Parser parser;
    parser.parse_statements();
    parser.print_structure();
    
    int n = parser.get_n();
//    cout << n << endl;
    string list_shapes[n];

    parser.to_array(list_shapes);
//    for(int i = 0 ; i < n ; i++){
//        cout << list_shapes[i] << "\n";
//    }
    
//    int n = 7;
//    string list_shapes[] = {"1nigger","2heeh","3hehe","2Declare x","2huhuhaha","3Print x","1Stop"};
    //                          1 for circle 3 for diamond 2 for rectangle
    sf::CircleShape list_circle[n];
    int circle_count = -1;
    sf::RectangleShape list_rect[n];
    int rectangle_count = -1;
    sf::CircleShape list_diamond[n];
    int diamond_count = -1;
    int last_x = 0;
    sf::Vector2f last_pos = sf::Vector2f(0,0);
    int last_object = 1;
    int i = -1 ,j = -1, k = -1;
    sf::Text list_text[n];
    int text_index = -1;
    
    int order[n];
    int order_count = -1;
    
    
    sf::RenderWindow window;
    window.create(sf::VideoMode(1500,1300),"My window");
//    1 = start 2 = normal 3 = if else 4 = stop

    
    
    sf::Font font;
    if (!font.loadFromFile("/Users/yashjain/Documents/coding/cpp/sfmltryingsomething/sfmltryingsomething/arial.ttf"))
    {
        // error...
        cout << "error\n";
        return 1;
    }

    
    
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        
        window.clear(sf::Color::White);
        
        for(string type : list_shapes){
            
            int type_ = (int)type[0] - 48;
            type.erase(0,1);
            sf::Text text;
            text.setFont(font);
            text.setString(type);
            text.setFillColor(sf::Color::White);
            text.setCharacterSize(25);
            text_index++;
            list_text[text_index] = text;
//            cout << type_ << endl;
            if(type_ == 1){
                
                circle_count++;
                
                list_circle[circle_count].setRadius(circle_radius);
                if(last_pos == sf::Vector2f(0,0)){
                    list_circle[circle_count].setPosition(500+(length/2)-circle_radius, 10);
                    last_pos = list_circle[circle_count].getPosition();
                    
                }else{
                    
                    if(last_object == 1){
                        list_circle[circle_count].setPosition(last_pos.x+(length/2)-circle_radius, last_pos.y+circle_radius*2+distance);
                    }else if(last_object == 2){
                        list_circle[circle_count].setPosition(last_pos.x+(length/2)-circle_radius, last_pos.y+breadth+distance);
                    }else if(last_object == 3){
                        list_circle[circle_count].setPosition(last_pos.x+(length/2)-circle_radius, last_pos.y+diamond_radius*2+distance);
                    }
                    
                    
                    last_pos = list_circle[circle_count].getPosition();
                    
                }
                
                list_circle[circle_count].setFillColor(sf::Color::Black);
                
                order_count++;
                order[order_count] = 1;
                last_object = 1;
            }else if(type_ == 2){
                
                
                rectangle_count++;
                
                list_rect[rectangle_count].setSize(sf::Vector2f(length,breadth));
                if(last_pos == sf::Vector2f(0,0)){
                    list_rect[rectangle_count].setPosition(500, 10);
                    last_pos = list_rect[rectangle_count].getPosition();
                }else{
                    if(last_object == 1){
                        list_rect[rectangle_count].setPosition(last_pos.x - ((length/2)-circle_radius), last_pos.y+circle_radius*2+distance);
                        last_pos = list_rect[rectangle_count].getPosition();
                    }else if(last_object == 2){
                        list_rect[rectangle_count].setPosition(last_pos.x , last_pos.y+breadth+distance);
                        last_pos = list_rect[rectangle_count].getPosition();
                    }else if(last_object == 3){
                        if(last_x == 120){
                            list_rect[rectangle_count].setPosition(last_pos.x+300 , last_pos.y+(diamond_radius/2)-10);
                            last_x = 0;
                            list_rect[rectangle_count].setFillColor(sf::Color::Black);

                            order_count++;
                            order[order_count] = 2;
                            last_object = 3;
                            continue;
                        }else{
                            
                            list_rect[rectangle_count].setPosition(last_pos.x - ((length/2)-circle_radius), last_pos.y+diamond_radius*2+distance);
                            last_pos = list_rect[rectangle_count].getPosition();
                            
                            
                        }
                        
                    }
                    
                    
                }
                
                
                list_rect[rectangle_count].setFillColor(sf::Color::Black);

                order_count++;
                order[order_count] = 2;
                last_object = 2;
                
            }else if(type_ == 3){
//                diamond for if else shit
                diamond_count++;
                list_diamond[diamond_count].setRadius(diamond_radius);
                list_diamond[diamond_count].setPointCount(4);
                last_x = 120;
                if(last_pos == sf::Vector2f(0,0)){
                    list_diamond[diamond_count].setPosition(500,10);
                    last_pos = list_diamond[diamond_count].getPosition();
                }else{
                    if(last_object == 1){
                        list_diamond[diamond_count].setPosition(last_pos.x+(length/2)-circle_radius, last_pos.y+circle_radius*2+distance);
                    }else if(last_object == 2){
                        list_diamond[diamond_count].setPosition(last_pos.x+(length/2)-circle_radius, last_pos.y+breadth+distance);
                    }else if(last_object == 3){
                        list_diamond[diamond_count].setPosition(last_pos.x+(length/2)-circle_radius, last_pos.y+diamond_radius*2+distance);
                    }
                    
                    last_pos = list_diamond[diamond_count].getPosition();
                }
                
                list_diamond[diamond_count].setFillColor(sf::Color::Black);
                
                order_count++;
                order[order_count] = 3;
                last_object = 3;
            }
        
        }
        
        last_pos = list_circle[0].getPosition();
        last_object = 1;
        last_x = 0;
        text_index = -1;
        for(int z = 0 ; z <= order_count; z++){
      
            if(order[z] == 1){
                i++;
                window.draw(list_circle[i]);
                sf::Vertex line[2];
                if(last_object == 1){
//              circle to circle
//                    cout << "executed\n";
                    line[0].position = sf::Vector2f(last_pos.x+circle_radius,last_pos.y+100);
                    line[0].color  = sf::Color::Black;
//                    cout << line[0].position.x << "\t" << line[0].position.y << endl;
                    line[1].position = sf::Vector2f(list_circle[i].getPosition().x+circle_radius,list_circle[i].getPosition().y);
                    line[1].color = sf::Color::Black;
//                    cout << line[1].position.x << "\t" << line[1].position.y << endl;
                }else if(last_object == 2){
//                    rectangle to circle
                    line[0].position = sf::Vector2f(last_pos.x+length/2,last_pos.y+breadth);
                    line[0].color  = sf::Color::Black;
                    line[1].position = sf::Vector2f(list_circle[i].getPosition().x+circle_radius,list_circle[i].getPosition().y);
                    line[1].color = sf::Color::Black;
                }
                else if (last_object == 3){
//                    diamond to circle
                    
                    line[0].position = sf::Vector2f(last_pos.x+diamond_radius,last_pos.y+diamond_radius*2);
                    
//
                    line[0].color  = sf::Color::Black;
                    line[1].position = sf::Vector2f(list_circle[i].getPosition().x+circle_radius,list_circle[i].getPosition().y);
//
                    line[1].color = sf::Color::Black;
                }
                
                
                window.draw(line,2,sf::Lines);
                last_pos = list_circle[i].getPosition();
                last_object = 1;
                
                text_index++;
                list_text[text_index].setPosition(list_circle[i].getPosition().x+15, list_circle[i].getPosition().y+circle_radius/2);
                window.draw(list_text[text_index]);
                
            }else if (order[z] == 2){
//              rectangle
                j++;
                
                sf::Vertex line[2];
                if(last_object == 1){
//                    circle to rectangle
                    line[0].position = sf::Vector2f(last_pos.x+circle_radius,last_pos.y+100);
                    line[0].color  = sf::Color::Black;
                    line[1].position = sf::Vector2f(list_rect[j].getPosition().x+length/2,list_rect[j].getPosition().y);
                    line[1].color = sf::Color::Black;
                    last_pos = list_rect[j].getPosition();
                    last_object = 2;
                    
                }else if(last_object == 2){
//                    rectangle to rectangle
//                    cout << "executed\n";
                    line[0].position = sf::Vector2f(last_pos.x+length/2,last_pos.y+80);
//                    cout << line[0].position.x << "\t" << line[0].position.y << endl;
                    line[0].color  = sf::Color::Black;
                    line[1].position = sf::Vector2f(list_rect[j].getPosition().x+length/2,list_rect[j].getPosition().y);
//                    cout << line[1].position.x << "\t" << line[1].position.y << endl;
                    line[1].color = sf::Color::Black;
                    last_pos = list_rect[j].getPosition();
                    last_object = 2;
                }
                else if (last_object == 3){
//                    diamond to rectangle
                    if(last_x == 120){
                        
//                        list_rect[j].setPosition(list_rect[j].getPosition().x + 120, last_pos.y);
                        
                        line[0].position = sf::Vector2f(last_pos.x+diamond_radius+diamond_radius,last_pos.y+diamond_radius);
    //
                        line[0].color  = sf::Color::Black;
                        line[1].position = sf::Vector2f(list_rect[j].getPosition().x,list_rect[j].getPosition().y+breadth/2);
    //
                        line[1].color = sf::Color::Black;
                        
                        


                        last_x = 0;
                            
                    }else{
                    
                    line[0].position = sf::Vector2f(last_pos.x+diamond_radius,last_pos.y+diamond_radius*2);
//
                    line[0].color  = sf::Color::Black;
                    line[1].position = sf::Vector2f(list_rect[j].getPosition().x+length/2,list_rect[j].getPosition().y);
//
                    line[1].color = sf::Color::Black;
                    
                    last_pos = list_rect[j].getPosition();
                    last_object = 2;
                    
                    }
                    
                    
                }
                
                
                window.draw(list_rect[j]);
                window.draw(line,2,sf::Lines);
                
                text_index++;
                list_text[text_index].setPosition(list_rect[j].getPosition().x+15, list_rect[j].getPosition().y+(breadth/2)/2);
                window.draw(list_text[text_index]);
                
            }else if (order[z] == 3){
                
                k++;
                window.draw(list_diamond[k]);
                sf::Vertex line[2];
                last_x = 120;
                if(last_object == 1){
//                    circle to diamond
                    line[0].position = sf::Vector2f(last_pos.x+circle_radius,last_pos.y+100);
                    line[0].color  = sf::Color::Black;
                    line[1].position = sf::Vector2f(list_diamond[k].getPosition().x+diamond_radius,list_diamond[k].getPosition().y);
                    line[1].color = sf::Color::Black;
                }else if(last_object == 2){
//                    rectangle to diamond
//
                    line[0].position = sf::Vector2f(last_pos.x+length/2,last_pos.y+breadth/2);
//
                    line[0].color  = sf::Color::Black;
                    line[1].position = sf::Vector2f(list_diamond[k].getPosition().x+diamond_radius,list_diamond[k].getPosition().y);
//
                    line[1].color = sf::Color::Black;
                }else if (last_object == 3){
//                    diamond to diamond
                    
                    line[0].position = sf::Vector2f(last_pos.x+diamond_radius,last_pos.y+100);
//
                    line[0].color  = sf::Color::Black;
                    line[1].position = sf::Vector2f(list_diamond[k].getPosition().x+diamond_radius,list_diamond[k].getPosition().y);
//
                    line[1].color = sf::Color::Black;
                }
                
                
                window.draw(line,2,sf::Lines);
                last_pos = list_diamond[k].getPosition();
                last_object = 3;
                text_index++;
                list_text[text_index].setPosition(list_diamond[k].getPosition().x+20, list_diamond[k].getPosition().y+(diamond_radius)-20);
                window.draw(list_text[text_index]);
            }
            
        }
        
        window.display();
        circle_count = -1;
        i = -1;
        j = -1;
        k = -1;
        order_count = -1;
        rectangle_count = -1;
        diamond_count = -1;
        last_x = 0;
        text_index = -1;
        last_pos = sf::Vector2f(0,0);
        
        
        
    }

    return 0;
}



