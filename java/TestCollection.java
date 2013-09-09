// javac TestCollection.java
// java TestCollection

import java.util.LinkedList;
import java.util.List;
import java.util.Vector; //not efficient on sigle thread but sync on multithreads
import java.util.ArrayList; //oppsite to Vector

import java.util.Set;
import java.util.HashSet;

import java.util.Comparator;
import java.util.SortedSet;
import java.util.TreeSet;

import java.util.Map;
import java.util.HashMap;

import com.wangyongjian.test.Employee;


import java.util.EnumSet;

public class TestCollection
{
    public static void main(String[] args)
    {
	System.out.println("TestCollection...");

	List<String> strL = new LinkedList<String>();
	strL.add("book");
	strL.add("Influnce");
	strL.add("Psychology");

	System.out.println(strL.toString());

	System.out.println(((LinkedList)strL).getLast());

	Set<String> strS = new HashSet<String>();
	strS.add("Fligt");
	strS.add("Pyrimid");
	strS.add("BigBang");
	//System.out.println(strS.toString());
	for(String s : strS)
	    {
		System.out.println(s);
	    }


	System.out.println("***************************");

	SortedSet<String> strSS = new TreeSet<String>();
	strSS.add("Fligt");
	strSS.add("Pyrimid");
	strSS.add("BigBang");
	//System.out.println(strS.toString());
	for(String ss : strSS)
	    {
		System.out.println(ss);
	    }


	EmployeeComparator eComp = new EmployeeComparator();
	SortedSet<Employee> empSS = new TreeSet<Employee>(eComp);
	Employee e1 = new Employee("Rose", 23);
	Employee e2 = new Employee("Jack", 21);
	Employee e3 = new Employee("Obama", 55);

	e1.setId(200);
	empSS.add(e3);
	empSS.add(e1);
	empSS.add(e2);
	// e1.setId(200);
	
	System.out.println("***************************");
	for(Employee e : empSS)
	    {
		System.out.println("id: " + e.getId());
	    }


	Map<Integer, Employee> empMap = new HashMap<Integer, Employee>();

	empMap.put(e1.getId(), e1);
	empMap.put(e2.getId(), e2);
	empMap.put(e3.getId(), e3);

	System.out.println("empMap.size() size: " + empMap.size());
	Employee ee = empMap.get(e1.getId());

	for(Map.Entry<Integer, Employee> entry : empMap.entrySet())
	    {
		System.out.println("id: " + entry.getKey() + " Name: " + entry.getValue().getName());
	    }



	EnumSet<Weekday> daysSet = EnumSet.allOf(Weekday.class);
	
    }
    
} 

enum Weekday {SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY};

class EmployeeComparator implements Comparator<Employee>
{
    public int compare(Employee e1, Employee e2)
    {
	return e1.getId() - e2.getId();
    }
}
