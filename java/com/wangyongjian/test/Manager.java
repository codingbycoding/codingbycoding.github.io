package com.wangyongjian.test;

import com.wangyongjian.test.Employee;

public class Manager extends Employee
{
    public Manager(String name, int age)
    {
	super(name,age);
    }
    
    public void setBouns(double bouns)
    {
	this.bouns = bouns;
    }

    public double getBouns()
    {
	return bouns;
    }    
    
    public double getSalary()
    {
	double baseSalary = super.getSalary();
	return baseSalary + bouns;
    }
    
    private double bouns = 0;
}
