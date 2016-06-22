// javac TestXML.java
// java TestXML    


import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;

import javax.xml.parsers.ParserConfigurationException;
import org.xml.sax.SAXException;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;


import javax.xml.parsers.SAXParserFactory;
import javax.xml.parsers.SAXParser;
import org.xml.sax.AttributeList;
import org.xml.sax.HandlerBase;
import org.xml.sax.SAXException;



import java.io.File;
import java.io.IOException;

public class TestXML
{
    public static void main(String[] args)
    {

	DocumentBuilderFactory fac = DocumentBuilderFactory.newInstance();
	DocumentBuilder docBuilder;

	try
	    {
		docBuilder = fac.newDocumentBuilder();
		File f = new File("../xml/Test.xml");
		Document doc = docBuilder.parse(f);
		System.out.println("doc: " + doc.getNodeName());
		Element ele = doc.getDocumentElement();
		System.out.println("element: " + ele.getNodeName());
		NodeList nodes = ele.getChildNodes();
		for(int i=0; i<nodes.getLength(); i++)
		    {
			Node node = nodes.item(i);
			if(node instanceof Element)
			    {
				System.out.println("i: " + i + node.getNodeName());
			    }
		    }


		
		
	    }
	catch(ParserConfigurationException e)
	    {
		
	    }
	catch(SAXException e)
	    {
		
	    }
	catch(IOException e)
	    {
		
	    }
	finally
	    {
		
	    }
	


	SAXParserFactory saxFac = SAXParserFactory.newInstance();
	SAXParser saxP;

	try
	    {
		HandlerBase handler = new HandlerBase()
		    {
			public void startElement(String name, AttributeList attributes)
			{
			    // if(name.equals(""))
			    // 	{
			    // 	    System.out.println(name);
			    // 	}
			    System.out.println("name: " + name);
			}
			
		    };

		saxP = saxFac.newSAXParser(); 
		saxP.parse("../xml/Test.xml", handler);
	    }
	catch(ParserConfigurationException e)
	    {
		
	    }
	catch(SAXException e)
	    {
		System.out.println(e.toString());
	    }
	catch(IOException e)
	    {
		
	    }
	finally
	    {
		
	    }
	
    }  
}
