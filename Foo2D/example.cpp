#include "Button.hpp"
#include "Canvas.hpp"


using namespace FooGE::Foo2D;

class MyApp:public AppFramework{
public:
    MyApp(){

    }
    ~MyApp(){

    }

    virtual void onCreate(){   
        AppFramework::onCreate();// 创建窗体 等

        D2DEngine& d2dge = GetEngine();



        // ui 元素创建
        Animator2D buttonAnime;
        

    }


};

int main(){
    MyApp app();
    app.Run();

    return 0;
}