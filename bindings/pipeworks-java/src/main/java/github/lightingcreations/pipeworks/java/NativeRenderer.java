package github.lightingcreations.pipeworks.java;

public class NativeRenderer implements Renderer {
    @SuppressWarnings("FieldCanBeLocal") // No, no it can't IntelliJ
    private long field;

    @Override
    public void close() {
        close0();
    }

    NativeRenderer(long field) {
        this.field = field;
    }

    private native void close0();

    static{
        registerNatives();
    }

    private static native void registerNatives();
}
