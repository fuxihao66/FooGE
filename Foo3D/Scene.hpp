#include <vector>


namespace FooGE{
    class Scene{
    public:
        void Update();
        void AddActor(const Actor& obj);
    private:
        std::vector<std::pair<RenderTechnique const *, std::vector<Actor*>>> renderQueue;       
         // rendertechnique:  numpass transparent ...
    };
}
