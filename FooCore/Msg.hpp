


namespace FooGE{
    enum MsgSource{
        MOUSE,
        KEYBOARD
    };
    enum MsgType{
        KEY_UP,
        KEY_DOWN,
        MOUSE_UP,
        MOUSE_DOWN,
        MOUSE_WHEEL
    };

    enum MsgPara{
        LEFT,
        RIGHT,
        MIDDLE
    };
    struct Msg{
        UINT Type;
        UINT Para;
        UINT Source;
        Msg(UINT s, UINT t, UINT k){
            Source = s;
            Type = t;
            Key = k;
        }
        
    };
}