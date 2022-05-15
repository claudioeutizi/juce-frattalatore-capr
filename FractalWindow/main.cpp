#include <SFML/Graphics.hpp>
#include "MainMenu.hpp"
#include "Fractal.h"
#include "threeValuesArray.h"
#include "changeParameters.h"
#include "osc/osc/OscOutboundPacketStream.h"
#include "osc/ip/UdpSocket.h"



#define ADDRESS "127.0.0.1"
#define PORT 9001

#define OUTPUT_BUFFER_SIZE 1024
using namespace sf;


//static variables
static int x_fp = 0;
static int y_fp = 0;
static double xPoint;
static double yPoint;

int main()
{
    //OSC
    UdpTransmitSocket transmitSocket(IpEndpointName(ADDRESS, PORT));
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);
    p << osc::BeginBundleImmediate
        << osc::BeginMessage("/test1")
        << true << 23 << (float)3.1415 << "hello" << osc::EndMessage
        << osc::BeginMessage("/test2")
        << true << 24 << (float)10.8 << "world" << osc::EndMessage
        << osc::EndBundle;
    transmitSocket.Send(p.Data(), p.Size());

    ExamplePacketListener listener;
    UdpListeningReceiveSocket s(
        IpEndpointName(IpEndpointName::ANY_ADDRESS, PORT),
        &listener);

    std::cout << "press ctrl-c to end\n";

    s.RunUntilSigInt();
    // Create the main window
    RenderWindow menu(VideoMode(800, 800), "Main Menu", Style::Default);
    MainMenu mainMenu(menu.getSize().x, menu.getSize().y);
    Image plotFrattale;
    Fractal mainFractal;
    double xNew;
    double yNew;
    static Event newEvent;
    threeValuesArray arrayOSC;
    Texture texture;
    Sprite sprite;
    changeParameters modifier;
    plotFrattale.create(mainFractal.getW(), mainFractal.getH());
    //set background
    RectangleShape background;
    background.setSize(Vector2f(800, 800));
    Texture Maintexture;
    Maintexture.loadFromFile("Images/Orange.png");
    background.setTexture(&Maintexture);


    while (menu.isOpen())
    {
        Event event;
        while (menu.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                menu.close();
                break;
            }


            else if (event.type == sf::Event::KeyReleased)
            {

                if (event.key.code == sf::Keyboard::Up)
                {

                    mainMenu.MoveUp();
                    break;
                }

                else if (event.key.code == sf::Keyboard::Down)
                {

                    mainMenu.MoveDown();
                    break;
                }

                else  if (event.key.code == sf::Keyboard::Enter)
                {

                  int scelta = mainMenu.getMainMenuPressed();

                  if (scelta == 0) {

                      RenderWindow MandelbrotWindow(VideoMode(600, 600), "Mandelbrot");
                      while (MandelbrotWindow.isOpen())
                      {
                          Event mandelbrotEvent;
                          while (MandelbrotWindow.pollEvent(mandelbrotEvent))
                          {
                              if (mandelbrotEvent.type == Event::Closed)
                              {
                                  MandelbrotWindow.close();
                              }
                              else if (mandelbrotEvent.type == Event::KeyPressed)
                              {
                                  if (mandelbrotEvent.key.code == Keyboard::Escape)
                                  {
                                      MandelbrotWindow.close();
                                  }
                              }
                          }

                              for (int y = 0; y < mainFractal.getH(); y++)
                              {
                                  for (int x = 0; x < mainFractal.getW(); x++)
                                  {
                                      double cr = mainFractal.getMinRe() + (static_cast<double>(mainFractal.getMaxRe()) - mainFractal.getMinRe()) * x / mainFractal.getW();
                                      double ci = mainFractal.getMinIm() + (static_cast<double>(mainFractal.getMaxIm()) - mainFractal.getMinIm()) * y / mainFractal.getH();
                                      int n = mainFractal.ricorsioniMandelbrot(cr, ci, mainFractal.getMaxIter());
                                      Color c = mainFractal.paint_fractal(n, mainFractal.getMaxIter());
                                      plotFrattale.setPixel(x, y, Color(c));
                                  }
                              }
                              texture.loadFromImage(plotFrattale);
                              sprite.setTexture(texture);
                              MandelbrotWindow.draw(sprite);
                              MandelbrotWindow.display();

                              if (mandelbrotEvent.key.code == Keyboard::Enter)
                              {
                                  const Vector2i mouse_pos = Mouse::getPosition(MandelbrotWindow);
                                  mainFractal.setXfp(mouse_pos.x);
                                  mainFractal.setYfp(mouse_pos.y);

                                  if (mainFractal.getXfp() > mainFractal.getW() || mainFractal.getYfp() > mainFractal.getH() || mainFractal.getXfp() < 0 || mainFractal.getYfp() < 0)
                                  {
                                      cout << "prendi un un punto appartenente alla window;";
                                  }
                                  else
                                  {
                                      cout << "le coordinate del punto scelto sono: " << "x :" << mainFractal.getXfp() << " y: " << mainFractal.getYfp() << endl;
                                      xNew = modifier.nuovaCoordinataX(mainFractal.getXfp());
                                      yNew = modifier.nuovaCoordinataY(mainFractal.getYfp());

                                      cout << " la nuova coordinata x e :" << xNew << endl;

                                      cout << " la nuova coordinata y e :" << yNew << endl;

                                      arrayOSC.calcoloMandelbrot(xNew, yNew, 5);
                                      break;
                                  }
                                  
                              }
                          
                      }

                  }
                  else if (scelta == 1) {

                      RenderWindow Julia1Window(VideoMode(600, 600), "Julia1");
                      while (Julia1Window.isOpen())
                      {
                          Event julia1Event;
                          while (Julia1Window
                              .pollEvent(julia1Event)) {
                              if (julia1Event.type == Event::Closed)
                              {
                                  Julia1Window.close();
                              }
                              if (julia1Event.type == Event::KeyPressed)
                              {
                                  if (julia1Event.key.code == Keyboard::Escape)
                                  {
                                      Julia1Window.close();
                                  }
                              }
                          }

                          for (int y = 0; y < mainFractal.getH(); y++)
                          {
                              for (int x = 0; x < mainFractal.getW(); x++)
                              {
                                  double cr = mainFractal.getMinRe() + (static_cast<double>(mainFractal.getMaxRe()) - mainFractal.getMinRe()) * x / mainFractal.getW();
                                  double ci = mainFractal.getMinIm() + (static_cast<double>(mainFractal.getMaxIm()) - mainFractal.getMinIm()) * y / mainFractal.getH();
                                  int n = mainFractal.ricorsioniJuliaSet1(cr, ci, mainFractal.getMaxIter());
                                  Color c = mainFractal.paint_fractal(n, mainFractal.getMaxIter());
                                  plotFrattale.setPixel(x, y, Color(c));
                              }
                          }
                          texture.loadFromImage(plotFrattale);
                          sprite.setTexture(texture);
                          Julia1Window.draw(sprite);
                          Julia1Window.display();
                          if (julia1Event.key.code == Keyboard::Enter)
                          {
                              const Vector2i mouse_pos = Mouse::getPosition(Julia1Window);
                              mainFractal.setXfp(mouse_pos.x);
                              mainFractal.setYfp(mouse_pos.y);

                              if (mainFractal.getXfp() > mainFractal.getW() || mainFractal.getYfp() > mainFractal.getH() || mainFractal.getXfp() < 0 || mainFractal.getYfp() < 0)
                              {
                                  cout << "prendi un un punto appartenente alla window;";
                              }
                              else
                              {
                                  cout << "le coordinate del punto scelto sono: " << "x :" << mainFractal.getXfp() << " y: " << mainFractal.getYfp() << endl;
                                  xNew = modifier.nuovaCoordinataX(mainFractal.getXfp());
                                  yNew = modifier.nuovaCoordinataY(mainFractal.getYfp());

                                  cout << " la nuova coordinata x e :" << xNew << endl;

                                  cout << " la nuova coordinata y e :" << yNew << endl;

                                  arrayOSC.calcoloJuliaSet1(xNew, yNew, 5);
                                  break;
                              }

                          }
                      }
                  }
                  else if (scelta == 2)
                  {

                      RenderWindow Julia2Window(VideoMode(600, 600), "Julia2");
                      while (Julia2Window.isOpen())
                      {
                          Event julia2Event;
                          while (Julia2Window
                              .pollEvent(julia2Event)) {
                              if (julia2Event.type == Event::Closed) {
                                  Julia2Window.close();
                              }
                              if (julia2Event.type == Event::KeyPressed) {
                                  if (julia2Event.key.code == Keyboard::Escape) {
                                      Julia2Window.close();
                                  }
                              }
                          }

                          for (int y = 0; y < mainFractal.getH(); y++)
                          {
                              for (int x = 0; x < mainFractal.getW(); x++)
                              {
                                  double cr = mainFractal.getMinRe() + (static_cast<double>(mainFractal.getMaxRe()) - mainFractal.getMinRe()) * x / mainFractal.getW();
                                  double ci = mainFractal.getMinIm() + (static_cast<double>(mainFractal.getMaxIm()) - mainFractal.getMinIm()) * y / mainFractal.getH();
                                  int n = mainFractal.ricorsioniJuliaSet2(cr, ci, mainFractal.getMaxIter());
                                  Color c = mainFractal.paint_fractal(n, mainFractal.getMaxIter());
                                  plotFrattale.setPixel(x, y, Color(c));
                              }
                          }
                          texture.loadFromImage(plotFrattale);
                          sprite.setTexture(texture);
                          Julia2Window.draw(sprite);
                          Julia2Window.display();

                          if (julia2Event.key.code == Keyboard::Enter)
                          {
                              const Vector2i mouse_pos = Mouse::getPosition(Julia2Window);
                              mainFractal.setXfp(mouse_pos.x);
                              mainFractal.setYfp(mouse_pos.y);

                              if (mainFractal.getXfp() > mainFractal.getW() || mainFractal.getYfp() > mainFractal.getH() || mainFractal.getXfp() < 0 || mainFractal.getYfp() < 0)
                              {
                                  cout << "prendi un un punto appartenente alla window;";
                              }
                              else
                              {
                                  cout << "le coordinate del punto scelto sono: " << "x :" << mainFractal.getXfp() << " y: " << mainFractal.getYfp() << endl;
                                  xNew = modifier.nuovaCoordinataX(mainFractal.getXfp());
                                  yNew = modifier.nuovaCoordinataY(mainFractal.getYfp());

                                  cout << " la nuova coordinata x e :" << xNew << endl;

                                  cout << " la nuova coordinata y e :" << yNew << endl;

                                  arrayOSC.calcoloJuliaSet2(xNew, yNew, 5);
                                  break;
                              }
                              
                          }
                      }

                  } else 
                    {

                        RenderWindow BurningShipWindow(VideoMode(600, 600), "Burning ship");
                        while (BurningShipWindow.isOpen())
                        {
                            Event burningEvent;
                            while (BurningShipWindow
                                .pollEvent(burningEvent))
                            {
                                if (burningEvent.type == Event::Closed)
                                {
                                    BurningShipWindow.close();
                                }
                                if (burningEvent.type == Event::KeyPressed)
                                {
                                    if (burningEvent.key.code == Keyboard::Escape)
                                    {
                                        BurningShipWindow.close();
                                    }
                                }
                            }


                            for (int y = 0; y < mainFractal.getH(); y++)
                            {
                                for (int x = 0; x < mainFractal.getW(); x++)
                                {
                                    double cr = mainFractal.getMinRe() + (static_cast<double>(mainFractal.getMaxRe()) - mainFractal.getMinRe()) * x / mainFractal.getW();
                                    double ci = mainFractal.getMinIm() + (static_cast<double>(mainFractal.getMaxIm()) - mainFractal.getMinIm()) * y / mainFractal.getH();
                                    int n = mainFractal.ricorsioniBurning_ship(cr, ci, mainFractal.getMaxIter());
                                    Color c = mainFractal.paint_fractal(n, mainFractal.getMaxIter());
                                    plotFrattale.setPixel(x, y, Color(c));
                                }
                            }
                            texture.loadFromImage(plotFrattale);
                            sprite.setTexture(texture);
                            BurningShipWindow.draw(sprite);
                            BurningShipWindow.display();

                            if (burningEvent.key.code == Keyboard::Enter)
                            {
                                const Vector2i mouse_pos = Mouse::getPosition(BurningShipWindow);
                                mainFractal.setXfp(mouse_pos.x);
                                mainFractal.setYfp(mouse_pos.y);

                                if (mainFractal.getXfp() > mainFractal.getW() || mainFractal.getYfp() > mainFractal.getH() || mainFractal.getXfp() < 0 || mainFractal.getYfp() < 0)
                                {
                                    cout << "prendi un un punto appartenente alla window;";
                                }
                                else
                                {
                                    cout << "le coordinate del punto scelto sono: " << "x :" << mainFractal.getXfp() << " y: " << mainFractal.getYfp() << endl;
                                    xNew = modifier.nuovaCoordinataX(mainFractal.getXfp());
                                    yNew = modifier.nuovaCoordinataY(mainFractal.getYfp());
                                    
                                    cout << " la nuova coordinata x e :" << xNew << endl;
                                    
                                    cout << " la nuova coordinata y e :" << yNew << endl;

                                    arrayOSC.calcoloBurninhShip(xNew, yNew, 5);
                                     break;
                                }
                               
                            }
                           

                        }
                    
                   
                  }
                    

                }
            }
            
        }
        menu.clear();
        menu.draw(background);
        mainMenu.draw(menu);
        menu.display();
    }
    return 0;
}
