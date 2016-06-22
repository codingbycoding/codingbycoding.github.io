// javac TestHttp.java
// java TestHttp    
import java.net.URL;
import java.net.URLConnection;
import java.net.MalformedURLException;

import java.io.InputStream;
import java.util.Scanner;
import java.io.IOException;

import java.util.List;
import java.util.Map;

public class TestHttp
{
    
    public static void main(String[] args)
    {

	String urlStr = null;

	if(args.length != 0)
	    {
		urlStr = args[0];
	    }
	else
	    {
		urlStr = "http://www.baidu.com";
	    }

	System.out.println("url: " + urlStr);
		
	try
	    {
		URL url = new URL(urlStr);
		// InputStream inS = url.openStream();
		// Scanner scan = new Scanner(inS);
		// while(scan.hasNext())
		//     {
		// 	System.out.println(scan.next());
		//     }

		URLConnection urlConn = url.openConnection();
		urlConn.connect();
		System.out.println("ConnectionTimeout: " + urlConn.getConnectTimeout());
		System.out.println("ContentType: " + urlConn.getContentType());

		Map<String, List<String>> headerFields = urlConn.getHeaderFields();

		// for(Map<String, List<String>>.Entry entry : headerFields.entrySet() )
		for(Map.Entry<String, List<String>> entry : headerFields.entrySet() )
		    {
			System.out.println("key: " + entry.getKey() + "  value: " + entry.getValue());
		    }

	    }
	catch(MalformedURLException e)
	    {
		e.printStackTrace();
	    }
	catch(IOException e)
	    {
		e.printStackTrace();
	    }
	
	
    }
    
}
