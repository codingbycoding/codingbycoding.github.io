// javac GenericJava.java
// java GenericJava


import java.io.Serializable;

public class GenericJava
{
    public static void main(String[] args)
    {
	System.out.println("GenericJava...");
	Container<String> con = new Container<String>("Key");

	int[] i5 ={1, 2, 3, 4, 5};

	Integer[] I5 = new Integer[5];
	for(int i=0; i<I5.length; ++i)
	    {
		I5[i] = new Integer(i+100);
	    }

	System.out.println("getMax: " + TestCon.getMax(I5) ); 

	
	
	String[] strs = new String[3];

	//TODO:to understand null reason. -- local vars?
	// for(String s: strs)
	//     {
	// 	System.out.println("in for.");
	// 	s = new String("ABC");
	//     }

	for(int i=0; i<strs.length; ++i)
	    {
		
		strs[i] = new String("ABC");
	    }

	for(String s: strs)
	    {
		System.out.println("s: " + s);
	    }
	
	System.out.println("getMid: " + TestCon.getMid(strs) );
	// System.out.println("getMid: " + TestCon.<String>getMid(strs) );//<String>can ommit
	// System.out.println("" + TestCon.<int>getMid(i5) );

	
    }
}



class Container<T>
{
    public Container(T val)
	{
	    this.val = val;
	    
	}

    
    private T val;
}


class TestCon
{
    public TestCon()
    {
	
    }
    
    //Generic Method
    public static <T> T getMid(T[] ts)
    {
	if(ts == null || ts.length == 0)// ts.length == 0 means T[] ts = new T[0]
	    {
		return null;
	    }
	return ts[ts.length/2];
    }


    public static <T extends Comparable & Serializable> T getMax(T[] ts)
    {
    	if(ts.length == 0)
    	    {
    		return null;
    	    }
    	T retval = ts[0];
    	for(T t : ts)
    	    {
    		if(t.compareTo(retval) > 0 )
    		    {
    			retval = t;
    		    }

    	    }
    	return retval;
    }

    // void ProcessBase(<? extends BaseContainer> )
    // {
	
    // }
    
}


class BaseContainer<T>
{
    BaseContainer(T t)
    {
	id = t;
    }

    private T id;
}

// class ContainerInteger extends BaseContainer<Integer>
// {
//     ContainerInteger()
//     {
	
//     }
// }



// class ContainerString extends BaseContainer<String>
// {
//     ContainerString()
//     {
	
//     }
    
// }
