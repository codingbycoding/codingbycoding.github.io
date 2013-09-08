//package com.wangyongjian.test;
//javac Welcome.java

//javac -g Welcome.java

//jdb Welcome.class
//stop Welcome.main
//run Welcome

//java Welcome
//java -classpath .  Welcome
//java -cp . Welcome
//java -cp . -enableassertions Welcome
//java -cp . -ea Welcome
//java -cp . -disableassertions Welcome
//java -cp . -da Welcome

//java -cp .  Welcome
//java -cp .  -verbose Welcome
//java -cp .  -Xlint Welcome
//jconsole


//jar -cvf Welcome.jar Welcome.class
//manifest.mf Main-Class: Welcome

//jar -uvf Welcome.jar Size.class
//jar -uvf Welcome.jar com/wangyongjian/test/Employ.class



import java.util.Date;
import java.lang.reflect.Array;
import java.io.Console;
//import java.util.*;


import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.lang.reflect.AccessibleObject;
import java.lang.reflect.InvocationTargetException;


import java.lang.NoSuchFieldException;
import java.lang.SecurityException;
import java.lang.IllegalAccessException;
import java.lang.IllegalArgumentException;
    
import com.wangyongjian.test.Employee;
import com.wangyongjian.test.Manager;
import com.wangyongjian.test.SubWelcome;


/**
   @author wangyongjian
   @date 2013-08-18
   <code>Welcome</code>is a test Class. 

 */   

enum Size
{
    SMALL, MEDIUM, LARGE, EXTRA_LARGE
}

public class Welcome
{

    // public static void main(String args[])
    public static double max(double... val)
    {
	double largest = Double.MIN_VALUE;
	for(double d : val)
	    {
		if(d > largest)
		    {
			largest = d;
		    }
	    }
	return largest;
    }
    
    public static void main(String[] args)	
    {
	String str = "Jack";
	System.out.println("Welcome Java\u2122 " + str);
 
	StringBuilder strBuild = new StringBuilder(); //more effecient in concat string or any type content use append() method exceed it's capacity will extend capacity automatically.
	StringBuffer strBuf = new StringBuffer();//not effecient as StringBuilder but safe at multithread env.

	
	Console con = System.console();
	if(null == con)
	    {
		System.out.println("No Console attached!");
	    }
	else
	    {
		con.readLine("Name:");
		con.readPassword("Password:");

	    }

	System.out.printf("Date(): %1$tc\n", new Date());

	BREAK_LABEL:
	while(true)
	    {
		System.out.println("outmost while:");
		
		while(true)
		    {
			while(true)
			    {
				System.out.println("inmost while");
				break BREAK_LABEL;
			    }
		    }
		
	    }

	int[] ia = {0,1,2,3};
	for(int i : ia)
	    {
		System.out.print(i + " ");
	    }
	System.out.println();


	int[] ianull = new int[0];// a array is different from null;

	SubWelcome sub = new SubWelcome();
	sub.print();

	Date today = sub.getToday();
	Date todayClone = sub.getToday_clone();	

	Employee worker1 = new Employee("Jack", 22);
	worker1.PrintInfo();

	Employee worker2 = new Employee("Tom", 24);
	worker2.PrintInfo();

	Manager manager = new Manager("VP Wang", 35);
	manager.PrintInfo();

	

	Employee[] staff = new Employee[3];

	staff[0] = manager;
	staff[1] = worker1;
	staff[2] = worker2;

	
	if(staff[0] instanceof Manager)
	    {
		Manager m = (Manager)staff[0];
		System.out.println("staff[0] is a Manager");
	    }

	System.out.println(manager.getClass().toString());
	System.out.println("max: " + max(10.0, 20.5, 2000));

	Size[] eS = Size.values();
	for(Size s: eS)
	    {
		System.out.println("Size toString: " + s.toString());
	    }

	Object obj = null;
	try
	    {
		// obj = Class.forName(worker1.getClass().getName());
		obj = Class.forName(worker1.getClass().getName()).newInstance();
		// obj = Class.forName(worker1.getClass().getName(newInstance()));
		
	    }
	catch( ClassNotFoundException e)
	    {
		System.out.println(e.toString());
	    }
	catch( Throwable t)
	    {
		System.out.println(t.toString());
	    }	
	finally
	    {
		System.out.println("finally");
	    }
	
	System.out.println("obj: " + obj.getClass().getName());

	Class clazz = obj.getClass();
	// Field[] fields = clazz.getFields();
	Field[] fields = clazz.getDeclaredFields();	
	System.out.println("Field[]: ");
	for(Field f : fields)
	    {
		System.out.println(f.toString());
	    }
	
	try
	    {
		AccessibleObject.setAccessible(fields, true);
	    }
	catch(IllegalArgumentException e)
	    {
		
	    }
	

	Field fname = null; 
	try
	    {
		//fname = clazz.getField("name");
		fname = clazz.getDeclaredField("name");		

	    }

	catch(NoSuchFieldException e)
	    {
		
	    }
	catch(SecurityException e)
	    {
		
	    }
	
	Field[] fnames = new Field[1];
	fnames[0] = fname; 

	try
	    {
		AccessibleObject.setAccessible(fnames, true);
	    }
	catch(IllegalArgumentException e)
	    {
		
	    }
	// catch(IllegalAccessException e)
	//     {
		
	//     }
	
	try
	    {
		fname.set(obj, "NewName");	
	    }
	catch(IllegalAccessException e)
	    {
		
	    }


	

	Method[] methods = clazz.getMethods();
	System.out.println("Method[]: ");	
	for(Method m : methods)
	    {
		System.out.println(m.toString());
	    }
	System.out.println("invoke:");
	try
	    {
		methods[0].invoke(obj);//, null);
	    }
	catch(IllegalAccessException e)
	    {
		
	    }
	catch(InvocationTargetException e)
	    {
		
	    }

	Constructor[] constructors  = clazz.getConstructors();
	System.out.println("Constructor[]: ");	
	for(Constructor c : constructors)
	    {
		System.out.println(c.toString());
	    }


	Employee[] employees = new Employee[10];
	employees[0] = new Employee();
	Class employeeComp = employees.getClass().getComponentType();

	Array.newInstance(employeeComp, 10);

	employees[0].TestInnerClass();

	
    }


    private final int id = 123456;
    
}

