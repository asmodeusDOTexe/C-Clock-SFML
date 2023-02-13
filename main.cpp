#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include"SFMLWorldTime.h"
#include<math.h>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(900, 900), L"Часы", Style::Default);
   /* Image icon;
  if (!icon.loadFromFile("Image/clock.png"))
    {
        return 3;
    }
    window.setIcon(128, 128, icon.getPixelsPtr());*/
   
    SFMLWorldTime etm(50, 50, 4, Color::White);
       
    CircleShape circleTime(300.f);
    circleTime.setOrigin(150,150);
    circleTime.setPosition(303, 303);
    circleTime.setFillColor(Color::Black);
    circleTime.setOutlineThickness(10);
    circleTime.setOutlineColor(Color::White);

    //Рисочки
    CircleShape PointMin;                    
    PointMin.setFillColor(Color::White);    //цвет
    float radiusNum = 280; //радиус расположения
    float radiusPoint;     //радиус рисочек 
    //координаты центра круга
    float CenterClockX = 450;  
    float CenterClockY = 450;
    //координаты рисочек
    float xPoint, yPoint;

    // Оцифровка циферблата
    Font fontTime;
    if (!fontTime.loadFromFile("lib/dockerthree.ttf")) return 777;
    Text TimeText;
    TimeText.setFont(fontTime);
    TimeText.setCharacterSize(30);
    TimeText.setFillColor(Color::White);
    float numx, numy;
    
    //стрелки
    RectangleShape secArrow(Vector2f(2,280));                //Сек
    InitRect(secArrow, 453, 453, 1, 280, Color::Red);
    RectangleShape minArrow(Vector2f(8, 260));               //Мин
    InitRect(minArrow, 455, 455, 4, 260, Color::White);
    RectangleShape hourArrow(Vector2f(12, 180));             //Час
    InitRect(hourArrow, 455, 455, 6, 180, Color::White);
        
   while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
    
        window.clear(Color::Black);
        window.draw(circleTime);  //Круг 
        etm.drawTime(window);     //Электронные

        //Рисочки 
        for (int a=0;a<60;a++)  {
        if (a % 5 == 0)  radiusPoint = 8; else  radiusPoint = 4;
        xPoint = CenterClockX + radiusNum * cos(-6*a*(M_PI/180)+ M_PI/2);
        yPoint = CenterClockY - radiusNum * sin(-6*a*(M_PI/180) + M_PI/2);
        PointMin.setRadius(radiusPoint);
        PointMin.setOrigin(radiusPoint/2, radiusPoint/2);
        PointMin.setPosition(xPoint, yPoint);
        window.draw(PointMin);}

        //Оцифровка циферблата
        for (int i = 1; i <= 12; i++)
        {
            numx = CenterClockX + (radiusNum - 30) * cos(-30 * i * (M_PI/ 180) + M_PI/ 2);
            numy = CenterClockX - (radiusNum - 30) * sin(-30 * i * (M_PI/ 180) + M_PI/ 2);

            if (i <= 5) TimeText.setPosition(numx - 10, numy - 17);
            else  TimeText.setPosition(numx - 8, numy - 15);
        TimeText.setString(to_string(i));
        window.draw(TimeText);

        }

      secArrow.setRotation(6* etm.getsec());  //Вращение сек 
      minArrow.setRotation(6 * etm.getmin()+ etm.getsec()*0.1); //Вращение мин
      hourArrow.setRotation(30 * etm.gethour()+ etm.getmin()*0.5); //Вращение час
      window.draw(hourArrow); // час
      window.draw(minArrow);  // мин
      window.draw(secArrow);  // сек
      window.display();
    }

    return 0;
}