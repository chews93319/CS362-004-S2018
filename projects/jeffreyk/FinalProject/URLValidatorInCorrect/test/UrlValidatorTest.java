import junit.framework.TestCase;
import static org.junit.Assert.*;
import static org.junit.runners.Parameterized.*;
import org.junit.Test;
import java.util.Random;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {
	static String[] valid = {"http://www.google.com",
			"ftp://123.32.0.193",
			"https://john.doe@www.example.com:123/forum/questions/?tag=networking&order=newest#top"};
	static String[] invalid = {"http:///w.google",
			"://1.2.3.4.5:80",
			"http://255.com:-1/test1",
			"ftp://go.com:65a/../",
			":80/t23",
			"0.0.0.0/t123",
			"255.com/test1",
			"urn:oasis:names:specification:docbook:dtd:xml:4.1.2",
			"ldap://[2001:db8::7]/c=GB?objectClass?one",
			"mailto:John.Doe@example.com",
			"news:comp.infosystems.www.servers.unix",
			"tel:+1-816-555-1212",
			"telnet://192.0.2.16:80/",
			""};
	static String[] schemes = {"http://", "ftp:", "", "http/", "ftp", "://", "h3t"};
	static String[] authorities = {"www.go.com", "1.2.3.4.", "www.google.com", "", "193.36.128.43", "err", "john.doe@www.example.com"};
	static String[] ports = {":80", ":98765", "", ":aa", ":3000", ":-3", ":0"};
	static String[] paths = {"/test", "/..", "/path/file", "/../", "/file/", "//test//", ""};
	static String[] queries = {"?action=view","err","","","","?err","?action=edit&mode=up"};
	
   public UrlValidatorTest(String testName) {
      super(testName);
   }

   @Test
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, 0);
	   
	   for(int i = 0; i < valid.length; i++) {
		   assertEquals(String.format("Fail valid case:%s",valid[i]),true,urlVal.isValid(valid[i]));
	   }
	   
	   for(int i = 0; i < invalid.length; i++) {
		   assertEquals(String.format("Fail invalid case:%s",invalid[i]),false,urlVal.isValid(invalid[i]));
	   }
	   
   }
   
   public void testYourFirstPartition()
   {
	   /*
	    * In the context of testing valid URLs, the default is to only accept http, https, and ftp.
	    * This tests that protocols outside this valid boundary are returned as false.
	    */
	   
	   String[] invalidProtocols = {"mailto", "news", "telnet"};
	   String[] validProtocols = {"http", "https", "ftp"};
	   
	   UrlValidator urlVal = new UrlValidator(null, null, 0);
	   
	   for (int i = 0; i < invalidProtocols.length; i++) {
		   String invalidProtocolString = String.format("%s://foo.bar.com/resource", invalidProtocols[i]);
		   assertEquals(String.format(
				   "Failed invalid case: %s\n",invalidProtocolString),
				   false,
				   urlVal.isValid(invalidProtocolString));
	   }
   
	   for (int i = 0; i < validProtocols.length; i++) {
		   String validProtocolString = String.format("%s://foo.bar.com/resource", validProtocols[i]);
		   assertEquals(String.format(
				   "Failed valid case: %s\n",validProtocolString),
				   true,
				   urlVal.isValid(validProtocolString));
	   }	   
	   
   }
   
   public void testYourSecondPartition(){
	   
	   /*
	    * RFC 2396 defines acceptable URI schemes, of which URLs are a subset. A regular expression is used by
	    * UrlValidator to validate these schemes. This tests that invalid schemes outside of this boundary
	    * are returned as false.
	    */
   
	   String[] invalidSchemeURLs = {
			   "http//:foo.com",
			   "http?://foo.com",
			   "http://foo.com//invalidPath",
			   "*ttp://foo.com",
			   "http://@bar.com",
			   "//foo.com",
			   "http://foo.com/&query?fragment"			   
	   };
	   
	   String[] validSchemeURLs = {
			   "http://foo.com",
			   "http://foo.com/validPath",
			   "http://foo@bar.com",
			   "http://foo.com/query?fragment&other"
	   };
	    
	   UrlValidator urlVal = new UrlValidator(null, null, 0);
	   
	   for (int i = 0; i < invalidSchemeURLs.length; i++) {
		   assertEquals(String.format(
				   "Failed invalid case: %s\n",invalidSchemeURLs[i]),
				   false,
				   urlVal.isValid(invalidSchemeURLs[i]));		   
	   }
	   
	   for (int i = 0; i < validSchemeURLs.length; i++) {
		   assertEquals(String.format(
				   "Failed valid case: %s\n",validSchemeURLs[i]),
				   true,
				   urlVal.isValid(validSchemeURLs[i]));
	   }
   }
   
   public void testYourThirdPartition() {
	   
	   /*
	    * RFC 2396 defines reserved characters in the URI scheme; these characters must be encoded.
	    * This tests that invalid characters which are not encoded are returned as invalid.
	    */
	   
	   String[] invalidCharacters = { ";", "/", "?", ":", "@", "&", "=", "+", "$", "," };
	   
	   UrlValidator urlVal = new UrlValidator(null, null, 0);
	   
	   for (int i = 0; i < invalidCharacters.length; i++) {
		   String invalidCharacterURL = String.format("http://foo%s.com/resource", invalidCharacters[i]);
		   assertEquals(String.format(
				   "Failed invalid case: %s\n", invalidCharacterURL),
				   false,
				   urlVal.isValid(invalidCharacterURL));
	   }	   
   }
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing
	   UrlValidator urltest = new UrlValidator(null, null, 0);
	   String url;
	   for(int i = 0; i < schemes.length; i++) {
		   if(i % 2 == 0) {
			   System.out.println(schemes[i]);
			   assertTrue(urltest.isValidScheme(schemes[i]));
			   System.out.println(authorities[i]);
			   assertTrue(urltest.isValidAuthority(authorities[i]));
			   System.out.println(paths[i]);
			   assertTrue(urltest.isValidPath(paths[i]));
			   System.out.println(queries[i]);
			   assertTrue(urltest.isValidQuery(queries[i]));
		   }
		   else {
			   System.out.println(schemes[i]);
			   assertFalse(urltest.isValidScheme(schemes[i]));
			   System.out.println(authorities[i]);
			   assertFalse(urltest.isValidAuthority(authorities[i]));
			   System.out.println(paths[i]);
			   assertFalse(urltest.isValidPath(paths[i]));
			   System.out.println(queries[i]);
			   assertFalse(urltest.isValidQuery(queries[i]));
		   }
	   }
	   for(int j = 0; j < 20; j++) {
		   Random rand = new Random();
		   int r;
		   if(j % 2 == 0) {
			   r = rand.nextInt(valid.length);
			   System.out.println(valid[r]);
			   assertTrue(urltest.isValid(valid[r]));
		   }
		   else {
			   r = rand.nextInt(invalid.length);
			   System.out.println(invalid[r]);
			   assertFalse(urltest.isValid(invalid[r]));
		   }
	   }
   }
   
}
