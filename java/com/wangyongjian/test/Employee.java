package com.wangyongjian.test;

public class Employee
{


    class InnerClassOne
    {

	public InnerClassOne()
	{
	}
	
	public String toString()
	{
	    // return "OutClass is Class Employee and This is Class InnerClassOne" + "OutClass Fileds name: " + name;
	    return "OutClass is Class Employee and This is Class InnerClassOne" + "OutClass Fileds name: " + Employee.this.name;
	}
    }
    
    public Employee()
    {
	this.name = "uninit name";
	this.age = 0;
	this.id = ++nextId;
    }

    public  Employee(String name, int age)
    {
	this.name = name;
	this.age = age;
	this.id = ++nextId;
    }

    public  boolean setSalary(double salary)
    {
	this.salary = salary;
	return true;
    }

    public double getSalary()
    {
	return salary;
    }

    public int getId()
    {
	return id; 
    }

    public boolean setId(int id)
    {
	if(id < nextId )
	    {
		return false;
	    }
	
	this.id = id;
	nextId = id+1;
	return true;
    }

    public String getName()
    {
	return name; 
    }
    
    public void PrintInfo()
    {
	System.out.println("Name: " + name + " age: " + age + " id: " + id + " salary: " + salary);
    }

    public void TestInnerClass()
    {
	InnerClassOne one = new InnerClassOne();
	System.out.println(one.toString());

    }
    
    private String name = "";
    private int age = 0;
    private int id = 0;
    private double salary = 0;
    
    private static int nextId = 0;
}
