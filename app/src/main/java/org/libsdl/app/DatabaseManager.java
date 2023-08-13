package org.libsdl.app;

public class DatabaseManager {
    static {
        System.loadLibrary("main");
    }

    public native void getData(DatabaseUsers[] users);
}
