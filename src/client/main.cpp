#include <iostream>
#include <cstring>
#include <state.h>
#include "render.h"
#include "../shared/engine.h"
#include "../shared/ai.h"

#include <unistd.h>
#include <chrono>

using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace ai;
using namespace std::chrono;

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

int main(int argc,char* argv[])
{
    // Exemple exemple;
    // exemple.setX(53);

    if (argc>1){

        if( std::strcmp( argv[1], "hello") == 0 ){
            cout << "Bonjour le monde!" << endl;
        }


//=====================================================================================================
//
//                                              RENDER TEST
//
//=====================================================================================================

        // else if(strcmp(argv[1],"render") == 0){
        //     cout<<"Turn Display Test"<<endl<<endl;
        //     cout<<"Controls:"<<endl;
        //     cout << "-Press Up, Down, Right or Left key to move around the map " << endl;
        //     cout << "-Press R key to rotate map anti-clockwise " << endl;
        //     cout << "-Press T key to rotate map clockwise " << endl<< endl;
        //     // === Init turn ===
        //     Turn testTurn;
        //     testTurn.initMap(10,10); //squares only
        //     testTurn.initTeams();
        //     testTurn.getTeams()[0]->addCharacter();
        //     testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().setPos(2,5);
        //     testTurn.getTeams()[0]->addCharacter();
        //     testTurn.getTeams()[0]->getListCharacter()[1]->getPosition().setPos(2,8);
        //     // === Display Turn ===
        //     TurnDisplay layer(testTurn);
        //
        //     // cout << "check map : " << testTurn.getMap().size() << endl;
        //     // cout << "check map : " << testTurn.getMap()[0].size() << endl;
        //     // int screensizeWidth=testTurn.getMap().size()*layer.getTilesets()[0]->getYsize();
        //     // int screensizeHeight=testTurn.getMap()[0].size()*layer.getTilesets()[0]->getYsize();
        //     sf::RenderWindow window(sf::VideoMode(  800,
        //                                             (600)),
        //                                             "Render");
        //     sf::View view1(sf::Vector2f(350, 300), sf::Vector2f(400, 300));
        //     sf::View view2(sf::Vector2f(400, 300), sf::Vector2f(800, 600));
        //     view1.zoom(3.f);
        //     window.setView(view1);
        //     cout << "Render begin." << endl;
        //     layer.initRender();
        //     cout << "Render done." << endl;
        //
        //     sf::Text message;
        //     sf::Font font;
        //     font.loadFromFile("res/COURG___.TTF");
        //     message.setFont(font);
        //     message.setColor(sf::Color::White);
        //     message.setStyle(sf::Text::Bold);
        //     message.setCharacterSize(25);
        //     message.setString("PAUSED\n\n Controls: \n -Press Up, Down, Right or Left key \n to move around the map \n -Press R key to rotate map anti-clockwise \n -Press T key to rotate map clockwise");
        //
        //     int k=0;
        //     milliseconds last_ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
        //     last_ms+=(milliseconds) 60;
        //     window.setFramerateLimit(60);
        //     bool resume=true;
        //     while (window.isOpen()){
        //         sf::Event event;
        //         while (window.pollEvent(event)){
        //             if (event.type == sf::Event::Closed){
        //                 window.close();
        //             }
        //             if (event.type == sf::Event::LostFocus){
        //                 resume=false;
        //                 window.setView(view2);
        //                 window.draw(message);
        //                 window.display();
        //             }
        //             if (event.type == sf::Event::GainedFocus){
        //                 window.setView(view1);
        //                 resume=true;
        //             }
        //         }
        //         if((duration_cast< milliseconds >(system_clock::now().time_since_epoch())) >= (last_ms) && resume){
        //             window.clear();
        //             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        //                 view1.move(40, 40);
        //                 window.setView(view1);
        //
        //             }
        //             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        //                 view1.move(-40, -40);
        //                 window.setView(view1);
        //
        //             }
        //             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        //                 view1.move(-40, +40);
        //                 window.setView(view1);
        //
        //             }
        //             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        //                 view1.move(+40, -40);
        //                 window.setView(view1);
        //
        //             }
        //             if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        //                 // right key is pressed: rotate map
        //                 testTurn.rotation=(testTurn.rotation+1)%4;
        //                 layer.initRender(testTurn,fullRender);
        //                 // cout << "check map tile 0,0: " << testTurn.getMap()[0][0].getTile() << endl;
        //                 // cout << "check map tile 0,1: " << testTurn.getMap()[0][1].getTile() << endl;
        //                 // cout << "check map tile 1,0: " << testTurn.getMap()[1][0].getTile() << endl;
        //             }
        //             if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
        //                 // left key is pressed: rotate map to other side
        //                 testTurn.rotation=(testTurn.rotation+3)%4;
        //                 layer.initRender(testTurn,fullRender);
        //                 // cout << "check map tile 0,0: " << testTurn.getMap()[0][0].getTile() << endl;
        //                 // cout << "check map tile 0,1: " << testTurn.getMap()[0][1].getTile() << endl;
        //                 // cout << "check map tile 1,0: " << testTurn.getMap()[1][0].getTile() << endl;
        //             }
        //             if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        //                 Attack testattack(*testTurn.getTeams()[0]->getListCharacter()[0],*testTurn.getTeams()[0]->getListCharacter()[1]);
        //                 testattack.action(testTurn);
        //             }
        //             if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
        //                 // press `M` to move char 0 to 2,2
        //                 Position dest;
        //                 dest.setPos(2,2);
        //                 Move testmove(*testTurn.getTeams()[0]->getListCharacter()[0],dest);
        //                 if(testmove.action(testTurn)){
        //                 testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().setPos(2,2);
        //                 }
        //                 layer.initRender();
        //             }
        //             // Draw map(roofs and walls)
        //             layer.display(window,k);
        //
        //
        //                 k=(k+1)%6;
        //                 last_ms=duration_cast< milliseconds >(system_clock::now().time_since_epoch()) + (milliseconds) 60;
        // 
        //
        //             window.display();
        //         }
        //     }
        // }

//=====================================================================================================
//
//                                              ENGINE TEST
//
//=====================================================================================================
        else if(strcmp(argv[1],"engine") == 0){
            cout<<"Engine Test"<<endl<<endl;
            cout<<"Controls:"<<endl;
            cout << "-Press E key to launch 1 turn of Engine Simulation Scenario" << endl << "   Simulation contains 6 turns" << endl;
            cout << "-Press P key to Pause" << endl;
            cout << "-Press Up, Down, Right or Left key to move around the map " << endl;
            cout << "-Press R key to rotate map anti-clockwise " << endl;
            cout << "-Press T key to rotate map clockwise " << endl<< endl;
            // === Init Turn ===
            Turn testTurn;
            testTurn.initMap(8,8,"g1d2g2g1g1g1g3g1g1g1d3g1g1g2g2g1g1s1s1s2s2g1d1g1g2g1g1g1g1g1g2g2g1g1p1g1w1g2g3g2g2g3g1g1w1g3g1g1g1w1w1w1g1s1g1g1p1g1g1g1r1g1g1g1"); //squares only
            testTurn.initTeams();
            testTurn.getTeams()[0]->addCharacter();
            testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().setPos(3,2);

            testTurn.initTeams();
            testTurn.getTeams()[1]->addCharacter();
            testTurn.getTeams()[1]->getListCharacter()[0]->getPosition().setPos(3,1);
            testTurn.getTeams()[1]->addCharacter();
            testTurn.getTeams()[1]->getListCharacter()[1]->getPosition().setPos(4,5);
            testTurn.getTeams()[1]->addCharacter();
            testTurn.getTeams()[1]->getListCharacter()[2]->getPosition().setPos(3,5);
            // === Init Engine ===
            Engine testEngine(testTurn);

            Item testItem("TestHeal",10,0,3) ;
            testEngine.getTurn().getTeams()[0]->addItem(testItem);
            // === Display Turn ===
            TurnDisplay layer(testTurn);

            TurnDisplay* ptr_layer=&layer;
			testEngine.getTurn().registerObserver(ptr_layer);

            sf::RenderWindow window(sf::VideoMode(  800,
                                                    (600)),
                                                    "Engine");
            sf::View view1(sf::Vector2f(350, 300), sf::Vector2f(400, 300));
            sf::View view2(sf::Vector2f(400, 300), sf::Vector2f(800, 600));
            view1.zoom(3.f);
            window.setView(view1);
            cout << "Render begin." << endl;
            layer.initRender();
            cout << "Render done." << endl;

            sf::Text message;
            sf::Font font;
            font.loadFromFile("res/COURG___.TTF");
            message.setFont(font);
            message.setColor(sf::Color::White);
            message.setStyle(sf::Text::Bold);
            message.setCharacterSize(25);
            message.setString("PAUSED\n\n Controls: \n -Press E key to launch 1 turn of \n   Engine Simulation Scenario \n -Press P key to Pause \n -Press Up, Down, Right or Left key \n   to move around the map \n -Press R key to rotate map anti-clockwise \n -Press T key to rotate map clockwise");

            int k=0, Epressed=0;
            milliseconds last_ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
            last_ms+=(milliseconds) 60;
            window.setFramerateLimit(60);
            bool resume=true;
            while (window.isOpen()){
                sf::Event event;
                while (window.pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        window.close();
                    }
                    if ( resume && ((event.type == sf::Event::LostFocus) || (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) ) ){
                        resume=false;
                        window.setView(view2);
                        window.draw(message);
                        window.display();
                        sf::Time t1 = sf::seconds(0.2f);
                        sf::sleep(t1);
                    }
                    if ( !resume && ((event.type == sf::Event::GainedFocus) || (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) ) ){
                        window.clear();
                        window.setView(view1);
                        resume=true;
                        sf::Time t1 = sf::seconds(0.2f);
                        sf::sleep(t1);
                    }
                }
                if((duration_cast< milliseconds >(system_clock::now().time_since_epoch())) >= (last_ms) && resume){


                    layer.display(window,k);

                    k=(k+1)%6;
                    last_ms=duration_cast< milliseconds >(system_clock::now().time_since_epoch()) + (milliseconds) 60;



                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                        view1.move(40, 40), window.setView(view1);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                        view1.move(-40, -40), window.setView(view1);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                        view1.move(-40, +40), window.setView(view1);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                        view1.move(+40, -40),window.setView(view1);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                        // right key is pressed: rotate map
                        testEngine.getTurn().rotation=(testTurn.rotation+1)%4;
                        layer.initRender(testEngine.getTurn(),fullRender);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
                        // left key is pressed: rotate map to other side
                        testEngine.getTurn().rotation=(testTurn.rotation+3)%4;
                        layer.initRender(testEngine.getTurn(),fullRender);
                    }

                    testEngine.turnCheckIn();
                    testEngine.updateDisplay(window);
                    //Commands
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                        // cout << "initial char pos is: " << testEngine.getTurn().getTeams()[0]->getListCharacter()[0]->getPosition().getX() << "|"<< testEngine.getTurn().getTeams()[0]->getListCharacter()[0]->getPosition().getY() << endl;
                        Epressed+=1;

                        if (Epressed==1){
                            Position dest;
                            dest.setPos(2,5);
                            cout << "[COMMAND]character blue at 2,2 attempts to MOVE to 2,5, SHOULD SUCCEED" << endl;
                            Move movetest(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0], dest);
                            if(movetest.validate(testEngine.getTurn())){
                                unique_ptr<Command> ptr_movetest (new Move (movetest));
                                testEngine.addCommand(move(ptr_movetest));
                                cout << "->[SUCCESS]move instruction added " << endl;
                            }
                            else cout << "->[FAILED]no move instruction added" << endl;
                        }

                        if (Epressed==2){
                            cout << "[COMMAND]character blue attempts to ATTACK during red team turn, SHOULD FAIL" << endl;
                            Attack attacktest(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],*testEngine.getTurn().getTeams()[1]->getListCharacter()[0]);
                            if(attacktest.validate(testEngine.getTurn())){
                                unique_ptr<Command> ptr_attacktest (new Attack (attacktest));
                                testEngine.addCommand(move(ptr_attacktest));
                                cout << "->[SUCCESS]attack instruction added " << endl;
                            }
                            else cout << "->[FAILED]no attack instruction added" << endl;



                            cout << "[COMMAND]character red at 3,1 attempts to ATTACK character blue, SHOULD FAIL" << endl;
                            Attack attacktest2(*testEngine.getTurn().getTeams()[1]->getListCharacter()[0],*testEngine.getTurn().getTeams()[0]->getListCharacter()[0]);
                            if(attacktest2.validate(testEngine.getTurn())){
                                unique_ptr<Command> ptr_attacktest2 (new Attack (attacktest2));
                                testEngine.addCommand(move(ptr_attacktest2));
                                cout << "->[SUCCESS]attack instruction added " << endl;
                            }
                            else cout << "->[FAILED]no attack instruction added" << endl;



                            cout << "[COMMAND]character red at 3,5 attempts to ATTACK character blue, SHOULD SUCCEED" << endl;
                            Attack attacktest3(*testEngine.getTurn().getTeams()[1]->getListCharacter()[2],*testEngine.getTurn().getTeams()[0]->getListCharacter()[0]);
                            if(attacktest3.validate(testEngine.getTurn())){
                                unique_ptr<Command> ptr_attacktest3 (new Attack (attacktest3));
                                testEngine.addCommand(move(ptr_attacktest3));
                                cout << "->[SUCCESS]attack instruction added " << endl;
                            }
                            else cout << "->[FAILED]no attack instruction added" << endl;

                            cout << "[COMMAND]red players skip the rest of the turn, SHOULD SUCCEED" << endl;
                            EndTurn endturntest(1);
                            if(endturntest.validate(testEngine.getTurn())){
                                unique_ptr<Command> ptr_endturntest (new EndTurn (endturntest));
                                testEngine.addCommand(move(ptr_endturntest));
                                cout << "->[SUCCESS]endturn instruction added " << endl;
                            }
                            else cout << "->[FAILED]no endturn instruction added" << endl;
                        }

                        if(Epressed==3){

                            cout << "[COMMAND]character blue attempts to DEFEND, SHOULD SUCCEED" << endl;
                            Defend deftest(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0]);
                            if(deftest.validate(testEngine.getTurn())){
                                unique_ptr<Command> ptr_deftest (new Defend (deftest));
                                testEngine.addCommand(move(ptr_deftest));
                                cout << "->[SUCCESS]defend instruction added " << endl;
                            }
                            else cout << "->[FAILED]no defend instruction added" << endl;

                        }

                        if(Epressed==4){

                            cout << "[COMMAND]character red at 3,5 attempts to ATTACK character blue which is defending, SHOULD SUCCEED" << endl;
                            Attack attacktest4(*testEngine.getTurn().getTeams()[1]->getListCharacter()[2],*testEngine.getTurn().getTeams()[0]->getListCharacter()[0]);
                            if(attacktest4.validate(testEngine.getTurn())){
                                unique_ptr<Command> ptr_attacktest4 (new Attack (attacktest4));
                                testEngine.addCommand(move(ptr_attacktest4));
                                cout << "->[SUCCESS]attack instruction added " << endl;
                            }
                            else cout << "->[FAILED]no attack instruction added" << endl;

                            cout << "[COMMAND]red players skip the rest of the turn, SHOULD SUCCEED" << endl;
                            EndTurn endturntest2(1);
                            if(endturntest2.validate(testEngine.getTurn())){
                                unique_ptr<Command> ptr_endturntest2 (new EndTurn (endturntest2));
                                testEngine.addCommand(move(ptr_endturntest2));
                                cout << "->[SUCCESS]endturn instruction added " << endl;
                            }
                            else cout << "->[FAILED]no endturn instruction added" << endl;
                        }

                        if(Epressed==5){

                            cout << "[COMMAND]character blue attempts to USE HEAL POTION, SHOULD SUCCEED" << endl;
                            UseObject testUseItem(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],0,0,*testEngine.getTurn().getTeams()[0]->getListCharacter()[0]);
                            if(testUseItem.validate(testEngine.getTurn())){
                                unique_ptr<Command> ptr_testUseItem (new UseObject (testUseItem));
                                testEngine.addCommand(move(ptr_testUseItem));
                                cout << "->[SUCCESS]objectuse instruction added " << endl;
                            }
                            else cout << "->[FAILED]no objectuse instruction added" << endl;
                        }

                        if(Epressed==6){
                          Skill fireStrike {};
                          fireStrike.skillName="fire strike";
                          fireStrike.setEffect(10,0);
                          fireStrike.setMpCost(5);
                          testEngine.getTurn().getTeams()[1]->getListCharacter()[2]->addSkill(fireStrike);

                            cout << "[COMMAND]character red at 3,1 attempts to USE a SKILL, SHOULD FAILED" << endl;
                            UseSkill testUseSkill(*testEngine.getTurn().getTeams()[1]->getListCharacter()[0],*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],0,0);
                            if(testUseSkill.validate(testEngine.getTurn())){
                              std::unique_ptr<UseSkill> ptr_testUseSkill (new UseSkill(testUseSkill));
                              testEngine.addCommand(move(ptr_testUseSkill));
                              cout << "->[SUCCESS]skilluse instruction added " << endl;
                            }
                            else cout << "->[FAILED]no skilluse instruction added" << endl;

                            cout << "[COMMAND]character red at 3,5 attempts to USE "<<testEngine.getTurn().getTeams()[1]->getListCharacter()[2]->getSkillList()[0]->skillName<<" SKILL, SHOULD SUCCESS" << endl;
                            UseSkill testUseSkill2(*testEngine.getTurn().getTeams()[1]->getListCharacter()[2],*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],0,0);
                            if(testUseSkill2.validate(testEngine.getTurn())){
                              std::unique_ptr<UseSkill> ptr_testUseSkill2 (new UseSkill(testUseSkill2));
                              testEngine.addCommand(move(ptr_testUseSkill2));
                              cout << "->[SUCCESS]skilluse instruction added " << endl;
                            }
                            else cout << "->[FAILED]no skilluse instruction added" << endl;


                            cout << "[COMMAND]red players skip the rest of the turn, SHOULD SUCCEED" << endl;
                            EndTurn endturntest3(1);
                            if(endturntest3.validate(testEngine.getTurn())){
                                unique_ptr<Command> ptr_endturntest3 (new EndTurn (endturntest3));
                                testEngine.addCommand(move(ptr_endturntest3));
                                cout << "->[SUCCESS]endturn instruction added " << endl;
                            }
                            else cout << "->[FAILED]no endturn instruction added" << endl;
                        }

                        sf::Time t1 = sf::seconds(0.1f);
                        sf::sleep(t1);
                    }

                }
            }
        }

