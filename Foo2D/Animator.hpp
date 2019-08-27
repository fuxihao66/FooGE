namespace FooGE{
    namespace Foo2D{
        class Animator2D{
        public:
            void AddAnimation(std::string name, const Animation& seq);
        private:
            std::map<std::string, Animation> animationMap;
        };
    }
}