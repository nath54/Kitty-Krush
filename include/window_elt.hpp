//
#include <vector>
#include <string>
#include <map>
//
#include "color.hpp"



//
class WindowElt{

    public:

        int x;
        int y;
        int w = 1;
        int h = 1;

        //
        WindowElt(int x, int y, int w = 1, int h = 1)
            : x(x), y(y), w(w), h(h) {};

        //
        void draw_elt();

};


//
class WindowEltText : public WindowElt {

    public:

        //
        std::string txt;
        //
        Color color;
        //
        int fontSize;

        //
        WindowEltText(std::string txt, Color color, int fontSize, int x, int y, int w = 1, int h = 1)
        : WindowElt(x, y, w, h), txt(txt), color(color), fontSize(fontSize) {};

};




//
class WindowPage{

    public:

        //
        std::vector<WindowElt> elts;

        //
        WindowPage( std::vector<WindowElt> elts )
            : elts(elts) {}

        //
        void draw_page();

};




//
class WindowPagesManager{

    public:

        //
        std::map<std::string, WindowPage> pages;

        //
        WindowPagesManager( std::map<std::string, WindowPage> pages )
            : pages(pages) {}

};



