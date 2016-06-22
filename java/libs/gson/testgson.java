//javac -cp /home/abc/Documents/google-gson-2.2.4/gson-2.2.4.jar:. testgson.java
//java -cp /home/abc/Documents/google-gson-2.2.4/gson-2.2.4.jar:. testgson


import com.google.gson.Gson;


public class testgson
{
    public static void main(String args[])
    {
	System.out.println("");

	House hou = new House("Songjiang, Shanghai", "LifeStyle", 180.0, 370.0);
	Gson gson = new Gson();
	String strHouse = gson.toJson(hou);
	System.out.println(strHouse);
	
    }
 
}


class House
{
    private String addr;
    private String style;
    private double area;
    private double cost;
	
    private House()
    {
	
    }

    public House(String addr, String style, double  area, double cost)
    {
	this.addr = addr;
	this.style = style;
	this.area = area;
	this.cost = cost;
    }

    
}
