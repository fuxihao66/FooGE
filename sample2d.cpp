#include "Foo2D/Canvas.hpp"
#include "FooCore/AppFramework.hpp"
#include "Foo2D/Button.hpp"
#include "Foo2D/Text.hpp"
#include "Foo2D/Canvas.hpp"
class MyApp : public FooGE::AppFramework {
    MyApp(){
        onCreate();
    }

    void onCreate(){

		FooGE::Foo2D::Canvas * mainCanvas = new FooGE::Foo2D::Canvas();
		FooGE::Foo2D::Button * btn1 = new FooGE::Foo2D::Button("Click Me");
        
		FooGE::Foo2D::Text * text1 = new FooGE::Foo2D::Text("before click");
        mainCanvas->AddWidget(btn1);
        btn1->addClickCallback([text1](){
            text1->setText("After click");
        });

        setEntryCanvas(mainCanvas);
    }
};

int main(){

    MyApp app;
    app.Run();

    return 0;
}