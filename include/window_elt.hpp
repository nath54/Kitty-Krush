//
#include <vector>
#include <string>
#include <map>



//
class WindowElt{


    public:

        //
        void draw_elt();

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



