#include "../include/drawGame.h"
void drawGameworld(std::vector<std::vector<tile*> > &_map, std::vector<actor*> &actors,std::vector<item*> localItems, sf::RenderWindow & window, announcements & announcementList)
{
    sf::RectangleShape announcementBorder;

    announcementBorder.setFillColor(sf::Color::Black);
    announcementBorder.setOutlineThickness(3);
    announcementBorder.setOutlineColor(sf::Color::White);
    announcementBorder.setPosition(window.getSize().x*.60,window.getSize().y*.25);
    announcementBorder.setSize(sf::Vector2f(window.getSize().x*.40,window.getSize().y*.75));

    int colortypeCounter=1;

    coordinate startingposition;
    coordinate charplaced;
short foregroundValue;
short backgroundValue;
    int colorToUse=1;

    //startingposition=coordinate((actors[0])->col(),(actors[0])->row());
    startingposition = coordinate(0,0);


    bool drawActor=false;
    bool drawItem=false;
    actor* actorToDraw;
    item* itemToDraw;

    window.clear();

    window.draw(announcementBorder);

    //do_fov(_map,actors[0]->col(),actors[0]->row(),15,window);
    //do_fov(_map,5,5,5,window);

    for (int y=0;y<25;y++)
    {
        for (int x=0;x<25;x++)
        {
            if (x+charplaced.x >=0 and y+charplaced.y >=0 and x+charplaced.x<_map[0].size() and y+charplaced.y<_map.size()){
                for (item* _i : localItems){
                    window.draw(_i->sprite);
                }
                for (actor* _a: actors)
                {
                    window.draw(_a->sprite);
                }
                _map[y][x]->drawTile(window);
            }
        }
    }
    announcementList.drawAnnouncements(window);
    window.display();
}

void announcements::drawAnnouncements(sf::RenderWindow & window)
{
    sf::Font font;
    font.loadFromFile("data/PressStart2P-Regular.ttf");
    sf::Text menuText;
    menuText.setCharacterSize(8);
    menuText.setFont(font);

    int x = window.getSize().x*.60+6,y = window.getSize().y - 15;
    for (std::string _s : announcementList){
        menuText.setString(_s);
        menuText.setPosition(x,y);
        window.draw(menuText);
        y-=15;
    }
}
