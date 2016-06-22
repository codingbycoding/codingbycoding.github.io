// javac TestNative.java

//javah TestNative  (to generate header of the native method)
// java TestNative



public class TestNative
{
    public static native void greeting();
    public static void main(String[] args)
    {
	greeting();
	NativeTester.greeting(100, "NativeTester.greeting");
    }

    static 
    {
	System.loadLibrary("TestNative");
    }
}


class NativeTester
{
    public static native void greeting(int i, String str);
}
