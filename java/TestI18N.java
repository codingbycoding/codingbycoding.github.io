// javac TestI18N.java
// java TestI18N

import java.util.Locale;
import java.text.NumberFormat;

public class TestI18N
{
    public static void main(String[] args)
    {

	Locale loc = Locale.getDefault();
	System.out.println(loc.toString());
	System.out.println(loc.getDisplayName());

	// Locale locDE = new Locale("de", "DE");
	Locale locDE = new Locale("zh", "CN");
	NumberFormat currencyFmt = NumberFormat.getCurrencyInstance(locDE);
	double currencyNum = 13343.66;
	String rtStr = currencyFmt.format(currencyNum);

	System.out.println("" + rtStr);
	
	
    }
    
}
