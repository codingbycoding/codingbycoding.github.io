package com.wangyongjian.test;

import java.util.Date;

public class SubWelcome
{
    public SubWelcome()
    {
	today = new Date();
    }

    public void print()
    {
	System.out.println("SubWelcome." + " Date: " + today);
    }

    public Date getToday()
    {
	return today;
    }

    public Date getToday_clone()
    {
	return (Date)today.clone();
    }



    public static void main(String[] args[])
    {
	
    }
    
    private Date today;

}