//=====================================================================================================
//
//                                             RANDOM AI TEST
//
//=====================================================================================================

        else if(strcmp(argv[1],"random_ai") == 0){

            cout<<"Engine Test"<<endl<<endl;
            cout<<"Controls:"<<endl;
            cout << "-Press P key to Pause" << endl;
            cout << "-Press Up, Down, Right or Left key to move around the map " << endl;
            cout << "-Press R key to rotate map anti-clockwise " << endl;
            cout << "-Press T key to rotate map clockwise " << endl<< endl;

            // === Init Turn ===
            Turn testTurn;
            testTurn.initMap(8,8); //squares only
            testTurn.initTeams();
            testTurn.getTeams()[0]->addCharacter();
            testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().setPos(3,2);

            testTurn.initTeams();
            testTurn.getTeams()[1]->addCharacter();
            testTurn.getTeams()[1]->getListCharacter()[0]->getPosition().setPos(3,1);
            testTurn.getTeams()[1]->addCharacter();
            testTurn.getTeams()[1]->getListCharacter()[1]->getPosition().setPos(4,5);
            testTurn.getTeams()[1]->addCharacter();
            testTurn.getTeams()[1]->getListCharacter()[2]->getPosition().setPos(3,5);
            // === Init Engine ===
            Engine testEngine(testTurn);

            Item testItem("TestHeal",10,0,3) ;
            testEngine.getTurn().getTeams()[0]->addItem(testItem);
            // === Init AI ===
            RandomAI testAI(testEngine);
            // === Display Turn ===
            TurnDisplay layer(testTurn);

            TurnDisplay* ptr_layer=&layer;
			testEngine.getTurn().registerObserver(ptr_layer);

            sf::RenderWindow window(sf::VideoMode(  800,
                                                    (600)),
                                                    "Random AI");
            sf::View view1(sf::Vector2f(350, 300), sf::Vector2f(400, 300));
            sf::View view2(sf::Vector2f(400, 300), sf::Vector2f(800, 600));
            view1.zoom(3.f);
            window.setView(view1);
            cout << "Render begin." << endl;
            layer.initRender();
            cout << "Render done." << endl;

            sf::Text message;
            sf::Font font;
            font.loadFromFile("res/COURG___.TTF");
            message.setFont(font);
            message.setColor(sf::Color::White);
            message.setStyle(sf::Text::Bold);
            message.setCharacterSize(25);
            message.setString("PAUSED\n\n Controls: \n -Press P key to Pause \n -Press Up, Down, Right or Left key \n   to move around the map \n -Press R key to rotate map anti-clockwise \n -Press T key to rotate map clockwise");

            int k=0;
            milliseconds last_ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
            milliseconds last_time_ai_run = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
            last_ms+=(milliseconds) 60;
            // window.setFramerateLimit(60);
            bool resume=true, firstturn=true;
            while (window.isOpen()){
                sf::Event event;
                while (window.pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        window.close();
                    }
                    if ( resume && ((event.type == sf::Event::LostFocus) || (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) ) ){
                        resume=false;
                        window.setView(view2);
                        window.draw(message);
                        window.display();
                        sf::Time t1 = sf::seconds(0.2f);
                        sf::sleep(t1);
                    }
                    if ( !resume && ((event.type == sf::Event::GainedFocus) || (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) ) ){
                        window.clear();
                        window.setView(view1);
                        resume=true;
                        sf::Time t1 = sf::seconds(0.2f);
                        sf::sleep(t1);
                    }
                }
                if((duration_cast<milliseconds>(system_clock::now().time_since_epoch()))>=(last_ms)&&resume){


                    layer.display(window,k);

                    k=(k+1)%6;
                    last_ms=duration_cast< milliseconds >(system_clock::now().time_since_epoch()) + (milliseconds) 60;

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                        view1.move(40, 40), window.setView(view1);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                        view1.move(-40, -40), window.setView(view1);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                        view1.move(-40, +40), window.setView(view1);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                        view1.move(+40, -40),window.setView(view1);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                        // right key is pressed: rotate map
                        testEngine.getTurn().rotation=(testTurn.rotation+1)%4;
                        layer.initRender(testEngine.getTurn(),fullRender);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
                        // left key is pressed: rotate map to other side
                        testEngine.getTurn().rotation=(testTurn.rotation+3)%4;
                        layer.initRender(testEngine.getTurn(),fullRender);
                    }
                }
                    testEngine.turnCheckIn();
                    testEngine.updateDisplay(window);

                    if((duration_cast<milliseconds>(system_clock::now().time_since_epoch()))>=(last_time_ai_run)){    
                        testAI.runAI();
                        last_time_ai_run=duration_cast< milliseconds >(system_clock::now().time_since_epoch()) + (milliseconds) 1500;
                    }    
                    sf::Time t1 = sf::seconds(0.1f);
                    sf::sleep(t1);
                
            }

        }
        else{
            cout << "Type hello to get welcome message.\nType random_ai to get random AI test." << endl;
        }
    }
    else{
            cout << "Type hello to get welcome message.\nType random_ai to get random AI test." << endl;
        }
    return 0;
}
