//
#include <vector>
#include <string>




//
class WindowElt{


    public:

        //
        void draw_elt();

}




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

}




//
class WindowPagesManager{

    public:

        //
        map<std::string, WindowPage> pages;

        //
        WindowPagesManager( map<std::string, WindowPage> pages )
            : pages(pages) {}

}



