// javac TestNet.java
// java TestNet    

import java.net.Socket;
import java.net.UnknownHostException;

import java.io.InputStream;
import java.io.IOException;
import java.util.Scanner;

public class TestNet
{
    
    public static void main(String[] args)
    {

	for(String str : args)
	    {
		System.out.println("str: " + str);
	    }
	
	
	Socket soc; 
	try
	    {
		if(args.length == 0)
		    {
			soc = new Socket("time-A.timefreq.bldrdoc.gov", 13);
		    }
		else
		    {
			soc = new Socket(args[0], 80);
		    }
		
		soc.setSoTimeout(3000);
		
		try
		    {
			InputStream inStream = soc.getInputStream();
			Scanner scan = new Scanner(inStream);
			while(scan.hasNextLine())
			    {
				String line = scan.nextLine();
				System.out.println("line: " + line);
			    }
		    }
		finally
		    {
			soc.close();
		    }
		
		
	    }
	catch(UnknownHostException e)
	    {
		e.printStackTrace();
	    }
	catch(IOException e)
	    {
		e.printStackTrace();
	    }

	
    }
}
