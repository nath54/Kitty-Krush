//
#include <vector>
#include <string>
#include <map>
//
#include "color.hpp"
#include "window_elt_style.hpp"
#include "window_attributes.hpp"


//
class Value{

    public:

        //
        int value;

        //
        Value(int value): value(value) {}

        //
        int get_value(){
            //
            return this->value;
        }

};



//
class ValuePercentWinWidth: public Value{

    public:

        //
        float percent;

        //
        WindowAttributes* win_attr;

        //
        ValuePercentWinWidth(float percent, WindowAttributes* win_attr): Value(0), percent(percent) {}

        //
        int get_value(){
            //
            return (int)(this->percent * 100.0 / this->win_attr->win_width);
        }

};



//
class ValuePercentWinHeight: public Value{

    public:

        //
        float percent;

        //
        WindowAttributes* win_attr;

        //
        ValuePercentWinHeight(float percent, WindowAttributes* win_attr): Value(0), percent(percent) {}

        //
        int get_value(){
            //
            return (int)(this->percent * 100.0 / this->win_attr->win_height);
        }

};


//
class WindowElt{

    public:

        //
        Value x;
        Value y;
        Value w;
        Value h;

        //
        Style* style;

        //
        WindowElt(Style* style, Value x, Value y, Value w = Value(1), Value h = Value(1))
            : style(style), x(x), y(y), w(w), h(h) {};

        //
        void draw_elt(WindowAttributes* win_attr);

};


//
class WindowEltText : public WindowElt {

    public:

        //
        std::string txt;

        //
        WindowEltText(Style* style, std::string txt, Value x, Value y, Value w = Value(-1), Value h = Value(-1))
            : WindowElt(style, x, y, w, h), txt(txt) {};

};


//
class WindowEltButton : public WindowElt {

    public:

        //
        std::string txt;
        //
        Color color;
        //
        int fontSize;

        //
        WindowEltButton(Style* style, std::string txt, Value x, Value y, Value w, Value h)
        : WindowElt(style, x, y, w, h), txt(txt) {};

};




//
class WindowPage{

    public:

        //
        std::vector<WindowElt> elts;


        // Constructeur par défaut
        WindowPage() = default;

        //
        WindowPage( std::vector<WindowElt> elts )
            : elts(elts) {}

        //
        void draw_page(WindowAttributes* win_attr);

};




//
class WindowPagesManager{

    public:

        //
        std::map<std::string, WindowPage> pages;
        std::string current_page;

        //
        WindowPagesManager( std::map<std::string, WindowPage> pages, std::string current_page )
            : pages(pages), current_page(current_page) {}

        //
        void draw_current_page( WindowAttributes* win_attr );

        //
        void set_current_page( std::string new_current_page );

};



