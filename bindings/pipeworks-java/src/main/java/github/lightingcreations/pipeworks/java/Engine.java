package github.lightingcreations.pipeworks.java;

public class Engine implements AutoCloseable {
    private final long ptr_mengine;

    private static native long engine_init0(Renderer r);
    private static native long engine_init1(NativeRenderer nr);

    public Engine(Renderer r){
        if(r instanceof NativeRenderer)
            ptr_mengine = engine_init1((NativeRenderer)r);
        else
            ptr_mengine = engine_init0(r);
    }

    @Override
    public void close() {
        close0();
    }

    private native void close0();


    static{
        registerNatives();
    }

    private static native void registerNatives();
}
