package com.wangyongjian.test;

public class Employee
{
    public Employee()
    {
	this.name = "";
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

    public void PrintInfo()
    {
	System.out.println("Name: " + name + " age: " + age + " id: " + id + " salary: " + salary);
    }

    private String name = "";
    private int age = 0;
    private int id = 0;
    private double salary = 0;
    
    private static int nextId = 0;
}
